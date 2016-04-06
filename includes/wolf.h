/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:46:28 by sganon            #+#    #+#             */
/*   Updated: 2016/04/06 18:28:24 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include 			"libft.h"
# include 			"../mlx/mlx.h"
# include 			<math.h>

# define WIN_X		1920.0
# define WIN_Y		1080.0

# define ESC		53
# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124

# define RED		0xFF0000
# define YELLOW		0xFFFF00
# define BLUE		0x0000FF
# define GREEN		0x00FF00

# define WALL		"textures/wall5.xpm"

# define ABS(x)		((x) < 0 ? -(x) : (x))
# define SP(x)		((x) * (x))

typedef unsigned char	t_bytes;

typedef struct			s_rgb
{
	t_bytes				r;
	t_bytes				g;
	t_bytes				b;
}						t_rgb;

typedef union			u_color
{
	size_t				color;
	t_rgb				rgb;
}						t_color;


typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_textures
{
	void			*img_ptr;
	char			*img;
	int				bpp;
	int				sl;
	int				end;
	int				x;
	int				y;
}					t_textures;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	char			*img;
	int				end;
	int				bpp;
	int				sl;
	int				map_y;
	int				map_x;
	char			**tab;
	int				**map;
	double			a_cam;
	double			fov;
	double			screen_dist;
	double			*cos;
	double			*sin;
	double			*tan;
	double			alpha;
	int				offset_x;
	int				offset_y;
	t_textures		wall;
	t_point			pos_cam;
	t_point			hit;
}					t_env;

void				read_that_file(char *filename, t_env *env);
int					key_events(int key, t_env *e);
int					init_env(t_env *e);
int					expose_hook(t_env *e);
void				cast(t_env *e);
int					create_image(t_env *e);
int					handle_angle(int key, t_env *e);
double				get_sin(double a);
double				get_tan(double a);
double				get_cos(double a);
#endif
