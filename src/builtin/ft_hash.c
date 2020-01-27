/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:11:59 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 12:21:56 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"

void	inti_hash_tab(void)
{
	if (!(g_hash_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab))))
		return ;
	if (!(g_hash_tab->path = (char **)ft_memalloc(sizeof(char *))))
		return ;
	g_hash_tab->count = 0;
}

void	set_hash_tab(char *path, t_hash_tab *g_hash_tab)
{
	int		size_hash_tab;

	if (path == NULL)
		return ;
	size_hash_tab = 0;
	if (g_hash_tab->count == 0)
		size_hash_tab = 0;
	else
		size_hash_tab = count_size(g_hash_tab->path);
	g_hash_tab->count = (size_hash_tab == 0) ? 1 : size_hash_tab;
	size_hash_tab = (size_hash_tab == 0) ? 1 : size_hash_tab + 1;
	if (!search_add(path, g_hash_tab))
		return ;
	g_hash_tab->path = copy_table(path, size_hash_tab, g_hash_tab);
}

int		search_add(char *add, t_hash_tab *g_hash_tab)
{
	int		i;

	i = 0;
	while (g_hash_tab->path[i] != NULL)
	{
		if (ft_strcmp(g_hash_tab->path[i], add) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	**copy_table(char *add, int size, t_hash_tab *g_hash_tab)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	if (g_hash_tab->count != 0)
	{
		while (g_hash_tab->path[i] != NULL)
		{
			if (ft_strlen(g_hash_tab->path[i]) != 0)
			{
				tmp[j] = ft_strdup(g_hash_tab->path[i]);
				j++;
			}
			i++;
		}
	}
	tmp[j] = ft_strdup(add);
	tmp[j + 1] = NULL;
	free_array(g_hash_tab->path);
	free(g_hash_tab->path);
	g_hash_tab->path = NULL;
	return (tmp);
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	array = NULL;
}
