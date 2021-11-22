/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 19:16:52 by hcanon            #+#    #+#             */
/*   Updated: 2020/01/30 00:00:12 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_header(int fd, int resol_x, int resol_y)
{
	static unsigned char	header[54] = {66, 77, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0,
		0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24};
	unsigned int			*ptr;

	ptr = (unsigned int *)&header[2];
	*ptr = 54 + resol_x * resol_y * 3 + (resol_x % 4) * resol_x;
	ptr = (unsigned int *)&header[18];
	*ptr = resol_x;
	ptr = (unsigned int *)&header[22];
	*ptr = resol_y;
	ptr = (unsigned int *)&header[34];
	*ptr = resol_x * resol_y * 3 + (resol_x % 4) * resol_x;
	ptr = (unsigned int *)&header[38];
	*ptr = 3780;
	ptr = (unsigned int *)&header[42];
	*ptr = 3780;
	write(fd, header, 54);
}

int		ft_export(char *path, t_pack *pack)
{
	int				fd;
	int				i;
	unsigned char	*pixel;
	int				line;
	int				t;

	fd = open(path, O_TRUNC | O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR |
			S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH);
	init_header(fd, pack->map.resol_x, pack->map.resol_y);
	line = pack->map.resol_y;
	while (--line >= 0)
	{
		i = line * pack->map.resol_x * 4;
		t = 0;
		while (t < pack->map.resol_x)
		{
			pixel = (unsigned char*)&pack->str[i];
			write(fd, pixel, 3);
			i += 4;
			t++;
		}
		write(fd, pixel, pack->map.resol_x % 4);
	}
	close(fd);
	return (0);
}
