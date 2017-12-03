/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 10:06:49 by mlinhard          #+#    #+#             */
/*   Updated: 2016/03/31 19:15:00 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_ldtoa_solve(t_ldtoa *db)
{
	while (db->ld > 0 || db->preci || (db->multi >= db->divi && db->preci == 0))
	{
		db->multi++;
		if (db->multi > db->divi && (db->divi = 999999) && db->preci > 0)
		{
			if (!db->i || db->ret[(db->i - 1)] == '-')
				db->ret[db->i++] = '0';
			db->ret[db->i++] = '.';
		}
		if (db->divi == 999999 && (--(db->preci) < 0))
			break ;
		db->ld *= 10;
		db->ret[db->i++] = ((int)db->ld) + '0';
		db->ld -= (int)db->ld;
	}
}

static void	ft_ldtoa_round(t_ldtoa *db)
{
	if (((int)(db->ld * 10)) < 5)
		return ;
	db->i = (int)ft_strlen(db->ret);
	while (db->ret[--db->i])
	{
		if (db->ret[db->i] == '.')
			continue ;
		else if (db->ret[db->i] == '9')
			db->ret[db->i] = '0';
		else
			break ;
	}
	db->ret[db->i] = ((db->ret[db->i] - '0') + 1) + '0';
}

char		*ft_ldtoa(long double ld, int preci)
{
	t_ldtoa		db;
	char		*ret;

	ft_bzero(&db, sizeof(t_ldtoa));
	if (!(db.ret = ft_strnew(2048)))
		return ((char *)NULL);
	if ((1 / ld) < 0 && (db.isneg = 1))
	{
		db.ret[db.i++] = '-';
		ld *= -1;
	}
	db.save = ld;
	db.ld = ld;
	db.preci = preci;
	while (db.ld >= 1 && ++db.divi)
		db.ld /= 10;
	ft_ldtoa_solve(&db);
	ft_ldtoa_round(&db);
	ret = ft_strdup(db.ret);
	ft_strdel(&db.ret);
	return (ret);
}
