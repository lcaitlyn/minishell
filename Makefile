NAME		=	minishell

LIBFT_A		=	libft.a
LIBFT_H		=	libft.h
LIBFT_DIR	=	./libft/
LIBFT_INC	=	libft/inc
LIBFT		=	-L libft -l ft -I libft/inc/

SRCS		= 	minishell.c\
			libft/ft_strindex.c libft/ft_strjoin_f.c\
			lists/ft_listclear.c lists/ft_listprint.c\
			get_next_line/gnl.c\
			signals/signal.c\
			commands/pwd.c commands/cd.c commands/export.c\
			commands/env.c\
			ft_exec.c name.c action.c\
			shell_init.c error.c shlvl.c\
			parser/parser.c

OBJ		=	$(SRCS:%.c=%.o)

CFLAGS		=	-g #-fsanitize=address #-Wall -Wextra -Werror

.PHONY		:	all clean fclean re

all		:	$(LIBFT_A) $(NAME)

%.o		:	%.c
				@gcc $(CFLAGS) -I include -c $< -o $@

$(NAME)		:	$(OBJ)
				@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

$(LIBFT_A)	:
				@make -sC $(LIBFT_DIR)
				@echo Minishell ready!

clean		:	
				@rm -f $(OBJ)
				@make clean -sC $(LIBFT_DIR)

fclean		:	clean
				@rm -f $(NAME)
				@make fclean -sC $(LIBFT_DIR)

re		:	fclean all

run		:	re
				./minishell
