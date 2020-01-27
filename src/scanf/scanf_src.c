/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf_src.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 16:21:41 by vlobunet          #+#    #+#             */
/*   Updated: 2018/07/28 16:21:45 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*full_deletion(char *cmd, int size_mess)
{
	go_to_start_str(size_mess);
	tputs(tgetstr("cd", NULL), 1, printnbr);
	ft_strdel(&cmd);
	return (NULL);
}

char		*del_after_cursor(char *cmd)
{
	char	*str;
	int		size;

	size = (int)ft_strlen(cmd);
	g_sel.pos[2] == size ?
	tputs(tgetstr("bl", NULL), 1, printnbr) : 0;
	tputs(tgetstr("cd", NULL), 1, printnbr);
	str = ft_strndup(cmd, g_sel.pos[2]);
	free(cmd);
	return (str);
}

t_select	*init_sel(void)
{
	t_select	*new;

	new = (t_select *)malloc(sizeof(t_select));
	new->cmd = NULL;
	new->s = 0;
	new->os = 0;
	return (new);
}

int			get_len(char *str)
{
	int		i;

	i = 1;
	if (str[i] == '!')
		i++;
	else if (str[i] && ft_isdigit(str[i]))
		while (str[i] && ft_isdigit(str[i]))
			i++;
	else if (str[i] && ft_isalpha(str[i]))
		while (str[i] && (ft_isdigit(str[i] || ft_isalpha(str[i]))))
			i++;
	return (i);
}
