/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 01:12:26 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/02 14:42:24 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_build_format_width(t_printf *pf)
{
	int		start;
	int		i;
	char	c;
	char	*tmp;

	if (pf->arg.width < (int)ft_strlen(pf->join))
		return (0);
	start = (pf->arg.less) ? 0 : (pf->arg.width - ft_strlen(pf->join));
	start = start + (pf->arg.diez2 * pf->arg.zero);
	c = (pf->arg.zero && !pf->arg.less) ? '0' : ' ';
	tmp = pf->join;
	if (!(pf->join = ft_strnew(pf->arg.width)))
		return (1);
	i = -1;
	pf->j = 0;
	while (++i < pf->arg.width)
	{
		if (pf->arg.zero && pf->arg.diez2 && pf->j < 2
		&& (pf->join[i] = tmp[pf->j++]))
			continue;
		pf->join[i] = (i < start || !(tmp[pf->j])) ? c : tmp[pf->j++];
	}
	ft_strdel(&tmp);
	return (0);
}

static int	pf_build_format_sign(t_printf *pf)
{
	char	*s;
	char	*tmp;
	int		i;
	int		need;

	s = (pf->arg.more) ? ft_strdup("+") : ft_strdup(" ");
	if (!s)
		return (1);
	tmp = pf->join;
	if (!(pf->join = ft_strnew((ft_strlen(pf->join) + 1))))
		return (1);
	pf->j = -1;
	i = 0;
	need = (pf->arg.more + pf->arg.space);
	while (tmp[i])
	{
		if (tmp[i] != ' ' && (need) && !(need = 0))
			pf->join[++pf->j] = *s;
		else
			pf->join[++pf->j] = tmp[i++];
	}
	ft_strdel(&s);
	ft_strdel(&tmp);
	return (0);
}

static int	pf_build__format_diez2(t_printf *pf)
{
	char	*tmp;

	tmp = pf->join;
	if (!(pf->join = ft_strjoin("0x", tmp)))
		return (1);
	ft_strdel(&tmp);
	return (0);
}

static void	pf_build_format_zero2(t_printf *pf)
{
	pf->j = -1;
	while (pf->join[++pf->j])
		if (pf->join[pf->j] == ' ')
			pf->join[pf->j] = '0';
}

void		pf_build_format(t_printf *pf)
{
	if (!pf->join && (pf->ret = 1))
		return ;
	if (pf->arg.diez2 && pf_build__format_diez2(pf) && (pf->ret = 1))
		return ;
	if (pf->arg.width && pf_build_format_width(pf) && (pf->ret = 1))
		return ;
	if (pf->arg.zero2)
		pf_build_format_zero2(pf);
	if ((pf->arg.more || pf->arg.space) && pf_build_format_sign(pf)
	&& (pf->ret = 1))
		return ;
	if (pf->arg.toupper)
		ft_strtoupper(pf->join);
}
