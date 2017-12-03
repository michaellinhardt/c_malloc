/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 19:52:53 by mlinhard          #+#    #+#             */
/*   Updated: 2016/06/29 09:19:23 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFF_SIZE 65568
# define MAP 0
# define F ft_bootstrap

typedef struct		s_gnl
{
	char			b[BUFF_SIZE + 1];
	int				fd;
	char			*t;
	int				r;
	int				i;
	char			*s;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(int fd, char **line);
void				ft_bootstrap(char **line);

#endif
