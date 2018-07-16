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

	ft_printf("way_number %d\n", way_number);
	if (!(tmp = (t_ways *)malloc(sizeof(t_ways *))))
		return ;
	if (!(tmp->way = (t_way *)malloc(sizeof(t_way))))
		return ;
	tmp->next = *all_paths;
	tmp->prev = NULL;
	tmp->number = way_number;
	tmp->way->distance = 0;

	while (tmp_queue->next)
		tmp_queue = tmp_queue->next;

	while (tmp_queue->room->which_room != START_ROOM)
	{
		tmp->way->name = tmp_queue->room->name;
		tmp->way->if_empty = 1;
		count++;
		ft_printf("way_number %d\n", way_number);
		tmp->way->next = new_head;
		ft_printf("way_number %d\n", way_number);
		new_head = tmp->way;
		tmp_queue->room->usage = 3;
		tmp_queue->room = tmp_queue->room->enter;
		ft_printf("way_number %d\n", way_number);
		if (!(tmp->way = (t_way *)malloc(sizeof(t_way))))
			return ;
	}
	ft_printf("way_number %d\n", way_number);
	if (!(tmp->way = (t_way *)malloc(sizeof(t_way))))
		return ;
	tmp->way->name = tmp_queue->room->name;
	tmp->way->if_empty = 1;
	tmp->way->distance = count;
	tmp->way->next = new_head;
	tmp->ant = 0;
	new_head = tmp->way;
	tmp_queue->room->usage = 3;
	tmp->next = *all_paths;
	if ((*all_paths))
		(*all_paths)->prev = tmp;
	*all_paths = tmp;
	new = tmp->way;
	ft_printf("tmp->way->distance%d\n", tmp->way->distance);
	while (new)
	{
		ft_printf("rev%s\n", "rev");
		ft_printf("3path%s\n", new->name);
		new = new->next;
	}
	//*all_paths = head_all_paths;
	//all_paths = all_paths->next;	
	/*t_way *all_paths1;
	while (all_paths)
	{
		all_paths1 = all_paths->way;
		ft_printf("6way%d\n", all_paths->number);
		while (all_paths1)
		{
		ft_printf("7way%s\n", all_paths1->name);
		all_paths1 = all_paths1->next;
	}
	all_paths = all_paths->next;
}*/

}

int if_ants_more_than_one(t_room_list *queue, t_ways **all_paths, t_params *params)
{
	int count;
	t_room_list *head_queue;

	count = 1;
	queue->room->usage = 1;
	head_queue = queue;
	

	while ((*params).ants != count)
	{
		ft_printf("1mult%s\n", "mult");
		queue = head_queue;
		queue = queue->next;
		while (queue)
		{
			if (queue->room->usage != 3 && queue->room->which_room != START_ROOM)
			{
				queue->room->usage = 0;
				queue->room->enter = NULL;
			}
			free(queue);
			queue = queue->next;
		}
		queue = head_queue;
		queue->next = NULL;
		
		while (queue)
		{
			if (queue->room->usage != 2 && (queue->room->which_room != END_ROOM && queue->room->usage != 3))
			{
				if (!add_to_queue(queue))
					break ;
			}
			ft_printf("2queue%s x%d y%d whichroom%d usage%d enter%s\n", (queue)->room->name,
				(queue)->room->x, (queue)->room->y, (queue)->room->which_room,
			(queue)->room->usage, queue->room->enter->name);
			queue = queue->next;
		}
		queue = head_queue;
		if (queue)
		{
			queue = head_queue;
			while (queue)
			{
				ft_printf("2queue%s x%d y%d whichroom%d usage%d enter%s\n", (queue)->room->name,
					(queue)->room->x, (queue)->room->y, (queue)->room->which_room,
				(queue)->room->usage, queue->room->enter->name);
				queue = queue->next;
			}
			queue = head_queue;

			create_path(all_paths, queue, count);

			count++;
		}
		return (1);
		}
		return (0);
}

void make_output(t_params *params, t_ways *all_paths)
{
	int i;
	int ants;
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
	t_room_list *tmp_rooms;
	t_ways *all_paths;

	all_paths = NULL;
	queue = NULL;
	tmp_rooms = farm;
	if (!(queue = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	queue->next = NULL;
	while (tmp_rooms && tmp_rooms->room->which_room != START_ROOM)
		tmp_rooms = tmp_rooms->next;
	queue->room = tmp_rooms->room;
	queue->room->usage = 1;
	queue->room->enter = queue->room;
	tmp_rooms = farm;
	tmp_queue = queue;
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
	{
		ft_printf("error%s\n", "ERROR12");
		return (0);
	}
	queue = tmp_queue;
	create_path(&all_paths, queue, 0);
	if ((*params).ants > 1)
	{
		if(!if_ants_more_than_one(queue, &all_paths, params))
			return (0);
	}
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
