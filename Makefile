NAME		=	minishell

SRCS		= 	minishell.c\
				libft/ft_strlen.c libft/ft_strcmp.c libft/ft_strnstr.c\
				libft/ft_strjoin.c libft/ft_split.c libft/ft_substr.c\
				libft/ft_strchr.c libft/ft_strindex.c libft/ft_atoi.c\
				libft/ft_itoa.c\
				lists/ft_lstnew.c lists/ft_lstadd.c lists/ft_lstclear.c\
				lists/ft_lstlast.c lists/ft_lstprint.c\
				get_next_line/gnl.c\
				signals/signal.c\
				commands/pwd.c commands/cd.c commands/export.c\
				ft_exec.c name.c action.c\
				shell_init.c\
				

OBJ			=	$(SRCS:%.c=%.o)

FLAGS		=	-g #-Wall -Wextra -Werror

.PHONY		:	all clean fclean re

all			:	$(NAME)

%.o			:	%.c
					@gcc $(FLAGS) -c $< -o $@

$(NAME)		:	$(OBJ)
					@gcc $(FLAGS) -o $(NAME) $(OBJ) -lreadline

clean		:	
					@rm -f $(OBJ)

fclean		:	clean
					@rm -f $(NAME)

re			:	fclean all
