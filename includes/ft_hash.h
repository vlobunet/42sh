/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:44:05 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 12:48:33 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "sh.h"

typedef struct		s_hash_tab
{
	char	**path;
	int		count;
}					t_hash_tab;

t_hash_tab			*g_hash_tab;

void				inti_hash_tab(void);
int					ft_hash(char **hash);
void				free_array(char **array);
char				**copy_table(char *add, int size, t_hash_tab *hash_tab);
int					count_size(char **array);
void				set_hash_tab(char *path, t_hash_tab *hash_tab);
void				print_table_row(int size, char symbol);
int					max_len(char **array);
void				print_res(char **tab);
int					search_add(char *add, t_hash_tab *hash_tab);
int					count_size_hash(char **array);
void				print_incor_flag(char *flag);

#endif
