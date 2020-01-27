/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:47:23 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/02 19:47:27 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FC_H
# define FT_FC_H

# include "./sh.h"

typedef struct			s_param
{
	int					r;
	int					n;
	int					l;
	int					first;
	int					last;
	int					e;
	char				*editor;
}						t_param;

int						ft_get_pr2(t_param *lst_pr, char *param);
int						ft_get_pr1(t_param *lst_pr, char *param, int i);
int						error_param(void);
t_history				**get_cmd_history(t_param p);
void					print_command_editor(t_param p,
								t_history **cmd, int fd);
#endif
