/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 03:30:31 by mlinhard          #+#    #+#             */
/*   Updated: 2016/02/17 03:59:23 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wstrtostr(wchar_t const *src)
{
	char *str;
	char *prev;
	char *next;

	if (!(str = ft_strnew(0)))
		return ((char *)NULL);
	while (*src)
	{
		prev = str;
		if (!(next = ft_wchartostr(*src)))
			return ((char *)NULL);
		if (!(str = ft_strjoin(prev, next)))
			return ((char *)NULL);
		if (*src++)
			;
		ft_strdel(&prev);
		ft_strdel(&next);
	}
	return (str);
}
