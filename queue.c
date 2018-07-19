/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 10:56:27 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/16 10:56:30 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int add_to_queue(t_room_list *queue)
{
	t_room_list *links;
	t_room *enter;
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
			if (!(new = (t_room_list *)malloc(sizeof(t_room_list))))
				return (0);
				new->next = NULL;
				new->room = links->room;
				new->room->usage = 1;
				new->room->enter = enter;
				end->next = new;
				end = end->next;
				if (new->room->which_room == END_ROOM)
					return (0);
		}
		links = links->next;
	}
	return (1);
}

void create_path(t_ways **all_paths, t_room_list *queue, int way_number)
{
	t_way *new;
	t_way *new_head;
	t_room_list *tmp_queue;
	int count;
	t_ways *tmp;

	count = 1;
	new = NULL;
	new_head = NULL;
	tmp_queue = queue;
	while (tmp_queue->next)
		tmp_queue = tmp_queue->next;
	if (!(tmp = (t_ways *)malloc(sizeof(t_ways *))))
		return ;
	if (!(tmp->way = (t_way *)malloc(sizeof(t_way))))
		return ;
	//tmp->next = *all_paths;
	//*all_paths = NULL;
	tmp->number = way_number;
	tmp->ant = 0;
	while (tmp_queue->room->which_room >= START_ROOM)
	{
		tmp->way->name = tmp_queue->room->name;
		tmp->way->if_empty = 1;
		tmp->way->distance = count;
		count++;
		tmp->way->next = new_head;
		new_head = tmp->way;

		tmp_queue->room->usage = 3;
		if (!tmp_queue->room->enter)
			break;
		tmp_queue->room = tmp_queue->room->enter;
		if (!(tmp->way = (t_way *)malloc(sizeof(t_way))))
			return ;
	}
	if (*all_paths)
	{
		tmp->next = *all_paths;
		*all_paths = tmp;
	}
	else
	{
		*all_paths = tmp;
		(*all_paths)->next = NULL;
	}

	new = tmp->way;
	while (new)
	{
		ft_printf("3path%s\n", new->name);
		new = new->next;
	}
}

void create_first_path(t_ways **all_paths, t_room_list *queue, int way_number)
{
	t_way *new;
	t_way *new_head;
	t_room_list *tmp_queue;
	int count;

	count = 1;
	new = NULL;
	tmp_queue = queue;
	new_head = NULL;

	while (tmp_queue->next)
		tmp_queue = tmp_queue->next;

	if (!(*all_paths = (t_ways *)malloc(sizeof(t_ways *))))
		return ;
		(*all_paths)->next = NULL;
		(*all_paths)->number = way_number;
		(*all_paths)->ant = 0;
		(*all_paths)->way = NULL;
	if (!((*all_paths)->way = (t_way *)malloc(sizeof(t_way))))
		return ;
	while (tmp_queue->room->which_room >= START_ROOM)
	{
		//if (!tmp->way)
			//tmp->way->next = NULL;
		tmp_queue->room->usage = 3;
		(*all_paths)->way->name = tmp_queue->room->name;
		(*all_paths)->way->if_empty = 1;
		(*all_paths)->way->distance = count;
		count++;
		if (tmp_queue->room->which_room == END_ROOM)
			(*all_paths)->way->next = NULL;
		else
			(*all_paths)->way->next = new_head;
		//(*all_paths)->way->next = new_head;
		new_head = (*all_paths)->way;
		if (!tmp_queue->room->enter)
			break;
		tmp_queue->room = tmp_queue->room->enter;
		if (!((*all_paths)->way = (t_way *)malloc(sizeof(t_way))))
			return ;
	}
	/*if (*all_paths)
		tmp->next = *all_paths;
	else
		tmp->next = NULL;*/
	/*if (way_number > 0)
		tmp->next = *all_paths;
	else
		tmp->next = NULL;
	*all_paths = tmp;*/

	new = (*all_paths)->way;
	while (new)
	{
		ft_printf("3path%s\n", new->name);
		new = new->next;
	}
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

int create_queue(t_room_list **queue, t_room_list **tmp_queue, t_room_list *farm)
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
		if ((*queue)->room->usage != 2)
		{
			if (!add_to_queue((*queue)))
				break ;
		}
		(*queue) = (*queue)->next;
	}
	if (!(*queue))
		return (0);
	return (1);
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
	if ((*params).ants > 1 && (*params).max_ways > 1)
		if_ants_more_than_one(queue, &all_paths, params);
	ft_printf("tmp%d\n", (*params).max_ways);
	t_way *all_paths1;
	while (all_paths)
	{
		/*if (!all_paths->way)
			break;*/
		//ft_printf("3way%s\n", "");
		all_paths1 = all_paths->way;
		//ft_printf("3test%s\n", "3test");
		//ft_printf("2test%s\n", "2test");
		ft_printf("1way%d\n", all_paths->number);
		while (all_paths1)
		{
			//ft_printf("1test%s\n", "1test");
			//ft_printf("3way%s\n", "");
		ft_printf("2way%s\n", all_paths1->name);

		all_paths1 = all_paths1->next;

	}
	//ft_printf("4way%s\n", "");
	all_paths = all_paths->next;
	//ft_printf("4way%s\n", "");
}
//ft_printf("5way%s\n", "");
	//make_output(params, all_paths);
	//calc_turns(params, all_paths);
	return (1);
}
