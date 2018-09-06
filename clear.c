/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:20:20 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/09/05 14:34:33 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_t_ways(t_ways *all_paths)
{
	t_ways	*tmp_paths;
	t_way	*tmp_way;

	while (all_paths)
	{
		tmp_paths = all_paths->next;
		while (all_paths->way)
		{
			tmp_way = all_paths->way->next;
			free(all_paths->way);
			all_paths->way = tmp_way;
		}
		free(all_paths);
		all_paths = tmp_paths;
	}
}

void	del_t_room_list(t_room_list *farm)
{
	t_room_list	*tmp_farm;
	//t_room_list	*tmp_links;
	//t_room		*tmp_room;

	while (farm)
	{
		tmp_farm = farm->next;
		/*while (farm->room)
		{
			tmp_room = farm->room->next;
			ft_strdel(&farm->room->name);
			del_t_room_list(farm->room->links);
			while (farm->room->links)
			{
				tmp_links = farm->room->links->next;
				free(farm->room->links);
				farm->room->links = tmp_links;
			}
			free(farm->room);
			farm->room = tmp_room;
		}*/
		free(farm);
		farm = tmp_farm;
	}
}

void	del_rooms_and_links(t_room *rooms, t_link *links)
{
	t_room *tmp_rooms;
	t_link *tmp_links;
	//t_room_list	*tmp_links2;

	while (rooms)
	{
		tmp_rooms = rooms->next;
		ft_strdel(&rooms->name);
		del_t_room_list(rooms->links);
		/*while (rooms->links)
		{
			tmp_links2 = rooms->links->next;
			free(rooms->links);
			rooms->links = tmp_links2;
		}*/
		free(rooms);
		rooms = tmp_rooms;
	}
	while (links)
	{
		tmp_links = links->next;
		ft_strdel(&links->first);
		ft_strdel(&links->second);
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
