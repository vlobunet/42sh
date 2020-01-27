/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:02:42 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 18:02:45 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

void	scan_arg(char **argp)
{
	char	*tmp;
	size_t	last;

	last = ft_strlen(*argp) - 1;
	if (*argp && (*argp)[0] == '\'' && (*argp)[last] == '\'')
	{
		tmp = ft_strsub(*argp, 1, last - 1);
		ft_strdel(argp);
		*argp = tmp;
	}
	else
		*argp = srch_dolllar_char(*argp, NULL, NULL);
}

int		expand_args(t_tree *node)
{
	char	**argp;
	t_cmd	*cmdp;
	int		i;

	if (node->command)
	{
		cmdp = node->command;
		while (cmdp)
		{
			if (cmdp->av)
			{
				i = 0;
				argp = cmdp->av;
				while (argp[i])
				{
					scan_arg(&argp[i]);
					++i;
				}
			}
			cmdp = cmdp->next;
		}
	}
	return (1);
}

int		handle_var(t_tree *head, int bg, int noreset)
{
	int			ret;
	char		*tmp;
	char		*name;
	enum e_exp	exp;
	t_intvar	*intvar;

	tmp = NULL;
	name = NULL;
	intvar = head->intvar;
	head->intvar = NULL;
	if (intvar->exp == UNIQUE)
		tmp = save_intvar(intvar->var, &name, &exp);
	set_intvar(intvar->var, intvar->exp, NULL, 0);
	ret = run_tree(head, bg, noreset);
	if (intvar->exp == UNIQUE)
	{
		unset_intvar(name);
		if (tmp)
			set_intvar(tmp, exp, NULL, 0);
		ft_strdel(&tmp);
		ft_strdel(&name);
	}
	ft_strdel(&intvar->var);
	free(intvar);
	return (ret);
}

int		handle_grp(t_tree *head, int bg)
{
	int ret;
	int pipefd[2];

	if (head->redir)
		handle_redirections(head->redir);
	if (head->command)
	{
		pipe(pipefd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	ret = run_tree(head->subtree, bg, 1);
	destruction_tree(head->subtree);
	if (head->command)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(g_sel.fd[1], STDOUT_FILENO);
		expand_args(head);
		ret = run_pipeline(head, bg, 0);
		reset_fd();
		return (ret);
	}
	reset_fd();
	return (ret);
}

int		run_tree(t_tree *head, int bg, int noreset)
{
	if (!head)
		return (1);
	sync();
	if (head->intvar)
		return (handle_var(head, bg, noreset));
	if (head->token == SEMI || head->token == BG)
	{
		bg = head->token == BG;
		run_tree(head->left, bg, noreset);
		return (run_tree(head->right, bg, noreset));
	}
	else if (head->token == AND)
		return (run_tree(head->left, bg, noreset)) &&
		run_tree(head->right, bg, noreset);
	else if (head->token == OR)
		return (run_tree(head->left, bg, noreset) ||
			run_tree(head->right, bg, noreset));
	else if (head->token == CMD)
		return (expand_args(head) && run_pipeline(head, bg, noreset));
	else if (head->token == GRP)
		return (handle_grp(head, bg));
	else if (!head->token || head->token == ASSIGN)
		return (1);
	return (0);
}
