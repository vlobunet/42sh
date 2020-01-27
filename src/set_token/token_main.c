/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:26:51 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 18:26:52 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	set_first_token(t_token *head)
{
	char *tmp;

	if (head->content[0] == '\'' || head->content[0] == '"')
	{
		tmp = ft_strndup(head->content + 1, (int)ft_strlen(head->content) - 2);
		ft_strdel(&head->content);
		head->content = ft_strdup(tmp);
		ft_strdel(&tmp);
		head->type = 1;
	}
}

void	check_prev_token(t_token *hed, int flag)
{
	if (ft_strequ(hed->content, ")") && flag)
	{
		hed->type = flag + 1;
		flag = 0;
	}
	else if (hed->prev->type == 1 || hed->prev->type == 17)
		hed->type = 17;
	else if (hed->prev->type == ASSIGN || hed->prev->type == P_SUBST ||
		hed->prev->type == SUBSH || hed->prev->type == GRP ||
		hed->prev->type == SEMI || hed->prev->type == PIPE ||
		hed->prev->type == OR || hed->prev->type == AND)
		hed->type = 1;
	else if (ft_is_dir(hed->prev->type))
		hed->type = 16;
}

void	set_all_token(t_token *hed, int flag)
{
	while (hed)
	{
		if (hed->type == 24 || hed->type == 26)
			flag = hed->type;
		if (hed->type == 0 && hed->prev)
			check_prev_token(hed, flag);
		else if ((hed->type == 0 || hed->type == 17) && !hed->prev)
			hed->type = 1;
		if (hed->type == ASSIGN && hed->prev && hed->prev->type == 1
			&& (ft_strequ(hed->prev->content, "export") ||
				ft_strequ(hed->prev->content, "alias")))
			hed->type = 17;
		hed = hed->next;
	}
}

void	check_token_lst(t_token **lst)
{
	t_token	*tmp;
	char	*filename;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp && tmp->next && tmp->next->next)
	{
		if (tmp->next->type == 10 && tmp->next->next)
		{
			filename = ft_strdup(run_heredoc(tmp->next->next->content));
			ft_strdel(&tmp->next->next->content);
			tmp->next->next->content = ft_strdup(filename);
			tmp->next->next->type = 16;
			tmp->next->type = 6;
			ft_strdel(&tmp->next->content);
			tmp->next->content = ft_strdup("0");
			ft_strdel(&filename);
		}
		tmp = tmp->next;
	}
	g_sel.f = 0;
}

int		token_main(char *str, t_token **lst, int s, int i)
{
	t_token *tmp;

	if (!str || is_empty(str))
		return (0);
	while (s > 0 && *(str + i))
	{
		if ((s = get_token_size(str + i)) == -1)
		{
			ft_strdel(&str);
			return (0);
		}
		tmp = creat_token(str + i, s, NULL);
		*(str + i) != 32 ?
		add_token_lst(lst, tmp) : delete_token(tmp);
		i = i + s;
	}
	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
	check_token_lst(lst);
	set_all_token(*lst, 0);
	set_quote_token(lst, NULL);
	return (validity_test(lst, NULL, NULL));
}
