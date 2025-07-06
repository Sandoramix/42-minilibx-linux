/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mlx_rgb_convert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:50:50 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/06 09:51:54 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

/**
 * TrueColor Visual is needed to have *_mask correctly set
*/
static void	_mlx_rgb_convert(t_xvar *xvar, int decrdb_idx, int *color)
{
	while (!(*color & 1))
	{
		*color >>= 1;
		xvar->decrgb[decrdb_idx]++;
	}
	while (*color & 1)
	{
		*color >>= 1;
		xvar->decrgb[decrdb_idx + 1]++;
	}
}

int	_mlx_rgb_conversion(t_xvar *xvar)
{
	bzero(xvar->decrgb, sizeof(int) * 6);
	_mlx_rgb_convert(xvar, 0, &xvar->visual->red_mask);
	_mlx_rgb_convert(xvar, 2, &xvar->visual->green_mask);
	_mlx_rgb_convert(xvar, 4, &xvar->visual->blue_mask);
}
