/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 17:37:50 by sganon            #+#    #+#             */
/*   Updated: 2016/03/31 17:45:00 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

//
#include <stdio.h>

void	handle_x_y_pos(int key, t_env *e)
{
	if (key == UP)
	{
		if (e->a_cam <= 4500 || e->a_cam > 31500)
			e->pos_cam.x += 1;
		else if (e->a_cam > 4500 && e->a_cam <= 13500)
			e->pos_cam.y -= 1;
		else if (e->a_cam > 13500 && e->a_cam <= 25500)
			e->pos_cam.x -= 1;
		else
			e->pos_cam.y += 1;
	}
	else if (key == DOWN)
	{
		if (e->a_cam <= 4500 || e->a_cam > 31500)
			e->pos_cam.x -= 1;
		else if (e->a_cam > 4500 && e->a_cam <= 13500)
			e->pos_cam.y += 1;
		else if (e->a_cam > 13500 && e->a_cam <= 25500)
			e->pos_cam.x += 1;
		else
			e->pos_cam.y -= 1;
	}
	expose_hook(e);
}

int		handle_angle(int key, t_env *e)
{
	if (key == LEFT)
		e->a_cam += 150;
	if (key == RIGHT)
		e->a_cam -= 150;
	e->a_cam = e->a_cam >= 36000 ? e->a_cam - 36000 : e->a_cam;
	e->a_cam = e->a_cam < 0 ? e->a_cam + 36000 : e->a_cam;
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
	return (1);
}
