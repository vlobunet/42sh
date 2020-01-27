/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_substitutions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:59 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/06 16:44:05 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	insert_subst(t_token *prev, t_token **tmp)
{
	char	**arr;
	int		i;
	int		type;

	arr = NULL;
	arr = substitute_command(tmp);
	prev->next = *tmp;
	if (*tmp)
		(*tmp)->prev = prev;
	*tmp = prev;
	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			if (*tmp && ((*tmp)->type == CMD || (*tmp)->type == ARG))
				type = ARG;
			else
				type = CMD;
			insert_token(tmp, arr[i], type);
			++i;
		}
		ft_freestrarr(arr);
	}
}

t_token		*find_substitutions(t_token **tokens)
{
	t_token **tmp;
	t_token *prev;
	t_token *head;

	head = (t_token*)ft_memalloc(sizeof(t_token));
	head->next = *tokens;
	(*tokens)->prev = head;
	tmp = tokens;
	while (*tmp)
	{
		if (*tmp && (*tmp)->type == C_SUBST)
		{
			prev = head;
			while (prev->next != *tmp)
				prev = prev->next;
			insert_subst(prev, tmp);
		}
		*tmp ? *tmp = (*tmp)->next : 0;
	}
	return (head);
}
