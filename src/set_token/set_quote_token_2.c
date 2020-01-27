/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:15:37 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/02 18:24:07 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*getintvar(t_intvar *ptr, char *word)
{
	char	*var_join;
	int		size;

	var_join = ft_strjoin(word, "=");
	size = ft_strlen(var_join);
	while (ptr)
	{
		if (ft_strncmp(ptr->var, var_join, size) == 0)
		{
			ft_strdel(&var_join);
			return (ptr->var);
		}
		ptr = ptr->next;
	}
	ft_strdel(&var_join);
	return (NULL);
}

char			*set_dollar(char *str, char *word, char *tmp, char *right)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (str[i++] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '?' || str[i] == '~'))
		size++;
	word = ft_strndup(str, size + 1);
	if (ft_strequ(word, "~"))
	{
		ft_strdel(&word);
		word = ft_strdup("$HOME");
	}
	tmp = ft_strdup(getintvar(g_sel.intvar, word + 1) ?
		(ft_strchr(getintvar(g_sel.intvar, word + 1), '=') + 1) : "");
	right = ft_strdup(str + size + 1);
	ft_strdel(&word);
	word = ft_strjoin(tmp, right);
	ft_strdel(&right);
	ft_strdel(&tmp);
	return (word);
}

static void		skip_backslash(char **old, int *i)
{
	char	*left;
	char	*right;

	left = NULL;
	right = NULL;
	left = ft_strndup(*old, *i);
	if ((*old)[*i + 1] && (*old)[*i + 1] != '$' && (*old)[*i + 1] != '~')
		++*i;
	right = ft_strdup((*old) + *i + 1);
	ft_strdel(old);
	*old = ft_strjoin(left, right);
	ft_strdel(&left);
	ft_strdel(&right);
}

char			*srch_dolllar_char(char *old,
								char *left, char *right)
{
	int		i;

	i = -1;
	while (old[++i])
	{
		if (old[i] == '\\')
			skip_backslash(&old, &i);
		else if (old[i] == '\'')
			while (old[++i] && old[i] != '\'')
				;
		else if (old[i] == '$' || old[i] == '~')
		{
			left = ft_strndup(old, i);
			right = set_dollar(old + i, NULL, NULL, NULL);
			ft_strdel(&old);
			old = ft_strjoin(left, right);
			ft_strdel(&right);
			ft_strdel(&left);
		}
	}
	return (old);
}

t_token			*creat_new_token(char *cont, int type)
{
	t_token		*t;

	t = (t_token *)malloc(sizeof(t_token));
	t->type = type;
	t->content = ft_strdup(cont);
	t->sel = 0;
	t->prev = NULL;
	t->next = NULL;
	return (t);
}
