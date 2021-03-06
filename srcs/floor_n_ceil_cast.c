/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_n_ceil_cast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:06:38 by sganon            #+#    #+#             */
/*   Updated: 2016/04/21 13:38:15 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		get_floor_color(t_env *e, t_point pix, int y)
{
	t_color	col;
	int		p;
	double	g;

	g = ABS(y - WIN_Y / 2.0) / (WIN_Y / 2.0);
	pix.x *= e->floor.x;
	pix.y *= e->floor.y;
	pix.x = pix.x >= 0 ? pix.x : pix.x + e->floor.x;
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

void	floor_cast(t_env *e, int ray, int y, double b)
{
	double	wrng_d;
	double	true_d;
	t_point	pix;
	double	a;

	a = e->alpha - (double)ray / (WIN_X / 6000.0);
	a = a >= 36000.0 ? a - 36000.0 : a;
	a = a <= 0 ? a + 36000.0 : a;
	while (++y < WIN_Y)
	{
		wrng_d = (WIN_X2 / (y - WIN_Y2)) * (e->screen_dist / WIN_Y);
		true_d = b <= 36000 || b >= 0 ? wrng_d / e->cos[(int)b] : wrng_d;
		pix.x = (true_d * e->cos[(int)a]) + e->pos_cam.x;
		pix.y = (-true_d * e->sin[(int)a]) + e->pos_cam.y;
		pix.x = pix.x - (int)pix.x;
		pix.y = pix.y - (int)pix.y;
		draw_in_img(e, y, ray, get_floor_color(e, pix, y));
	}
}

int		get_ceil_color(t_env *e, t_point pix, int y)
{
	t_color	col;
	int		p;
	double	g;

	g = ABS(y - WIN_Y / 2.0) / (WIN_Y / 2.0);
	pix.x *= e->ceil.x;
	pix.y *= e->ceil.x;
	pix.x = pix.x >= 0 ? pix.x : pix.x + e->ceil.x;
	pix.y = pix.y >= 0 ? pix.y : pix.y + e->ceil.y;
	p = (int)pix.x * 4 + ((int)pix.y + e->gif * e->ceil.x) * e->ceil.sl;
	if (p < 0
			|| p >= e->CL(x) * 4 + (e->CL(x) + e->gif * e->CL(x)) * e->CL(sl))
		return (0);
	col.rgb.r = (t_bytes)e->ceil.img[p] * g;
	col.rgb.g = (t_bytes)e->ceil.img[p + 1] * g;
	col.rgb.b = (t_bytes)e->ceil.img[p + 2] * g;
	return (col.color);
}

void	ceil_cast(t_env *e, int ray, int y, double b)
{
	double	wrng_d;
	double	true_d;
	t_point	pix;
	double	a;

	a = e->alpha - (double)ray / (WIN_X / 6000.0);
	a = a >= 36000.0 ? a - 36000.0 : a;
	a = a < 0 ? a + 36000.0 : a;
	while (--y > 0)
	{
		wrng_d = (WIN_X2 / (y - WIN_Y2)) * (e->screen_dist / WIN_Y);
		true_d = b <= 36000 || b > 0 ? wrng_d / e->cos[(int)b] : wrng_d;
		pix.x = (true_d * e->cos[(int)a]) + e->pos_cam.x;
		pix.y = (-true_d * e->sin[(int)a]) + e->pos_cam.y;
		pix.x = pix.x - (int)pix.x;
		pix.y = pix.y - (int)pix.y;
		draw_in_img(e, y, ray, get_ceil_color(e, pix, y));
	}
}
