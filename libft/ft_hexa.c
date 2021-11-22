/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:05:29 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/20 15:55:56 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*recur_hexa(char *str, long n, int type)
{
	char	*hexa;
	char	reste[2];

	hexa = (type == 2) ? "0123456789ABCDEF" : "0123456789abcdef";
	reste[1] = '\0';
	if (n > 15)
		str = recur_hexa(str, n / 16, type);
	reste[0] = hexa[(unsigned char)(n % 16)];
	str = ft_strcat(str, reste);
	return (str);
}

char		*x(long n, int type)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * 14)))
		return (0);
	str[0] = 0;
	if (type == 3)
	{
		str[0] = '0';
		str[1] = 'x';
		str[2] = 0;
	}
	str = recur_hexa(str, n, type);
	return (str);
}
