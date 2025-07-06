/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mlx_normalize_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:23:12 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/06 18:00:17 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	_mlx_normalize_color(t_xvar *xvar, int color)
{
	XColor	xc;

	if (xvar->depth >= 24)
		return (color);
	xc.red = (color >> 8) & 0xFF00;
	xc.green = color & 0xFF00;
	xc.blue = (color << 8) & 0xFF00;
	xc.pixel = ((xc.red >> (16 - xvar->decrgb[1])) << xvar->decrgb[0])
		+ ((xc.green >> (16 - xvar->decrgb[3])) << xvar->decrgb[2])
		+ ((xc.blue >> (16 - xvar->decrgb[5])) << xvar->decrgb[4]);
	return (xc.pixel);
}
