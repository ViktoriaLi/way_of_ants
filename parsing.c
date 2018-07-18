/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 10:56:20 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/16 10:56:22 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static unsigned long long int main_uns_atoi(const char *str, int i)
{
	unsigned long long int tmp;
	unsigned long long int res;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = res * 10 + (str[i] - '0');
		if (tmp / 10 != res)
			return (0);
		if (tmp / 10 != res)
			return (-1);
		res = tmp;
		i++;
	}
	return (unsigned long long int)(res);
}

unsigned long long int	ft_uns_atoi(const char *str)
{
	unsigned int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		i++;
	else if (str[i] == '+')
		i++;
	return (main_uns_atoi(str, i));
}


int main_rooms_saving(int *room_count, t_params *params, t_room **rooms, int which_room)
{
	if (*room_count != 0)
		{
			ft_strdel(&params->buf);
			return (0);
		}
		else
		{
			(*room_count) = 1;
			ft_printf("%s\n", (*params).buf);
			ft_strdel(&params->buf);
			get_next_line(0, &params->buf);
			if (!if_room(params, rooms, which_room))
				return(0);
		}
	return(1);
}

int 	comments_parsing(t_params *params, int *ifstart, int *ifend, t_room **rooms)
{
	if ((*params).buf[1] == '#' && ft_strstr(&params->buf[2], "start"))
	{
		if (main_rooms_saving(ifstart, params, rooms, START_ROOM))
			return(1);
		return(0);
	}
	if ((*params).buf[1] == '#' && ft_strstr(&params->buf[2], "end"))
	{
		if (main_rooms_saving(ifend, params, rooms, END_ROOM))
			return(1);
		return(0);
	}
	else
	{
		ft_printf("%s\n", (*params).buf);
		ft_strdel(&params->buf);
		return(1);
	}
}

int pre_comments_parsing(t_params *params)
{
	if ((*params).buf[1] == '#' && (ft_strstr(&params->buf[2], "start")
	|| ft_strstr(&params->buf[2], "end")))
	{
		ft_printf("%s\n", (*params).buf);
		ft_strdel(&params->buf);
		return (0);
	}
	ft_printf("%s\n", (*params).buf);
	ft_strdel(&params->buf);
	return (1);
}

int ants_saving(t_params *params)
{
	int i;

	i = 0;
	if ((*params).buf[0] < '1' || (*params).buf[0] > '9')
	{
		ft_strdel(&params->buf);
		return (0);
	}
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i] || i > 9)
	{
		ft_strdel(&params->buf);
		return (0);
	}
	(*params).ants = ft_uns_atoi((*params).buf);
	if ((*params).ants > 2147483647)
	{
		ft_strdel(&params->buf);
		return (0);
	}
	ft_printf("%s\n", (*params).buf);
	ft_strdel(&params->buf);
	return (1);
}

int if_not_repeat_room(t_room **head, char *new_room_name)
{
	t_room *tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(new_room_name, tmp->name) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int if_repeat_coords(t_room **head, unsigned long long int x, unsigned long long int y)
{
	t_room *tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	save_room(t_room **head, t_params *params, int which_room)
{
	int i;
	t_room *new_room;

	i = 0;
	if (!(new_room = (t_room *)malloc(sizeof(t_room))))
		return (0);
	new_room->which_room = which_room;
	new_room->links = NULL;
	new_room->enter = NULL;
	new_room->usage = 0;
	while ((*params).buf[i] && (*params).buf[i] != ' ')
		i++;
	new_room->name = ft_strsub((*params).buf, 0, i++);
	if (!if_not_repeat_room(head, new_room->name))
	{
		free(new_room);
		ft_strdel(&params->buf);
		return (0);
	}
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		new_room->x = ft_atoi(&params->buf[i]);
	else
		return (0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i++] != ' ')
		return (0);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		new_room->y = ft_atoi(&params->buf[i]);
	else
		return(0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i])
		return(0);
	if (new_room->x > 2147483647 || new_room->y > 2147483647 ||
		!if_repeat_coords(head, new_room->x, new_room->y))
	{
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

int if_room(t_params *params, t_room **rooms, int which_room)
{
	if (!ft_strchr((*params).buf, '-') && (*params).buf[0] != '#' &&
		ft_strchr((*params).buf, ' ') && save_room(rooms, params, which_room))
	{

		ft_printf("%s\n", (*params).buf);
		ft_strdel(&params->buf);
		return (1);
	}
	ft_strdel(&params->buf);
	return (0);
}
