/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historu_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:24:49 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 17:25:27 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		run_history(char **str)
{
	t_history *cur;
	t_history *res;

	str && *str && *(str + 1) && !ft_strcmp(*(str + 1), "-c")
		? clear_story_lst() : 0;
	if (str && *str && *(str + 1) && ft_strcmp(*(str + 1), "-c"))
		return (print_error_history(*(str + 1)));
	res = g_sel.story;
	while (g_sel.story && g_sel.story->next)
		g_sel.story = g_sel.story->next;
	cur = g_sel.story;
	while (cur)
	{
		ft_putstr_fd("[", 1);
		ft_putnbr_fd(cur->id, 1);
		ft_putstr_fd("] ", 1);
		ft_putendl_fd(cur->content, 1);
		cur = cur->prev;
	}
	g_sel.story = res;
	return (1);
}

void	add_comand_to_story(char *cmd)
{
	t_history *new;

	if (!ft_strcmp(cmd, "history"))
		return ;
	if (g_sel.story)
		while (g_sel.story->prev)
			g_sel.story = g_sel.story->prev;
	if (cmd && *cmd != ' ')
	{
		new = ft_lstnew_el(cmd, (g_sel.story ? g_sel.story->id + 1 : 1));
		if (g_sel.story)
		{
			g_sel.story->prev = new;
			new->next = g_sel.story;
		}
		g_sel.story = new;
		g_sel.real_story = g_sel.story->id;
	}
	return ;
}

char	*history_up(char *cmd, int size_mess)
{
	int	i;

	i = 0;
	if (!g_sel.story)
		return (cmd);
	cmd = full_deletion(cmd, size_mess);
	cmd = ft_strdup(g_sel.story->content);
	if (cmd && *cmd)
		while (cmd[i])
			print_key(cmd[i++], 1);
	g_sel.real_story = g_sel.story->id;
	if (g_sel.story->next)
		g_sel.story = g_sel.story->next;
	return (cmd);
}

char	*history_down(char *cmd, int size_mess)
{
	int	i;

	i = 0;
	if (!g_sel.story)
		return (cmd);
	if (g_sel.story->prev)
	{
		g_sel.story->id != g_sel.real_story ?\
		g_sel.story = g_sel.story->prev : 0;
		g_sel.story->prev ? g_sel.story = g_sel.story->prev : 0;
		cmd = full_deletion(cmd, size_mess);
		cmd = ft_strdup(g_sel.story->content);
		if (cmd && *cmd)
			while (cmd[i])
				print_key(cmd[i++], 1);
		g_sel.real_story = g_sel.story->id;
	}
	else
		cmd = full_deletion(cmd, size_mess);
	return (cmd);
}

char	*cancel(char *cmd)
{
	ft_print_message();
	ft_strdel(&cmd);
	g_sel.pos[2] = 0;
	return (NULL);
}
