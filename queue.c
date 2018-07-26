/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:14:00 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/25 15:28:10 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_queue(t_room_list *head_queue, t_room_list *queue, int if_finish)
{
	t_room_list *tmp;

	tmp = NULL;
	queue = head_queue;
	if (!if_finish)
		queue = queue->next;
	while (queue)
	{
		if (!if_finish && queue->room->usage != 3 &&
			queue->room->which_room != START_ROOM)
		{
			queue->room->usage = 0;
			queue->room->enter = NULL;
		}
		tmp = queue->next;
		free(queue);
		queue = tmp;
	}
	queue = head_queue;
	queue->next = NULL;
}

int		fill_queue_params(t_room_list **new, t_room_list *links,
t_room *enter, t_room_list **end)
{
	if (!((*new) = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	(*new)->next = NULL;
	(*new)->room = links->room;
	(*new)->room->usage = 1;
	(*new)->room->enter = enter;
	(*end)->next = (*new);
	(*end) = (*end)->next;
	if ((*new)->room->which_room == END_ROOM)
		return (0);
	return (1);
}

int		add_to_queue(t_room_list *queue)
{
	t_room_list	*links;
	t_room		*enter;
	t_room_list *end;
	t_room_list *new;

	new = NULL;
	enter = queue->room;
	links = queue->room->links;
	end = queue;
	while (end->next)
		end = end->next;
	if (links)
		queue->room->usage = 2;
	while (links)
	{
		if (links->room->usage == 0 || links->room->which_room == END_ROOM)
		{
			if (!fill_queue_params(&new, links, enter, &end))
				return (0);
		}
		links = links->next;
	}
	return (1);
}

int		create_queue(t_room_list **queue, t_room_list **tmp_queue,
	t_room_list *farm)
{
	t_room_list *tmp_rooms;

	tmp_rooms = farm;
	if (!(*queue = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	(*queue)->next = NULL;
	while (tmp_rooms && tmp_rooms->room->which_room != START_ROOM)
		tmp_rooms = tmp_rooms->next;
	(*queue)->room = tmp_rooms->room;
	(*queue)->room->usage = 1;
	(*queue)->room->enter = NULL;
	tmp_rooms = farm;
	*tmp_queue = (*queue);
	while ((*queue))
	{
		if ((*queue)->room->usage != 2 && !add_to_queue(*queue))
			break ;
		(*queue) = (*queue)->next;
	}
	if (!(*queue))
		return (0);
	return (1);
}
