/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 15:28:45 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/09/05 14:29:55 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_ants(t_way *path)
{
	t_way *tmp;

	tmp = path;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->if_room && tmp->ant_numb)
		{
			ft_printf("L%d-%s ", tmp->ant_numb, tmp->name);
			if (!tmp->next)
				tmp->ant_numb = 0;
		}
		tmp = tmp->prev;
	}
}

void	ants_shift(t_way *path, int *finished_ants)
{
	t_way *tmp;

	tmp = path;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (!tmp->ant_numb && tmp->prev && tmp->prev->ant_numb)
		{
			tmp->ant_numb = tmp->prev->ant_numb;
			tmp->prev->ant_numb = 0;
			if (!tmp->next)
				(*finished_ants) = (*finished_ants) - 1;
		}
		tmp = tmp->prev;
	}
}

void	ants_moving(t_ways *all_paths, int last_way, t_params *params)
{
	t_ways	*tmp;
	int		finished_ants;

	tmp = all_paths;
	finished_ants = (*params).ants;
	while (finished_ants > 0)
	{
		tmp = all_paths;
		while (tmp && tmp->number <= last_way)
		{
			ants_shift(tmp->way, &finished_ants);
			print_ants(tmp->way);
			tmp = tmp->next;
		}
		ft_printf("%c", '\n');
	}
}

void	add_ant_node(t_ways *all_paths, int last_way)
{
	t_way	*new_head;
	int		ants;
	int		counter;
	t_way	*ants_list;

	ants = all_paths->start_ant;
	new_head = all_paths->way;
	ants_list = NULL;
	counter = 0;
	while (counter < all_paths->ant_quantity)
	{
		if (!(ants_list = (t_way *)malloc(sizeof(t_way))))
			return ;
		ants_list->name = NULL;
		ants_list->if_room = 0;
		ants_list->ant_numb = ants;
		ants_list->distance = 0;
		ants_list->next = new_head;
		ants_list->prev = NULL;
		if (new_head)
			new_head->prev = ants_list;
		new_head = ants_list;
		ants += (last_way + 1);
		counter++;
	}
}

void	add_ants_to_rooms(t_ways *all_paths, int last_way, t_params *params)
{
	int		i;
	t_ways	*tmp;

	i = 0;
	tmp = all_paths;
	while (i <= last_way)
	{
		add_ant_node(all_paths, last_way);
		all_paths = all_paths->next;
		i++;
	}
	all_paths = tmp;
	ants_moving(all_paths, last_way, params);
}
