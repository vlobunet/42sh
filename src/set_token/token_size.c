/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:21:21 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 18:21:24 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_x(char s)
{
	if (s && (ft_isalpha(s) || ft_isdigit(s) ||
	s == '-' || s == '_' || s == '+' || s == '/' ||
	s == '~' || s == '.' || s == ':' || s == '\\' ||
	s == '$' || s == '#' || s == '!' || s == '?' ||
	s == '=' || s == '%' || s == '*' || s == '@' ||
	s == '^' || s == '\'' || s == '"' || s == '`' ||
	s == '[' || s == ']'))
		return (1);
	return (0);
}

int		get_str_size(char *s, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		while (is_x(s[i]))
			if (s[i] == '\\' && s[i + 1])
				i = i + 2;
			else if (s[i] == '\'' || s[i] == '"' || s[i] == '`')
				i = i + get_str_size(s + i, 2);
			else
				i++;
	}
	else if (flag == 2)
	{
		while (s[i + 1] && s[i + 1] != s[0])
			i = (s[i + 1] == '\\' && s[0] != '\'' ? i + 2 : i + 1);
		i = ((s[i + 1] && s[i + 1] == s[0]) ? i + 2 : i + 1);
	}
	return (i);
}

int		get_token_size(char *s)
{
	int	size;

	size = 0;
	*s == ';' || *s == '\n' || *s == 32 || *s == '(' ||
	*s == ')' || *s == '{' || *s == '}' ? size = 1 : 0;
	(*s == '|' || *s == '&') ? size = get_size(s, 0, 0) : 0;
	ft_isdigit(*s) ? size = get_size(s, 1, 0) : 0;
	(ft_isalpha(*s) || *s == '/' || *s == '-' || *s == '+' || *s == '~' ||
		*s == '.' || *s == '\\' || *s == '$' || *s == '!' || *s == '%' ||
		*s == '*' || *s == '@' || *s == '^' ||
		*s == '\'' || *s == '"' || *s == '`' || *s == '[' ||
		*s == ']') ? size = get_str_size(s, 1) : 0;
	(*s == '>' || *s == '<') ? size = get_redirected(s, 0) : 0;
	return (size);
}

void	delete_token(t_token *tk)
{
	ft_strdel(&tk->content);
	free(tk);
	tk = NULL;
}
