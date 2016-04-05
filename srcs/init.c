/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 13:40:20 by sganon            #+#    #+#             */
/*   Updated: 2016/04/05 14:27:13 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
int			init_trigo(t_env *e)
{
	int			i;
	double		rad;

	i = 0;
	e->cos = (double *)malloc(sizeof(double) * 36000);
	e->sin = (double *)malloc(sizeof(double) * 36000);
	e->tan = (double *)malloc(sizeof(double) * 36000);
	if (!e->cos || !e->sin || !e->tan)
		return (0);
	while (i < 36000)
	{
		rad = (((double)i / (100.0)) * (2.0) * M_PI) / (360.0);
		(e->cos)[i] = cos(rad);
		(e->sin)[i] = sin(rad);
		(e->tan)[i] = tan(rad);
		i++;
	}
	e->screen_dist = (WIN_X / 2 ) / e->tan[(int)3000];
	return (1);
}

int			init_textures(t_env *e)
{
	t_textures	*wall;

	wall = &e->wall;
	wall->img_ptr = mlx_xpm_file_to_image(e->mlx, WALL, &wall->x, &wall->y);
	if (wall->img_ptr == NULL)
		return (0);
	wall->img = mlx_get_data_addr(wall->img_ptr, &wall->bpp, &wall->sl, &wall->end);
	return (1);
}

int		init_env(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return (0);
	e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "Wolf3D");
	e->img_ptr = NULL;
	e->pos_cam.x = 8.0;
	e->pos_cam.y = 18.0;
	e->fov = 6000.0;
	e->a_cam = 9000;
	if (!init_trigo(e) || !init_textures(e))
		return (0);
	return (1);
}
