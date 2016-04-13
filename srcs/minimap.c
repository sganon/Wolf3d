/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 17:27:08 by sganon            #+#    #+#             */
/*   Updated: 2016/04/13 14:02:51 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_in_mm(t_env *e, int x, int y, int color)
{
	int		p;
	t_color u;

	u.color = color;
	p = x * e->minimap.bpp / 8 + y * e->minimap.sl;
	e->minimap.img[p] = u.rgb.r;
	e->minimap.img[p + 1] = u.rgb.g;
	e->minimap.img[p + 2] = u.rgb.b;
	p = (x + 1) * e->minimap.bpp / 8 + y * e->minimap.sl;
	e->minimap.img[p] = u.rgb.r;
	e->minimap.img[p + 1] = u.rgb.g;
	e->minimap.img[p + 2] = u.rgb.b;
	p = x * e->minimap.bpp / 8 + (y - 1) * e->minimap.sl;
	e->minimap.img[p] = u.rgb.r;
	e->minimap.img[p + 1] = u.rgb.g;
	e->minimap.img[p + 2] = u.rgb.b;
	p = (x + 1) * e->minimap.bpp / 8 + (y - 1) * e->minimap.sl;
	e->minimap.img[p] = u.rgb.r;
	e->minimap.img[p + 1] = u.rgb.g;
	e->minimap.img[p + 2] = u.rgb.b;
}

void	discover_map(t_env *e)
{
	int			start_x;
	int			start_y;

	start_y = (int)e->pos_cam.y - 3;
	while (++start_y <= (int)e->pos_cam.y + 2)
	{
		start_x = (int)e->pos_cam.x - 3;
		while (++start_x <= e->pos_cam.x + 2)
		{
			if (start_y >= 0 && start_y < e->map_y && start_x >= 0
					&& start_x < e->map_x && e->map[start_y][start_x] == 0)
			{
				draw_in_mm(e, start_x * 4, start_y * 4, GREY);
			}
			else if (start_y >= 0 && start_y < e->map_y && start_x >= 0
					&& start_x < e->map_x && e->map[start_y][start_x] == 1)
			{
				draw_in_mm(e, start_x * 4, start_y * 4, L_BLUE);
			}
		}
	}
	draw_in_mm(e, (int)e->pos_cam.x * 4, (int)e->pos_cam.y * 4, YELLOW);
}

void	minimap(t_env *e)
{
	t_textures	*mm;

	mm = &e->minimap;
	if (mm->img_ptr == NULL)
	{
		mm->img_ptr = mlx_new_image(e->mlx, e->map_x * 4, e->map_y * 4);
		mm->img = mlx_get_data_addr(mm->img_ptr, &mm->bpp, &mm->sl, &mm->end);
	}
	discover_map(e);
}
