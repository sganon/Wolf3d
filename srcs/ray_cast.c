/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 13:07:25 by sganon            #+#    #+#             */
/*   Updated: 2016/03/23 14:57:31 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double		get_disth(t_env *e, int x)
{
	
}

void		cast(t_env *e)
{
	int		x;
	double	disth;
	double	distv;

	x = -1;
	while (++x < WIN_X)
	{
		disth = get_disth(e);
		distv = get_distv(e);
	}
}
