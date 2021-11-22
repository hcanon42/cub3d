/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managmnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:08:08 by hcanon            #+#    #+#             */
/*   Updated: 2020/06/10 10:13:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_map *map, int i, int j, int type)
{
	if (map->map[i][j] == '2' || map->map[i][j] == '0' || map->map[i][j] >= 'A')
	{
		if (i == 0 || j == 0)
			ft_error(5);
		if (type == 0)
		{
			if (map->map[i - 1][j - 1] == ' ' || map->map[i - 1][j] == ' ' ||
				map->map[i][j - 1] == ' ' || map->map[i - 1][j + 1] == ' ')
				ft_error(5);
		}
		else
		{
			if (i == map->map_y - 1 || j == ft_strlen(map->map[i]) - 1 ||
				map->map[i + 1][j - 1] == ' ' || map->map[i][j + 1] == ' ' ||
				map->map[i + 1][j] == ' ' || map->map[i + 1][j + 1] == ' ')
				ft_error(5);
		}
	}
}

void	ft_error(int type)
{
	ft_putstr("Error\n");
	if (type == -1)
		ft_putstr(" ==>> Error due to wrong input values.\n");
	if (type == 0)
		ft_putstr(" ==>> Error while allocating memory.\n");
	if (type == 1)
		ft_putstr(" ==>> Due to a wrong parameter in the .cub file.\n");
	if (type == 2)
		ft_putstr(" ==>> Error while opening the .cub file.\n");
	if (type == 3)
		ft_putstr(" ==>> Error due to wrong resolution values.\n");
	if (type == 4)
		ft_putstr(" ==>> Error due to wrong textures values.\n");
	if (type == 5)
		ft_putstr(" ==>> Error due to wrong map values.\n");
	if (type == 6)
		ft_putstr(" ==>> Error due to wrong color values.\n");
	if (type == 7)
		ft_putstr(" ==>> Error due to too little resolution values.\n");
	exit(0);
}
