/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimaxtoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 00:01:24 by mlinhard          #+#    #+#             */
/*   Updated: 2016/02/14 03:25:01 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_base_len(uintmax_t n, size_t lb)
{
	size_t	l;

	l = (n <= 0);
	while (n != 0)
	{
		n /= lb;
		l++;
	}
	return (l);
}

static void		ft_itoa_base_fill1(uintmax_t bn, char *s
				, const char *b, size_t lb)
{
	if (bn == 0)
		*s = *b;
	while (bn != 0)
	{
		*s-- = *(b + ((uintmax_t)bn % lb));
		bn /= lb;
	}
}

char			*ft_uimaxtoa_base(uintmax_t n, const char *b)
{
	char		*s;
	size_t		l;
	uintmax_t	bn;
	size_t		lb;

	bn = n;
	lb = ft_strlen(b);
	l = ft_itoa_base_len(bn, lb);
	if (!(s = ft_strnew(l)))
		return (NULL);
	ft_itoa_base_fill1(bn, s + l - 1, b, lb);
	return (s);
}
