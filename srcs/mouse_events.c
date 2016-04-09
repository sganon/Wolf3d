/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/09 18:06:56 by sganon            #+#    #+#             */
/*   Updated: 2016/04/09 18:17:11 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		mouse_angle(int x, int y, t_env *e)
{
	static int	first_x = WIN_X / 2;

	(void)y;
	if (x > first_x)
	{
		e->a_cam -= 150;
		first_x = x;
	}
	else if (x < first_x)
	{
		e->a_cam += 150;
		first_x = x;
	}
	e->a_cam = e->a_cam >= 36000 ? e->a_cam - 36000 : e->a_cam;
	e->a_cam = e->a_cam < 0 ? e->a_cam + 36000 : e->a_cam;
	expose_hook(e);
	return (1);
}
