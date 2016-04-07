/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 13:39:25 by sganon            #+#    #+#             */
/*   Updated: 2016/04/07 16:18:51 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
//
//
//
#include <stdio.h>
int		get_floor_color(t_env *e, t_point pix, int y)
{
	t_color	col;
	int		p;
	double	g;

	g = ABS(y - WIN_Y / 2.0) / (WIN_Y / 2.0);
	pix.x *= e->floor.y;
	pix.y *= e->floor.y;
	pix.x = pix.x >= 0 ? pix.x : pix.x + e->floor.y;
	pix.y = pix.y >= 0 ? pix.y : pix.y + e->floor.y;
	p = (int)pix.x * e->floor.bpp / 8 + (int)pix.y * e->floor.sl;
	if (p >= 0)
	{
		col.rgb.r = (t_bytes)e->floor.img[p] * g;	
		col.rgb.g = (t_bytes)e->floor.img[p + 1] * g;	
		col.rgb.b = (t_bytes)e->floor.img[p + 2] * g;	
		return (col.color);
	}
	else
		return (0);
}

void	floor_cast(t_env *e, int ray, int y, double beta)
{
	double	wrng_dist;
	double	true_dist;
	t_point	pix;
	double	a;

	a = e->alpha - (double)ray / (WIN_X / 6000.0);
	a = a >= 36000.0 ? a - 36000.0 : a;
	a = a < 0 ? a + 36000.0 : a;
	while (++y < WIN_Y)
	{
		wrng_dist = ((WIN_X / 2.0) / (y - WIN_Y / 2.0)) * (e->screen_dist / WIN_Y);
		true_dist = beta <= 36000 || beta > 0 ? wrng_dist / e->cos[(int)beta] : wrng_dist;
		pix.x = (true_dist * e->cos[(int)a]) + e->pos_cam.x;
		pix.y = (-true_dist * e->sin[(int)a]) + e->pos_cam.y;
		pix.x = pix.x - (int)pix.x;
		pix.y = pix.y - (int)pix.y;
		draw_in_img(e, y, ray, get_floor_color(e, pix, y));
	}
}
