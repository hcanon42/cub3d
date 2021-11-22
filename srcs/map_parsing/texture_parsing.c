/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:34:05 by hcanon            #+#    #+#             */
/*   Updated: 2019/12/04 21:16:21 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_north_texture(t_pack *pack, char *line, int i)
{
	char	*path;
	void	*ptr;
	int		garbage;

	if (pack->map.test[1] != 0)
		ft_error(1);
	path = line + i;
	if (open(path, O_RDONLY) == -1)
		ft_error(4);
	ptr = mlx_xpm_file_to_image(pack->mlx_ptr, path, &garbage, &garbage);
	if (!ptr)
		ft_error(4);
	pack->map.north_texture = mlx_get_data_addr(ptr, &garbage, &garbage,
								&garbage);
	free(ptr);
	pack->map.test[1] += 1;
}

void	ft_south_texture(t_pack *pack, char *line, int i)
{
	void	*ptr;
	int		garbage;

	if (pack->map.test[2] != 0)
		ft_error(1);
	if (open(line + i, O_RDONLY) == -1)
		ft_error(4);
	ptr = mlx_xpm_file_to_image(pack->mlx_ptr, line + i, &garbage, &garbage);
	if (!ptr)
		ft_error(4);
	pack->map.south_texture = mlx_get_data_addr(ptr, &garbage, &garbage,
								&garbage);
	free(ptr);
	pack->map.test[2] += 1;
}

void	ft_west_texture(t_pack *pack, char *line, int i)
{
	void	*ptr;
	int		garbage;

	if (pack->map.test[3] != 0)
		ft_error(1);
	if (open(line + i, O_RDONLY) == -1)
		ft_error(4);
	ptr = mlx_xpm_file_to_image(pack->mlx_ptr, line + i, &garbage, &garbage);
	if (!ptr)
		ft_error(4);
	pack->map.west_texture = mlx_get_data_addr(ptr, &garbage, &garbage,
								&garbage);
	free(ptr);
	pack->map.test[3] += 1;
}

void	ft_east_texture(t_pack *pack, char *line, int i)
{
	void	*ptr;
	int		garbage;

	if (pack->map.test[4] != 0)
		ft_error(1);
	if (open(line + i, O_RDONLY) == -1)
		ft_error(4);
	ptr = mlx_xpm_file_to_image(pack->mlx_ptr, line + i, &garbage, &garbage);
	if (!ptr)
		ft_error(4);
	pack->map.east_texture = mlx_get_data_addr(ptr, &garbage, &garbage,
								&garbage);
	free(ptr);
	pack->map.test[4] += 1;
}

void	ft_sprite_texture(t_pack *pack, char *line, int i)
{
	void	*ptr;
	int		garbage;

	if (pack->map.test[5] != 0)
		ft_error(1);
	if (open(line + i, O_RDONLY) == -1)
		ft_error(4);
	ptr = mlx_xpm_file_to_image(pack->mlx_ptr, line + i, &garbage, &garbage);
	if (!ptr)
		ft_error(4);
	pack->map.sprite_texture = mlx_get_data_addr(ptr, &garbage, &garbage,
								&garbage);
	free(ptr);
	pack->map.test[5] += 1;
}
