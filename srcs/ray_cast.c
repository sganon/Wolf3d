/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 13:07:25 by sganon            #+#    #+#             */
/*   Updated: 2016/03/24 00:31:51 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

double		get_dist_x(t_env *e, int ray)
{
	t_point	x1;
	double	y_a;
	double	x_a;
	
	(void)ray;
	if (e->alpha >= 0 && e->alpha <= 180)
	{
	   x1.y = (e->pos_cam.y / 64) * 64 - 1;
	   y_a = -64;
	}
	else
	{
		x1.y = (e->pos_cam.y / 64) * 64 + 64;
		y_a = 64;
	}
	x1.x = e->pos_cam.x + (e->pos_cam.y - x1.y) / e->tan[(int)e->alpha * 100];
	x_a = 64 / e->tan[(int)e->alpha * 100];
	x1.x /= 64;
	x1.y /= 64;
	while (x1.x < e->map_x && x1.y < e->map_y && x1.y >= 0 && x1.x >= 0 
			&& e->map[(int)x1.y][(int)x1.x] == 0) 
	{
		x1.x = (x1.x + x_a) / 64;
		x1.y = (x1.y + y_a) / 64 ;
	}
	return (sqrt(SP(e->pos_cam.x - x1.x) + SP(e->pos_cam.y - x1.y)));
}

double		get_dist_y(t_env *e, int ray)
{
	t_point	y1;
	double	y_a;
	double	x_a;
	
	(void)ray;
	if (e->alpha >= e->a_cam)
	{
		y1.x = (e->pos_cam.x / 64) * 64 + 64;
		x_a = 64;
	}
	else
	{
		y1.x = (e->pos_cam.x / 64) * 64 - 1; 
		x_a = -64;
	}
	y1.y = e->pos_cam.y + (e->pos_cam.x - y1.x) * e->tan[(int)e->alpha * 100];
	y_a = e->tan[(int)e->alpha];
	y1.x /= 64;
	y1.y /= 64;
	while (y1.x < e->map_x && y1.y < e->map_y && y1.y >= 0 && y1.x >= 0 
			&& e->map[(int)y1.y][(int)y1.x] == 0) 
	{
		y1.x = (y1.x + x_a) / 64;
	   	y1.y = (y1.y + y_a) / 64;
	}
	return (sqrt(SP(e->pos_cam.x - y1.x) + SP(e->pos_cam.y - y1.y)));
}

void		draw_in_img(t_env *e, int y, int ray)
{
	int		p;
	t_color	u;

	u.color = 0xFF0000;
	p = ray * 4 + y * e->sl;
	if (p < (WIN_X * 4 + WIN_Y * e->sl) && p >= 0)
	{
		e->img[p] = u.rgb.b;
		e->img[p + 1] = u.rgb.g;
		e->img[p + 2] = u.rgb.r;
	}
}

void		draw_wall(t_env *e, double wrng_dist, int ray)
{
	double	true_dist;
	int		h_wall;
	int		y;
	
	if (e->alpha >= e->a_cam)
		true_dist = wrng_dist * e->cos[3000];
	else
		true_dist = wrng_dist * (e->cos[3000]);
	printf("true_dist = %f\n", true_dist);
	h_wall = (64 / true_dist) * 277;
	printf("h_wall = %d\n", h_wall);
	y = (WIN_Y / 2) + (h_wall / 2);
	printf("y = %d\n", y);
	while (y > (WIN_Y / 2) - (h_wall / 2))	
	{
		draw_in_img(e, y, ray);
		y--;
	}
}

void		cast(t_env *e)
{
	int		ray;
	double	dist_x;
	double	dist_y;
	double	wrng_dist;

	ray = 0;
	while (ray < WIN_X)
	{
		e->alpha = e->a_start - ray * e->inter_ray;
		printf("alpha = %f\n", e->alpha);
		e->alpha = e->alpha < 0 ? e->alpha + 3600 : (int)e->alpha % 3600;
		dist_x = get_dist_x(e, ray);
		dist_y = get_dist_y(e, ray);
		printf("dist_x = %f\n", dist_x);
		printf("dist_y = %f\n", dist_y);
		if (dist_x <= dist_y)
			wrng_dist = dist_x;
		else
			wrng_dist = dist_y;
		draw_wall(e, wrng_dist, ray);
		ray++;
	}
}
