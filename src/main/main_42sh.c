/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_42sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:54:22 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/02 19:54:25 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

void	ft_freestrarr(char **arr)
{
	int i;

	if (arr == NULL)
		return ;
	i = -1;
	if (*arr)
	{
		while (arr[++i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
	}
	free(arr);
	arr = NULL;
}

void	clear_story_lst(void)
{
	t_history	*head;

	if (!g_sel.story)
		return ;
	while ((g_sel.story)->next)
	{
		head = (g_sel.story)->next;
		ft_strdel(&(g_sel.story)->content);
		(g_sel.story)->next->prev = NULL;
		g_sel.story ? free(g_sel.story) : 0;
		g_sel.story = head;
	}
	(g_sel.story)->content ? ft_strdel(&(g_sel.story)->content) : 0;
	g_sel.story ? free(g_sel.story) : 0;
	g_sel.story = NULL;
}

char	*get_history(int fd)
{
	char	buff[4097];
	char	*pwd;
	char	*line;

	pwd = ft_strjoin(getcwd(buff, 4096), H_FILE);
	fd = open(pwd, O_RDONLY | O_CREAT, 0600);
	while (get_next_line(fd, &line))
	{
		add_comand_to_story(line);
		ft_strdel(&line);
	}
	close(fd);
	return (pwd);
}

void	init_term(char *pwd, char *tmp, t_alias *alias)
{
	g_sel.cmd = NULL;
	g_sel.res = 1;
	init_process_group();
	copy_env();
	pwd = get_history(0);
	set_intvar(tmp = ft_strjoin("HISTORY=", pwd), INTERN, NULL, 0);
	ft_strdel(&tmp);
	ft_strdel(&pwd);
	g_sel.fd[0] = dup(0);
	g_sel.fd[1] = dup(1);
	g_sel.fd[2] = dup(2);
	tcgetattr(g_sel.shell_terminal, &g_sel.savetty);
	creat_alias(&alias);
	inti_hash_tab();
}

int		main(void)
{
	t_token	*tok;

	tok = NULL;
	g_jobs = NULL;
	g_current_job = NULL;
	init_term(NULL, NULL, NULL);
	pre_intron();
	while (1)
	{
		ft_print_message();
		if (token_main(ft_scanf(0, g_sel.strlen_mes, 0), &tok, 1, 0) > 0)
		{
			set_alias(&tok);
			run_token_cmd(&tok);
			ft_strdel(&g_sel.cmd);
		}
		clear_token_lst(&tok);
	}
	clear_story_lst();
	ft_freestrarr(g_sel.m_env);
	res_default_settings(g_sel.savetty);
	return (0);
}
