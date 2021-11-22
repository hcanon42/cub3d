/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 22:05:38 by hcanon            #+#    #+#             */
/*   Updated: 2019/11/18 04:52:25 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	starter(char *file, t_pack *pack)
{
	int		i;

	i = -1;
	pack->charac.angle = -1;
	pack->map.resol_x = -1;
	structs_malloc(&pack->map);
	pack->charac.x = 0;
	map_parsing(file, pack);
	big_mapping(&pack->map, &pack->charac);
	while (++i < pack->map.map_y)
		free(pack->map.map[i]);
	free(pack->map.map);
}

void	mlx_starter(t_pack *pack)
{
	pack->win_ptr = mlx_new_window(pack->mlx_ptr, pack->map.resol_x,
						pack->map.resol_y, "Cub3D");
	if (pack->win_ptr == NULL)
		ft_exit(pack);
}

void	ft_cub3d(t_pack *pack, int type)
{
	pack->nb_moves = 0;
	pack->plane.distance_char = (pack->map.resol_x / 2) /
						tan((FOV / 2) * M_PI / 180);
	pack->plane.angles = (double)FOV / (double)pack->map.resol_x;
	if (type == 1)
		ft_save(pack);
	mlx_starter(pack);
	pt_image(pack);
	mlx_expose_hook(pack->win_ptr, pt_image, (void *)pack);
	mlx_hook(pack->win_ptr, 33, 0, deal_end, (void *)pack);
	mlx_hook(pack->win_ptr, 2, (1L << 0),
			deal_key, (void *)pack);
	mlx_loop(pack->mlx_ptr);
}

void	ft_error_management(t_pack *pack)
{
	int		i;
	int		resol_x;
	int		resol_y;

	i = -1;
	mlx_get_screen_size(pack->mlx_ptr, &resol_x, &resol_y);
	if (pack->map.resol_x > resol_x)
		pack->map.resol_x = resol_x;
	if (pack->map.resol_y > resol_y)
		pack->map.resol_y = resol_y - 25;
	if (pack->charac.angle == -1 || pack->map.resol_x == -1)
		ft_error(5);
	if (pack->map.test[0] != 11)
		ft_error(1);
	while (++i < 3)
	{
		if (pack->map.f_color[i] > 255 || pack->map.f_color[i] < 0 ||
			pack->map.c_color[i] > 255 || pack->map.c_color[i] < 0)
			ft_error(6);
	}
}

int		main(int ac, char **av)
{
	t_pack		*pack;
	int			i;

	if (ac < 2 || ac > 3)
		ft_error(-1);
	if (ac > 2 && ft_strcmp(av[2], "--save") != 0)
		ft_error(-1);
	i = ft_strlen(av[1]) - 4;
	if (i < 0 || ft_strcmp(av[1] + i, ".cub") != 0)
		ft_error(-1);
	if (!(pack = (t_pack *)malloc(sizeof(t_pack) * 1)))
		ft_error(0);
	if (!(pack->mlx_ptr = mlx_init()))
		ft_error(0);
	starter(av[1], pack);
	ft_error_management(pack);
	ft_cub3d(pack, (ac > 2) ? 1 : 0);
	return (0);
}
