/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_page.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 22:51:59 by mlinhard          #+#    #+#             */
/*   Updated: 2017/12/21 07:41:00 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** - Create a new page and chain it to book->pages at the first place
** - This function use handle size and size_pages to manage difference beetwin
**   TINY/SMALL and LARGE page
*/
void			malloc_page_new(t_book *book, size_t size
								, float division, float reste)
{
	int			nb_page;
	int			req_size;
	int			size_pages;
	t_page		*new;

	size += book->size_pages == 0 ? sizeof(t_page) + sizeof(t_block) : 0;
	size_pages = book->size_pages > 0 ? book->size_pages : getpagesize();
	division = ((float)size / (float)size_pages);
	reste = division - (int)division;
	nb_page = reste > 0 ? (int)division + 1 : (int)division;
	req_size = nb_page * size_pages;
	new = (t_page *)do_mmap(req_size);
	bzero(new, sizeof(t_page));
	new->next = book->pages;
	book->pages = new;
	new->id = book->id_page++;
	if ((new->size_bigger = book->size_block) == 0)
	 	new->size_bigger = req_size - sizeof(t_page) - sizeof(t_block);
	new->block_free = 1;
	new->blocks = (t_block *)((void *)new + sizeof(t_page));
	malloc_page_new_block(new->blocks, new->size_bigger);
	if (book->size_bigger < new->size_bigger)
		book->size_bigger = new->size_bigger;
	book->count_pages += 1;
}

void			malloc_page_new_block(t_block *block, size_t size)
{
	bzero(block, sizeof(t_block));
	block->is_free = 1;
	block->size = size;
	block->data = (void *)((void *)block + sizeof(t_block));
}
