/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:22:44 by bjones            #+#    #+#             */
/*   Updated: 2017/10/18 18:56:07 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	frame_timer(t_mlx *data)
{
	double	old_time;
	double	frame_time;
	char	*fps;

	old_time = data->timer.timer;
	data->timer.timer = clock();
	frame_time = (data->timer.timer - old_time) / CLOCKS_PER_SEC;
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, "FPS: ");
	fps = ft_itoa(floor(1.0 / frame_time));
	mlx_string_put(data->mlx, data->win, 50, 10, 0xFFFFFF, fps);
	ft_strdel(&fps);
	data->timer.move_speed = frame_time * 5.0;
	data->timer.rot_speed = frame_time * 3.0;
}

t_image	get_image(t_mlx *e, char *str)
{
	t_image	img;

	img.image = mlx_xpm_file_to_image(e->mlx, str, &img.width, &img.height);
	img.image_data = mlx_get_data_addr(img.image,
		&img.bpp, &img.size_line, &img.endian);
	return (img);
}

void	set_position(t_mlx *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			if (!data->map[y][x])
			{
				data->v.pos_x = y + 0.5;
				data->v.pos_y = x + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
	ft_putendl("unable to find starting location");
	exit(-1);
}

int		init_data(t_mlx *data, char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) <= 0)
		return (0);
	data->map_w = get_map_width(filename);
	data->map_h = fd_linecount(filename);
	data->map = init_world_map(data->map_w, data->map_h, fd);
	close(fd);
	set_position(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
		"wolf3d");
	data->tex[0] = get_image(data, "imgs/eagle.XPM");
	data->tex[1] = get_image(data, "imgs/redbrick.XPM");
	data->tex[2] = get_image(data, "imgs/purplestone.XPM");
	data->tex[3] = get_image(data, "imgs/greystone.XPM");
	data->tex[4] = get_image(data, "imgs/42.XPM");
	data->tex[5] = get_image(data, "imgs/mossy.XPM");
	data->tex[6] = get_image(data, "imgs/wood.XPM");
	data->tex[7] = get_image(data, "imgs/colorstone.XPM");
	data->v.dir_x = -1;
	data->v.dir_y = 0;
	data->v.plane_x = 0;
	data->v.plane_y = 0.66;
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx	data;
	char	*filename;

	if (argc != 2)
	{
		ft_putendl("usage: ./wolf3d [map file path]");
		exit(-1);
	}
	filename = argv[1];
	if (!init_data(&data, filename))
	{
		ft_putendl("usage: ./wolf3d [map file path]");
		exit(-1);
	}
	check_map_bounds(&data);
	mlx_hook(data.win, 2, 0, keydown_hooks, &data);
	mlx_hook(data.win, 3, 0, keyrelease_hooks, &data.keys);
	mlx_hook(data.win, 17, 0, exit_hook, &data);
	mlx_loop_hook(data.mlx, loop_hooks, &data);
	mlx_loop(data.mlx);
	return (0);
}
