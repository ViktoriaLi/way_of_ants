/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:37:02 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/19 16:38:26 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned long long int	main_uns_atoi(const char *str, int i)
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

int						if_room(t_params *params,
t_room **rooms, int which_room)
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

int						if_not_repeat_room(t_room **head, char *new_room_name)
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

int						if_repeat_coords(t_room **head,
unsigned long long int x, unsigned long long int y)
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
