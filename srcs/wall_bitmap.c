/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_bitmap2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 13:06:55 by sganon            #+#    #+#             */
/*   Updated: 2016/04/18 13:35:28 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		get_offset_x(t_env *e, double dist_x, double dist_y)
{
	if (dist_y >= dist_x)
	{
		e->hit.x = e->hit.x - (int)e->hit.x;
		e->offset_x = e->hit.x * e->wall.x;
	}
	else
	{
		e->hit.y = e->hit.y - (int)e->hit.y;
		e->offset_x = e->hit.y * e->wall.x;
	}
}

int			get_wall_color(t_env *e, double h, int y)
{
	t_color new;
	int		p;
	double	g;

	if (h < 20)
		return (0);
	g = WIN_Y / h / 2.0 > 1 ? WIN_Y / h / 2.0 : 1;
	e->offset_y = y * e->wall.y / h;
	p = e->offset_y * e->wall.sl + e->offset_x * e->wall.bpp / 8;
	new.rgb.r = (t_bytes)(e->wall.img[p]) / g;
	new.rgb.g = (t_bytes)(e->wall.img[p + 1]) / g;
	new.rgb.b = (t_bytes)(e->wall.img[p + 2]) / g;
	return (new.color);
}

void		draw_in_img(t_env *e, int y, int ray, int color)
{
	int		p;
	t_color	u;

	u.color = color;
	p = ray * e->bpp / 8 + y * e->sl;
	if (p < (WIN_X * (e->bpp / 8) + WIN_Y * e->sl) && p >= 0)
	{
		e->img[p] = u.rgb.r;
		e->img[p + 1] = u.rgb.g;
		e->img[p + 2] = u.rgb.b;
	}
}
