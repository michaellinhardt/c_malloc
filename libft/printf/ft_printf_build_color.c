/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:47:13 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/02 16:12:16 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		pf_build_color_get(t_printf *pf)
{
	if (pf->arg.width == 0 && !(pf->join = ft_strdup(CWHI)))
		return (1);
	if (pf->arg.width == 1 && !(pf->join = ft_strdup(CRED)))
		return (1);
	if (pf->arg.width == 2 && !(pf->join = ft_strdup(CGRE)))
		return (1);
	if (pf->arg.width == 3 && !(pf->join = ft_strdup(CYEL)))
		return (1);
	if (pf->arg.width == 4 && !(pf->join = ft_strdup(CBLU)))
		return (1);
	if (pf->arg.width == 5 && !(pf->join = ft_strdup(CGREY)))
		return (1);
	return (0);
}

int				pf_build_color(t_printf *pf)
{
	pf->arg.diez = 0;
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.zero = 0;
	pf->arg.less = 0;
	pf->arg.ispreci = 0;
	pf->arg.preci = 0;
	if (pf->arg.width < 0 || pf->arg.width > 5)
		pf->arg.width = 0;
	if (pf_build_color_get(pf))
		return (1);
	pf->valid = 1;
	return (0);
}
