/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_expose_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 10:47:03 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/06 17:20:24 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_expose_hook(t_win_list *win, int (*hook_function)(), void *param)
{
	win->hooks[Expose].hook = hook_function;
	win->hooks[Expose].param = param;
	win->hooks[Expose].mask = ExposureMask;
}
