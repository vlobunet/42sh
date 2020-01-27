/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:58:32 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 14:58:35 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef	int	(*t_pfb) (char**);

typedef enum {
	B_ECHO,
	B_CD,
	B_TYPE,
	B_SET,
	B_UNSET,
	b_EXPORT,
	B_EXIT,
	B_JOBS,
	B_BG,
	B_FG,
	B_KILL,
	B_ALIAS,
	B_UNALIAS,
	B_HISTORY,
	B_FC,
	B_TEST,
	B_HASH,
	B_END,
	BUILT
}	t_built;

typedef struct	s_bset
{
	char		*command;
	t_pfb		function;
}				t_bset;

int				ft_built_exe(char **args, t_built cmd);

#endif
