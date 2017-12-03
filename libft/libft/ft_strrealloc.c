/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:31:00 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/10 16:12:34 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrealloc(char *str, int size)
{
	char	*ret;

	if (!(ret = ft_strnew(ft_strlen(str) + size + 2)))
		return (NULL);
	ft_memcpy(ret, str, ft_strlen(str));
	ft_strdel(&str);
	return (ret);
}
