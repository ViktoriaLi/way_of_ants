#include "lem_in.h"

int make_rooms_with_links(t_room *rooms, t_link *links, t_params *params)
{
	t_room_list *farm;
	t_room_list *head;
	//t_room_list *tmp_rooms;

	if (!(farm = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	head = farm;
	while (rooms)
	{
		farm->room = rooms;
		if (rooms->next)
		{
			if (!(farm->next = (t_room_list *)malloc(sizeof(t_room_list))))
				return (0);
		}
		else
			farm->next = NULL;
		rooms = rooms->next;
		farm = farm->next;
	}
	ft_printf("%s\n", "non valid");
	farm = head;
	/*while (farm)
	{
		tmp_rooms = farm->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (farm)->room->name,
			(farm)->room->x, (farm)->room->y, (farm)->room->which_room);
		while (tmp_rooms)
		{
			ft_printf("1links%s x%d y%d dist%d\n", tmp_rooms->room->name,
				tmp_rooms->room->x, tmp_rooms->room->y, tmp_rooms->room->which_room);
			tmp_rooms = tmp_rooms->next;
		}
		farm = farm->next;
	}*/
	if (!add_links(&farm, links, params))
		return (0);
	return (1);
}

int create_links(t_room_list **farm, t_link *links)
{
	t_room_list	*tmplist1;
	t_room_list	*tmplist2;

	tmplist1 = NULL;
	tmplist2 = NULL;

	t_room	*link;
	t_room	*head;
	t_room_list	*list;

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
	if (!(tmplist2 = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmplist2->next = link->links;
	link->links = tmplist2;
	tmplist2->room = head;
	return (1);
}

int add_links(t_room_list **farm, t_link *links, t_params *params)
{
	t_room_list	*tmplist1;
	t_room_list	*list;
	tmplist1 = NULL;
	while (links)
	{
		create_links(farm, links);
		links = links->next;
	}
	ft_printf("%s\n", "non valid");

	list = *farm;
	while (list)
	{
		tmplist1 = list->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (list)->room->name,
			(list)->room->x, (list)->room->y, (list)->room->which_room);
		while (tmplist1)
		{
		ft_printf("1links%s x%d y%d dist%d\n", tmplist1->room->name,
			tmplist1->room->x, tmplist1->room->y, tmplist1->room->which_room);
		tmplist1 = tmplist1->next;
	}
	list = list->next;
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
	if ((*params).buf[0] == '#' || !ft_strchr((*params).buf, '-'))
		return (0);
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
	return (1);
}
