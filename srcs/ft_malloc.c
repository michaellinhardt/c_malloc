/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 02:41:43 by mlinhard          #+#    #+#             */
/*   Updated: 2017/12/21 05:25:49 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** It return the enum corresponding to the page category needed for this
** allocation, depending on the demanded size and the size max for pages
*/
enum book_name	get_book_name(size_t size)
{
	t_book		**book;

	book = book_open();
	if (size <= book[0]->size_block)
		return TINY;
	else if (size <= book[1]->size_block)
		return SMALL;
	else
		return LARGE;
}

void			book_init(t_book **book)
{
	int		page_size;

	page_size = getpagesize();

	bzero(book[0], sizeof(t_book));
	bzero(book[1], sizeof(t_book));
	bzero(book[2], sizeof(t_book));

	book[0]->size_pages = TINY_PAGE_MULTIPLIER > 0
	? page_size * TINY_PAGE_MULTIPLIER: page_size * 2;
	book[1]->size_pages = SMALL_PAGE_MULTIPLIER > 0
	? page_size * SMALL_PAGE_MULTIPLIER : page_size * 4;
	book[2]->size_pages = 0;

	book[0]->size_block = ((book[0]->size_pages / 100) - sizeof(t_block) - 1);
	book[1]->size_block = ((book[1]->size_pages / 100) - sizeof(t_block) - 1);
	book[2]->size_block = 0;
}

/*
** Function mmap wrapper, shorten the code and allow easy code incrementation
*/
void			*do_mmap(size_t size)
{
	return mmap(
		NULL,
		size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
		0,
		0
	);
}

/*
** This function keep a static ptr to the 3 pages list
** [0] for tiny pages, [1] for small and [2] for large
*/
t_book			**book_open(void)
{
	static t_book		**book;
	static int			init;

	if (!init)
	{
		init = 1;
		book = (t_book **)do_mmap(sizeof(t_book *) * 3);
		book[0] = (t_book *)do_mmap(sizeof(t_book));
		book[1] = (t_book *)do_mmap(sizeof(t_book));
		book[2] = (t_book *)do_mmap(sizeof(t_book));
		book_init(book);
	}
	return (book);
}

void			*ft_malloc(size_t size)
{
	enum book_name		book_name;
	t_book				*book;

	book_name = get_book_name(size);
	book = book_open()[book_name];

	malloc_print_book(book_name);
	ft_printf("size needed: %zu\n", size);

	if (book->size_bigger < size)
		malloc_page_new(book, size, 0, 0);

	return (NULL);
}
