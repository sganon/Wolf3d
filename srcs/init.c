/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 13:40:20 by sganon            #+#    #+#             */
/*   Updated: 2016/03/30 18:09:15 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
void			init_trigo(t_env *e)
{
	int			i;
	double		rad;

	i = 0;
	e->cos = (double *)malloc(sizeof(double) * 36000);
	e->sin = (double *)malloc(sizeof(double) * 36000);
	e->tan = (double *)malloc(sizeof(double) * 36000);
	while (i < 36000)
	{
		rad = (((double)i / (100.0)) * (2.0) * M_PI) / (360.0);
		(e->cos)[i] = cos(rad);
		(e->sin)[i] = sin(rad);
		(e->tan)[i] = tan(rad);
		i++;
	}
}

int		init_env(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return (0);
	e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "Wolf3D");
	e->img_ptr = NULL;
	e->h_wall = 64;
	e->h_cam = e->h_wall / 2;
	e->pos_cam.x = 8.0;
	e->pos_cam.y = 18.0;
	e->fov = 6000.0;
	e->a_cam = 9000;
	e->a_start = e->a_cam + (e->fov / 2);
	e->a_end = e->a_cam - (e->fov / 2);
	e->inter_ray = e->fov / WIN_X;
	init_trigo(e);
	e->screen_dist = (WIN_X / 2 ) / e->tan[(int)3000];
	return (1);
}
