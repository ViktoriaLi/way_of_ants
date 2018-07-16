/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 10:56:38 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/16 10:56:41 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*void del_farm(t_room *rooms)
{
	t_room *rooms
}*/

int make_rooms_with_links(t_room *rooms, t_link *links, t_params *params)
{
	t_room_list *farm;
	t_room_list *head;

	if (!(farm = (t_room_list *)malloc(sizeof(t_room_list))))
		exit (0);
	head = farm;
	while (rooms)
	{
		farm->room = rooms;
		if (rooms->next)
		{
			if (!(farm->next = (t_room_list *)malloc(sizeof(t_room_list))))
			{
				exit (0);
			}
		}
		else
			farm->next = NULL;
		rooms = rooms->next;
		farm = farm->next;
	}
	farm = head;
	if (!add_links(&farm, links, params))
		exit (0);
	return (1);
}

int create_links(t_room_list **farm, t_link *links)
{
	t_room_list	*tmplist1;
	t_room	*link;
	t_room	*head;
	t_room_list	*list;

	tmplist1 = NULL;
	head = NULL;
	link = NULL;
	list = *farm;
	while (list)
	{
		if (ft_strcmp(list->room->name, links->first) == 0)
			head = list->room;
		if (ft_strcmp(list->room->name, links->second) == 0)
			link = list->room;
		list = list->next;
	}
	if (!head || !link)
		return (0);
	if (!(tmplist1 = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmplist1->next = head->links;
	head->links = tmplist1;
	tmplist1->room = link;
	if (!(tmplist1 = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmplist1->next = link->links;
	link->links = tmplist1;
	tmplist1->room = head;
	return (1);
}

int add_links(t_room_list **farm, t_link *links, t_params *params)
{

	while (links)
	{
		create_links(farm, links);
		links = links->next;
	}
	search_way(*farm, params);
	return (1);
}

int	save_link(t_link **head, t_params *params)
{

	int i;
	t_link	*newelem;

	i = 0;
	newelem = NULL;
	if (!(newelem = (t_link *)malloc(sizeof(t_link))))
		return (0);
	if ((*params).buf[0] == '#' || !ft_strchr((*params).buf, '-'))
		return (0);
	while ((*params).buf[i] && (*params).buf[i] != '-')
		i++;
	newelem->first = ft_strsub((*params).buf, 0, i);
	i++;
	if (!(*params).buf[i])
		return (0);
	newelem->second = ft_strsub((*params).buf, i, ft_strlen((*params).buf - 1 + 1));
	newelem->next = *head;
	*head = newelem;
	ft_printf("%s\n", (*params).buf);
	return (1);
}
