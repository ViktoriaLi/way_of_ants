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

void add_ants_to_rooms(t_params *params, t_ways *all_paths, int last_way)
{
	int i;
	t_ways *tmp;

	i = 0;
	tmp = all_paths;
	while (i <= last_way)
	{
		
		tmp = tmp->next;
		i++;
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

	int i;
	i = 0;
	int j;
	j = 0;
	int add_ants;
	add_ants = 0;
	unsigned long long ants_at_finish;
	ants_at_finish = 0;

	quantity = all_paths->number + 1;
	tmp = all_paths;
	ants = (*params).ants;
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

	add_ants_to_rooms(params, all_paths, last_way);
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
