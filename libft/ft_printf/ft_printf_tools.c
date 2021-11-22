/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:58:52 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/23 17:57:18 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		skip_chars(const char *str, int *i, int *cpt)
{
	while (str[*i])
	{
		if (str[*i] == '%')
			return (1);
		write(1, &str[*i], 1);
		(*i)++;
		(*cpt)++;
	}
	return (0);
}

char	*gestion_flags(const char *str, int *i)
{
	int		j;
	char	*flags;
	int		n;

	j = 0;
	n = 0;
	if (!(flags = (char *)malloc(sizeof(char) * ft_strlen(str))))
		return (NULL);
	(*i)++;
	while (str[*i] == '0' || str[*i] == '-')
		flags[j++] = str[(*i)++];
	flags[j] = 0;
	flags[++j] = 0;
	if (in_str(flags, '0') && in_str(flags, '-'))
		while (flags[++n])
			flags[n] == '0' ? flags[n] = '-' : 0;
	return (flags);
}

int		*gestion_width(const char *str, int *i)
{
	int		*width;

	if (!(width = (int *)malloc(sizeof(int) * 3)))
		return (NULL);
	width[0] = 0;
	width[1] = -2;
	while (str[*i] >= '0' && str[*i] <= '9')
		width[0] = width[0] * 10 + str[(*i)++] - 48;
	if (str[*i] == '*' && width[0] == 0)
		width[0] = -1;
	if (str[*i] == '*' && width[0] == -1)
		(*i)++;
	if (str[*i] == '.')
		width[1] = 0;
	if (str[*i] == '.')
		(*i)++;
	if (str[*i] == '*' && width[1] == 0)
	{
		(*i)++;
		width[1] = -1;
		return (width);
	}
	while (str[*i] >= '0' && str[*i] <= '9' && width[1] != -2)
		width[1] = width[1] * 10 + str[(*i)++] - 48;
	return (width);
}

int		gestion_arg(char c, va_list *ap, char *flags, int *width)
{
	char	str[2];

	(width[0] < 0) ? width[0] = -width[0] : 0;
	if (c == 'c')
	{
		str[0] = (unsigned char)va_arg(*ap, int);
		str[1] = 0;
		return (print(str, flags, width, 1));
	}
	else if (c == 's')
		return (print(va_arg(*ap, char *), flags, width, 0));
	else if (c == 'd' || c == 'i')
		return (test(ltoa((long)va_arg(*ap, int)), flags, width));
	else if (c == 'u')
		return (test(ltoa((long)va_arg(*ap, unsigned int)), flags, width));
	else if (c == 'x')
		return (test(x((long)va_arg(*ap, unsigned int), 1), flags, width));
	else if (c == 'X')
		return (test(x((long)va_arg(*ap, unsigned int), 2), flags, width));
	else if (c == 'p')
		return (test(x((long)va_arg(*ap, void *), 3), flags, width));
	else if (c == '%')
		return (print("%", flags, width, 2));
	else
		return (-1);
}
