/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:46:28 by sganon            #+#    #+#             */
/*   Updated: 2016/03/20 17:41:02 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include 			"libft.h"
# include 			"../mlx/mlx.h"
# include 			<math.h>
# include			"get_next_line.h"

# define WIN_X		900
# define WIN_Y		900

# define ESC		53

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	char			*img;
	int				y;
	int				x;
	char			**tab;
	int				**map;
}					t_env;

void				read_that_file(char *filename, t_env *env);
int					key_events(int key, t_env *e);
#endif
