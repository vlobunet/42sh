/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:44:08 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/06 15:44:10 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		get_command(t_token **tokens, t_cmd **cmd, t_cmd **cur)
{
	int count;
	int i;

	i = 0;
	(*cur)->av = (char**)ft_memalloc(sizeof(char*) *
		((count = count_words(tokens)) + 1));
	(*cur)->prev = *cmd;
	(*cur)->next = NULL;
	(*cur)->out_fd = STDOUT_FILENO;
	if (*cmd)
		(*cmd)->next = *cur;
	while (i < count)
	{
		if (*tokens && (*tokens)->type == P_SUBST)
			(*cur)->av[i] = substitute_process(tokens, *tokens);
		else if (*tokens)
		{
			(*cur)->av[i] = ft_strdup((*tokens)->content);
			*tokens ? *tokens = (*tokens)->next : 0;
		}
		++i;
	}
	(*cur)->av[count] = NULL;
}

static t_cmd	*first_of_list(t_cmd *cur)
{
	while (cur->prev)
		cur = cur->prev;
	return (cur);
}

static int		is_command(t_token **tokens, t_cmd **cmd, t_cmd **cur)
{
	if (*tokens && ((*tokens)->type == CMD || (*tokens)->type == P_SUBST
			|| (*tokens)->type == C_SUBST))
	{
		if (!(*cur = (t_cmd*)ft_memalloc(sizeof(t_cmd))))
		{
			ft_putstr_fd("42sh: out of memory\n", STDERR_FILENO);
			run_exit(NULL);
		}
		get_command(tokens, cmd, cur);
		return (1);
	}
	return (0);
}

static int		is_redirection(t_token **tokens, t_cmd *cur)
{
	if (*tokens && ((*tokens)->type == GREAT || (*tokens)->type == LESS
		|| (*tokens)->type == GGREAT || (*tokens)->type == LESSAND
		|| (*tokens)->type == GREATAND))
	{
		if (!get_redirections(tokens, cur))
		{
			ft_putstr_fd("REDIRECTION ERROR\n", 2);
			return (0);
		}
		return (1);
	}
	return (0);
}

t_cmd			*get_pipeline(t_token **tokens)
{
	t_cmd	*cmd;
	t_cmd	*cur;

	cmd = NULL;
	cur = NULL;
	while (*tokens)
	{
		if (is_command(tokens, &cmd, &cur))
			continue ;
		else if (*tokens && (*tokens)->type == PIPE)
		{
			cmd = cur;
			*tokens = remove_token(*tokens);
			continue ;
		}
		else if (is_redirection(tokens, cur))
			continue ;
		return (first_of_list(cur));
	}
	return (first_of_list(cur));
}
