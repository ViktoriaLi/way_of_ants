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
