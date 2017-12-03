/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_build_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 01:12:04 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/31 19:23:55 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_build_wstring_preci(t_printf *pf, wchar_t const *ws)
{
	size_t	i;
	size_t	last;

	i = 0;
	last = 0;
	while (*ws && (i <= (size_t)pf->arg.preci))
	{
		last = i;
		if (*ws <= 0x7F)
			i++;
		else if (*ws <= 0x7FF)
			i += 2;
		else if (*ws <= 0xFFFF)
			i += 3;
		else if (*ws <= 0x10FFFF)
			i += 4;
		if (*ws++)
			;
	}
	pf->arg.preci = (i <= (size_t)pf->arg.preci) ? i : last;
}

int			pf_build_wstring(t_printf *pf)
{
	wchar_t	*verif;
	char	*str;
	int		dofree;

	dofree = 0;
	if (!(verif = (wchar_t *)va_arg(pf->ap, void *)))
	{
		dofree = 1;
		verif = (wchar_t *)ft_strdup("(null)");
	}
	str = (dofree) ? ft_strdup((char *)verif) : ft_wstrtostr(verif);
	if (pf->arg.ispreci && pf->arg.preci)
		pf_build_wstring_preci(pf, verif);
	if (dofree)
		ft_memdel((void **)&verif);
	pf->join = (pf->arg.ispreci) ? ft_strsub(str, 0, pf->arg.preci) :
	ft_strdup(str);
	ft_strdel(&str);
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.diez = 0;
	pf_build_format(pf);
	pf->valid = 1;
	return (0);
}

int			pf_build_string(t_printf *pf)
{
	char	*verif;
	int		dofree;

	if (pf->arg.length == l)
		return (pf_build_wstring(pf));
	dofree = (pf->freestr == 1) ? 1 : 0;
	if (!(verif = (char *)va_arg(pf->ap, void *)))
	{
		dofree = 1;
		verif = ft_strdup("(null)");
	}
	pf->join = (pf->arg.ispreci) ? ft_strsub(verif, 0, pf->arg.preci) :
	ft_strdup(verif);
	if (dofree)
		ft_strdel(&verif);
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.diez = 0;
	pf_build_format(pf);
	pf->valid = 1;
	return (0);
}

int			pf_build_char(t_printf *pf)
{
	if (pf->arg.length == l)
		return (pf_build_wchar(pf));
	if (!(pf->join = ft_strnew(1)))
	{
		pf->ret = 1;
		return (0);
	}
	if (!(pf->join[0] = (char)va_arg(pf->ap, void *)))
		pf->join[0] = (char)pf_build_nulchar(pf);
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.diez = 0;
	pf->arg.ispreci = 0;
	pf->arg.preci = 0;
	pf_build_format(pf);
	pf->valid = 1;
	return (0);
}

int			pf_build_wchar(t_printf *pf)
{
	wchar_t wc;

	if (!(wc = (wchar_t)va_arg(pf->ap, void *)))
		wc = (wchar_t)pf_build_nulchar(pf);
	else
	{
		if ((wc < 0 || (wc > 55295 && wc < 57344) || wc > 1114111)
			&& (pf->ret = 1))
			return (0);
	}
	if (!(pf->join = ft_wchartostr(wc)))
		return (1);
	pf->arg.more = 0;
	pf->arg.space = 0;
	pf->arg.diez = 0;
	pf->arg.ispreci = 0;
	pf->arg.preci = 0;
	pf_build_format(pf);
	pf->valid = 1;
	return (0);
}
