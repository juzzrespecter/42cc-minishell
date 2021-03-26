
SRCS	= main.c parser.c parser2.c parsercore.c parser_utils.c

SRCS	+= input_split.c parser_redir.c parser_redir2.c  

SRCS	+= pwd.c env.c pipe.c signal.c exit.c

SRCS	+= parser_utils_2.c b_echo.c b_export.c b_unset.c b_cd.c env_edit_utils.c exec_cmd.c parser_variable.c parser_error.c search_env.c error_funcs.c expand_and_control.c

LIBFT	= libft/libft.a

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

LIBFT	= libft/libft.a

CLANG	= clang

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -L libft -lft




all:	$(NAME)

.PHONY:	clean fclean re 

$(NAME): $(OBJS)
	cd libft && $(MAKE)
	$(CLANG) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDE)

clean:
	rm -f $(OBJS) $(B_OBJS)
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	cd libft && $(MAKE) fclean

re: fclean all

%.o: %.c
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)
