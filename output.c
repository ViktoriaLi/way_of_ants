/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 15:28:45 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/25 15:28:46 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
// ptr -> a -> b -> c
SingleList *a = ptr->Next;
SingleList *b = a->Next;
ptr->Next = b; // a -> b -> c
               //      ^
               //  ptr |

a->Next = b->Next;  //        a -> c
                    //             ^
                    //  ptr ->   b |

b->Next = a;        //  ptr -> b -> a -> c*/

/*List* shiftRight(List* list) {
    if (list->head == list->tail) {
        return list;
    }

    Node* node;
    for (node = list->head; node->next != list->tail; node = node->next) { ; }

    node->next = NULL;
    list->tail->next = list->head;
    list->head = list->tail;
    list->tail = node;

    return list;
}*/

/*void ants_moving(t_ways *all_paths, int last_way, t_params *params)
{
	t_way *end;
	t_way *tmp;
	t_way *prev;
	int finished_ants;
	int i;

	i = 0;
	end = NULL;
	tmp = NULL;
	prev = NULL;
	finished_ants = (*params).ants;
	while (tmp->next)
		tmp = tmp->next;
	end = tmp;
	tmp = all_paths;
	if (tmp == end)
		return ;
	while (finished_ants > 0)
	{
		tmp
		while()
		{
			if (tmp->way->next->if_room)
			{

			}
		}
		tmp = tmp->next;
		i++;
	}
	Node* node;
	for (node = list->head; node->next != list->tail; node = node->next) { ; }

	node->next = NULL;
	list->tail->next = list->head;
	list->head = list->tail;
	list->tail = node;


	return list;
}*/

int		add_ant_node(t_ways *all_paths, int last_way)
{
	t_way	*new_head;
	int ants;
	int counter;
	t_way	*ants_list;

	ants = all_paths->start_ant;
	new_head = all_paths->way;
	ants_list = NULL;
	counter = 0;
	while (counter < all_paths->ant_quantity)
	{
		if (!(ants_list = (t_way *)malloc(sizeof(t_way))))
			return (0);
		ants_list->name = NULL;
		ants_list->if_room = 0;
		ants_list->ant_numb = ants;
		ants_list->distance = 0;
		ants_list->next = new_head;
		//ants_list->fict_next = new_head;
		new_head = ants_list;
		ants += (last_way + 1);
		counter++;
	}
	all_paths->way = new_head;
	return (1);
}

void add_ants_to_rooms(t_ways *all_paths, int last_way)
{
	int i;
	t_ways *tmp;

	i = 0;
	tmp = all_paths;
	while (i <= last_way)
	{
		add_ant_node(all_paths, last_way);
		all_paths = all_paths->next;
		i++;
	}
	all_paths = tmp;

	t_way *all_paths1;
	t_ways *all_paths2;
	all_paths2 = all_paths;
	while (all_paths2)
	{
		all_paths1 = all_paths2->way;
		ft_printf("1way%d %d %d\n", all_paths2->number, all_paths2->ant_quantity, all_paths2->start_ant);
		while (all_paths1)
		{
			ft_printf("2way%s %d\n", all_paths1->name, all_paths1->ant_numb);
			all_paths1 = all_paths1->next;
		}
		all_paths2 = all_paths2->next;
	}
}

void calc_turns(t_params *params, t_ways *all_paths)
{
	t_ways *tmp;
	int ants;
	int quantity;
	int min_way;
	int if_all_one_way;
	int last_way;
	int ants_id;

	int i;
	i = 0;
	int j;
	j = 0;
	int add_ants;
	add_ants = 0;
	unsigned long long ants_at_finish;
	ants_at_finish = 0;
	ants_id = 1;
	quantity = all_paths->number + 1;
	tmp = all_paths;
	ants = (*params).ants;
	min_way = tmp->way->distance;
	if_all_one_way = min_way + (*params).ants - 1;
	ft_printf("if_all_one_way%d \n", if_all_one_way);
	while (tmp->next && tmp->way->distance < if_all_one_way)
	{
		tmp->start_ant = ants_id;
		ants_id++;
		tmp = tmp->next;
	}
	tmp->start_ant = ants_id;
	last_way = tmp->number;
	quantity = tmp->number + 1;
	ft_printf("lastway %d if_all_one_way%d min_way%d %d\n", last_way, if_all_one_way, min_way, (*params).ants / quantity);
	tmp = all_paths;
	while (tmp)
	{
		tmp->ant_quantity = (*params).ants / quantity;
		if (tmp->number == last_way)
			break ;
		ants--;
		tmp = tmp->next;
	}
	tmp = all_paths;
	if (ants)
		tmp->ant_quantity = ants;
	ants = 1;

	add_ants_to_rooms(all_paths, last_way);
/*	while (1)
	{
		tmp = all_paths;
		i = 0;
		ft_printf("%s\n", "2test");
		while (tmp && tmp->way && i < quantity)
		{
			//scroll_way(j, tmp->way);
			ft_printf("%s\n", "3test");
			ft_printf("L%d-%s ", ants + add_ants, tmp->way->name);

			tmp->way = tmp->way->next;
			add_ants++;

			tmp = tmp->next;
			if (!tmp->way)
				ants_at_finish++;
			i++;
			if (i == quantity - 1)
			{
				tmp = all_paths;
				while (tmp)
				{
					tmp->way = tmp->way->next;
					tmp = tmp->next;
				}

			}

		}
		ft_printf("%c", '\n');
		j++;
		ft_printf("%s\n", "1test");
		if (ants_at_finish == (*params).ants)
			break;
	}*/
	/*while (tmp)
	{
		ft_printf("number %d ants%d\n", tmp->number, tmp->ant);
		tmp = tmp->next;
	}*/

}
