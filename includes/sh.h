/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:44:55 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 17:13:33 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "libft.h"
# include "builtins.h"
# include "ft_hash.h"
# include <stdlib.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <ftw.h>
# include <unistd.h>
# include <sys/param.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

/*
**╔═══════════════╦═════════════════════════════════════════════════════╗
**║     TOKEN     ║                          KEY                        ║
**╠═══════════════╬═════════════════════════════════════════════════════╣
**║ 1	CMD		  ║	ALT_RT	alt+right		по слову вправо				║
**║ 3	";"		  ║	ALT_LT	alt+left		по слову влево				║
**║ 4	'|"		  ║	HOME	home			в начало					║
**║ 6	"<"		  ║	END		end				в конец						║
**║ 7	">"		  ║	RIGHT	right			по символу вправо			║
**║ 8	'||"	  ║	LEFT	left 			по символу влево			║
**║ 9	'&&"	  ║	UP		up				вверх на 1					║
**║ 10	"<<"	  ║	DOWN	down			вниз на 1					║
**║ 11	">>"	  ║	ESC		esc				очистить или выйти			║
**║ 12	"<>"   *  ║	BACK	backspase 		удалить перед курсором 1	║
**║ 13	"<&"	  ║	TAB		tab				автодополнение				║
**║ 14	">&"	  ║	DEL		del				удалить после курсора все	║
**║ 18	">>&"  *  ║	S_L		shift+left		выделить слева 1 символ		║
**║ 19	"&>"   *  ║	S_R		shift+right		выделить справа 1 символ	║
**║ 20	"&<"   *  ║	S_H		shift+home		выделить до начала строки	║
**║ 21	"&>>"  *  ║	S_E		shift+end		выделить до конца строки	║
**║ 22	"&<<"  *  ║	SA_L	shift+alt+left	выделить левое слово		║
**║ 15	FD_IN	  ║	SA_R	shift+alt+right	выделить правое слово		║
**║ 16	TARGET	  ║	A_A		alt+a			выделить всю строку			║
**║ 17	ARG		  ║	A_CPY	alt+c			копировать					║
**║               ║	A_PST	alt+v			вставить					║
**║               ║	A_CUT	alt+x			вырезать					║
**╚═══════════════╩═════════════════════════════════════════════════════╝
*/

# define CMD 1
# define SEMI 3
# define PIPE 4
# define LESS 6
# define GREAT 7
# define OR 8
# define AND 9
# define HRDC 10
# define GGREAT 11
# define LESSGREAT 12
# define LESSAND 13
# define GREATAND 14
# define GGRAETAND 18
# define ANDGREAT 19
# define ANDLESS 20
# define ANDGGREAT 21
# define ANDLLESS 22
# define FD_IN 15
# define TARGET 16
# define ARG 17
# define BG 23

# define P_SUBST 24
# define P_SUBST_END 25
# define SUBSH 26
# define SUBSH_END 27
# define GRP 28
# define GRP_END 29
# define C_SUBST 30
# define C_SUBST_END 31
# define ASSIGN 32

# define ALT_RT		1130044187
# define ALT_LT		1146821403
# define HOME		4741915
# define END		4610843
# define RIGHT		4414235
# define LEFT		4479771
# define UP			4283163
# define DOWN		4348699
# define ESC		27
# define BACK		127
# define TAB		9
# define C_C 		3
# define DEL		2117294875
# define S_L		74982532143899L
# define S_R		73883020516123L
# define S_H		79380578655003
# define S_E		77181555399451
# define SA_L		19193286420945691
# define SA_R		18911811444235035
# define A_CPY		42947
# define A_PST		10127586
# define A_CUT		8948194
# define A_A		42435
# define H_FILE 	"/.history"

# define LENLIB		16
# define BUFF_SIZE	19

# define STDINN		0
# define STDOUT		1
# define STDERR		2

# define COMPLETED 		1
# define STOPPED 		2
# define ERROR 			-1
# define MUTE 			1
# define NORM 			0

# define FILE_PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

typedef struct			s_gnl
{
	char				*content;
	int					fd;
	struct s_gnl		*prev;
	struct s_gnl		*next;
}						t_gnl;

typedef struct			s_history
{
	char				*content;
	int					id;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

typedef struct			s_alias
{
	char				*name;
	char				*value;
	struct s_alias		*prev;
	struct s_alias		*next;
}						t_alias;

typedef struct			s_intvar
{
	char				*var;
	enum				e_exp
	{
		INTERN,
		EXPORTED,
		UNIQUE
	}					exp;
	struct s_intvar		*next;
}						t_intvar;

typedef struct			s_sel
{
	char				*cmd;
	int					strlen_mes;
	struct termios		savetty;
	int					pos[3];
	char				**m_env;
	t_intvar			*intvar;
	t_history			*story;
	char				*cpy;
	int					real_story;
	int					size_sel;
	int					f;
	int					fd[3];
	int					shell_interactive;
	pid_t				shell_pgid;
	int					shell_terminal;
	int					res;
	t_alias				*alias;
}						t_sel;

typedef struct			s_list
{
	char				*content;
	char				*name;
	int					size;
	struct s_list		*prev;
	struct s_list		*next;
}						t_list;

typedef struct			s_tmp
{
	char				*left;
	char				*right;
	int					ws;
	t_list				*e;
}						t_tmp;
t_sel					g_sel;

typedef struct			s_token
{
	struct s_token		*next;
	struct s_token		*prev;
	int					sel;
	char				*content;
	int					type;
}						t_token;

typedef struct			s_scanf
{
	char				*cmd;
	long				key;
}						t_scanf;

typedef struct			s_lib
{
	int					token;
	int					priority;
}						t_lib;

typedef struct			s_redirect
{
	int					type;
	int					left;
	enum				e_outtype
	{
		FD,
		NAME,
		CLOSED
	}					outtype;
	union				u_right
	{
		int				fd;
		char			*filename;
	}					right;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_tree	t_tree;

typedef struct			s_cmd
{
	int					in_fd;
	int					out_fd;
	pid_t				pid;
	int					status;
	int					state;
	char				**av;
	char				*path;
	enum				e_cmd_type
	{
		REGULAR,
		SUBSHELL
	}					cmd_type;
	t_tree				*subtree;
	t_redirect			*redir;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

struct					s_tree
{
	int					token;
	char				**cmd;
	t_token				*token_or;
	struct s_tree		*subtree;
	struct s_tree		*father;
	struct s_tree		*left;
	struct s_tree		*right;
	t_intvar			*intvar;
	t_cmd				*command;
	t_redirect			*redir;
};

typedef struct			s_select
{
	char				*cmd;
	int					s;
	int					os;
}						t_select;

typedef struct			s_job
{
	pid_t				pgid;
	uint8_t				notified;
	unsigned			nbr;
	t_cmd				*cmds;
	int					state;
	int					bg;
	struct termios		tmodes;
	struct s_job		*next;
}						t_job;

/*
** Helper structure for set_quote_tokin
*/
typedef struct			s_helper
{
	int					i;
	int					size;
	int					start;
	int					end;
}						t_helper;

t_job					*g_jobs;

typedef struct			s_i
{
	char				k;
	int					i;
}						t_i;

void					print_key(char key, int flag);
int						printnbr(int i);
void					ft_printf(char key, char *str, int size_mess);
char					*ft_scanf(int fd, int size_mess, long key);
t_scanf					*new_scanf(int fd, int size_mess);
char					*go_up(char *cmd, int size_mess);
char					*go_down(char *cmd, int size_mess);
void					go_left(int flag, int size_mess);
void					go_right(char *cmd, int flag);
void					go_to_start_str(int size_mess);
void					go_to_end_str(char *cmd);
void					go_to_next_word(char *cmd);
void					go_to_prev_word(char *cmd, int size_mess);
char					*del_previous_word(char *cmd, int size_mess);
char					*line_editing(char *cmd,
									long key, int size_mess, int f);
char					*full_deletion(char *cmd, int size_mess);
char					*del_after_cursor(char *cmd);
char					*del_sumb(char *s1, int size_mess, int flag, char *tmp);
char					*print_sumb(char buff, char *s1, int size_mess);
void					ft_lstadd(t_list **alst, t_list *new_lst);
t_list					*ft_lstnew(char *name, char *path);
t_history				*ft_lstnew_el(char *cmd, int fd);
void					free_lst(t_token *lst);
void					ft_lstdel_all(t_list **lst);
void					ft_tokdel_all(t_token **lst);
char					*get_env(char *env, char **env_g);
struct termios			get_default_settings(void);
void					res_default_settings(struct termios savetty);
void					ft_freestrarr(char **arr);
void					add_comand_to_story(char *cmd);
char					*history_up(char *cmd, int size_mess);
char					*history_down(char *cmd, int size_mess);
char					*cancel(char *cmd);
void					autocomplete(long key, int size_mess,
									int i, t_token *t);
void					if_dquote_cmd(char *str, t_scanf *q, t_i ret, int key);
int						token_main(char *str,
									t_token **lst_token, int s, int i);
t_token					*creat_token(char *str, int s, char *tmp);
void					add_token_lst(t_token **lst_token, t_token *new);
int						get_token_size(char *str);
int						validity_test(t_token **lst,
									t_token *tmp, t_token *prev);
void					clear_token_lst(t_token **tok);
void					ft_print_message(void);
int						run_tree(t_tree *root, int bg, int noreset);
int						set_type(char *content);
int						ft_is_separ(int type);
int						ft_is_dir(int type);
int						ft_isredir(int type);
void					print_error_term(void);
void					print_error_data(int i);
void					print_error_quote(void);
int						ft_err_message(char *s);
void					print_error(char *error);
void					error_arg(char arg);
int						error_unset(char *str);
void					print_error_name_t(void);
char					*set_cmd(char *str);
int						ft_is_error(t_token *tmp, t_token *prev, int *open_br);
t_token					*search_token(t_token *token);
int						run_token_cmd(t_token **tok);
char					*run_get_env(char *env, char **env_g, int flag);
char					*ft_get_env_var(char *str);
int						check_token3(t_token **t, char *str, int s, int i);
void					check_token_lst(t_token **lst);
void					set_all_token(t_token *hed, int flag);
void					check_key(long key, int size_mess, int flag);
int						pr_autoc(t_token *t, char *lstr, char *word,
								int size_mess);
void					get_fd(t_list **lst, char *str);
void					get_bin(t_list **lst, char *str, int i, char **fd);
void					select_start(long key, int size_mess, t_select *sel);
void					select_char(long key, int size_mess, t_select *sel);
void					check_select_key(long key, int size_mess,
										t_select *s, int startpos);
void					paste_select(int size_mess, char *lcmd,
									char *rcmd, char *tmp);
int						get_size(char *str, int flag, int i);
int						get_redirected(char *s, int i);
void					divide_the_string(t_token *t, char *tmp,
										char **cmd, int *i);
void					set_quote_token(t_token **tok, t_token *cur);
char					*set_bquote_ctr(char *str, char *cmd, int i, int j);
char					*get_copy_env(char *needle, int warning);
void					set_intvar(char *var, enum e_exp is_exported,
								t_intvar *ptr, size_t name_len);
void					push_intvar(char *var, enum e_exp is_exported);
int						ft_setenv(char *var);
char					*get_intvar(char *name, enum e_exp *exp);
void					sigwinch_handler(int signum);
int						check_builtins(t_cmd *cmd);
int						check_commands(t_cmd *commands);
int						ft_find(t_cmd *command, int warning);
void					ft_freeredirections(t_cmd *cmd);
t_cmd					*get_pipeline(t_token **tokens);
t_tree					*build_tree(t_tree *head, t_token **tokens);
t_cmd					*get_subtree_as_cmd(t_token **tokens, int tok);
void					reset_fd(void);
char					**substitute_command(t_token **t);
void					destruction_tree(t_tree *root);
void					print_tree(t_tree *ast);
void					creat_alias(t_alias **list);
void					add_aliases(t_alias **list, char *name, char *value);
int						check_alias(char **cmd);
int						check_unalias(char **cmd);
void					set_alias(t_token **hed);
void					check_negation(int size_mess, char *left,
									char *r, char *t);
void					init_pos(void);
int						chek_cmd(char *str);
char					*get_cmd(int flag, int id);
int						get_id(char *str);
int						run_history(char **str);
void					clear_story_lst(void);
int						print_error_history(char *str);
char					*set_backslash_char(char *str, char *cpy, int i, int j);
char					*srch_dolllar_char(char *old, char *left,
										char *right);
char					*set_dollar(char *str, char *word,
								char *tmp, char *right);
char					*getintvar(t_intvar *ptr, char *word);
void					handle_redirections(t_redirect *redir);
void					unset_intvar(char *var);
int						get_next_line(const int fd, char **line);
void					print_all_token(t_token *tok);
t_token					*remove_token(t_token *token);
void					free_all(t_tmp tmp, t_token *t);
int						ft_export_error(char *str);
t_history				**error_get(void);
char					*save_intvar(char *new, char **var, enum e_exp *exp);
void					exec_child(t_cmd *cmd, t_job *job, int builtin);
int						run_pipeline(t_tree *node, int bg, int noreset);
int						make_pipe(t_cmd *cmd, int *fds);
int						init_job(t_tree *node, t_job **job, t_cmd *ptr, int bg);
char					**substitute_command(t_token **tokens);
void					insert_token(t_token **head, char *content, int type);
t_tree					*build_tree(t_tree *head, t_token **tokens);
int						get_redirections(t_token **tokens, t_cmd *cur);
t_tree					*get_subtree_as_tree(t_token **tokens);
t_cmd					*get_subtree_as_cmd(t_token **tokens, int tok);
t_tree					*push_node(t_tree *head, t_tree *node);
t_token					*find_substitutions(t_token **tokens);
char					*substitute_process(t_token **tokens, t_token *tok);
void					if_back_slash(char *str, t_scanf *q);
/*
** for set_quteo_token.c
*/
t_token					*creat_new_token(char *cont, int type);
char					*run_heredoc(char *str);
void					print_all_token(t_token *tok);
t_token					*remove_token(t_token *token);
void					free_all(t_tmp tmp, t_token *t);
int						ft_export_error(char *str);
t_history				**error_get(void);
int						int_error(char *str);
char					*null_error(char *str);
void					init_process_group(void);
int						env_size(char **envp);
void					copy_env(void);
void					ft_lstadd_gnl(t_gnl **alst, t_gnl *new_lst);
t_gnl					*ft_lstnew_gnl(int fd, int buf_size);
void					ft_lstdel_gnl(t_gnl **cur_lst);
t_select				*init_sel(void);
int						get_len(char *str);
int						is_empty(char *str);
int						count_words(t_token **tkn);
void					delete_token(t_token *tk);
t_token					*create_new_token_line(int s, int e, char *content);

/*
**	Builtins
*/
int						ft_cd(char **cmd);
int						run_fc(char **cmd);
int						ft_set(char **argv);
int						ft_unset(char **argv);
int						ft_echo(char **argv);
int						ft_type(char **argv);
int						ft_test(char **av);
int						ft_export(char **argv);
int						run_exit(char **argv);

/*
**	Parser
*/
int						parse(t_token *lookahead, int cmd);
int						check_prev(t_token *lookahead);
int						match_ctrl_operator(t_token **lookahead);
int						match_separator(t_token **lookahead);
int						optredir(t_token **lookahead);
int						optpipe(t_token **lookahead);
t_token					*optargs(t_token *lookahead);
void					pre_intron(void);

#endif
