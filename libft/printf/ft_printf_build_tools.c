/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 01:12:04 by mlinhard          #+#    #+#             */
/*   Updated: 2016/02/02 07:33:40 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_build_nulchar(t_printf *pf)
{
	pf->j = 0;
	while (pf->nulchar[pf->j] > -1)
		pf->j++;
	pf->nulchar[pf->j] = ft_strlen(pf->out);
	if (pf->arg.width && !pf->arg.less)
		pf->nulchar[pf->j] += pf->arg.width - 1;
	pf->nulchar[++pf->j] = -1;
	return ((int)'*');
}

int		pf_build_invalid(t_printf *pf)
{
	if (!(pf->join = ft_strnew(1)))
		return (1);
	if (pf->in[pf->i])
		pf->join[0] = pf->in[pf->i];
	else
		pf->arg.width = 0;
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.diez = 0;
	pf_build_format(pf);
	return (0);
}

int		pf_build_modulo(t_printf *pf)
{
	if (!(pf->join = ft_strdup("%")))
		return (1);
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.diez = 0;
	pf->arg.preci = 0;
	pf_build_format(pf);
	pf->valid = 1;
	return (0);
}
