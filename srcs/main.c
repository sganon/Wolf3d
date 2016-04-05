/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:44:43 by sganon            #+#    #+#             */
/*   Updated: 2016/04/05 17:59:59 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
	//	e->end = 0;
	//	e->bpp = 8;
	//	e->sl = WIN_X;
		e->img_ptr = mlx_new_image(e->mlx, WIN_X, WIN_Y);
		e->img = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->sl), &(e->end));
		return (1);
}

void	floor_cast(t_env *e)
{
	int		y;
	int		x;
	int		p;
	t_color	u;

	y = WIN_Y / 2;
	u.color = 0x808080;
	while (y < WIN_Y)
	{
		x = 0;
		while(x < WIN_X)
		{
			p = x * 4 + y * e->sl;
			if (e->img[p] == 0 && e->img[p + 1] == 0 && e->img[p + 2] == 0 && p < WIN_X * 4 + WIN_Y * e->sl)
			{
				e->img[p] = u.rgb.b;
				e->img[p + 1] = u.rgb.g;
				e->img[p + 2] = u.rgb.r;
			}
			x++;
		}
		y++;
	}
}

int		expose_hook(t_env *e)
{
	if (!e->img_ptr)
		create_image(e);
	cast(e);
	floor_cast(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0 , 0);
	mlx_put_image_to_window(e->mlx, e->win, e->wall.img_ptr, 0 , 0);
	ft_clean(e);
	mlx_do_sync(e->mlx);
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
	print_map(e);
	mlx_key_hook(e->win, key_events, e);
	mlx_hook(e->win, 2, (1L << 0), key_events, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
