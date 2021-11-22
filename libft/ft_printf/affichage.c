/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:32:22 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/23 18:01:46 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			test_2(char *final_str, char *str, char *flags, int *width)
{
	int		i;

	i = 0;
	if (in_str(flags, '0') && str[0] == '-')
		ft_putchar('-');
	while (i < final_str[i] && in_str(flags, '-'))
		ft_putchar(final_str[i++]);
	while (i++ < width[2] && in_str(flags, '-'))
		ft_putchar((in_str(flags, '0')) ? '0' : ' ');
	i = (in_str(flags, '0') && str[0] == '-') ? 1 : 0;
	if (in_str(flags, '-') == 0)
	{
		while (i++ < width[0] - ft_strlen(final_str))
			ft_putchar((in_str(flags, '0') && width[1] < ft_strlen(str)) ?
			'0' : ' ');
		i = 0;
		while (i < final_str[i])
			ft_putchar(final_str[i++]);
	}
	(!width[0] && width[1] == 0 && str[0] == '0') ? width[2]-- : 0;
	width[2] += (width[1] > ft_strlen(str) && str[0] == '-') ? 1 : 0;
	free(final_str);
	free(str);
	return (width[2]);
}

int			test(char *str, char *flags, int *width)
{
	char	*final_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	width[2] = (width[0] < width[1]) ? width[1] : width[0];
	(ft_strlen(str) > width[2]) ? width[2] = ft_strlen(str) : 0;
	if (!(final_str = (char *)malloc(sizeof(char) * (width[2] + 2))))
		return (0);
	(str[0] == '-' && in_str(flags, '0')) ? j++ : 0;
	if (str[0] == '-' && !in_str(flags, '0'))
	{
		final_str[++i] = str[j++];
		width[1] += (width[1] >= 0) ? 1 : 0;
	}
	if (width[1] > ft_strlen(str) - j)
		while (++i < width[1])
			final_str[i] = (i < width[1] - ft_strlen(str) + j) ? '0' : str[j++];
	else
		while (++i < ft_strlen(str))
			final_str[i] = str[j++];
	final_str[(width[1] == 0 && str[0] == '0') ? 0 : i] = '\0';
	return (test_2(final_str, str, flags, width));
}

char		*remplissage(char *str, char *flags, int *width, int c)
{
	char	*f_str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str) + ((c == 1 && !str[0]) ? 1 : 0);
	j = 0;
	i = (c == 1 && !str[0] && in_str(flags, '-')) ? 0 : -1;
	if (!(f_str = (char *)malloc(sizeof(char) * (width[2] + 1))))
		return (NULL);
	(c == 1 && !str[0] && in_str(flags, '-')) ? f_str[0] = 0 : 0;
	while (++i < width[2] + ((c == 1 && !str[0] && in_str(flags, '-')) ? 1 : 0))
	{
		if (in_str(flags, '-') == 1 && width[1] >= 0 && width[1] < len)
			f_str[i] = (str[j] && j < width[1]) ? str[j++] : ' ';
		else if (in_str(flags, '-') == 1)
			f_str[i] = (str[j]) ? str[j++] : ' ';
		else if (width[1] > width[0])
			f_str[i] = (i < width[0] - width[1] || !str[j]) ? ' ' : str[j++];
		else if (width[0] > width[1] && width[1] >= 0 && width[1] < len)
			f_str[i] = (i < width[0] - width[1]) ? ' ' : str[j++];
		else
			f_str[i] = (i < width[0] - ft_strlen(str)) ? ' ' : str[j++];
	}
	return (f_str);
}

int			print(char *str, char *flags, int *width, int c)
{
	int		i;
	char	*final_str;

	i = 0;
	width[2] = (width[0] < width[1]) ? width[1] : width[0];
	(str == NULL) ? ft_putstr("(null)") : 0;
	if (str == NULL)
		return (6);
	(c == 1 && !str[0]) ? width[0]-- : 0;
	(c == 2 && width[1] == 0) ? width[1]++ : 0;
	(ft_strlen(str) > width[2]) ? width[2] = ft_strlen(str) : 0;
	if (!(final_str = remplissage(str, flags, width, c)))
		return (-1);
	final_str[width[2]] = 0;
	if (width[0] && !(c == 1 && !str[0] && in_str(flags, '-')))
		final_str[(width[0] < ft_strlen(str)) ? ft_strlen(str) : width[0]] = 0;
	else if (!width[0] && width[1] >= 0)
		final_str[(width[1] < ft_strlen(str)) ? width[1] : ft_strlen(str)] = 0;
	(c == 1 && !str[0] && in_str(flags, '-')) ? ft_putchar(final_str[i++]) : 0;
	while (final_str[i] != 0)
		ft_putchar(final_str[i++]);
	(c == 1 && !str[0] && !in_str(flags, '-')) ? ft_putchar(final_str[i++]) : 0;
	free(final_str);
	return (i);
}
