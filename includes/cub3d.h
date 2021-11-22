/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:11:51 by hcanon            #+#    #+#             */
/*   Updated: 2019/12/04 21:18:45 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FOV	60
# define WHITE	0xEEEEEE
# define RED	0xff0000
# define GREEN	0x00ff00

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibX/mlx.h"
# include "../includes/get_next_line.h"

typedef struct		s_map
{
	char			**big_map;
	char			**map;
	char			*north_texture;
	char			*south_texture;
	char			*east_texture;
	char			*west_texture;
	char			*sprite_texture;
	int				map_y;
	int				*f_color;
	int				*c_color;
	int				resol_x;
	int				resol_y;
	int				*test;
}					t_map;

typedef struct		s_charac
{
	int				x;
	int				y;
	int				angle;
	int				hp;
}					t_charac;

typedef struct		s_plane
{
	int				distance_char;
	double			angles;
}					t_plane;

typedef struct		s_pack
{
	t_map			map;
	t_charac		charac;
	t_plane			plane;
	void			*mlx_ptr;
	void			*win_ptr;
	char			*str;
	int				nb_moves;
}					t_pack;

typedef struct		s_point
{
	double			x;
	double			y;
	int				column;
	double			distance;
	char			texture;
	char			type;
}					t_point;

typedef struct		s_wall
{
	long long		height;
	int				x;
	int				y;
	char			texture;
	int				purcentage;
	double			heat;
	char			type;
}					t_wall;

void				ft_north_texture(t_pack *pack, char *line, int i);
void				ft_south_texture(t_pack *pack, char *line, int i);
void				ft_east_texture(t_pack *pack, char *line, int i);
void				ft_west_texture(t_pack *pack, char *line, int i);
void				ft_sprite_texture(t_pack *pack, char *line, int i);
int					line_test(char *line, t_pack *pack);
void				ft_error(int type);
void				check_map(t_map *map, int i, int j, int type);
int					map_parsing(char *file, t_pack *pack);
int					ft_export(char *path, t_pack *pack);
int					structs_malloc(t_map *map);
int					big_mapping(t_map *map, t_charac *charac);
t_point				find_inter(t_pack *pack, double angle, int column);
t_wall				init_wall(t_map map, t_plane plane, t_point inter,
					int column);
void				print_wall(t_wall wall, char *str, t_map map,
					t_pack *pack);
int					pt_image(t_pack *pack);
int					deal_key(int key, void *param);
int					deal_end(void *param);
void				free_map(t_map *map);
void				print_hud(t_pack *pack);
void				ft_exit(t_pack *pack);
void				ft_end(t_pack *pack);
void				ft_save(t_pack *pack);

#endif
