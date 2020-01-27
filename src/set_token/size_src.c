/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_src.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 11:31:26 by vlobunet          #+#    #+#             */
/*   Updated: 2018/08/15 11:36:03 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	pars_error(void)
{
	ft_putendl_fd("PARS ERROR", 2);
	return (-1);
}

int	get_redirected_src(char *s, int i)
{
	if (((s[i] == '>' || s[i] == '<') && s[i + 1] == '&' && !s[i + 2]) ||
		(s[i] == '>' && s[i + 1] == '>' && !s[i + 2]) ||
		((s[i] == '>' || s[i] == '<') && !s[i + 1]) ||
		(s[i] == s[i + 1] && (s[i] == '<' || s[i] == '>') && !s[i + 1]) ||
		(i != 0 && (s[i] == '<' || s[i] == '>') && s[i + 1] == '&') ||
		(i != 0 && s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '&') ||
		(s[i] == '<' && s[i + 1] == '<' && !s[i + 2]))
		return (ft_err_message(NULL));
	if ((s[i] == '<' || s[i] == '>') && s[i + 1] == '&')
		return (i + 2);
	if (s[i] == s[i + 1] && (s[i] == '<' || s[i] == '>'))
		return (i + 2);
	if ((s[i] == '<' || s[i] == '>') && (s[i + 1] == '(' || s[i + 1] == '&'))
		return (i + 2);
	if (s[i] == '<' || s[i] == '>')
		return (i + 1);
	return (0);
}

int	get_redirected(char *s, int i)
{
	if (ft_isdigit(s[i]))
	{
		while (ft_isdigit(s[i]))
			i++;
		if ((s[i] == '<' && s[i + 1] == '<') ||
		((s[i] == '<' || s[i] == '>') && s[i + 1] == '&' && !s[i + 2]) ||
		(s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '&' && !s[i + 3]) ||
		((s[i] == '>' || s[i] == '<') && !s[i + 1]) ||
		(s[i] == s[i + 1] && (s[i] == '<' || s[i] == '>') && !s[i + 2]))
			return (ft_err_message(NULL));
		if ((s[i] == '<' || s[i] == '>') && s[i + 1] == '&')
			return (i + 2);
		if (s[i] == s[i + 1] && (s[i] == '<' || s[i] == '>'))
			return (i + 2);
		if ((s[i] == '<' || s[i] == '>') && (s[i + 1] == '(' ||
			s[i + 1] == '&'))
			return (i + 2);
		if (s[i] == '<' || s[i] == '>')
			return (i + 1);
	}
	else
		return (get_redirected_src(s, i));
	return (0);
}

int	get_size(char *s, int flag, int i)
{
	if (flag == 1)
	{
		while (ft_isdigit(s[i]))
			i++;
		if (s[i] == '>')
			return (get_redirected(s, 0));
		else if (s[i] == '<')
			return (i);
		else
			while (s[i] && (ft_isalpha(s[i]) || ft_isdigit(s[i]) ||
			s[i] == '-' || s[i] == '+' || s[i] == '*' || s[i] == '_' ||
			s[i] == '/' || s[i] == '~' || s[i] == '.' || s[i] == ':' ||
			s[i] == '\\' || s[i] == '%' || s[i] == '@' || s[i] == '^' ||
			s[i] == '\'' || s[i] == '"' || s[i] == '`'))
				i++;
		return (i);
	}
	if (s[0] == '&' && s[1] && (s[1] == '<' || s[1] == '>'))
		return (get_redirected(s, 1));
	else if (s[0] == s[1] && (s[0] == '|' || s[0] == '&'))
		return (2);
	else if (s[0] != s[1] && (s[0] == '|' || (s[0] == '&')))
		return (1);
	return (0);
}
