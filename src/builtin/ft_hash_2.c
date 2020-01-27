/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:22:43 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 12:22:57 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"

int		ft_hash(char **hash)
{
	if (count_size_hash(hash) == 0)
		return (1);
	if (hash != NULL && hash[1] != NULL)
	{
		if (ft_strcmp(hash[1], "-d") != 0)
		{
			print_incor_flag(hash[1]);
			return (1);
		}
		if (g_hash_tab->count == 0 && ft_strcmp(hash[1], "-d") == 0)
		{
			g_hash_tab->count = 0;
			return (0);
		}
		if (ft_strcmp(hash[1], "-d") == 0 || g_hash_tab->count != 0)
		{
			g_hash_tab->count = 0;
			free_array(g_hash_tab->path);
			return (0);
		}
	}
	if (g_hash_tab->count != 0)
		print_res(g_hash_tab->path);
	return (0);
}

void	print_res(char **tab)
{
	int		max;
	int		i;

	i = 0;
	max = max_len(tab);
	ft_putstr("<");
	print_table_row(max / 2 + 1, '-');
	ft_putstr("Hash Table");
	print_table_row(max / 2 + 1, '-');
	ft_putstr(">\n");
	while (tab[i] != NULL)
	{
		ft_putstr("|");
		print_table_row(((max - ft_strlen(tab[i])) / 2) + 13 / 2, ' ');
		ft_putstr(tab[i]);
		print_table_row(((max - ft_strlen(tab[i])) / 2) + 13 / 2, ' ');
		ft_putstr("|\n");
		i++;
	}
	ft_putstr("<");
	print_table_row(max + 13, '-');
	ft_putstr(">\n");
}

int		count_size(char **array)
{
	int		i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
	{
		i++;
	}
	return (i);
}

int		max_len(char **array)
{
	int		i;
	int		max;

	i = 0;
	max = ft_strlen(array[0]);
	while (array[i] != NULL)
	{
		if ((int)ft_strlen(array[i]) > max)
			max = ft_strlen(array[i]);
		i++;
	}
	return (max);
}

void	print_table_row(int size, char symbol)
{
	int		i;

	i = 0;
	while (i <= size)
	{
		ft_putchar(symbol);
		i++;
	}
}
