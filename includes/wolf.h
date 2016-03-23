/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:46:28 by sganon            #+#    #+#             */
/*   Updated: 2016/03/23 13:51:28 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include 			"libft.h"
# include 			"../mlx/mlx.h"
# include 			<math.h>

# define WIN_X		420
# define WIN_Y		420

# define ESC		53

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;
typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	char			*img;
	int				map_y;
	int				map_x;
	char			**tab;
	int				**map;
	int				h_wall;
	int				h_cam;
	double			a_cam;
	double			a_start;
	double			a_end;
	int				fov;
	t_point			pos_cam;
}					t_env;

void				read_that_file(char *filename, t_env *env);
int					key_events(int key, t_env *e);
int					init_env(t_env *e);
#endif
