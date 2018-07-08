#include "lem_in.h"

int add_to_queue(t_room_list *queue, t_params *params)
{
	ft_printf("startstart %s x%d y%d dist%d %s usage%d\n", (queue)->room->name,
		(queue)->room->x, (queue)->room->y, (queue)->room->which_room, queue->room->enter->name,
		queue->room->usage);

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
		if (links->room->usage == 0 || links->room->which_room == 2)
		{
			ft_printf("TTT%d\n", links->room->usage);
			if (!(new = (t_room_list *)malloc(sizeof(t_room_list))))
				return (0);
				new->next = NULL;
				new->room = links->room;
				new->room->usage = 1;
				new->room->distance = (*params).step++;
				new->room->enter = enter;
				ft_printf("add %s x%d y%d dist%d %s %d\n", links->room->name,
					links->room->x, links->room->y, links->room->which_room, links->room->enter->name,
				links->room->usage);
				end->next = new;
				end = end->next;
				if (new->room->which_room == END_ROOM)
					return (0);
		}
		links = links->next;
	}
	return (1);
}

void create_path(t_ways *all_paths, t_room_list *queue)
{
	t_ways *new;
	t_ways *new_head;
	t_room_list *tmp_queue;

	new = NULL;
	new_head = NULL;
	tmp_queue = queue;
	while (tmp_queue->next)
		tmp_queue = tmp_queue->next;
	/*while (all_paths->next)
		all_paths = all_paths->next;*/
	while (tmp_queue->room->which_room != 1)
	{
		if (!(new = (t_ways *)malloc(sizeof(t_ways))))
			return ;
		ft_printf("path%s\n", tmp_queue->room->name);
		new->name = tmp_queue->room->name;
		new->number = all_paths->number;
		tmp_queue->room->usage = 3;
		new->next = new_head;
		new_head = new;
		ft_printf("2path%s\n", new->name);
		//new = new->next;
		tmp_queue->room = tmp_queue->room->enter;
	}
	if (!(new = (t_ways *)malloc(sizeof(t_ways))))
		return ;
		new->name = tmp_queue->room->name;
		tmp_queue->room->usage = 3;
		new->next = new_head;
		new_head = new;
	ft_printf("22path%s\n", new->name);
	ft_printf("path%s\n", tmp_queue->room->name);
	while (new)
	{
		ft_printf("rev%s\n", "rev");
		ft_printf("3path%s\n", new->name);
		new = new->next;
	}
	all_paths->number++;
	all_paths->name = NULL;
	all_paths->way = new_head;
	if (!(all_paths->next = (t_ways *)malloc(sizeof(t_ways))))
		return ;
	all_paths = all_paths->next;
	/*while (all_paths->way)
	{
		ft_printf("rev%s\n", "rev");
		ft_printf("3path%s\n", all_paths->way->name);
		all_paths->way = all_paths->way->next;
	}*/
}

int add_multiply_ways(t_ways *all_paths, t_room_list *rooms, t_params *params)
{
	t_room_list *tmp_queue;
	t_room_list *queue;
	t_room_list *tmp_rooms;
	queue = NULL;
	tmp_queue = NULL;
	tmp_rooms = rooms;
	//tmp_queue = tmp_queue->next;
	ft_printf("2mult%s\n", "mult");
	(*params).step = 0;
	if (!(queue = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmp_queue = queue;
	while (tmp_rooms->room->which_room != START_ROOM)
		tmp_rooms = tmp_rooms->next;
	tmp_queue->room = tmp_rooms->room;
	tmp_queue->next = NULL;
	tmp_queue->room->distance = (*params).step++;
	tmp_queue->room->usage = 1;
	tmp_queue->room->enter = tmp_queue->room;
	tmp_rooms = rooms;
	ft_printf("3mult%s\n", "mult");
	while (tmp_rooms)
	{
		if (tmp_rooms->room->usage != 3 && tmp_rooms->room->which_room != 1)
		{
			tmp_rooms->room->usage = 0;
			tmp_rooms->room->distance = 0;
			tmp_rooms->room->enter = NULL;
		}
		tmp_rooms = tmp_rooms->next;
	}
	tmp_rooms = rooms;
	ft_printf("4mult%s\n", "mult");
	while (tmp_queue)
	{
		ft_printf("5mult%s\n", "mult");
		if (!add_to_queue(tmp_queue, params))
			break ;
		ft_printf("5mult%s\n", "mult");
		tmp_queue = tmp_queue->next;
	}
	if (!tmp_queue)
	{
		ft_printf("error%s\n", "ERROR12");
		return (0);
	}
	tmp_queue = queue;
	ft_printf("7mult%s\n", "mult");
	while (tmp_queue)
	{
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (tmp_queue)->room->name,
			(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room,
		(tmp_queue)->room->usage, (tmp_queue)->room->distance, tmp_queue->room->enter->name);
		//if ((tmp_queue)->room->which_room != 1)
			//ft_printf("enter %s\n", tmp_queue->room->enter->name);
		tmp_queue = tmp_queue->next;
	}
	ft_printf("7mult%s\n", "mult");
	if (!(all_paths = (t_ways *)malloc(sizeof(t_ways *))))
		return (0);
	ft_printf("7mult%s\n", "mult");
	create_path(all_paths, tmp_queue);
	return (1);
}

int if_ants_more_than_one(t_room_list *queue, t_ways *all_paths, t_params *params)
{
	int count;
	t_room_list *head_queue;

	count = 1;
	queue->room->usage = 1;
	head_queue = queue;
	while ((*params).ants != count)
	{
		queue = head_queue;
		queue = queue->next;
		while (queue)
		{
			if (queue->room->usage != 3 && queue->room->which_room != 1)
			{
				queue->room->usage = 0;
				queue->room->distance = 0;
				queue->room->enter = NULL;
			}
			free(queue);
			queue = queue->next;
		}
		queue = head_queue;
		queue->next = NULL;
		ft_printf("1mult%s\n", "mult");
		while (queue)
		{
			if (queue->room->usage != 2 && (queue->room->which_room != 2 && queue->room->usage != 3))
			{
				if (!add_to_queue(queue, params))
					break ;
			}
			ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (queue)->room->name,
				(queue)->room->x, (queue)->room->y, (queue)->room->which_room,
			(queue)->room->usage, (queue)->room->distance, queue->room->enter->name);
			queue = queue->next;
		}
		queue = head_queue;
		if (queue)
		{
			queue = head_queue;
			while (queue)
			{
				ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (queue)->room->name,
					(queue)->room->x, (queue)->room->y, (queue)->room->which_room,
				(queue)->room->usage, (queue)->room->distance, queue->room->enter->name);
				queue = queue->next;
			}
			queue = head_queue;
			if (!(all_paths = (t_ways *)malloc(sizeof(t_ways *))))
				return (0);
			count++;
			create_path(all_paths, queue);
		}
		return (1);
		}
		return (0);
}

int search_way(t_room_list *farm, t_params *params)
{

	t_room_list *queue;

	t_room_list *tmp_queue;
	t_room_list *tmp_queue1;
	t_room_list *tmp_rooms;
	t_ways *all_paths;
	t_ways *head_all_paths;

	all_paths = NULL;

	queue = NULL;
	tmp_rooms = farm;

	if (!(queue = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	queue->next = NULL;
	while (tmp_rooms && tmp_rooms->room->which_room != START_ROOM)
		tmp_rooms = tmp_rooms->next;
	queue->room = tmp_rooms->room;
	queue->room->distance = (*params).step++;
	queue->room->usage = 1;
	queue->room->enter = queue->room;
	tmp_rooms = farm;
	tmp_queue = queue;

	while (queue)
	{
		if (queue->room->usage != 2)
		{
			if (!add_to_queue(queue, params))
				break ;
		}
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (queue)->room->name,
			(queue)->room->x, (queue)->room->y, (queue)->room->which_room,
		(queue)->room->usage, (queue)->room->distance, queue->room->enter->name);
		queue = queue->next;
	}
	if (!queue)
	{
		ft_printf("error%s\n", "ERROR12");
		return (0);
	}
	queue = tmp_queue;
	/*if (tmp_queue)
		return (0);*/
	while (queue)
	{
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (queue)->room->name,
			(queue)->room->x, (queue)->room->y, (queue)->room->which_room,
		(queue)->room->usage, (queue)->room->distance, queue->room->enter->name);
		queue = queue->next;
	}
	queue = tmp_queue;
	while (tmp_rooms)
	{
		tmp_queue1 = tmp_rooms->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (tmp_rooms)->room->name,
			(tmp_rooms)->room->x, (tmp_rooms)->room->y, (tmp_rooms)->room->which_room);
		while (tmp_queue1)
		{
		ft_printf("1links%s x%d y%d dist%d\n", tmp_queue1->room->name,
			tmp_queue1->room->x, tmp_queue1->room->y, tmp_queue1->room->which_room);
		tmp_queue1 = tmp_queue1->next;
	}
	tmp_rooms = tmp_rooms->next;
}

	if (!(all_paths = (t_ways *)malloc(sizeof(t_ways *))))
		return (0);
	head_all_paths = all_paths;
	all_paths->number = -1;
	all_paths->name = NULL;
	create_path(all_paths, queue);
	/*tmp_rooms = farm;
	while (tmp_rooms)
	{
		tmp_queue1 = tmp_rooms->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (tmp_rooms)->room->name,
			(tmp_rooms)->room->x, (tmp_rooms)->room->y, (tmp_rooms)->room->which_room);
		while (tmp_queue1)
		{
		ft_printf("1links%s x%d y%d dist%d\n", tmp_queue1->room->name,
			tmp_queue1->room->x, tmp_queue1->room->y, tmp_queue1->room->which_room);
		tmp_queue1 = tmp_queue1->next;
	}
	tmp_rooms = tmp_rooms->next;
}*/
	if ((*params).ants > 1)
	{
		if(!if_ants_more_than_one(queue, all_paths, params))
			return (0);
	}
	all_paths = head_all_paths;
	t_ways *all_paths1;
	while (all_paths)
	{
		all_paths1 = all_paths->way;
		ft_printf("1way1%d\n", (all_paths)->number);
		while (all_paths1)
		{
		ft_printf("2way%s\n", all_paths1->name);
		all_paths1 = all_paths1->next;
	}
	all_paths = all_paths->next;
}
	return (1);
}
