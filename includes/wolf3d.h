/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 18:37:16 by bjones            #+#    #+#             */
/*   Updated: 2017/10/18 18:44:16 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdlib.h>
# include <mlx.h>
# include <libft.h>
# include <get_next_line.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_SHIFT 257
# define KEY_ESC 53
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct	s_image
{
	void		*image;
	char		*image_data;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct	s_time
{
	double		timer;
	double		move_speed;
	double		rot_speed;
}				t_time;

typedef struct	s_vectors
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_vectors;

typedef struct	s_ray
{
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perp_wall_dist;
	int			side;
	int			step_x;
	int			step_y;
	double		sidedist_x;
	double		sidedist_y;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
}				t_ray;

typedef struct	s_keys
{
	int			a:1;
	int			s:1;
	int			d:1;
	int			w:1;
	int			left:1;
	int			right:1;
	int			down:1;
	int			up:1;
	int			shift:1;
}				t_keys;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			**map;
	int			map_w;
	int			map_h;
	t_vectors	v;
	t_keys		keys;
	t_time		timer;
	t_image		tex[8];
}				t_mlx;

/*
** MAIN
*/
void			frame_timer(t_mlx *data);

/*
** MAP READER
*/
int				**init_world_map(int width, int height, int fd);
int				fd_linecount(char *filename);
int				get_map_width(char *filename);

/*
** REDRAW
*/
void			redraw(t_mlx *data);

/*
**	REDRAW 2
*/
void			init_calc(t_mlx *data, t_ray *r, int x);
void			dist_calc(t_mlx *data, t_ray *r);
void			dda_calc(t_mlx *data, t_ray *r);
void			line_calc(t_mlx *data, t_ray *r);

/*
** LOOP HOOKS
*/
int				loop_hooks(t_mlx *e);

/*
** KEY HOOKS
*/
int				keydown_hooks(int keycode, t_mlx *data);
int				keyrelease_hooks(int keycode, t_keys *keys);
int				exit_hook(t_mlx *data);

/*
** ERRORS
*/
void			check_map_bounds(t_mlx *data);
void			map_err(void);

#endif
