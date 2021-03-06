/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:50:38 by sganon            #+#    #+#             */
/*   Updated: 2016/04/21 13:31:40 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		ft_cnt_parts(const char *s, char c)
{
	int		cnt;
	int		in_substring;

	in_substring = 0;
	cnt = 0;
	while (*s != '\0')
	{
		if (in_substring == 1 && *s == c)
			in_substring = 0;
		if (in_substring == 0 && *s != c)
		{
			in_substring = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int		get_max_x(char **tab, t_env *env)
{
	int i;
	int	x;
	int	max_x;

	i = 0;
	max_x = 0;
	while (tab[i])
	{
		x = ft_cnt_parts(tab[i], ' ');
		max_x = max_x < x ? x : max_x;
		i++;
	}
	env->map_x = max_x;
	return (0);
}

static int		get_map(char **tab, t_env *env)
{
	int		**map;
	char	**tmp;
	int		i;
	int		j;

	check_for_char(env->tab);
	get_max_x(env->tab, env);
	if (!(map = (int **)malloc(sizeof(int *) * env->map_y)))
		ft_error("Malloc error", 2);
	i = -1;
	while (tab[++i])
	{
		j = -1;
		if (!(map[i] = (int *)malloc(sizeof(int) * env->map_x)))
			ft_error("Malloc error", 2);
		tmp = ft_strsplit(tab[i], ' ');
		while (tmp[++j])
			map[i][j] = ft_atoi(tmp[j]);
		while (j++ < env->map_x)
			map[i][j] = 1;
	}
	env->map = map;
	return (0);
}

int				read_that_file(char *filename, t_env *env)
{
	int		fd;
	char	*str;
	char	*tmp;
	int		ret;
	char	*nl;

	nl = ft_strdup("\n");
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	tmp = ft_strnew(0);
	env->map_y = 0;
	while (42)
	{
		ret = get_next_line(fd, &str);
		if (ret != 1)
			break ;
		tmp = ft_strjoin(tmp, str);
		tmp = ft_strjoin(tmp, nl);
		env->map_y++;
	}
	if (ret == -1)
		return (0);
	env->tab = ft_strsplit(tmp, '\n');
	get_map(env->tab, env);
	return (1);
}
