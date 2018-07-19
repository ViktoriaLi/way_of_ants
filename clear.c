/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:20:20 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/19 16:20:54 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_rooms_and_links(t_room *rooms, t_link *links)
{
	t_room *tmp_rooms;
	t_link *tmp_links;

	while (rooms)
	{
		tmp_rooms = rooms->next;
		free(rooms);
		rooms = tmp_rooms;
	}
	while (links)
	{
		tmp_links = links->next;
		free(links);
		links = tmp_links;
	}
}

void	struct_nulling(t_params *params)
{
	(*params).buf = NULL;
	(*params).ants = 0;
	(*params).links_count = 0;
	(*params).rooms_count = 0;
	(*params).if_error = 0;
	(*params).end_entries = 0;
	(*params).start_exits = 0;
	(*params).max_ways = 0;
	(*params).start = NULL;
	(*params).end = NULL;
}

void	read_params_nulling(t_reading *read_params)
{
	(*read_params).res = -2;
	(*read_params).ifstart = 0;
	(*read_params).ifend = 0;
	(*read_params).rooms = NULL;
	(*read_params).links = NULL;
}
