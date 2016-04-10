/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 17:27:08 by sganon            #+#    #+#             */
/*   Updated: 2016/04/10 18:59:45 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"



void	minimap(t_env *e)
{
	t_textures	*mm;
	int			p;

	mm = &e->minimap;
	if (mm->img_ptr == NULL)
	{
		mm->img_ptr = mlx_new_image(e->mlx,e->map_x * 4, e->map_y * 4);
		mm->img = mlx_get_data_addr(mm->img_ptr, &mm->bpp, &mm->sl, &mm->end);
	}
	p = (int)e->pos_cam.x * mm->bpp / 8 + (int)e->pos_cam.y * mm->sl;
   	mm->img[p] = 255;
	mm->img[p + 1] = 255;
	mm->img[p + 2] = 255;
	p = (int)(e->pos_cam.x + 1) * mm->bpp / 8 + (int)e->pos_cam.y * mm->sl;
   	mm->img[p] = 255;
	mm->img[p + 1] = 255;
	mm->img[p + 2] = 255;
	p = (int)(e->pos_cam.x + 1) * mm->bpp / 8 + (int)(e->pos_cam.y - 1) * mm->sl;
   	mm->img[p] = 255;
	mm->img[p + 1] = 255;
	mm->img[p + 2] = 255;
	p = (int)e->pos_cam.x * mm->bpp / 8 + (int)(e->pos_cam.y - 1) * mm->sl;
   	mm->img[p] = 255;
	mm->img[p + 1] = 255;
	mm->img[p + 2] = 255;
}
