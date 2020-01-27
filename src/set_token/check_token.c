/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:51:21 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 14:51:23 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_token1(char *s, int size)
{
	if ((size == 1) && (s[0] == ';' || s[0] == '\n'))
		return (SEMI);
	if (size == 1 && s[0] == '|')
		return (PIPE);
	if (size == 1 && s[0] == '&')
		return (BG);
	if (size == 1 && s[0] == '(')
		return (SUBSH);
	if (size == 1 && s[0] == '}')
		return (GRP_END);
	if (size == 1 && s[0] == '{')
		return (GRP);
	if (size == 1 && s[0] == '=')
		return (ASSIGN);
	if (size > 1 && s[0] == s[1] && (s[0] == '|' || s[0] == '&'))
		return ((s[0] == '|' ? 8 : 9));
	if (size > 1 && s[0] != s[1])
		if (s[0] == '<' && s[1] == '>')
			return (12);
	return (0);
}

int		check_type(int size_token, char *str)
{
	int	ret;

	ret = 0;
	if (size_token == 1 && (*str == '|' || *str == '&' || *str == ';' ||
		*str == '\n' || *str == '~' || *str == '.' || *str == '(' ||
		*str == ')' || *str == '{' || *str == '}'))
		ret = check_token1(str, size_token);
	else if (size_token > 1 && (*str == '|' || *str == '&' || *str == '.'))
		ret = check_token1(str, size_token);
	else if (*str == '"' || *str == '\'' || *str == '`' || *str == '$')
		ret = 17;
	else if (ft_strchr(str, '='))
		ret = ASSIGN;
	else
		ret = 0;
	return (ret);
}

t_token	*creat_token(char *str, int s, char *tmp)
{
	t_token	*t;

	tmp = (str != NULL ? ft_strndup(str, s) : NULL);
	t = (t_token *)ft_memalloc(sizeof(t_token));
	if (tmp && !check_token3(&t, tmp, (int)ft_strlen(tmp), 0))
	{
		t->type = check_type((int)ft_strlen(tmp), tmp);
		t->content = ft_strdup(tmp);
	}
	ft_strdel(&tmp);
	t->sel = 0;
	t->prev = NULL;
	t->next = NULL;
	return (t);
}
