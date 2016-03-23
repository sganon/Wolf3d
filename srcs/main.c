/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:44:43 by sganon            #+#    #+#             */
/*   Updated: 2016/03/23 20:05:58 by sganon           ###   ########.fr       */
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

int		create_image(t_env *e)
{
		e->end = 0;
		e->bpp = 8;
		e->sl = WIN_X;
		e->img_ptr = mlx_new_image(e->mlx, WIN_X, WIN_Y);
		e->img = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->sl), &(e->end));
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
	mlx_key_hook(e->win, key_events, e);
	print_map(e);
	create_image(e);
	cast(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0 , 0);
	mlx_loop(e->mlx);
	return (0);
}
