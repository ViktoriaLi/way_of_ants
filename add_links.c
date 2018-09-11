/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 13:47:31 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/09/05 14:33:22 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		add_links_to_rooms(t_room *rooms, t_room_list *farm)
{
	while (rooms)
	{
		farm->room = rooms;
		if (rooms->next)
		{
			if (!(farm->next = (t_room_list *)malloc(sizeof(t_room_list))))
				return (0);
		}
		else
			farm->next = NULL;
		rooms = rooms->next;
		farm = farm->next;
	}
	return (1);
}

int		make_rooms_with_links(t_room *rooms, t_link *links, t_params *params)
{
	t_room_list *farm;
	t_room_list *head;

	if (!(farm = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	head = farm;
	if (!add_links_to_rooms(rooms, farm))
	{
		del_t_room_list(farm);
		return (0);
	}
	farm = head;
	if (!add_links(&farm, links, params))
	{
		del_t_room_list(farm);
		return (0);
	}
	del_rooms_and_links(rooms, NULL);
	return (1);
}

void	search_links(t_room_list **farm, t_room **link,
	t_room **head, t_link *links)
{
	t_room_list	*tmp_farm;

	tmp_farm = *farm;
	while (tmp_farm)
	{
		if (ft_strcmp(tmp_farm->room->name, links->first) == 0)
			*head = tmp_farm->room;
		if (ft_strcmp(tmp_farm->room->name, links->second) == 0)
			*link = tmp_farm->room;
		tmp_farm = tmp_farm->next;
	}
}

int		create_links(t_room_list **farm, t_link *links)
{
	t_room_list	*tmp;
	t_room		*link;
	t_room		*head;

	tmp = NULL;
	head = NULL;
	link = NULL;
	search_links(farm, &link, &head, links);
	if (!head || !link)
		return (0);
	if (!(tmp = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmp->next = head->links;
	head->links = tmp;
	tmp->room = link;
	if (!(tmp = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmp->next = link->links;
	link->links = tmp;
	tmp->room = head;
	return (1);
}

int		add_links(t_room_list **farm, t_link *links, t_params *params)
{
	t_link *tmp_links;

	tmp_links = links;
	while (links)
	{
		if (!create_links(farm, links))
			return (0);
		links = links->next;
	}
	del_rooms_and_links(NULL, tmp_links);
	if (!(*params).start_exits || !(*params).end_entries)
		return (0);
	if ((*params).start_exits < (*params).end_entries)
		(*params).max_ways = (*params).start_exits;
	else
		(*params).max_ways = (*params).end_entries;
	if (!search_way(*farm, params))
		return (0);
	return (1);
}
