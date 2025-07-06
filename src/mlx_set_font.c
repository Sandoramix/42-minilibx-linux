/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_set_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 13:30:47 by amalliar          #+#    #+#             */
/*   Updated: 2025/07/06 17:37:06 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

/**
 * @brief Allows to specify the font that will be used by mlx_string_put.
 * Note: only fixed-width bitmap fonts are supported by Xlib, refer to xfontsel
 * utility to get valid font names for this function.
 * @param xvar The current X variable.
 * @param win The current window.
 * @param name The name of the font.
 */
void	mlx_set_font(t_xvar *xvar, t_win_list *win, char *name)
{
	static Font		font = 0;

	if (font)
		XUnloadFont(xvar->display, font);
	font = XLoadFont(xvar->display, name);
	XSetFont(xvar->display, win->gc, font);
}
