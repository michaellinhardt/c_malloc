/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 01:12:04 by mlinhard          #+#    #+#             */
/*   Updated: 2016/02/02 07:18:38 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_join_specifier(t_printf *pf)
{
	char	*prev;

	if (!pf->join)
		return (0);
	prev = pf->out;
	if (!(pf->out = ft_strjoin(prev, pf->join)))
		return (1);
	ft_strdel(&prev);
	ft_strdel(&pf->join);
	return (0);
}

static int	pf_join_format(t_printf *pf)
{
	char	*prev;
	char	*next;

	if ((pf->i - pf->start) == 0)
		return (0);
	prev = pf->out;
	if (!(next = ft_strsub(pf->in, pf->start, (pf->i - pf->start))))
		return (1);
	if (!(pf->out = ft_strjoin(prev, next)))
		return (1);
	pf->start = pf->i;
	ft_strdel(&prev);
	ft_strdel(&next);
	return (0);
}

int			pf_join(t_printf *pf, int src)
{
	if (src == 1 && pf_join_format(pf))
		return (1);
	if (src == 2 && pf_join_specifier(pf))
		return (1);
	return (0);
}
