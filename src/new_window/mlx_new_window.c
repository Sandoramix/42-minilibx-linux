/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 10:03:19 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/06 10:27:29 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

/*
** We do not use White/BlackPixel macro, TrueColor Visual make sure
** 0 is black & -1 is white
**
** With mlx_int_wait_first_expose, no flush is needed.
*/

int	_mlx_wait_first_expose(t_xvar *xvar, Window win)
{
	XEvent	ev;

	ev = (XEvent){0};
	XWindowEvent(xvar->display,win,ExposureMask,&ev);
	XPutBackEvent(xvar->display,&ev);
}

int	_mlx_block_window_resize(t_xvar *xvar, Window win, int w, int h)
{
	XSizeHints	hints;
	long		toto;

	hints = (XSizeHints){0};
	XGetWMNormalHints(xvar->display, win, &hints, &toto);
	hints.width = w;
	hints.height = h;
	hints.min_width = w;
	hints.min_height = h;
	hints.max_width = w;
	hints.max_height = h;
	hints.flags = PPosition | PSize | PMinSize | PMaxSize;
	XSetWMNormalHints(xvar->display, win, &hints);
}


static void	_mlx_init_defaults(t_xvar *xvar,
	XSetWindowAttributes *xswa, XGCValues *xgcv)
{
	*xswa = (XSetWindowAttributes){0};
	xswa->border_pixel = -1;
	xswa->colormap = xvar->cmap;
	(void)"Mask for all events";
	xswa->event_mask = 0xFFFFFF;
	*xgcv = (XGCValues){0};
	xgcv->foreground = -1;
	xgcv->function = GXcopy;
	xgcv->plane_mask = AllPlanes;
}

t_win_list	*mlx_new_window(t_xvar *xvar, int size_x, int size_y, char *title)
{
	t_win_list				*new_win;
	XSetWindowAttributes	xswa;
	XGCValues				xgcv;

	_mlx_init_defaults(xvar, &xswa, &xgcv);
	new_win = calloc(1, sizeof(t_win_list));
	if (!new_win)
		return (NULL);
	new_win->window = XCreateWindow(xvar->display, xvar->root,
			0, 0, size_x, size_y,
			0, CopyFromParent, InputOutput, xvar->visual,
			CWEventMask | CWBackPixel | CWBorderPixel | CWColormap, &xswa);
	_mlx_block_window_resize(xvar, new_win->window, size_x, size_y);
	XStoreName(xvar->display, new_win->window, title);
	XSetWMProtocols(xvar->display, new_win->window,
		&(xvar->wm_delete_window), 1);
	new_win->gc = XCreateGC(xvar->display, new_win->window,
			GCFunction | GCPlaneMask | GCForeground, &xgcv);
	new_win->next = xvar->win_list;
	xvar->win_list = new_win;
	XMapRaised(xvar->display, new_win->window);
	_mlx_wait_first_expose(xvar, new_win->window);
	return (new_win);
}

/*
xswa.event_mask = ButtonPressMask | ButtonReleaseMask | ExposureMask |
	KeyPressMask | KeyReleaseMask | StructureNotifyMask;
xswa.event_mask = ExposureMask;

new_win->mouse_hook = mlx_int_do_nothing;
new_win->key_hook = mlx_int_do_nothing;
new_win->expose_hook = mlx_int_do_nothing;
*/