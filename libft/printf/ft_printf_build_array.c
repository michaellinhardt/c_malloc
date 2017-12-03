/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:58:52 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/05 08:42:30 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		pf_build_array_info(t_printf *pf)
{
	char	*prev;
	char	*itoa;

	if (!(itoa = ft_itoa(pf->j)))
		return (1);
	prev = ft_strjoin(pf->join, "[");
	ft_strdel(&pf->join);
	pf->join = prev;
	prev = ft_strjoin(pf->join, itoa);
	ft_strdel(&pf->join);
	pf->join = ft_strjoin(prev, "] ");
	ft_strdel(&prev);
	ft_strdel(&itoa);
	return (0);
}

static int		pf_build_array_int(t_printf *pf)
{
	int			*tab;
	char		*prev;
	char		*next;
	static char	space[2] = {0};

	if (!(tab = (int *)va_arg(pf->ap, void *)))
		return (1);
	pf->j = -1;
	space[0] = (pf->arg.space) ? ' ' : '\n';
	if (!(pf->join = ft_strnew(0)))
		return (1);
	while (++pf->j < pf->arg.width)
	{
		prev = (pf->j > 0) ? ft_strjoin(pf->join, space) : ft_strdup(pf->join);
		ft_strdel(&pf->join);
		pf->join = prev;
		if (pf->arg.zero && pf_build_array_info(pf))
			return (1);
		prev = pf->join;
		next = ft_itoa(tab[pf->j]);
		pf->join = ft_strjoin(prev, next);
		ft_strdel(&next);
		ft_strdel(&prev);
	}
	return (0);
}

static int		pf_build_array_char(t_printf *pf)
{
	char		**tab;
	char		*prev;
	char		*next;
	static char	space[2] = {0};

	if (!(tab = (char **)va_arg(pf->ap, void *)))
		return (1);
	pf->j = -1;
	space[0] = (pf->arg.space) ? ' ' : '\n';
	if (!(tab[0]) || !(pf->join = ft_strnew(0)))
		return (1);
	while (tab[++pf->j])
	{
		prev = (pf->j > 0) ? ft_strjoin(pf->join, space) : ft_strdup(pf->join);
		ft_strdel(&pf->join);
		pf->join = prev;
		if (pf->arg.zero && pf_build_array_info(pf))
			return (1);
		prev = pf->join;
		next = ft_strdup(tab[pf->j]);
		pf->join = ft_strjoin(prev, next);
		ft_strdel(&next);
		ft_strdel(&prev);
	}
	return (0);
}

int				pf_build_array(t_printf *pf)
{
	pf->arg.diez = 0;
	pf->arg.more = 0;
	pf->arg.less = 0;
	pf->arg.ispreci = 0;
	pf->arg.preci = 0;
	if (pf->arg.width < 0)
		pf->arg.width = 0;
	if (pf->in[pf->i] == 'T' && pf_build_array_char(pf))
		return (1);
	if (pf->in[pf->i] == 't' && (!(pf->arg.width) || pf_build_array_int(pf)))
		return (1);
	pf->valid = 1;
	return (0);
}
