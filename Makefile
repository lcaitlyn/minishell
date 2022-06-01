NAME		=	minishell

LIBFT_A		=	libft.a
LIBFT_H		=	libft.h
LIBFT_DIR	=	./libft/
LIBFT_INC	=	libft/inc
LIBFT		=	-L libft -l ft -I libft/inc/

SRCS		= 	minishell.c\
				libft_lcaitlyn/ft_strlen.c \
				libft_lcaitlyn/ft_strcmp.c\
				libft_lcaitlyn/ft_strnstr.c\
				libft_lcaitlyn/ft_strjoin_f.c\
				libft_lcaitlyn/ft_split.c\
				libft_lcaitlyn/ft_substr.c\
				libft_lcaitlyn/ft_strchr.c \
				libft_lcaitlyn/ft_strindex.c\
				libft_lcaitlyn/ft_atoi.c\
				libft_lcaitlyn/ft_itoa.c\
				lists/ft_listnew.c \
				lists/ft_listadd.c \
				lists/ft_listclear.c \
				lists/ft_listlast.c\
				get_next_line/gnl.c\
				signals/signal.c\
				ft_exec.c name.c commands/pwd.c\
				commands/cd.c action.c commands/ls.c\
				shell_init.c\
				parser/parser.c

OBJ			=	$(SRCS:%.c=%.o)

CFLAGS		=	-Wall -Wextra -Werror -g

.PHONY		:	all clean fclean re

all			:	$(LIBFT_A) $(NAME)

%.o			:	%.c
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

re			:	fclean all

run:	re
		./minishell
