/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 13:40:20 by sganon            #+#    #+#             */
/*   Updated: 2016/03/23 13:39:31 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		init_env(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return (0);
	e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "Wolf3D");
	e->h_wall = 64;
	e->h_cam = e->h_wall / 2;
	e->pos_cam.x = 10;
	e->pos_cam.y = 10;
	e->fov = 60;
	e->a_cam = 90;
	e->a_start = e->a_cam - e->fov / 2;
	e->a_end = e->a_cam + e->fov / 2;
	return (1);
}
