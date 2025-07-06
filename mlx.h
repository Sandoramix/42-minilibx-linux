/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:48:04 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/06 17:59:08 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

/*
** mlx.h for MinilibX in
**
** Made by Charlie Root
** Login   <ol@epitech.net>
**
** Started on  Mon Jul 31 16:37:50 2000 Charlie Root
** Last update Tue May 15 16:23:28 2007 Olivier Crouzet
*/

/*
**   MinilibX -  Please report bugs
*/


/*
** FR msg - FR msg - FR msg
**
** La MinilibX utilise 2 librairies supplementaires qu'il
**      est necessaire de rajouter a la compilation :
**   -lmlx -lXext -lX11
**
** La MinilibX permet le chargement des images de type Xpm.
** Notez que cette implementation est incomplete.
** Merci de communiquer tout probleme de chargement d'image
** de ce type.
*/

# include "mlx_int.h"
/* #include	<X11/xpm.h> */


/**
 * @brief Initializes the MinilibX library. Must be called before any other
 * MinilibX function.
 * @attention One of variables to look for in t_xvar is `do_flush`. If it is
 * set to 0, the library will not flush the screen after each drawing
 * operation. This could be useful if you want to use those functions without
 * losing performance, and call it once with do_flush set to 1 when needed.
 * @return A pointer to the MinilibX structure. NULL if failed.
 */
t_xvar				*mlx_init(void);


/*
** Basic actions
*/

/**
 * @brief Creates a new window on the screen.
 * @param xvar The current X variable.
 * @param size_x The width of the window.
 * @param size_y The height of the window.
 * @param title The title of the window.
 * @return A pointer to the new window. NULL if failed.
 */
t_win_list			*mlx_new_window(t_xvar *xvar,
						int size_x, int size_y, char *title);

/**
 * @brief Clears the window to black and flushes the changes to the screen.
 * @attention This function flushes the screen,
 * unless xvar->do_flush is set to 0.
 * @param mlx_ptr The current X variable.
 * @param win_ptr The current window.
 * @return 0 if failed, 1 if successful.
 */
int					mlx_clear_window(t_xvar *mlx_ptr, t_win_list *win_ptr);

/**
 * @brief Puts a pixel in the window at the given coordinates.
 * @attention This function flushes the screen,
 * unless xvar->do_flush is set to 0.
 * Also the origin (0,0) is top left corner of the window.
 * @param mlx_ptr The current X variable.
 * @param win_ptr The current window.
 * @param x The x coordinate of the pixel.
 * @param y The y coordinate of the pixel.
 * @param color The color of the pixel. Follows the pattern 0x00RRGGBB.
 * @return 0 if failed, 1 if successful.
 */
int					mlx_pixel_put(t_xvar *mlx_ptr, t_win_list *win_ptr,
						int x, int y, int color);

/*
** Image stuff
*/

void				*mlx_new_image(t_xvar *mlx_ptr, int width, int height);

/**
 * @brief
 * return NULL if failed
 * obsolete : image2 data is stored using bit planes
 * void	*mlx_new_image2(t_xvar *mlx_ptr,int width,int height);
 * @deprecated
 * Do not use this function. It just extracts all the variables from the
 * structure t_img. Access them directly instead.
 */
char		*mlx_get_data_addr(t_img *img, int *bits_per_pixel,
				int *size_line, int *endian);
/*
**  endian : 0 = sever X is little endian, 1 = big endian
**  for mlx_new_image2, 2nd arg of mlx_get_data_addr is number_of_planes
*/
int	mlx_put_image_to_window(t_xvar *mlx_ptr, t_win_list *win_ptr, void *img_ptr,
				int x, int y);
int	mlx_get_color_value(t_xvar *xvar, int color);


/*
** dealing with Events
*/

int	mlx_mouse_hook (t_win_list *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_key_hook (t_win_list *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_expose_hook (t_win_list *win_ptr, int (*funct_ptr)(), void *param);

int	mlx_loop_hook (t_xvar *mlx_ptr, int (*funct_ptr)(), void *param);
int	mlx_loop (t_xvar *mlx_ptr);
int mlx_loop_end (t_xvar *mlx_ptr);

/*
**  hook funct are called as follow :
**
**   expose_hook(void *param);
**   key_hook(int keycode, void *param);
**   mouse_hook(int button, int x,int y, void *param);
**   loop_hook(void *param);
**
*/


/*
**  Usually asked...
*/

int	mlx_string_put(t_xvar *mlx_ptr, t_win_list *win_ptr, int x, int y, int color,
		       char *string);
void	mlx_set_font(t_xvar *mlx_ptr, t_win_list *win_ptr, char *name);
void	*mlx_xpm_to_image(t_xvar *mlx_ptr, char **xpm_data,
			  int *width, int *height);
void	*mlx_xpm_file_to_image(t_xvar *mlx_ptr, char *filename,
			       int *width, int *height);
int	mlx_destroy_window(t_xvar *mlx_ptr, t_win_list *win_ptr);

int	mlx_destroy_image(t_xvar *mlx_ptr, t_img *img_ptr);

int	mlx_destroy_display(t_xvar *mlx_ptr);

/*
**  generic hook system for all events, and minilibX functions that
**    can be hooked. Some macro and defines from X11/X.h are needed here.
*/

int	mlx_hook(t_win_list *win, int x_event, int x_mask, int (*funct)(), void *param);

int	mlx_do_key_autorepeatoff(t_xvar *mlx_ptr);
int	mlx_do_key_autorepeaton(t_xvar *mlx_ptr);
int	mlx_do_sync(t_xvar *mlx_ptr);

int	mlx_mouse_get_pos(t_xvar *mlx_ptr, t_win_list *win_ptr, int *x, int *y);
int	mlx_mouse_move(t_xvar *mlx_ptr, t_win_list *win_ptr, int x, int y);
int	mlx_mouse_hide(t_xvar *mlx_ptr, t_win_list *win_ptr);
int	mlx_mouse_show(t_xvar *mlx_ptr, t_win_list *win_ptr);

int	mlx_get_screen_size(t_xvar *mlx_ptr, int *sizex, int *sizey);

#endif
