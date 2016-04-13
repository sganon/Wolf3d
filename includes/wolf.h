/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:46:28 by sganon            #+#    #+#             */
/*   Updated: 2016/04/13 13:48:08 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include 			"libft.h"
# include 			"../mlx/mlx.h"
# include 			<math.h>
# include			<time.h>

# define WIN_X		1920.0
# define WIN_Y		1080.0
# define WIN_X2		(WIN_X / 2.0)
# define WIN_Y2		(WIN_Y / 2.0)

# define ESC		53
# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124

# define RED		0xFF0000
# define YELLOW		0xFFFF00
# define BLUE		0x0000FF
# define GREEN		0x00FF00
# define WHITE		0xFFFFFF 
# define GREY		0x585858
# define L_BLUE		0x00ECFF

# define WALL		"textures/wall7.xpm"
# define FLOOR		"textures/floor3.xpm"
# define CEIL		"textures/ceil4.xpm"

# define ABS(x)		((x) < 0 ? -(x) : (x))
# define SP(x)		((x) * (x))
# define MLX_DAT(w, x, y, z)	mlx_get_data_addr(w, x, y, z)

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
	double			speed;
	double			a_speed;
	int				offset_x;
	int				offset_y;
	t_textures		wall;
	t_textures		floor;
	t_textures		ceil;
	t_textures		minimap;
	t_point			pos_cam;
	t_point			hit;
	clock_t			old_clock;
	int				gif;
	int				frame;
	int				fps;
}					t_env;

void				read_that_file(char *filename, t_env *env);
int					key_events(int key, t_env *e);
int					mouse_angle(int x, int y, t_env *e);
int					init_env(t_env *e);
int					expose_hook(t_env *e);
void				cast(t_env *e);
void				floor_cast(t_env *e, int ray, int y, double beta);
void				ceil_cast(t_env *e, int ray, int y, double beta);
void				draw_in_img(t_env *e, int y, int ray, int color);
void				minimap(t_env *e);
int					create_image(t_env *e);
int					handle_angle(int key, t_env *e);
void				handle_fps_for_gif(t_env *e);
void				get_offset_x(t_env *e, double dist_x, double dist_y);
int					get_wall_color(t_env *e, double h, int y);
#endif
