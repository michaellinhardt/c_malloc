/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 21:03:29 by mlinhard          #+#    #+#             */
/*   Updated: 2017/12/20 21:40:41 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** This functions print the content of the static struct book
** It allow to view the memory state at instant T
*/
void			malloc_print_book(enum book_name book_name)
{
	t_book		*book;

	book = book_open()[book_name];
	printf("*** [ BOOK NUMBER %d ] ***\n", book_name);
	printf("size_pages: %zu\n", book->size_pages);
	printf("size_block: %zu\n", book->size_block);
	printf("size_free: %zu\n", book->size_free);
	printf("count_pages: %zu\n", book->count_pages);
}
