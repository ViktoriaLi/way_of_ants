/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 10:56:20 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/19 17:03:12 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main_rooms_saving(int *room_count, t_params *params,
t_room **rooms, int which_room)
{
	if (*room_count != 0)
	{
		ft_strdel(&params->buf);
		return (0);
	}
	else
	{
		(*params).rooms_count++;
		(*room_count) = 1;
		ft_printf("%s\n", (*params).buf);
		ft_strdel(&params->buf);
		get_next_line(0, &params->buf);
		if (!if_room(params, rooms, which_room))
			return (0);
	}
	return (1);
}

int		take_room_params(t_params *params, t_room *new_room)
{
	int	i;

	i = 0;
	while ((*params).buf[i] && (*params).buf[i] != ' ')
		i++;
	new_room->name = ft_strsub((*params).buf, 0, i++);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		new_room->x = ft_uns_atoi(&params->buf[i]);
	else
		return (0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i++] != ' ')
		return (0);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		new_room->y = ft_uns_atoi(&params->buf[i]);
	else
		return (0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i] || new_room->x > 2147483647
		|| new_room->y > 2147483647)
		return (0);
	return (1);
}

int		save_room(t_room **head, t_params *params, int which_room)
{
	t_room	*new_room;

	if (!(new_room = (t_room *)malloc(sizeof(t_room))))
		return (0);
	new_room->which_room = which_room;
	new_room->links = NULL;
	new_room->enter = NULL;
	new_room->usage = 0;
	if (!take_room_params(params, new_room) || !if_not_repeat_room(head,
		new_room->name) || new_room->x > 2147483647 || new_room->y >
		2147483647 || !if_repeat_coords(head, new_room->x, new_room->y))
	{
		ft_strdel(&new_room->name);
		free(new_room);
		ft_strdel(&params->buf);
		return (0);
	}
	if (which_room == START_ROOM)
		(*params).start = new_room->name;
	if (which_room == END_ROOM)
		(*params).end = new_room->name;
	new_room->next = *head;
	*head = new_room;
	return (1);
}
