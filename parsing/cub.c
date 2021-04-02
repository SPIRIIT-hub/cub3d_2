/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:33:03 by efarin            #+#    #+#             */
/*   Updated: 2021/04/02 09:55:07 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_next_line.h"
#include "../headers/cub3d.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*liste;

	if (!(liste = malloc(sizeof(t_list))))
		return (NULL);
	liste->content = content;
	liste->next = NULL;
	return (liste);
}

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ok;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	ok = *alst;
	while (ok->next != NULL)
		ok = ok->next;
	ok->next = new;
}

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ok;

	ok = (*lst);
	while (ok != NULL)
	{
		ok = (*lst)->next;
		del((*lst)->content);
		free((*lst));
		(*lst) = ok;
	}
	(*lst) = NULL;
}

int			ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list		*makelst(int fd, t_struct *mstruct)
{
	t_list	*thelist;
	char	*line;
	int		result;
	t_list	*new;

	result = 1;
	line = NULL;
	thelist = NULL;
	while (result == 1)
	{
		result = get_next_line(fd, &line);
		mstruct->i = shouldiskip(line, mstruct, 0);
		if (mstruct->i == 0)
		{
			new = ft_lstnew(line);
			ft_lstadd_back(&thelist, new);
		}
		if (mstruct->i == -1)
		{
			free(line);
			ft_lstclear(&thelist, free);
			return (NULL);
		}
	}
	return (thelist);
}

int			getlenmax(t_list **alst)
{
	int		len;
	t_list	*lst;
	int		lenmax;

	lst = *alst;
	lenmax = 0;
	while (lst->next != NULL)
	{
		len = ft_strlen(lst->content);
		if (len > lenmax)
			lenmax = len;
		lst = lst->next;
	}
	return (lenmax);
}

char	**fromlsttotab(t_list **alst, t_struct *mstruct)
{
	char			**tab;
	int				i;
	int				lenmax;
	t_list			*lst;

	i = 0;
	lst = *alst;
	mstruct->lenmax = getlenmax(&lst);
	if (!(tab = malloc((ft_lstsize(lst) + 1) * sizeof(char *))))
		return (NULL);
	while (lst != NULL)
	{
		if (!(tab[i] = malloc((mstruct->lenmax + 1) * sizeof(char))))
			return (NULL);
		ft_bzero(tab[i], mstruct->lenmax + 1);
		tab[i] = ft_strcpy(tab[i], lst->content, ft_strlen(lst->content));
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**fillthetabwithspaces(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j])
			j++;
		while (j < mstruct->lenmax)
		{
			tab[i][j] = ' ';
			j++;
			if (j == mstruct->lenmax)
				tab[i][j] = '\0';
		}
		i++;
	}
	return (tab);
}

int		checkthefilename(char **arv)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(arv[1]);
	if (len > 1)
		i = len - 1;
	else
		return (-1);
	if (arv[1][i] == 'b')
		if (arv[1][i - 1] == 'u')
			if (arv[1][i - 2] == 'c')
				if (arv[1][i - 3] == '.')
					return (1);
	return (-1);
}

t_struct	*ismapvalid(char **arv, int arc)
{
	int				fd;
	t_list			*lst;
	char			**tab;
	t_struct		*mstruct;

	if (!(mstruct = malloc(sizeof(t_struct))))
		return (NULL);
	structinit(mstruct);
	fd = open(arv[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (checkthefilename(arv) == -1)
		return (NULL);
	lst = makelst(fd, mstruct);
	if (lst == NULL)
		return (NULL);
	tab = fromlsttotab(&lst, mstruct);
	if (tab != NULL)
		tab = fillthetabwithspaces(tab, mstruct);
	if (checkthemap(tab, mstruct) == 1)
		{
			mstruct->map = tab;
			return (mstruct);
		}
	shouldiskip("", mstruct, 1);
	return (NULL);
}

// int		main(int arc, char **arv)
// {
// 	char **tab;
// 	int i;
// 	int	j;

// 	i = 0;
// 	if (arc > 0)
// 		tab = ismapvalid(arv, arc);
// 	if (tab == NULL)
// 	{
// 		printf("%d\n", -1);
// 		return (0);
// 	}
// 	while (tab[i])
// 	{
// 		j = 0;
// 		while (tab[i][j])
// 		{
// 			printf("%c", tab[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	return (0);
// }
