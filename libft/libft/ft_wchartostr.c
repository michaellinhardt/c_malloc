/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchartostr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 03:38:59 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/05 08:52:16 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wchartostr(wchar_t const wc)
{
	char conv[5];

	ft_bzero(conv, 5);
	if (wc <= 0x7F)
		conv[0] = (char)wc;
	else if (wc <= 0x7FF)
	{
		conv[0] = (wc >> 6) + 0xC0;
		conv[1] = (wc & 0x3F) + 0x80;
	}
	else if (wc <= 0xFFFF)
	{
		conv[0] = (wc >> 12) + 0xE0;
		conv[1] = ((wc >> 6) & 0x3F) + 0x80;
		conv[2] = (wc & 0x3F) + 0x80;
	}
	else if (wc <= 0x10FFFF)
	{
		conv[0] = (wc >> 18) + 0xF0;
		conv[1] = ((wc >> 12) & 0x3F) + 0x80;
		conv[2] = ((wc >> 6) & 0x3F) + 0x80;
		conv[3] = (wc & 0x3F) + 0x80;
	}
	return (ft_strdup(conv));
}
