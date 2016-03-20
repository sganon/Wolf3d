/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:44:43 by sganon            #+#    #+#             */
/*   Updated: 2016/03/20 17:10:27 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	print_map(t_env *e)
{
	int	y;
	int	x;

	y = 0;
	while(y < e->y)
	{
		x = 0;
		while (x < e->x)
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

	(void)argc;
	e = (t_env *)malloc(sizeof(t_env));
	read_that_file(argv[1], e);
	print_map(e);
	return (0);
}
