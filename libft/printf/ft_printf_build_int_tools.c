/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_int_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 01:12:04 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/21 17:13:05 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	pf_build_get_int(t_printf *pf)
{
	intmax_t	nbr;

	if (pf->arg.length == hh)
		nbr = (char)va_arg(pf->ap, void *);
	else if (pf->arg.length == h)
		nbr = (short int)va_arg(pf->ap, void *);
	else if (pf->arg.length == l)
		nbr = (long int)va_arg(pf->ap, void *);
	else if (pf->arg.length == ll)
		nbr = (long long int)va_arg(pf->ap, void *);
	else if (pf->arg.length == j)
		nbr = (intmax_t)va_arg(pf->ap, void *);
	else if (pf->arg.length == z)
		nbr = (size_t)va_arg(pf->ap, void *);
	else
		nbr = (int)va_arg(pf->ap, void *);
	return (nbr);
}

uintmax_t	pf_build_get_uint(t_printf *pf)
{
	uintmax_t	nbr;

	if (pf->arg.length == hh)
		nbr = (unsigned char)va_arg(pf->ap, void *);
	else if (pf->arg.length == h)
		nbr = (unsigned short int)va_arg(pf->ap, void *);
	else if (pf->arg.length == l)
		nbr = (unsigned long int)va_arg(pf->ap, void *);
	else if (pf->arg.length == ll)
		nbr = (unsigned long long int)va_arg(pf->ap, void *);
	else if (pf->arg.length == j)
		nbr = (uintmax_t)va_arg(pf->ap, void *);
	else if (pf->arg.length == z)
		nbr = (size_t)va_arg(pf->ap, void *);
	else
		nbr = (unsigned int)va_arg(pf->ap, void *);
	return (nbr);
}

static void	pf_build_swapless(t_printf *pf)
{
	int		zero;
	int		i;

	zero = 0;
	i = -1;
	while (pf->join[++i])
	{
		if (pf->join[i] == '0' && !zero && (zero = 1))
			pf->join[i] = '-';
		else if (pf->join[i] == '-')
		{
			pf->join[i] = '0';
			break ;
		}
	}
}

void		pf_build_itoa(t_printf *pf)
{
	int		i;
	int		len;
	char	*tmp;

	if (pf->arg.preci && pf->arg.preci > (int)ft_strlen(pf->join))
	{
		if (!(tmp = ft_strnew(pf->arg.preci)))
		{
			pf->ret = 1;
			return ;
		}
		i = -1;
		pf->j = -1;
		len = (int)ft_strlen(pf->join);
		while (++i < pf->arg.preci)
			tmp[i] = ((pf->arg.preci - i) > len) ? '0' : pf->join[++pf->j];
		ft_strdel(&pf->join);
		pf->join = tmp;
	}
	pf_build_format(pf);
	if (pf->arg.swapless)
		pf_build_swapless(pf);
	pf->valid = 1;
}
