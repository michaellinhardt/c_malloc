/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_n.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 01:10:31 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/29 01:50:51 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_build_n(t_printf *pf)
{
	intmax_t	n;
	intmax_t	*np;

	n = ft_strlen(pf->out);
	if (!(np = va_arg(pf->ap, void *)))
		return (1);
	*np = n;
	pf->join = ft_strnew(0);
	pf->valid = 1;
	pf->arg.diez = 0;
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.zero = 0;
	pf->arg.less = 0;
	pf->arg.ispreci = 0;
	pf->arg.width = 0;
	pf_build_format(pf);
	return (0);
}
