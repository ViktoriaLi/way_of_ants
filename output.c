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

void scroll_way(int quant, t_way *way)
{
	int i;

	i = 0;
	while (i < quant)
	{
		way = way->next;
	}
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
	min_way = tmp->way->distance;
	if_all_one_way = min_way + (*params).ants - 1;
	ft_printf("if_all_one_way%d \n", if_all_one_way);
	while (tmp->next && tmp->way->distance < if_all_one_way)
		tmp = tmp->next;
	last_way = tmp->number;
	quantity = tmp->number + 1;
	ft_printf("lastway %d if_all_one_way%d min_way%d %d\n", last_way, if_all_one_way, min_way, (*params).ants / quantity);
	tmp = all_paths;
	while (tmp)
	{
		tmp->ant = (*params).ants / quantity;
		if (tmp->number == last_way)
			break ;
		ants--;
		tmp = tmp->next;
	}
	tmp = all_paths;
	if (ants)
		tmp->ant = ants;
	ants = 1;
	int i;
	i = 0;
	int j;
	j = 0;
	int add_ants;
	add_ants = 0;
	unsigned long long ants_at_finish;
	ants_at_finish = 0;
	while (1)
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
			/*if (i == quantity - 1)
			{
				tmp = all_paths;
				while (tmp)
				{
					tmp->way = tmp->way->next;
					tmp = tmp->next;
				}

			}*/

		}
		ft_printf("%c", '\n');
		j++;
		ft_printf("%s\n", "1test");
		if (ants_at_finish == (*params).ants)
			break;
	}
	/*while (tmp)
	{
		ft_printf("number %d ants%d\n", tmp->number, tmp->ant);
		tmp = tmp->next;
	}*/

}
