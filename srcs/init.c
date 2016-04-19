/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 13:40:20 by sganon            #+#    #+#             */
/*   Updated: 2016/04/18 16:20:59 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	handle_fps_for_gif(t_env *e)
{
	clock_t	new_clock;

	new_clock = clock();
	e->fps = CLOCKS_PER_SEC / (new_clock - e->old_clock);
	e->old_clock = new_clock;
	e->speed = 8.0 / (double)e->fps;
	e->a_speed = 9000.0 / (double)e->fps;
	e->speed *= 0.75;
	e->frame++;
	if (e->frame > e->fps / 20)
	{
		e->gif++;
		e->frame = 0;
	}
	if (e->gif > 33)
		e->gif = 0;
}

int		init_trigo(t_env *e)
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
	e->screen_dist = (WIN_X / 2) / e->tan[(int)3000];
	return (1);
}

int		init_textures(t_env *e)
{
	t_textures	*wall;
	t_textures	*floor;
	t_textures	*ceil;

	wall = &e->wall;
	floor = &e->floor;
	ceil = &e->ceil;
	wall->img_ptr = mlx_xpm_file_to_image(e->mlx, WALL, &wall->x, &wall->y);
	floor->img_ptr = mlx_xpm_file_to_image(e->mlx, FLOOR, &floor->x, &floor->y);
	ceil->img_ptr = mlx_xpm_file_to_image(e->mlx, CEIL, &ceil->x, &ceil->y);
	if (!wall->img_ptr || !floor->img_ptr || !ceil->img_ptr)
		return (0);
	wall->img = MLX_DAT(wall->img_ptr, &wall->bpp, &wall->sl, &wall->end);
	floor->img = MLX_DAT(floor->img_ptr, &floor->bpp, &floor->sl, &floor->end);
	ceil->img = MLX_DAT(ceil->img_ptr, &ceil->bpp, &ceil->sl, &ceil->end);
	return (1);
}

int		init_env(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return (0);
	e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "Wolf3D");
	e->img_ptr = NULL;
	e->pos_cam.x = e->map_x / 2.0 + 3;
	e->pos_cam.y = e->map_y - 3.0;
	e->fov = 6000.0;
	e->a_cam = 9000;
	e->gif = 0;
	e->fps = 0;
	e->frame = 0;
	e->old_clock = clock();
	e->speed = 0.30;
	e->a_speed = 600;
	if (!init_trigo(e) || !init_textures(e))
		return (0);
	return (1);
}
