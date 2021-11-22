/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:09:50 by hcanon            #+#    #+#             */
/*   Updated: 2019/11/19 17:50:03 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_str(t_wall wall, char *str, t_map map, t_pack *pack)
{
	int		i;

	i = wall.x * 4;
	wall.y *= map.resol_x * 4;
	while (i < wall.y)
	{
		str[i++] = (char)map.c_color[2];
		str[i++] = (char)map.c_color[1];
		str[i++] = (char)map.c_color[0];
		i += map.resol_x * 4 - 3;
	}
	print_wall(wall, str + i, map, pack);
	i += wall.height * 4 * map.resol_x;
	wall.y = map.resol_x * map.resol_y * 4;
	while (i < wall.y && i > 0)
	{
		str[i++] = (char)map.f_color[2];
		str[i++] = (char)map.f_color[1];
		str[i++] = (char)map.f_color[0];
		i += map.resol_x * 4 - 3;
	}
}

int		pt_image(t_pack *pack)
{
	void		*ptr;
	char		*str;
	int			column;
	double		angle;

	ptr = mlx_new_image(pack->mlx_ptr, pack->map.resol_x, pack->map.resol_y);
	str = mlx_get_data_addr(ptr, &column, &column, &column);
	pack->str = str;
	angle = pack->charac.angle + FOV / 2;
	column = 0;
	while (angle > pack->charac.angle - FOV / 2 && column < pack->map.resol_x)
	{
		change_str(init_wall(pack->map, pack->plane, find_inter(pack,
			angle, column), column), str, pack->map, pack);
		angle -= pack->plane.angles;
		column++;
	}
	mlx_put_image_to_window(pack->mlx_ptr,
		pack->win_ptr, ptr, 0, 0);
	print_hud(pack);
	free(ptr);
	return (0);
}

void	ft_save(t_pack *pack)
{
	void		*ptr;
	char		*str;
	int			column;
	double		angle;

	ptr = mlx_new_image(pack->mlx_ptr, pack->map.resol_x, pack->map.resol_y);
	str = mlx_get_data_addr(ptr, &column, &column, &column);
	pack->str = str;
	angle = pack->charac.angle + FOV / 2;
	column = 0;
	while (angle > pack->charac.angle - FOV / 2 && column < pack->map.resol_x)
	{
		change_str(init_wall(pack->map, pack->plane, find_inter(pack,
			angle, column), column), str, pack->map, pack);
		angle -= pack->plane.angles;
		column++;
	}
	ft_export("./save/save.bmp", pack);
	free(ptr);
	ft_exit(pack);
}
