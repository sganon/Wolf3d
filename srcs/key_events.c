/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 17:37:50 by sganon            #+#    #+#             */
/*   Updated: 2016/04/13 19:37:12 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	handle_x_y_pos(int key, t_env *e)
{
	double	d_x;
	double	d_y;

	d_x = e->cos[(int)e->a_cam] * e->speed;
	d_y = e->sin[(int)e->a_cam] * e->speed;
	if (key == UP
			&& !e->map[(int)(e->pos_cam.y - d_y)][(int)(e->pos_cam.x + d_x)])
	{
		e->pos_cam.x += d_x;
		e->pos_cam.y -= d_y;
	}
	else if (key == DOWN
			&& !e->map[(int)(e->pos_cam.y + d_y)][(int)(e->pos_cam.x - d_x)])
	{
		e->pos_cam.x -= d_x;
		e->pos_cam.y += d_y;
	}
	handle_fps_for_gif(e);
	expose_hook(e);
}

int		handle_angle(int key, t_env *e)
{
	if (key == LEFT)
		e->a_cam += e->a_speed;
	if (key == RIGHT)
		e->a_cam -= e->a_speed;
	e->a_cam = e->a_cam >= 36000 ? e->a_cam - 36000 : e->a_cam;
	e->a_cam = e->a_cam < 0 ? e->a_cam + 36000 : e->a_cam;
	handle_fps_for_gif(e);
	expose_hook(e);
	return (1);
}

int		key_events(int key, t_env *e)
{
	if (key == ESC)
		exit(0);
	else if (key == UP || key == DOWN)
		handle_x_y_pos(key, e);
	else if (key == LEFT || key == RIGHT)
		handle_angle(key, e);
	else if (key == LEFT || key == RIGHT || key == UP || key == DOWN)
	{
		handle_x_y_pos(key, e);
		handle_angle(key, e);
	}
	return (1);
}
