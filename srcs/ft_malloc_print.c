/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 21:03:29 by mlinhard          #+#    #+#             */
/*   Updated: 2017/12/20 22:26:16 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** This functions print the informations about book, page and block
*/

void			malloc_print_book(enum book_name book_name)
{
	t_book		*book;

	book = book_open()[book_name];
	ft_printf("*** [ BOOK NUMBER %d ] ***\n", book_name);
	ft_printf("size_pages: %zu\n", book->size_pages);
	ft_printf("size_block: %zu\n", book->size_block);
	ft_printf("size_bigger: %zu\n", book->size_bigger);
	ft_printf("size_free: %zu\n", book->size_free);
	ft_printf("size_used: %zu\n", book->size_used);
	ft_printf("count_pages: %zu\n", book->count_pages);
	ft_printf("id_page: %zu\n", book->id_page);
	ft_printf("id_block: %zu\n", book->id_block);
}

void			malloc_print_page(t_page *page)
{
	ft_printf("*** [ PAGE ID %zu ] ***\n", page->id);
	ft_printf("size_bigger: %zu\n", page->size_bigger);
	ft_printf("size_free: %zu\n", page->size_free);
	ft_printf("size_used: %zu\n", page->size_used);
	ft_printf("block_free: %zu\n", page->block_free);
	ft_printf("block_used: %zu\n", page->block_used);
	if (page->blocks)
		ft_printf("page->blocks addr: %p\n", page->blocks);
	else
		ft_printf("page->blocks addr: NONE\n");
}
