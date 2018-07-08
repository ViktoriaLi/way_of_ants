#include "lem_in.h"

int comments_parsing(t_params *params, int *ifstart, int *ifend, t_room **rooms)
{
	if (!ft_strstr(&params->buf[2], "start") && !ft_strstr(&params->buf[2], "end"))
	{
		ft_printf("buf3 %s\n", (*params).buf);
		ft_strdel(&params->buf);
		return(1);
	}
	if ((*params).buf[1] == '#' && ft_strstr(&params->buf[2], "start"))
	{
		if (*ifstart != 0)
		{
			ft_printf("%s\n", "ERROR3");
			ft_strdel(&params->buf);
			return (0);
		}
		else
		{
			(*ifstart) = 1;
			ft_printf("buf4 %s\n", (*params).buf);
			ft_strdel(&params->buf);
			get_next_line(0, &params->buf);
			if (!if_room(params, rooms, START_ROOM))
				return(0);
			//ft_printf("buf5 %s\n", *buf);
			(*params).rooms_count++;
			return(1);
		}
	}
	if ((*params).buf[1] == '#' && ft_strstr(&params->buf[2], "end"))
	{
		if ((*params).ants == 0)
		{
			ft_strdel(&params->buf);
			return (0);
		}
		if (*ifend != 0)
		{
			ft_printf("%s\n", "ERROR4");
			ft_strdel(&params->buf);
			return (0);
		}
		else
		{
			(*ifend) = 1;
			ft_printf("buf6 %s\n", (*params).buf);
			ft_strdel(&params->buf);
			get_next_line(0, &params->buf);
			if (!if_room(params, rooms, END_ROOM))
				return(0);
			//ft_printf("buf7 %s\n", *buf);
			(*params).rooms_count++;
			return(1);
		}
	}
	return(1);
}

int pre_comments_parsing(t_params *params)
{
	if ((*params).buf[1] == '#' && (ft_strstr(&params->buf[2], "start")
	|| ft_strstr(&params->buf[2], "end")))
	{
		ft_printf("buf3 %s\n", (*params).buf);
		ft_strdel(&params->buf);
		return(0);
	}
	else
		return (1);
}

int ants_saving(t_params *params)
{
	int i;

	i = 0;
	if ((*params).buf[0] < '1' || (*params).buf[0] > '9')
	{
		ft_strdel(&params->buf);
		ft_printf("%s\n", "ERROR5");
		return (0);
	}
	while ((*params).buf[i] > '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i])
	{
		ft_strdel(&params->buf);
		ft_printf("%s\n", "ERROR6");
		return (0);
	}
		(*params).ants = ft_atoi((*params).buf);
		ft_printf("buf8 %s\n", (*params).buf);
		ft_printf("ants %d\n", (*params).ants);
		ft_strdel(&params->buf);
		return(1);
}

int	save_room(t_room **head, t_params *params, int which_room)
{
	int i;
	t_room *new_room;

	i = 0;
	//list = rooms;
	if (!(new_room = (t_room *)malloc(sizeof(t_room))))
		return (0);
	new_room->which_room = which_room;
	new_room->distance = 0;
	new_room->links = NULL;
	new_room->enter = NULL;
	new_room->usage = 0;
	while ((*params).buf[i] && (*params).buf[i] != ' ')
		i++;
	new_room->name = ft_strsub((*params).buf, 0, i++);
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
	if (i != (int)ft_strlen((*params).buf))
		return(0);

	new_room->next = *head;
	*head = new_room;
	return (1);
}

int if_room(t_params *params, t_room **rooms, int which_room)
{
	if ((*params).buf[0] != '#' && ft_strchr((*params).buf, ' '))
	{
		if (ft_strchr((*params).buf, '-'))
		{
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR1");
			return (0);
		}
		if (!save_room(rooms, params, which_room))
		{
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR2");
			return (0);
		}
		ft_printf("buf1 %s\n", (*params).buf);
		ft_strdel(&params->buf);
		return (1);
	}
	return (0);
}
