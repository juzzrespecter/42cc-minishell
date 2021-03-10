
SRCS	= main.c \
		  env.c \
		  signal.c \
		  pwd.c \
		  exit.c \
		  pipe.c \
		  parser.c \
		  parser2.c \
		  input_split.c \
		  parser_redir.c \
		  parser_redir2.c \
		  b_cd.c \
		  b_echo.c \
		  b_export.c \
		  b_unset.c \
		  env_edit_utils.c \
		  exec_cmd.c \
		  janitor.c \
		  parser_error.c \
		  parser_utils.c \
		  parser_variable.c \
		  print_error.c \
		  search_env.c

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

