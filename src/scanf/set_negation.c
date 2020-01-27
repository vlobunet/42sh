/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_negation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:32:29 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 17:36:04 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*paste_word(char *str, char *word, size_t pos1, size_t pos2)
{
	char	*ltmp;
	char	*rtmp;
	char	*tmp;
	char	*res;

	if (ft_strlen(str) < pos1 || ft_strlen(str) < pos2 || pos1 > pos2)
	{
		ft_strdel(&str);
		return (NULL);
	}
	ltmp = ft_strndup(str, pos1);
	tmp = ft_strjoin(ltmp, word);
	rtmp = ft_strdup(str + pos2);
	res = ft_strjoin(tmp, rtmp);
	ft_strdel(&ltmp);
	ft_strdel(&tmp);
	ft_strdel(&rtmp);
	ft_strdel(&str);
	return (res);
}

char	*get_cmd(int flag, int id)
{
	t_history	*cur;

	if (!g_sel.story)
		return (NULL);
	cur = g_sel.story;
	if (flag == 1)
		return (cur->content);
	if (flag == 2)
	{
		while (cur && cur->id != id)
			cur = cur->next;
		return (cur ? cur->content : NULL);
	}
	return (NULL);
}

int		get_id(char *str)
{
	int		i;
	int		res;

	i = 1;
	res = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}

char	*set_negation(char *s, char *r)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		ft_strdel(&r);
		(s[i] == '!' && s[i + 1] == '!') ? r = get_cmd(1, 0) : 0;
		(s[i] == '!' && ft_isdigit(s[i + 1]))
			? r = get_cmd(2, get_id(s + i)) : 0;
		(s[i] == '!' && !ft_isalpha(s[i + 1]) && !ft_isdigit(s[i + 1]))
			? r = ft_strdup("") : 0;
		if (s[i] == '!' && !r)
		{
			init_pos();
			ft_putchar_fd('\n', 1);
			ft_err_message(": no such event");
			return (ft_strdel(&s));
		}
		s[i] == '!' ? s = paste_word(s, r, i, i + get_len(s + i)) : 0;
		i = i + ft_strlen(r);
	}
	return (s);
}

int		chek_and_set(long *key, int i, int j, int res)
{
	char	*str;

	while (g_sel.cmd && g_sel.cmd[++j])
		if (g_sel.cmd[j] == '!')
		{
			str = ft_strdup(g_sel.cmd);
			ft_strdel(&g_sel.cmd);
			res_default_settings(g_sel.savetty);
			str = set_negation(str, NULL);
			ft_print_message();
			while (str && str[i])
				print_key(str[i++], 1);
			str ? g_sel.cmd = ft_strdup(str) : 0;
			str ? ft_strdel(&str) : 0;
			res = 1;
			break ;
		}
	*key = 0;
	return (res);
}
