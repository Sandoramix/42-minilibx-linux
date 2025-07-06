/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_screen_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:34:48 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/06 17:49:53 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_get_screen_size(t_xvar *mlx_ptr, int *sizex, int *sizey)
{
	XWindowAttributes	xw_attr;
	Status				ret;
	t_xvar				*xvar;

	xvar = mlx_ptr;
	ret = XGetWindowAttributes(xvar->display, xvar->root, &xw_attr);
	(*sizex) = xw_attr.width;
	(*sizey) = xw_attr.height;
}
