/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 13:47:44 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/25 13:47:46 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int if_repeat_link(t_link **head, t_link *newelem)
{
	t_link *tmp;

	tmp = *head;
	while (tmp)
	{
		if ((ft_strcmp(newelem->first, tmp->first) == 0 &&
		ft_strcmp(newelem->second, tmp->second) == 0) ||
		(ft_strcmp(newelem->first, tmp->second) == 0 &&
		ft_strcmp(newelem->second, tmp->first) == 0))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int if_corrects_link_names(t_link *newelem, t_room *rooms)
{
	t_room *tmp;
	int if_first;
	int if_second;

	tmp = rooms;
	if_first = 0;
	if_second = 0;
	while (tmp)
	{
		if (ft_strcmp(newelem->first, tmp->name) == 0)
			if_first++;
		if (ft_strcmp(newelem->second, tmp->name) == 0)
			if_second++;
		tmp = tmp->next;
	}
	if (if_first == 1 && if_second == 1)
		return (1);
	return (0);
}

void add_new_link(t_link **head, t_link	*newelem, t_params *params)
{
	if (if_repeat_link(head, newelem))
	{
		if (ft_strcmp(newelem->first, (*params).end) == 0 ||
		ft_strcmp((*params).end, newelem->second) == 0)
			(*params).end_entries++;
		else if (ft_strcmp(newelem->first, (*params).start) == 0 ||
		ft_strcmp((*params).start, newelem->second) == 0)
			(*params).start_exits++;
		newelem->next = *head;
		*head = newelem;
	}
	else
		free(newelem);
	ft_printf("%s\n", (*params).buf);
}

int	save_link(t_link **head, t_params *params, t_room *rooms)
{
	int i;
	t_link	*newelem;

	i = 0;
	newelem = NULL;
	if (!(*params).start || !(*params).end)
		return (0);
	if (!(newelem = (t_link *)malloc(sizeof(t_link))))
		return (0);
	while ((*params).buf[i] && (*params).buf[i] != '-')
		i++;
	newelem->first = ft_strsub((*params).buf, 0, i++);
	if (!(*params).buf[i])
		return (0);
	newelem->second = ft_strsub((*params).buf, i, ft_strlen((*params).buf - 1 + 1));
	if (!if_corrects_link_names(newelem, rooms) ||
	ft_strcmp(newelem->first, newelem->second) == 0)
	{
		free(newelem);
		return (0);
	}
	add_new_link(head, newelem, params);
	return (1);
}
