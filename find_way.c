/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:12:57 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/25 14:12:59 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void create_path(t_ways **all_paths, t_room_list *queue, int way_number)
{
	t_way *new_head;
	int count;
	t_ways *tmp;
	t_ways *head_paths;

	count = 1;
	new_head = NULL;
	head_paths = *all_paths;
	while (queue->next)
		queue = queue->next;
	if (!(tmp = (t_ways *)malloc(sizeof(t_ways))))
		return ;
	if (!(tmp->way = (t_way *)malloc(sizeof(t_way))))
		return ;
	tmp->number = way_number;
	tmp->ant = 0;
	while (queue->room->which_room >= START_ROOM)
	{
		tmp->way->name = queue->room->name;
		tmp->way->if_empty = 1;
		tmp->way->distance = count;
		count++;
		tmp->way->next = new_head;
		new_head = tmp->way;
		queue->room->usage = 3;
		if (!queue->room->enter)
			break;
		queue->room = queue->room->enter;
		if (!(tmp->way = (t_way *)malloc(sizeof(t_way))))
			return ;
	}
	tmp->next = NULL;
	if (!head_paths)
	{
		*all_paths = tmp;
		return ;
	}
	while (head_paths->next)
		head_paths = head_paths->next;
	head_paths->next = tmp;
}

void if_ants_more_than_one(t_room_list *queue, t_ways **all_paths, t_params *params)
{
	int count;
	t_room_list *head_queue;
	t_room_list *tmp;

	count = 1;
	tmp = NULL;
	queue->room->usage = 1;
	head_queue = queue;

	while ((*params).max_ways != count)
	{
		queue = head_queue;
		queue = queue->next;
		while (queue)
		{
			if (queue->room->usage != 3 && queue->room->which_room != START_ROOM)
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
		while (queue)
		{
			if (queue->room->usage != 2)
			{
				if (!add_to_queue(queue))
					break ;
			}
			queue = queue->next;
		}
		if (!queue)
			break ;
		queue = head_queue;
		while (queue)
		{
			ft_printf("queue %s\n", queue->room->name);
			queue = queue->next;
		}
		queue = head_queue;
		create_path(all_paths, queue, count);
		count++;
	}
}

void make_output(t_params *params, t_ways *all_paths)
{
	unsigned int i;
	unsigned int ants;
	int all_ants[(*params).ants];
	t_ways *head_ways;
	//void *concret_ways[all_paths->number];

	i = 0;
	ants = 1;

	while (i < (*params).ants)
		all_ants[i++] = ants++;
	i = 0;
	ants = 1;
	while (all_paths->next)
		all_paths = all_paths->next;
	head_ways = all_paths;
	/*while (i < all_paths->number)
	{
		concret_ways[i++] = all_paths->way;
		all_paths = all_paths->next;
	}*/
	i = 0;
	all_paths = head_ways;
	while (all_paths && ants <= (*params).ants)
	{
		ft_printf("L%d-%s\n", all_ants[i], all_paths->way->name);
		all_paths->way = all_paths->way->next;
		if (!all_paths->way)
			break;

	}
	/*while (1)
	{
		if (ants == (*params).ants)
			ants = 1;
		all_paths = head_ways;
		while (all_paths)
		{
			while (all_paths->way && !all_paths->way->if_empty)
			{
				all_paths->way = all_paths->way->next;
			}
			if (all_paths->way && all_paths->way->if_empty)

			all_paths = all_paths->prev;
		}
	}*/
}

void calc_turns(t_params *params, t_ways *all_paths)
{
	//int i;
	////int turn;
	t_ways *tmp;
	int ants;
	//int ways[all_paths->number + 1];
	int quantity;
	int min_way;
	int if_all_one_way;
	int last_way;

	quantity = all_paths->number + 1;
	tmp = all_paths;
	ants = (*params).ants;
	//turn = 1;
	//i = 0;
	while(tmp)
	{
		//ways[i++] = tmp->way->distance;
		if (!tmp->next)
			min_way = tmp->way->distance;
		tmp = tmp->next;
	}
	if_all_one_way = min_way + (*params).ants - 2;
	tmp = all_paths;
	while (tmp->way->distance > if_all_one_way)
		tmp = tmp->next;
	last_way = tmp->number;
	quantity = tmp->number + 1;
	ft_printf("lastway %d if_all_one_way%d min_way%d %d\n", last_way, if_all_one_way, min_way, (*params).ants / quantity);
	while (tmp)
	{
		tmp->ant = (*params).ants / quantity;
		if (!tmp->next)
			tmp->ant = ants;
		ants--;
		tmp = tmp->next;
	}
	tmp = all_paths;
	while (tmp->number != last_way)
	{
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_printf("number %d ants%d\n", tmp->number, tmp->ant);
		tmp = tmp->next;
	}

}

int search_way(t_room_list *farm, t_params *params)
{
	t_room_list *queue;
	t_room_list *tmp_queue;
	t_ways *all_paths;

	all_paths = NULL;
	queue = NULL;
	tmp_queue = NULL;
	if (!create_queue(&queue, &tmp_queue, farm))
		return (0);
	queue = tmp_queue;
	while (queue)
	{
		ft_printf("queue %s\n", queue->room->name);
		queue = queue->next;
	}
	queue = tmp_queue;
	create_path(&all_paths, queue, 0);
	queue = tmp_queue;
	if ((*params).ants > 1 && (*params).max_ways > 1)
		if_ants_more_than_one(queue, &all_paths, params);
	t_way *all_paths1;
	while (all_paths)
	{
		all_paths1 = all_paths->way;
		ft_printf("1way%d\n", all_paths->number);
		while (all_paths1)
		{
			ft_printf("2way%s\n", all_paths1->name);
			all_paths1 = all_paths1->next;
		}
		all_paths = all_paths->next;
	}
	//make_output(params, all_paths);
	//calc_turns(params, all_paths);
	return (1);
}
