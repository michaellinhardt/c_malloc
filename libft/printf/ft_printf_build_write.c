/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_write.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 02:02:20 by mlinhard          #+#    #+#             */
/*   Updated: 2016/06/11 05:39:14 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_build_write(t_printf *pf)
{
	if (!(pf->wout = (char **)va_arg(pf->ap, void **)))
		return (1);
	pf->join = ft_strnew(0);
	pf->valid = 1;
	pf->arg.diez = 0;
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.zero = 0;
	if (pf->arg.less)
		pf->freestr = 1;
	pf->arg.less = 0;
	pf->arg.ispreci = 0;
	pf->arg.width = 0;
	pf->write = 1;
	pf_build_format(pf);
	return (0);
}
