/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 17:37:50 by sganon            #+#    #+#             */
/*   Updated: 2016/03/30 16:33:09 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

//
#include <stdio.h>

void	handle_x_y_pos(int key, t_env *e)
{
	if (key == UP 
			&& e->map[(int)(e->pos_cam.y + 0.2)][(int)(e->pos_cam.x + 0.2)] == 0)
		e->pos_cam.y -= 1.0;
	else if (key == DOWN && e->map[(int)(e->pos_cam.y - 0.2)][(int)(e->pos_cam.x - 0.2)] == 0)
		e->pos_cam.y += 1.0;
	printf("cam_x : %f;\n", e->pos_cam.x);
	printf("cam_y : %f;\n", e->pos_cam.y);
	expose_hook(e);
}

void	handle_angle(int key, t_env *e)
{
	if (key == LEFT)
		e->a_cam -= 100;
	if (key == RIGHT)
		e->a_cam += 100;
	expose_hook(e);
}

int		key_events(int key, t_env *e)
{
	if (key == ESC)
		exit(0);
	else if (key == UP || key == DOWN)
		handle_x_y_pos(key, e);
	else if (key == LEFT || key == RIGHT)
		handle_angle(key, e);
	return (1);
}
