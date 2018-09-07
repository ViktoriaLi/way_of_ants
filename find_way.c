/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:12:57 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/25 15:33:27 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		create_path_cycle(t_room_list *queue, t_ways *tmp, t_way *new_head)
{
	int count;

	count = 1;
	while (queue->room->which_room > START_ROOM)
	{
		tmp->way->name = queue->room->name;
		tmp->way->if_room = 1;
		tmp->way->ant_numb = 0;
		tmp->way->distance = count;
		count++;
		tmp->way->next = new_head;
		tmp->way->prev = NULL;
		if (new_head)
			new_head->prev = tmp->way;
		new_head = tmp->way;
		queue->room->usage = 3;
		queue->room = queue->room->enter;
		if (queue->room->which_room == START_ROOM)
			break ;
		if (!(tmp->way = (t_way *)malloc(sizeof(t_way))))
			return (0);
	}
	return (1);
}

int		create_path(t_ways **all_paths, t_room_list *queue, int way_number)
{
	t_way	*new_head;
	t_ways	*tmp;
	t_ways	*head_paths;

	new_head = NULL;
	head_paths = *all_paths;
	while (queue->next)
		queue = queue->next;
	if (!(tmp = (t_ways *)malloc(sizeof(t_ways))) ||
		!(tmp->way = (t_way *)malloc(sizeof(t_way))))
		return (0);
	tmp->number = way_number;
	tmp->ant_quantity = 0;
	if (!create_path_cycle(queue, tmp, new_head))
		return (0);
	tmp->next = NULL;
	if (!head_paths)
	{
		*all_paths = tmp;
		return (0);
	}
	while (head_paths->next)
		head_paths = head_paths->next;
	head_paths->next = tmp;
	return (1);
}

void	if_ants_more_than_one(t_room_list *queue, t_ways **all_paths,
	t_params *params)
{
	int			count;
	t_room_list	*head_queue;

	count = 1;
	queue->room->usage = 1;
	head_queue = queue;
	while ((*params).max_ways != count)
	{
		clear_queue(head_queue, queue, 0);
		while (queue)
		{
			if (!add_to_queue(queue))
				break ;
			queue = queue->next;
		}
		if (!queue)
			break ;
		queue = head_queue;
		create_path(all_paths, queue, count);
		count++;
	}
}

void	calc_turns(t_params *params, t_ways *all_paths, t_ways *tmp)
{
	int quantity;
	int ants_id;

	ants_id = 1;
	while (tmp->next && tmp->way->distance <
		(tmp->way->distance + (*params).ants - 1))
	{
		tmp->start_ant = ants_id++;
		tmp = tmp->next;
	}
	tmp->start_ant = ants_id;
	(*params).last_way = tmp->number;
	quantity = tmp->number + 1;
	tmp = all_paths;
	ants_id = (*params).ants;
	while (tmp)
	{
		tmp->ant_quantity = (*params).ants / quantity;
		if (tmp->number == (*params).last_way)
			break ;
		ants_id -= tmp->ant_quantity;
		tmp = tmp->next;
	}
	if (ants_id)
		all_paths->ant_quantity = ants_id;
}

int		search_way(t_room_list *farm, t_params *params)
{
	t_room_list *queue;
	t_room_list *tmp_queue;
	t_ways		*all_paths;
	t_ways		*tmp_all_paths;

	all_paths = NULL;
	queue = NULL;
	tmp_queue = NULL;
	if (!create_queue(&queue, &tmp_queue, farm))
	{
		clear_queue(tmp_queue, queue, 1);
		return (0);
	}
	create_path(&all_paths, queue, 0);
	tmp_all_paths = all_paths;
	if ((*params).ants > 1 && (*params).max_ways > 1)
		if_ants_more_than_one(queue, &all_paths, params);
	all_paths = tmp_all_paths;
	calc_turns(params, all_paths, tmp_all_paths);
	add_ants_to_rooms(all_paths, (*params).last_way, params);
	all_paths = tmp_all_paths;
	del_t_room_list(tmp_queue);
	del_t_ways(all_paths);
	del_t_room_list(farm);
	return (1);
}
