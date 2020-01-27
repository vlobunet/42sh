/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:57:22 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 15:57:23 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

void		job_push_back(t_job *elem)
{
	t_job *ptr;

	if (!g_jobs)
	{
		g_jobs = elem;
		return ;
	}
	ptr = g_jobs;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = elem;
}

void		set_job_number(t_job *j)
{
	t_job *ptr;

	j->nbr = 1;
	ptr = g_jobs;
	while (ptr)
	{
		if (j != ptr && j->nbr >= ptr->nbr)
			j->nbr++;
		ptr = ptr->next;
	}
}

void		reset_fd(void)
{
	dup2(g_sel.fd[0], 0);
	dup2(g_sel.fd[1], 1);
	dup2(g_sel.fd[2], 2);
}

static char	*get_result(char **varname, char **value, char **result)
{
	char	*tmp;

	*result = ft_strjoin(*varname, "=");
	tmp = ft_strjoin(*result, *value);
	ft_strdel(value);
	ft_strdel(result);
	*result = tmp;
	tmp = NULL;
	return (*result);
}

char		*save_intvar(char *newvar, char **varname, enum e_exp *exp)
{
	char	*value;
	char	*result;
	int		i;

	i = 0;
	while (newvar[i])
	{
		if (newvar[i] == '=')
			break ;
		++i;
	}
	if (!newvar[i])
	{
		*varname = newvar;
		newvar = NULL;
	}
	else
		*varname = ft_strndup(newvar, i);
	value = ft_strdup(get_intvar(*varname, exp));
	if (!value)
		result = NULL;
	else
		result = get_result(varname, &value, &result);
	return (result);
}
