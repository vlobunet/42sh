/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:44:27 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 15:44:29 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

static void	open_file(t_redirect *redir, int flags, int fd)
{
	if (redir->type == LESS)
	{
		flags |= O_RDONLY;
		if (access(redir->right.filename, F_OK) != NORM)
			ft_putstr_fd("42sh: File open error\n", STDERR_FILENO);
	}
	else
		flags |= O_WRONLY | O_CREAT | (redir->type == GGREAT
			? O_APPEND : O_TRUNC);
	if ((fd = open(redir->right.filename, flags, FILE_PERM)) >= 0)
	{
		dup2(fd, redir->left);
		close(fd);
	}
	else
		ft_putstr_fd("42sh: File open error\n", STDERR_FILENO);
}

void		handle_redirections(t_redirect *redir)
{
	int flags;
	int fd;

	while (redir)
	{
		fd = -1;
		flags = 0;
		if (redir->type == GREATAND || redir->type == LESSAND)
		{
			if (redir->outtype == CLOSED)
				close(redir->left);
			else if (redir->outtype == FD)
			{
				dup2(redir->right.fd, redir->left);
				if (redir->right.fd > STDERR_FILENO)
					close(redir->right.fd);
			}
		}
		else if (redir->type == GREAT || redir->type == GGREAT
			|| redir->type == LESS)
			open_file(redir, flags, fd);
		redir = redir->next;
	}
}

void		ft_freeredirections(t_cmd *cmd)
{
	t_redirect *tmp;

	while (cmd->redir)
	{
		tmp = cmd->redir->next;
		if (cmd->redir->outtype == NAME)
			free(cmd->redir->right.filename);
		free(cmd->redir);
		cmd->redir = tmp;
	}
}
