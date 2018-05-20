#include "lem_in.h"

void	list_push_back(t_list **begin_list, char *content)
{
	t_list	*list;
	t_list	*oneelem;

	list = *begin_list;
	oneelem = ft_lstnew(content, ft_strlen(content));
	if (!list)
	{
		*begin_list = oneelem;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = oneelem;
}

int	room_push_back(t_room **begin_list, char *content)
{
	int i;
	t_room	*list;
	t_room	*oneelem;

	i = 0;
	oneelem = NULL;
	if (!(oneelem = (t_room *)malloc(sizeof(t_room))))
		return (0);
	list = *begin_list;
	while (content[i] != ' ')
		i++;
	ft_printf("5111%s\n", "test");
	ft_printf("5111%d\n", i);
	oneelem->name = ft_strsub(content, 0, i);
	ft_printf("5111%s\n", oneelem->name);
	i++;
	ft_printf("IND%d\n", i);
	if (content[i] >= '0' && content[i] <= '9')
		oneelem->x = ft_atoi(&content[i]);
	else
		return (0);
	ft_printf("222%d \n", oneelem->x);
	while (content[i] >= '0' && content[i] <= '9')
		i++;
	if (content[i] != ' ')
		return (0);
	i++;
	if (content[i] >= '0' && content[i] <= '9')
		oneelem->y = ft_atoi(&content[i]);
	else
		return(0);
	ft_printf("333%d \n", oneelem->y);
	if (!list)
	{
		*begin_list = oneelem;
		return (1);
	}
	while (list->next)
		list = list->next;
	list->next = oneelem;
	return (1);
}


int main(void)
{
	char *buf;
	int count;
	int ants;
	buf = NULL;
	t_list *all_lines;
	t_room *rooms;
	//t_list *head;
	//head = all_lines;
	rooms = NULL;
	count = 0;
	all_lines = NULL;
	ants = 0;
	while (get_next_line(0, &buf))
	{
		if (ft_strcmp(buf, "\n") == 0 || buf[0] == 'L')
		{
			ft_printf("%s\n", "ERROR");
			return (0);
		}

		ft_printf("%s\n", buf);
		if (count == 0)
		{
			ants = ft_atoi(buf);
			count++;
			continue;
		}
		else
			list_push_back(&all_lines, buf);
		ft_printf("ANTS %d\n", ants);
		ft_printf("3111%s\n", "test");
		if (buf[0] != '#' && count != 0)
		{
			if (!room_push_back(&rooms, buf))
			{
				ft_printf("%s\n", "ERROR");
				return (0);
			}
		}
		ft_printf("%s\n", all_lines->content);
		all_lines = all_lines->next;
		free(buf);
		count++;
	}
}