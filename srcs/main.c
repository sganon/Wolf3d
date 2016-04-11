/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:44:43 by sganon            #+#    #+#             */
/*   Updated: 2016/04/11 19:01:45 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
//
//
#include <stdio.h>

void	print_map(t_env *e)
{
	int	y;
	int	x;

	y = 0;
	while(y < e->map_y)
	{
		x = 0;
		while (x < e->map_x)
		{
			ft_putnbr(e->map[y][x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
	y++;
	}
}

void	ft_clean(t_env *e)
{
	int		p;

	p = -1;
	while (++p < WIN_X * 4 + WIN_Y * e->sl)
		e->img[p] = 0;
}

int		create_image(t_env *e)
{
		e->end = 0;
		e->bpp = 8;
		e->sl = WIN_X;
		e->img_ptr = mlx_new_image(e->mlx, WIN_X, WIN_Y);
		e->img = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->sl), &(e->end));
		return (1);
}

void	handle_fps_for_gif(t_env *e)
{
	clock_t	new_clock;

	new_clock = clock();
	e->fps = CLOCKS_PER_SEC / (new_clock - e->old_clock);
	e->old_clock = new_clock;
	e->speed = 8.0 / e->fps;
	e->a_speed = 3000.0 / e->fps;
	e->a_speed *= 0.75;
	e->frame++;
	if (e->frame > e->fps / 15)
	{
		e->gif++;
		e->frame = 0;
	}
	if (e->gif > 34)
		e->gif = 0;
}

int		expose_hook(t_env *e)
{
	if (!e->img_ptr)
		create_image(e);
	cast(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0 , 0);
	minimap(e);
	mlx_put_image_to_window(e->mlx, e->win, e->minimap.img_ptr, WIN_X - (e->map_x * 4), WIN_Y - (e->map_y * 4));
	//mlx_put_image_to_window(e->mlx, e->win, e->floor.img_ptr, 0 , 0);
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
//	mlx_hook(e->win, 6, (1L << 6), mouse_angle, e);
	//mlx_expose_hook(e->mlx, expose_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
