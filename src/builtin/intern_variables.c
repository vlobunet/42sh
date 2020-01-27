/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:36:41 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 18:36:43 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_export_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (1);
}

char		*get_intvar(char *name, enum e_exp *exp)
{
	t_intvar	*ptr;
	size_t		len;

	ptr = g_sel.intvar;
	while (ptr)
	{
		len = ft_strlen(name);
		if (ft_strnequ(name, ptr->var, len) && (ptr->var[len] == '=' ||
			ptr->var[len] == '\0'))
		{
			if (exp)
				*exp = ptr->exp;
			return (ptr->var[len] == '=' ? &ptr->var[len + 1] : &ptr->var[len]);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

void		push_intvar(char *var, enum e_exp is_exported)
{
	t_intvar	*tmp;

	if (var)
	{
		tmp = (t_intvar*)ft_memalloc(sizeof(t_intvar));
		if (!tmp)
		{
			ft_putstr_fd("42sh: Out of memory\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		tmp->var = ft_strdup(var);
		tmp->exp = is_exported;
		tmp->next = g_sel.intvar;
		g_sel.intvar = tmp;
	}
}

void		set_intvar(char *var, enum e_exp is_exp, t_intvar *ptr, size_t n)
{
	if (!var)
		return ;
	while (var[n] != '\0' && var[n] != '=')
		++n;
	ptr = g_sel.intvar;
	while (ptr)
	{
		if (ft_strnequ(var, ptr->var, n) && (ptr->var[n] == '=' ||
			!ptr->var[n]))
		{
			ptr->exp = (ptr->exp == EXPORTED ? EXPORTED : is_exp);
			if (!ft_strequ(var, ptr->var) && var[n] == '=')
			{
				ft_strdel(&ptr->var);
				ptr->var = ft_strdup(var);
			}
			ptr->exp == EXPORTED ? ft_setenv(ptr->var) : 0;
			return ;
		}
		ptr = ptr->next;
	}
	push_intvar(var, is_exp);
	if (is_exp == EXPORTED)
		ft_setenv(var);
}

int			ft_export(char **argv)
{
	int		i;
	int		flag;
	char	*str;

	i = 0;
	flag = 0;
	if (argv[1] && argv[2])
		return (ft_export_error("42sh: export: wrong number of arguments"));
	if (argv[1] && ft_strequ("-p", argv[1]))
		flag = 1;
	str = (flag ? "export " : "");
	if (!argv[1] || flag)
	{
		while (g_sel.m_env[i])
		{
			ft_putstr(str);
			ft_putendl(g_sel.m_env[i]);
			++i;
		}
	}
	else if (argv[1][0] != '-')
		set_intvar(argv[1], EXPORTED, NULL, 0);
	else
		return (ft_export_error("42sh: export: wrong argument"));
	return (0);
}
