NAME		=	minishell

SRCS		= 	minishell.c\
				libft/ft_strlen.c libft/ft_strcmp.c libft/ft_strnstr.c\
				libft/ft_strjoin.c libft/ft_split.c libft/ft_substr.c\
				libft/ft_strchr.c\
				get_next_line/gnl.c\
				command.c name.c pwd.c\
				cd.c action.c ls.c\
				

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
