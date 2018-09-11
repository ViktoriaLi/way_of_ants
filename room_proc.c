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

intmax_t		long_main_atoi(const char *str, int i, int sign)
{
	intmax_t	tmp;
	intmax_t	res;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = res * 10 + sign * (str[i] - '0');
		if (tmp / 10 != res && sign == -1)
			return (0);
		if (tmp / 10 != res && sign == 1)
			return (-1);
		res = tmp;
		i++;
	}
	return (res);
}

intmax_t				ft_long_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (long_main_atoi(str, i, sign));
}

void		comment_between_commands(t_params *params)
{
	while (get_next_line(0, &params->buf) > 0 && params->buf[0] == '#'
		&& !ft_strstr(&params->buf[2], "start") &&
		!ft_strstr(&params->buf[2], "end"))
	{
		add_str_to_list(params);
		ft_strdel(&params->buf);
	}
}

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
		add_str_to_list(params);
		ft_strdel(&params->buf);
		comment_between_commands(params);
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
	if (((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		|| (((*params).buf[i] == '+' || (*params).buf[i] == '-')
		&& (*params).buf[i + 1] >= '0' && (*params).buf[i + 1] <= '9'))
		new_room->x = ft_long_atoi(&params->buf[i]);
	else
		return (0);
	while ((*params).buf[i] == '+' || (*params).buf[i] == '-' ||
		((*params).buf[i] >= '0' && (*params).buf[i] <= '9'))
		i++;
	if ((*params).buf[i++] != ' ')
		return (0);
	if (ft_strrchr((*params).buf, ' ') - ft_strchr((*params).buf, ' ') > 11)
		return (0);
	if (((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		|| (((*params).buf[i] == '+' || (*params).buf[i] == '-')
		&& (*params).buf[i + 1] >= '0' && (*params).buf[i + 1] <= '9'))
		new_room->y = ft_long_atoi(&params->buf[i]);
	else
		return (0);
	while ((*params).buf[i] == '+' || (*params).buf[i] == '-' ||
		((*params).buf[i] >= '0' && (*params).buf[i] <= '9'))
		i++;
	if ((*params).buf[i] || new_room->x > 2147483647
		|| new_room->y > 2147483647 || new_room->x < -2147483648
		|| new_room->y < -2147483648)
		return (0);
	if (&params->buf[i] - ft_strrchr((*params).buf, ' ') > 11)
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
		2147483647 || new_room->x < -2147483648
		|| new_room->y < -2147483648 || !if_repeat_coords(head, new_room->x, new_room->y))
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
