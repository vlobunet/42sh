/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:42:16 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 16:42:17 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TEST_H
# define FT_TEST_H

# include "./sh.h"

int		size_array(char **args);
void	ft_free_test(char **av);
int		make_test(char **args, char **param);
int		ft_check_flag(char *args, char *val, char *val2);
int		ft_check_flag_1(char *args, char *val, char *val2);
int		ft_check_flag_2(char *args, char *val, char *val2);
int		ft_check_flag_3(char *args, char *val, char *val2);
int		ft_check_flag_4(char *args, char *val, char *val2);
int		ft_check_flag_5(char *args, char *val, char *val2);
int		ft_check_flag_6(char *args, char *val, char *val2);
int		ft_check_flag_7(char *args, char *val, char *val2);
int		ft_check_flag_8(char *args, char *val, char *val2);
int		ft_test(char **av);

#endif
