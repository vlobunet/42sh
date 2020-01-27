/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_print_command_editor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:47:57 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 15:48:01 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

t_tree	*creat_tmp_tree(char **cmd)
{
	t_tree *node;

	if (!(node = (t_tree *)ft_memalloc(sizeof(t_tree))))
		return (NULL);
	node->token = 1;
	node->cmd = NULL;
	node->token_or = NULL;
	node->subtree = NULL;
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	node->intvar = NULL;
	node->redir = NULL;
	if ((node->command = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
	{
		node->command->out_fd = 1;
		node->command->av = cmd;
		node->command->path = NULL;
		node->command->subtree = NULL;
		node->command->redir = NULL;
		node->command->next = NULL;
		node->command->prev = NULL;
	}
	return (node);
}

void	creat_and_run_tree(char *editor)
{
	t_tree	*ast;
	char	**cmd;

	cmd = (char **)ft_memalloc(sizeof(char *) * 3);
	cmd[0] = ft_strdup(editor);
	cmd[1] = ft_strdup("/tmp/.log");
	cmd[2] = NULL;
	ast = creat_tmp_tree(cmd);
	run_tree(ast, 0, 0);
	reset_fd();
	destruction_tree(ast);
}

void	run_new_history(char *line, t_token *tok)
{
	int	fd;

	fd = open("/tmp/.log", O_RDONLY | O_CREAT, 0600);
	while (get_next_line(fd, &line))
	{
		if (token_main(line, &tok, 1, 0) > 0)
		{
			set_alias(&tok);
			run_token_cmd(&tok);
			ft_strdel(&g_sel.cmd);
		}
		clear_token_lst(&tok);
		ft_strdel(&line);
	}
	close(fd);
	unlink("/tmp/.log");
}

void	print_command_editor(t_param p, t_history **cmd, int fd)
{
	fd = open("/tmp/.log", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	close(fd);
	fd = open("/tmp/.log", O_WRONLY | O_CREAT | O_APPEND, 0600);
	while (cmd && *cmd)
	{
		ft_putendl_fd((*cmd)->content, fd);
		*cmd = (*cmd)->next;
	}
	close(fd);
	if (p.e && p.editor)
	{
		if (!ft_strcmp(p.editor, "vi") || !ft_strcmp(p.editor, "nano") ||
			!ft_strcmp(p.editor, "vim") || !ft_strcmp(p.editor, "emacs"))
			creat_and_run_tree(p.editor);
		run_new_history(NULL, NULL);
	}
}
