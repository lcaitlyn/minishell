NAME		=	minishell

LIBFT_A		=	libft.a
LIBFT_H		=	libft.h
LIBFT_DIR	=	libft/
LIBFT_INC	=	libft/inc
LIBFT		=	-L libft -l ft -I libft/inc/

# Lexer
LEXER_DIR		=	lexer/
LEXER_SRCS		=	insert_env_var.c insert_env_var_utils.c strip_quotes.c\
					split_into_space.c lexer_utils.c lexer.c
LEXER_OBJS		=	$(addprefix $(LEXER_DIR), $(LEXER_SRCS:%.c=%.o))

# Parser
PARSER_DIR		=	parser/
PARSER_SRCS		=	parser.c parser_utils.c prints.c\
					validation_tokens.c free_list_cmd.c check_pipe_end.c
PARSER_OBJS		=	$(addprefix $(PARSER_DIR), $(PARSER_SRCS:%.c=%.o))

# Executor
EXECUTOR_DIR	=	executor/
EXECUTOR_SRCS	=	check_redirs_read.c check_redirs_write.c\
					execute_builtin_cmd.c execute_cmd.c executor.c
EXECUTOR_OBJS	=	$(addprefix $(EXECUTOR_DIR), $(EXECUTOR_SRCS:%.c=%.o))

# Commands
COMMANDS_DIR	=	commands/
COMMANDS_SRCS	=	pwd.c cd.c export.c export_utils.c\
					env.c env_utils.c echo.c unset.c exit.c
COMMANDS_OBJS	=	$(addprefix $(COMMANDS_DIR), $(COMMANDS_SRCS:%.c=%.o))

# Other
SRCS_DIR	=	src/
SRCS		=	minishell.c ft_strindex.c ft_strjoin_f.c my_strnstr.c\
				lists/ft_listclear.c lists/ft_listprint.c\
				get_next_line/gnl.c signals/signal.c\
				ft_exec.c name.c action.c shell_init.c error.c shlvl.c
SRCS_OBJS	=	$(addprefix $(SRCS_DIR), $(SRCS:%.c=%.o))

OBJ			=	$(SRCS_OBJS)\
				$(LEXER_OBJS)\
				$(PARSER_OBJS)\
				$(EXECUTOR_OBJS)\
				$(COMMANDS_OBJS)

CFLAGS	=	-Wall -Wextra -Werror #-g -fsanitize=address

CC		=	cc

.PHONY	:	all clean fclean re

all		:	$(LIBFT_A) $(NAME)

%.o		:	%.c
			@$(CC) $(CFLAGS) -I include -c $< -o $@

$(NAME)	:	$(OBJ)
			@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
			@echo 🤟 Minishell ready! 👺👍

$(LIBFT_A):
			@make -sC $(LIBFT_DIR)

clean	:	
			@rm -f $(OBJ)
			@make clean -sC $(LIBFT_DIR)

fclean	:	clean
			@rm -f $(NAME)
			@make fclean -sC $(LIBFT_DIR)

re		:	fclean all

run		:	all
			@./minishell
