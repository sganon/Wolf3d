/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:44:43 by sganon            #+#    #+#             */
/*   Updated: 2016/03/22 14:00:08 by sganon           ###   ########.fr       */
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
	mlx_loop(e->mlx);
	return (0);
}
