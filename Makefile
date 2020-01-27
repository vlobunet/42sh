NAME		= 42sh
SRCS		= src/scanf/history_func.c \
			  src/scanf/key_func.c \
			  src/scanf/scanf_src.c \
			  src/scanf/up_do_le_nd.c \
			  src/scanf/scanf.c \
			  src/scanf/myquote.c\
			  src/scanf/line_editing.c \
			  src/scanf/set_negation.c\
			  src/scanf/negation.c\
			  src/scanf/get_next_line.c \
			  src/scanf/get_next_line_src.c \
			  src/scanf/if_back_slash.c \
			  \
			  src/set_token/src_token.c\
			  src/set_token/token_size.c\
			  src/set_token/token_main.c \
			  src/set_token/run_heredoc.c  \
			  src/set_token/check_token.c \
			  src/set_token/check_token_src.c \
			  src/set_token/validity_test.c \
			  src/set_token/validity_test_src.c \
			  src/set_token/size_src.c \
			  src/set_token/set_quote_token.c \
			  src/set_token/set_quote_token_2.c \
			  src/set_token/create_new_token_line.c \
			  src/set_token/alias_func.c \
			  src/set_token/unalias_func.c \
			  src/set_token/set_alias_func.c \
			  src/set_token/set_token_src.c \
			  \
			  src/signal/main_signal.c\
			  \
			  src/main/ft_printmessage.c\
			  src/main/set_mode.c \
			  src/main/main_42sh.c \
			  src/main/lst_func.c \
			  src/main/intro.c \
			  src/main/init_process_group.c \
			  src/main/ft_setenv.c \
			  src/main/copy_env.c \
			  \
			  src/error/error_1.c \
			  src/error/error_2.c \
			  src/error/error_3.c \
			  \
			  src/tree/run_tree.c \
			  src/tree/find_command.c \
			  src/tree/job_control1.c  \
			  src/tree/job_control2.c  \
			  src/tree/job_control3.c  \
			  src/tree/handle_redirections.c  \
			  src/tree/help_functions.c  \
			  src/tree/exec_child.c  \
			  src/tree/run_pipeline.c \
			  src/tree/run_pipeline_help.c  \
			  \
			  src/exec/run_token_cmd.c 	\
			  src/exec/parser.c 	\
			  src/exec/parser_help.c 	\
			  src/exec/find_substitutions.c  	\
			  src/exec/get_pipeline.c  	\
			  src/exec/get_pipeline_help.c  	\
			  src/exec/build_tree.c 	\
			  src/exec/command_substitution.c	\
			  src/exec/process_substitution.c  	\
			  src/exec/token_functions.c \
			  src/exec/tree_functions.c \
			  src/exec/get_subtree.c \
			  src/exec/get_redirections.c  \
			  src/exec/run_env.c \
			  src/exec/run_cd.c \
			  src/exec/run_echo.c \
			  \
			  src/autocomplete/autocoplete.c \
			  src/autocomplete/autocoplete_src1.c \
			  src/autocomplete/autocoplete_src2.c \
			  \
			  src/select/select_main.c \
			  src/select/select_src.c \
			  \
			  src/builtin/intern_variables.c \
			  src/builtin/check_builtins.c \
			  src/builtin/jobs_builtin.c \
			  src/builtin/jobs_builtin_2.c \
			  src/builtin/echo.c \
			  src/builtin/type.c \
			  src/builtin/fc.c \
			  src/builtin/ft_test.c \
			  src/builtin/ft_hash.c \
			  src/builtin/ft_hash_2.c \
			  src/builtin/ft_hash_3.c \
			  src/builtin/fc_pars_param.c \
			  src/builtin/fc_get_cmd_src.c \
			  src/builtin/fc_print_command_editor.c \
			  src/builtin/intern_set_and_unset.c \
			  src/builtin/get_copy_env.c \
			  \
			  src/ft_test/ft_check_flag_1.c \
			  src/ft_test/ft_check_flag_2.c \
			  src/ft_test/make_test.c

OBJS		= $(SRCS:.c=.o)
FLAGS		= -g3 -Wall -Wextra -Werror
INCL 		= -I./includes -I./libft/includes
HEADER		= includes/sh.h
LIB			= libft/libft.a

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[01;38;05;46m
YELLOW      = \033[01;38;05;226m
BLUE        = \033[03;38;05;21m
VIOLET      = \033[01;38;05;201m
CYAN        = \033[1;36m
WHITE       = \033[01;38;05;15m
RES			= \033[m


all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@gcc -o $(NAME) $(FLAGS) $(OBJS) $(LIB) -ltermcap
		@echo  "\b$(YELLOW) : OK$(RES)"

%.o: %.c $(HEADER)
	@gcc -c $(FLAGS) $(INCL) -o $@ -c $<
	@echo  "$(YELLOW)█$(RES)\c)"

$(LIB):
	@echo  "$(GREEN)Compiling: $(WHITE)libft$(RES)$(YELLOW) : $(RES)\c)"
	@make -C libft
	@echo  "$(GREEN)Compiling: $(WHITE)42sh $(RES)$(YELLOW) : $(RES)\c)"

clean:
	@make -C libft clean
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME) $(OBJS)
	@make -C libft fclean

re: fclean $(NAME)
