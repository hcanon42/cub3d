/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 23:29:15 by hcanon            #+#    #+#             */
/*   Updated: 2019/12/06 23:29:18 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->map_y * 64)
		free(map->big_map[i]);
	free(map->big_map);
	free(map->f_color);
	free(map->c_color);
	free(map->test);
}

void	ft_exit(t_pack *pack)
{
	free_map(&pack->map);
	free(pack->mlx_ptr);
	free(pack->win_ptr);
	free(pack);
	exit(0);
}

int		deal_end(void *param)
{
	t_pack	*pack;

	pack = (t_pack *)param;
	ft_exit(pack);
	return (0);
}

void	ft_end(t_pack *pack)
{
	char	*str;

	str = ft_itoa(pack->nb_moves);
	if (pack->map.resol_x > 100 && pack->map.resol_y > 200)
	{
		mlx_string_put(pack->mlx_ptr,
				pack->win_ptr, pack->map.resol_x / 2 - 50,
				pack->map.resol_y / 2, WHITE, "SCORE :");
		mlx_string_put(pack->mlx_ptr,
				pack->win_ptr, pack->map.resol_x / 2 + 30,
				pack->map.resol_y / 2, GREEN, str);
		mlx_string_put(pack->mlx_ptr,
				pack->win_ptr, pack->map.resol_x / 2 - 50,
				pack->map.resol_y / 2 + 25, RED, "PRESS ESC TO CLOSE");
	}
	pack->charac.hp = -100;
	free(str);
}
