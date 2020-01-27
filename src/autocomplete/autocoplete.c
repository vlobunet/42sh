/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocoplete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:32:31 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 15:32:48 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		chek_cmd(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] == 32)
		i++;
	return (!str[i] ? 0 : 1);
}

void	token_src_1(char *str, t_token **lst)
{
	int	size_token;
	int	i;

	size_token = 1;
	i = 0;
	if (!str)
		return ;
	while (size_token > 0 && *(str + i))
	{
		size_token = get_token_size(str + i);
		*(str + i) != 32 ?
		add_token_lst(lst, creat_token(str + i, size_token, NULL)) : 0;
		i = i + size_token;
	}
	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
	check_token_lst(lst);
	set_all_token(*lst, 0);
	while (*lst && (*lst)->next)
		*lst = (*lst)->next;
}

void	go_to_start_lst(t_list **lst)
{
	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
}

int		lstlen(t_list *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	autocomplete(long key, int size_mess, int i, t_token *t)
{
	t_tmp	tmp;
	int		flag;

	tmp.e = NULL;
	if (!chek_cmd(tmp.left = ft_strndup(g_sel.cmd, g_sel.pos[2])))
		return ((void)ft_strdel(&tmp.left));
	tmp.ws = (tmp.left[g_sel.pos[2] - 1] == 32 ? 1 : 0);
	token_src_1(tmp.left, &t);
	(tmp.ws && (t->type == 1 || t->type == 17)) ? get_fd(&tmp.e, NULL) : 0;
	(!tmp.ws && t && t->type == 17) ? get_fd(&tmp.e, t->content) : 0;
	(!tmp.ws && t && t->type == 1) ? get_bin(&tmp.e, t->content, -1, NULL) : 0;
	tmp.right = ft_strdup(g_sel.cmd + g_sel.pos[2]);
	flag = lstlen(tmp.e);
	while (flag && tmp.e && key == TAB)
	{
		t->type = tmp.ws;
		i = pr_autoc(t, ft_strjoin(" ", tmp.right), tmp.e->name, size_mess);
		tmp.e->next ? tmp.e = tmp.e->next : go_to_start_lst(&tmp.e);
		key = 0;
		read(0, &key, 8);
	}
	free_all(tmp, t);
	check_key(key, size_mess, i);
}
