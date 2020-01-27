/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:42:55 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 16:44:29 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include "sh.h"

t_job		*g_current_job;

void		update_jobs(void);
int			job_is_completed(t_job *j);
int			job_is_stopped(t_job *j);
void		run_foreground(t_job *j, int cont);
void		run_background(t_job *j, int cont);
void		wait_for_job(t_job *j);
int			continue_job(t_job *j, int foreground);
void		update_status(void);
int			ft_jobs(char **argv);
int			ft_kill(char **args);
int			ft_fg(char **args);
int			ft_bg(char **args);
void		ft_freecmdlist(t_cmd *list);
void		set_child_signals(t_job *job,
				struct sigaction act, sigset_t set);
void		print_processes(t_job *j, int fd);
void		job_control(t_job *job);
int			check_status(pid_t pid, int status);
void		free_job(t_job *j);
void		job_push_back(t_job *elem);
void		set_job_number(t_job *j);

#endif
