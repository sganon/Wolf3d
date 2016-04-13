/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:44:43 by sganon            #+#    #+#             */
/*   Updated: 2016/04/13 14:18:05 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_clean(t_env *e)
{
	int		p;

	p = -1;
	while (++p < WIN_X * 4 + WIN_Y * e->sl)
		e->img[p] = 0;
}

int		create_image(t_env *e)
{
	e->img_ptr = mlx_new_image(e->mlx, WIN_X, WIN_Y);
	e->img = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->sl), &(e->end));
	return (1);
}

int		expose_hook(t_env *e)
{
	int	mmx;
	int	mmy;

	mmx = WIN_X - e->map_x * 4;
	mmy = WIN_Y - e->map_y * 4;
	if (!e->img_ptr)
		create_image(e);
	cast(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0, 0);
	minimap(e);
	mlx_put_image_to_window(e->mlx, e->win, e->minimap.img_ptr, mmx, mmy);
	ft_clean(e);
	mlx_do_sync(e->mlx);
	return (1);
}

int		loop_hook(t_env *e)
{
	handle_fps_for_gif(e);
	expose_hook(e);
	return (1);
}

int		main(int argc, char **argv)
{
	t_env	*e;

	e = (t_env *)malloc(sizeof(t_env));
	if (argc == 2)
		read_that_file(argv[1], e);
	if (!(init_env(e)))
		return (0);
	mlx_hook(e->win, 2, (1L << 0), key_events, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
