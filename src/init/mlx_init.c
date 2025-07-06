/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:11:09 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/06 09:54:17 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	_mlx_rgb_conversion(t_xvar *xvar);

/**
 * pshm_format of -1 :	Not XYBitmap|XYPixmap|ZPixmap
 * alpha libX need a check of the DISPLAY env var, or shm is allowed
 * in remote Xserver connections.
*/
static int	_mlx_deal_shm(t_xvar *xvar)
{
	int		use_pshm;
	int		bidon;
	char	*dpy;
	char	buff[33];

	xvar->use_xshm = XShmQueryVersion(xvar->display, &bidon, &bidon, &use_pshm);
	if (xvar->use_xshm && use_pshm)
		xvar->pshm_format = XShmPixmapFormat(xvar->display);
	else
		xvar->pshm_format = -1;
	gethostname(buff, 32);
	dpy = getenv(ENV_DISPLAY);
	if (dpy && strlen(dpy) && *dpy != ':' && strncmp(dpy, buff, strlen(buff))
		&& strncmp(dpy, LOCALHOST, strlen(LOCALHOST)))
	{
		xvar->pshm_format = -1;
		xvar->use_xshm = 0;
	}
}

static int	_mlx_get_visual_info(t_xvar *xvar)
{
	XVisualInfo		*vi;
	XVisualInfo		template;
	int				nb_item;

	xvar->private_cmap = 0;
	xvar->visual = DefaultVisual(xvar->display, xvar->screen);
	if (xvar->visual->class == TrueColor)
		return (0);
	template.class = TrueColor;
	template.depth = xvar->depth;
	vi = XGetVisualInfo(xvar->display, VisualDepthMask | VisualClassMask,
			&template, &nb_item);
	if (!vi)
		return (-1);
	xvar->visual = vi->visual;
	xvar->private_cmap = 1;
	return (0);
}

static void	_mlx_init_defaults(t_xvar *xvar)
{
	xvar->screen = DefaultScreen(xvar->display);
	xvar->root = DefaultRootWindow(xvar->display);
	xvar->cmap = DefaultColormap(xvar->display, xvar->screen);
	xvar->depth = DefaultDepth(xvar->display, xvar->screen);
	if (_mlx_get_visual_info(xvar) == -1)
	{
		//TODO cleanup everything
		printf(ERR_NO_TRUECOLOR);
		exit(1);
	}
	xvar->do_flush = 1;
	xvar->wm_delete_window = XInternAtom(xvar->display,
			"WM_DELETE_WINDOW", False);
	xvar->wm_protocols = XInternAtom(xvar->display,
			"WM_PROTOCOLS", False);
}

t_xvar	*mlx_init(void)
{
	t_xvar	*xvar;

	xvar = calloc(1, sizeof(t_xvar));
	if (!xvar)
		return (NULL);
	xvar->display = XOpenDisplay("");
	if (xvar->display == 0)
		return (free(xvar), NULL);
	_mlx_init_defaults(xvar);
	_mlx_deal_shm(xvar);
	if (xvar->private_cmap)
		xvar->cmap = XCreateColormap(xvar->display, xvar->root,
				xvar->visual, AllocNone);
	_mlx_rgb_conversion(xvar);
	xvar->end_loop = 0;
	return (xvar);
}
