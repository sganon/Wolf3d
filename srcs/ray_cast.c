/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 13:07:25 by sganon            #+#    #+#             */
/*   Updated: 2016/03/31 16:04:32 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

double		get_dist_x(t_env *e, int ray)
{
	t_point	fx;
	double	y_a;
	double	x_a;
	double	a;
	
	a = e->alpha - (double)ray / (WIN_X / 6000.0);
	a = a >= 36000.0 ? a - 36000.0 : a;
	a = a < 0 ? a + 36000.0 : a;
	fx.y = e->pos_cam.y;
	fx.y = a < 18000.0 ? fx.y - 0.00001 : fx.y + 1.0;
	y_a = a < 18000.0 ? -1.0 : 1.0;
	fx.x = e->pos_cam.x + (e->pos_cam.y - fx.y) / (double)e->tan[(int)a];
	x_a = -y_a / e->tan[(int)a];
	while (fx.x < e->map_x && fx.y < e->map_y && fx.y >= 0 && fx.x >= 0 
			&& e->map[(int)fx.y][(int)fx.x] != 1) 
	{
		fx.x = (fx.x + x_a);
		fx.y = (fx.y + y_a);
	}
	return (sqrt(SP(e->pos_cam.x - fx.x) + SP(e->pos_cam.y - fx.y)));
}

double		get_dist_y(t_env *e, int ray)
{
	t_point	fy;
	double	y_a;
	double	x_a;
	double	a;
	
	a = e->alpha - (double)ray / (WIN_X / 6000.0);
	a = a >= 36000.0 ? a - 36000.0 : a;
	a = a < 0 ? a + 36000.0 : a;
	fy.x = e->pos_cam.x;
	fy.x = a >= 9000 && a < 27000 ? fy.x - 0.00001 : fy.x + 1.0;
	x_a = a >= 9000 && a < 27000 ? -1.0 : 1.0;
	fy.y = e->pos_cam.y + (e->pos_cam.x - fy.x) * (double)e->tan[(int)a];
	y_a = -x_a * e->tan[(int)a];
	while (fy.x < e->map_x && fy.y < e->map_y && fy.y >= 0 && fy.x >= 0 
			&& e->map[(int)fy.y][(int)fy.x] != 1) 
	{
		fy.x = (fy.x + x_a);
	   	fy.y = (fy.y + y_a);
	}
	return (sqrt(SP(e->pos_cam.x - fy.x) + SP(e->pos_cam.y - fy.y)));
}

void		draw_in_img(t_env *e, int y, int ray, int color)
{
	int		p;
	t_color	u;

	u.color = color;
	p = ray * 4 + y * e->sl;
	if (p < (WIN_X * 4 + WIN_Y * e->sl) && p >= 0)
	{
		e->img[p] = u.rgb.b;
		e->img[p + 1] = u.rgb.g;
		e->img[p + 2] = u.rgb.r;
	}
}

void		draw_wall(t_env *e, double dist, int ray, int color)
{
	int		y;
	double	i;
	double	beta;

	beta = ray < WIN_X / 2 ? 0.0 - ((6000.0 / WIN_X) * ((double)ray - (WIN_X / 2.0))) 
		: 36000.0 - ((6000.0 / WIN_X) * ((double)ray - (WIN_X / 2.0)));
	if (beta < 36000 && beta >= 0)
		dist = dist * e->cos[(int)beta];
	dist = 1.0 / dist * e->screen_dist;
	i = WIN_Y / 2.0 - dist / 2.0;
	y = i < 0 ? -i : 0;
	while (y + i < WIN_Y - i)
	{
		draw_in_img(e, y + i, ray, color);
		y++;
		if (y + i > WIN_Y)
			return ;
	}
}

void		cast(t_env *e)
{
	int		ray;
	double	dist_x;
	double	dist_y;
	double	a;

	ray = 0;
	e->alpha = e->a_cam + 3000.0;
	while (ray < WIN_X)
	{
		dist_x = get_dist_x(e, ray);
		dist_y = get_dist_y(e, ray);
		a = e->alpha - (double)ray / (WIN_X / 6000.0);
		a = a >= 36000.0 ? a - 36000.0 : a;
		a = a < 0 ? a + 36000.0 : a;
		if (dist_y >= dist_x && a > 18000)
			draw_wall(e, dist_x, ray, RED);
		else if (dist_y >= dist_x && a <= 18000)
			draw_wall(e, dist_x, ray, YELLOW);
		else if (a >= 9000 && a < 27000)
			draw_wall(e, dist_y, ray, BLUE);
		else
			draw_wall(e, dist_y, ray, GREEN);
		ray++;
	}
}
