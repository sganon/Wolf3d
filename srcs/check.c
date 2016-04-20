/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 17:40:53 by sganon            #+#    #+#             */
/*   Updated: 2016/04/20 16:29:56 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_error(char *s, int fd)
{
	ft_putstr_fd(ANSI_COLOR_RED, fd);
	ft_putendl_fd(s, fd);
	exit(EXIT_FAILURE);
}

void	check_border(t_env *e)
{
	int y;
	int	x;

	y = 0;
	x = -1;
	while (++x < e->map_x)
	{
		if (e->map[y][x] != 1)
			ft_error("Border error", 2);
	}
	while (++y < e->map_y - 1)
	{
		if (e->map[y][0] != 1 || e->map[y][e->map_x - 1] != 1)
			ft_error("Border error", 2);
	}
	x = -1;
	while (++x < e->map_x)
	{
		if (e->map[y][x] != 1)
			ft_error("Border error", 2);
	}
}

void	check_start_pos(t_env *e)
{
	int start_y;
	int	start_x;

	check_border(e);
	if (e->map_y <= 5 || e->map_x <= 5)
		ft_error("Map error: map is too small", 2);
	if (e->pos_cam.x >= e->map_x || e->pos_cam.y >= e->map_y ||
			e->pos_cam.x < 0 || e->map_y < 0)
		ft_error("Starting point is outside the map", 2);
	start_y = e->pos_cam.y - 1;
	while (start_y <= e->pos_cam.y + 1 && start_y <= e->map_y && start_y > 0)
	{
		start_x = e->pos_cam.x - 1;
		while (start_x <= e->pos_cam.x + 1 && start_x < e->map_x && start_x > 0)
		{
			if (e->map[start_y][start_x] != 0)
				ft_error("Starting point is (or is to close to) a wall", 2);
			start_x++;
		}
		start_y++;
	}
}

void	check_for_char(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] != '0' && tab[i][j] != '1' && tab[i][j] != '\n' 
					&& tab[i][j] != ' ')
				ft_error("Map error: not correctly formated", 2);
			j++;
		}
		i++;
	}
}
