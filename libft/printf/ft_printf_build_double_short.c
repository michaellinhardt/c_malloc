/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_double_short.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 22:29:28 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/31 19:08:30 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*pf_build_float_g_normal2(t_printf *pf, long double ld)
{
	char	*verif;
	int		i;
	int		stop;

	stop = 0;
	while (!stop)
	{
		verif = ft_ldtoa(ld, pf->arg.preci);
		i = -1;
		while (verif[++i])
		{
			if (verif[i] != '0' && verif[i] != '.' && verif[i] != '-'
			&& (++stop || 1))
				break ;
			if (verif[i] == '0' && i > 0)
				pf->arg.preci++;
		}
		ft_strdel(&verif);
		if (ld == 0)
			stop = 1;
	}
	return (ft_ldtoa(ld, pf->arg.preci));
}

static int			pf_build_float_g_normal1(t_printf *pf, long double ld)
{
	int		i;

	pf->join = pf_build_float_g_normal2(pf, ld);
	if (ft_strchr(pf->join, '.') && ((i = (int)ft_strlen(pf->join)) || 1))
	{
		while (--i > -1 && pf->join[i] == '0')
			pf->join[i] = '\0';
		pf->join[i] = (pf->join[i] == '.') ? '\0' : pf->join[i];
	}
	if (pf->join[0] == '0' && ft_strlen(pf->join) > 6)
		return (0);
	if (ld < 0 && !(pf->arg.more = 0))
		pf->arg.space = 0;
	else if (pf->arg.more)
		pf->arg.space = 0;
	if (pf->arg.width > (int)ft_strlen(pf->join)
		&& (pf->arg.more || pf->arg.space))
		pf->arg.width--;
	pf->arg.diez = 0;
	pf->valid = 1;
	pf_build_format(pf);
	return (1);
}

static char			*pf_build_float_g_exp_round(t_printf *pf, long double ld
												, char *tmp)
{
	int		i;

	i = (int)ft_strlen(tmp);
	while (tmp[--i])
	{
		if (tmp[i] != '.' && tmp[i] != '0')
			break ;
		tmp[i] = '\0';
	}
	if (ld < 0 && !(pf->arg.more = 0))
		pf->arg.space = 0;
	else if (pf->arg.more)
		pf->arg.space = 0;
	return (tmp);
}

int					pf_build_float_g_exp(t_printf *pf, long double ld)
{
	char		*end;
	char		*tmp1;
	char		*tmp2;

	end = ft_strnew(100);
	end[0] = (pf->in[pf->i] + '0') - 2 - '0';
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
	tmp1 = ft_ldtoa(ld, pf->arg.preci - 1);
	tmp1 = pf_build_float_g_exp_round(pf, ld, tmp1);
	pf->join = ft_strjoin(tmp1, tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	pf->arg.diez = 0;
	return (ld);
}

int					pf_build_float_g(t_printf *pf)
{
	long double	ld;
	long double	tmp;
	int			divi;

	ld = pf_build_float_get(pf);
	tmp = ld;
	divi = 0;
	while ((int)tmp != 0 && ++divi)
		tmp /= 10;
	pf->arg.preci -= divi;
	if ((pf->arg.preci >= 0) && pf_build_float_g_normal1(pf, ld))
		return (0);
	pf->arg.preci += divi;
	ld = pf_build_float_g_exp(pf, ld);
	if (pf->arg.width > (int)ft_strlen(pf->join)
		&& (pf->arg.more || pf->arg.space))
		pf->arg.width--;
	pf->valid = 1;
	pf_build_format(pf);
	return (0);
}
