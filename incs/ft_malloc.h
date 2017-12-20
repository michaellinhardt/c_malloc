/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 02:41:35 by mlinhard          #+#    #+#             */
/*   Updated: 2017/12/20 22:44:48 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"

# include <stdlib.h>
# include <sys/mman.h>

/*
** Pages multiplyer is used to calculate the page size, basically tiny page
** size will be getpagesize() * TINY_PAGE_MULTIPLIER and same for small page
*/
# define TINY_PAGE_MULTIPLIER 2
# define SMALL_PAGE_MULTIPLIER 16

typedef struct			s_block
{
	int					init;
}						t_block;

typedef struct			s_page
{
	size_t				id;
	size_t				id_block;
	size_t            	size_bigger;
	size_t            	size_free;
	size_t            	size_used;
	size_t				block_free;
	size_t				block_used;
	t_block				*blocks;
	struct s_page		*next;
}						t_page;

typedef struct			s_book
{
	t_page            	*pages;
	size_t				id_page;
	size_t            	size_pages;
	size_t            	size_block;
	size_t            	size_bigger;
	size_t            	size_free;
	size_t            	size_used;
	size_t            	count_pages;
}						t_book;

enum book_name {
	TINY,
	SMALL,
	LARGE,
};

/*
** ft_malloc.c functions:
*/
enum book_name	get_book_name(size_t size);
void			*do_mmap(size_t size);
t_book			**book_open(void);
void			book_init(t_book **book);
void			*ft_malloc(size_t size);

/*
** ft_malloc_print functions:
*/
void			malloc_print_book(enum book_name book_name);
void			malloc_print_page(t_page *page);

#endif
