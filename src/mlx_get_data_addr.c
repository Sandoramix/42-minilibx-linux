/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_data_addr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:25:08 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/06 17:42:24 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

char	*mlx_get_data_addr(t_img *img, int *bits_per_pixel,
						int *size_line, int *endian)
{
	*bits_per_pixel = img->bpp;
	*size_line = img->size_line;
	*endian = img->image->byte_order;
	return (img->data);
}
