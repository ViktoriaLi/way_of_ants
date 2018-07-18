/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 10:56:38 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/16 10:56:41 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*void del_farm(t_room *rooms)
{
	t_room *rooms
}*/

int make_rooms_with_links(t_room *rooms, t_link *links, t_params *params)
{
	t_room_list *farm;
	t_room_list *head;

	if (!(farm = (t_room_list *)malloc(sizeof(t_room_list))))
	{
		del_rooms_and_links(rooms, links);
		return (0);
	}
	head = farm;
	while (rooms)
	{
		farm->room = rooms;
		if (rooms->next)
		{
			if (!(farm->next = (t_room_list *)malloc(sizeof(t_room_list))))
			{
				del_rooms_and_links(rooms, links);
				return (0);
			}
		}
		else
			farm->next = NULL;
		rooms = rooms->next;
		farm = farm->next;
	}
	farm = head;
	add_links(&farm, links, params);
	return (1);
}

int create_links(t_room_list **farm, t_link *links)
{
	t_room_list	*tmp;
	t_room	*link;
	t_room	*head;
	t_room_list	*tmp_farm;

	tmp = NULL;
	head = NULL;
	link = NULL;
	tmp_farm = *farm;
	while (tmp_farm)
	{
		if (ft_strcmp(tmp_farm->room->name, links->first) == 0)
			head = tmp_farm->room;
		if (ft_strcmp(tmp_farm->room->name, links->second) == 0)
			link = tmp_farm->room;
		tmp_farm = tmp_farm->next;
	}
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

int add_links(t_room_list **farm, t_link *links, t_params *params)
{
	while (links)
	{
		create_links(farm, links);
		links = links->next;
	}
	ft_printf("start enters %d\n", (*params).start_exits);
	ft_printf("finish enters %d\n", (*params).end_entries);
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

int if_repeat_link(t_link **head, t_link *newelem)
{
	t_link *tmp;

	tmp = *head;
	while (tmp)
	{
		if ((ft_strcmp(newelem->first, tmp->first) == 0 &&
		ft_strcmp(newelem->second, tmp->second) == 0) ||
		(ft_strcmp(newelem->first, tmp->second) == 0 &&
		ft_strcmp(newelem->second, tmp->first) == 0))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int if_corrects_link_names(t_link *newelem, t_room *rooms)
{
	t_room *tmp;
	int if_first;
	int if_second;

	tmp = rooms;
	if_first = 0;
	if_second = 0;
	while (tmp)
	{
		if (ft_strcmp(newelem->first, tmp->name) == 0)
			if_first++;
		if (ft_strcmp(newelem->second, tmp->name) == 0)
			if_second++;
		tmp = tmp->next;
	}
	if (if_first == 1 && if_second == 1)
		return (1);
	return (0);
}

int	save_link(t_link **head, t_params *params, t_room *rooms)
{
	int i;
	t_link	*newelem;

	i = 0;
	newelem = NULL;
	if (!(newelem = (t_link *)malloc(sizeof(t_link))))
		return (0);
	while ((*params).buf[i] && (*params).buf[i] != '-')
		i++;
	newelem->first = ft_strsub((*params).buf, 0, i++);
	if (!(*params).buf[i])
		return (0);
	newelem->second = ft_strsub((*params).buf, i, ft_strlen((*params).buf - 1 + 1));
	if (!if_corrects_link_names(newelem, rooms) ||
	ft_strcmp(newelem->first, newelem->second) == 0)
	{
		free(newelem);
		return (0);
	}
	//ft_printf("%s\n", "ERROR8");
	if (if_repeat_link(head, newelem))
	{
		if (ft_strcmp(newelem->first, (*params).end) == 0 ||
		ft_strcmp((*params).end, newelem->second) == 0)
			(*params).end_entries++;
		else if (ft_strcmp(newelem->first, (*params).start) == 0 ||
		ft_strcmp((*params).start, newelem->second) == 0)
			(*params).start_exits++;
		newelem->next = *head;
		*head = newelem;
	}
	else
		free(newelem);
	ft_printf("%s\n", (*params).buf);
	return (1);
}
