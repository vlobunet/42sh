/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:28:32 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 17:29:35 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	paste_res(int size_mess, char *lcmd, char *rcmd, char *r)
{
	char	*tmp;
	int		i;

	if (!r)
		return ;
	i = 0;
	lcmd = (g_sel.cmd ? ft_strndup(g_sel.cmd, g_sel.pos[2]) : NULL);
	rcmd = (g_sel.cmd ? ft_strdup(g_sel.cmd + g_sel.pos[2]) : NULL);
	ft_strdel(&g_sel.cmd);
	tmp = (lcmd ? ft_strjoin(lcmd, r) : ft_strdup(r));
	g_sel.cmd = (rcmd ? ft_strjoin(tmp, rcmd) : ft_strdup(tmp));
	while (r[i])
		print_key(r[i++], 1);
	i = 0;
	while (rcmd && rcmd[i])
		print_key(rcmd[i++], 1);
	while (i--)
		go_left(1, size_mess);
	ft_strdel(&tmp);
	ft_strdel(&lcmd);
	ft_strdel(&rcmd);
}

char	*token_src_2(char *str, t_token *lst)
{
	int		size_token;
	int		i;
	char	*res;

	size_token = 1;
	i = 0;
	if (!str)
		return (NULL);
	while (size_token > 0 && *(str + i))
	{
		size_token = get_token_size(str + i);
		*(str + i) != 32 ?
		add_token_lst(&lst, creat_token(str + i, size_token, NULL)) : 0;
		i = i + size_token;
	}
	res = ft_strdup(lst->content);
	ft_tokdel_all(&lst);
	ft_strdel(&str);
	return (res);
}

char	*find_cmd(char *str)
{
	t_history	*cur;
	int			size;

	if (!g_sel.story)
		return (NULL);
	cur = g_sel.story;
	size = ft_strlen(str);
	while (cur)
	{
		if (!ft_strncmp(str, cur->content, size))
			return (cur->content);
		cur = cur->next;
	}
	return (NULL);
}

void	check_negation(int size_mess, char *left, char *r, char *t)
{
	int		i;

	if (!chek_cmd(left = ft_strndup(g_sel.cmd, g_sel.pos[2])))
		return ((void)ft_strdel(&left));
	t = token_src_2(ft_strjoin(left, " "), NULL);
	if (t && t[0] == '!' && ft_strlen(t) > 1)
	{
		(t[1] == '!') ? r = get_cmd(1, 0) : 0;
		(ft_isdigit(t[1])) ? r = get_cmd(2, get_id(t)) : 0;
		(ft_isalpha(t[1])) ? r = find_cmd(t + 1) : 0;
		(!ft_isalpha(t[1]) && !ft_isdigit(t[1])) ? r = NULL : 0;
		if (r)
		{
			i = ft_strlen(t);
			while (i--)
				g_sel.cmd = del_sumb(g_sel.cmd, size_mess, 0, NULL);
			paste_res(size_mess, NULL, NULL, r);
		}
	}
	ft_strdel(&left);
	ft_strdel(&t);
}
