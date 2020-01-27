/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_token_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:29:27 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/07 14:29:29 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		for_free(char *tmp1, char *tmp2)
{
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
}

static void		add_center(int s, int e, t_token **lst, char *content)
{
	t_token		*center;
	char		*tmp1;

	center = NULL;
	add_token_lst(lst, creat_new_token("`", 30));
	tmp1 = ft_strndup(content + (s + 1), e - s - 1);
	token_main(tmp1, &center, 1, 0);
	(*lst)->next = center;
	center->prev = *lst;
	while ((*lst)->next)
		*lst = (*lst)->next;
	add_token_lst(lst, creat_new_token("`", 31));
	ft_strdel(&tmp1);
}

t_token			*create_new_token_line(int s, int e, char *content)
{
	t_token		*lst;
	char		*tmp1;
	char		*tmp2;

	lst = NULL;
	if (ft_strequ(content, "`"))
		return (NULL);
	tmp1 = ft_strndup(content, s);
	tmp2 = ft_strjoin(tmp1, "\"");
	s > 1 ? add_token_lst(&lst, creat_new_token(tmp2, 17)) : 0;
	for_free(tmp1, tmp2);
	if (s < e)
		add_center(s, e, &lst, content);
	if (content[e + 1] != '\0' && !ft_strequ(content + e + 1, "\""))
	{
		tmp1 = ft_strjoin("\"", content + e + 1);
		add_token_lst(&lst, creat_new_token(tmp1, 17));
		ft_strdel(&tmp1);
	}
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}
