/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:14:43 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/23 17:56:46 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		cpt;
	char	*flags;
	int		*w;

	i = 0;
	cpt = 0;
	va_start(ap, str);
	while (str[i] && cpt >= 0)
	{
		if (skip_chars(str, &i, &cpt) == 1)
		{
			flags = gestion_flags(str, &i);
			w = gestion_width(str, &i);
			w[0] = (w[0] == -1) ? (int)va_arg(ap, unsigned int) : w[0];
			(w[0] < 0) ? flags[ft_strlen(flags)] = '-' : 0;
			w[1] = (w[1] == -1) ? (int)va_arg(ap, unsigned int) : w[1];
			cpt += gestion_arg(str[i++], &ap, flags, w);
			free(flags);
			free(w);
		}
	}
	va_end(ap);
	return (cpt);
}
