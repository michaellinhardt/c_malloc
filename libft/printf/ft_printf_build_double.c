/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_double.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 16:00:17 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/31 19:12:39 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double			pf_build_exp_solve(t_printf *pf, long double ld)
{
	char		*end;
	char		*tmp1;
	char		*tmp2;

	end = ft_strnew(100);
	end[0] = pf->in[pf->i];
	end[1] = '+';
	while ((ld < -9.9 || ld > 9.9) && ++pf->arg.diez)
		ld /= 10;
	while (ld > -1 && ld < 1 && (ld > 0 || ld < 0)
			&& ++pf->arg.diez && (end[1] = '-'))
		ld *= 10;
	if (pf->arg.diez < 10)
		end[2] = '0';
	tmp1 = ft_itoa(pf->arg.diez);
	tmp2 = ft_strjoin(end, tmp1);
	ft_strdel(&end);
	ft_strdel(&tmp1);
	tmp1 = ft_ldtoa(ld, pf->arg.preci);
	pf->join = ft_strjoin(tmp1, tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (ld);
}

long double			pf_build_float_get(t_printf *pf)
{
	long double	ld;

	ld = (pf->arg.length == L) ?
	(long double)va_arg(pf->ap, long double)
	: (long double)va_arg(pf->ap, double);
	if ((pf->in[pf->i] == 'g' || pf->in[pf->i] == 'G') && pf->arg.ispreci
		&& pf->arg.preci == 0)
		pf->arg.preci = 1;
	pf->arg.preci = (!pf->arg.ispreci) ? 6 : pf->arg.preci;
	pf->arg.diez = 0;
	pf->arg.zero = (pf->arg.less) ? 0 : pf->arg.zero;
	return (ld);
}

int					pf_build_exp(t_printf *pf)
{
	long double	ld;

	ld = pf_build_float_get(pf);
	ld = pf_build_exp_solve(pf, ld);
	pf->arg.diez = 0;
	if (ld < 0 && !(pf->arg.more = 0))
		pf->arg.space = 0;
	else if (pf->arg.more)
		pf->arg.space = 0;
	if (pf->arg.width > (int)ft_strlen(pf->join)
		&& (pf->arg.more || pf->arg.space))
		pf->arg.width--;
	pf->valid = 1;
	pf_build_format(pf);
	return (0);
}

int					pf_build_float(t_printf *pf)
{
	long double	ld;

	ld = pf_build_float_get(pf);
	pf->join = ft_ldtoa(ld, pf->arg.preci);
	if (ld < 0 && !(pf->arg.more = 0))
		pf->arg.space = 0;
	else if (pf->arg.more)
		pf->arg.space = 0;
	if (pf->arg.width > (int)ft_strlen(pf->join)
		&& (pf->arg.more || pf->arg.space))
		pf->arg.width--;
	pf->valid = 1;
	pf_build_format(pf);
	return (0);
}
