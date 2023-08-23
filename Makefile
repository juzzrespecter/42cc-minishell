.PHONY:	clean fclean re 

SRC = main.c
SRC_BUILTIN = b_cd.c \
			 b_echo.c \
			 b_export.c \
			 b_unset.c \
			 env.c \
			 env_edit_utils.c \
			 exit.c \
			 pwd.c
SRC_CMD = exec_cmd.c \
 			 parsercore.c \
			 pipe.c \
			 select_cmd.c
SRC_UTILS = error_funcs.c \
			 expand_and_control.c \
		 	 input_split.c \
			 signal.c
SRC_PARSER = parser.c \
			 parser2.c \
			 parser_error.c \
			 parser_redir.c \
			 parser_redir2.c \
			 parser_utils.c \
			 parser_utils_2.c \
			 parser_utils_3.c \
			 parser_variable.c
SRC_HISTORY = history.c \
			 history2.c \
			 history_mode.c \
			 line_edit.c \
			 line_edit_history.c

INC = minishell.h \
	  libft.h

DIR         = src/
DIR_BUILTIN = $(DIR)builtin/
DIR_CMD     = $(DIR)cmd/
DIR_UTILS   = $(DIR)utils/
DIR_PARSER  = $(DIR)parser/
DIR_HISTORY = $(DIR)history/

DIR_INC = inc/

DIR_OBJ = obj/

OBJ_MAIN    = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC))
OBJ_BUILTIN = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_BUILTIN))
OBJ_CMD     = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_CMD))
OBJ_UTILS   = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_UTILS))
OBJ_PARSER  = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_PARSER))
OBJ_HISTORY = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_HISTORY))

OBJ = $(OBJ_MAIN) \
	  $(OBJ_BUILTIN) \
	  $(OBJ_CMD) \
	  $(OBJ_UTILS) \
	  $(OBJ_PARSER) \
	  $(OBJ_HISTORY)

LIBFT	= libft/libft.a
LIB     = -L libft -lft -ltermcap

CXX      = clang
CXXFLAGS = -Wall -Werror -Wextra

NAME	= minishell

debug:	CXXFLAGS += -fsanitize=address -g3
debug:	fclean all

all:	$(NAME)

$(NAME): $(OBJ)
	cd libft && $(MAKE)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(DIR_OBJ)%.o: $(DIR)%.c
	$(CXX) $(CXXFLAGS) -c $< -I$(DIR_INC)
	@mkdir -pv $(DIR_OBJ)
	@mv -v $(@F) $(@D)

$(DIR_OBJ)%.o: $(DIR_BUILTIN)%.c
	$(CXX) $(CXXFLAGS) -c $< -I$(DIR_INC)
	@mkdir -pv $(DIR_OBJ)
	@mv -v $(@F) $(@D)

$(DIR_OBJ)%.o: $(DIR_CMD)%.c
	$(CXX) $(CXXFLAGS) -c $< -I$(DIR_INC)
	@mkdir -pv $(DIR_OBJ)
	@mv -v $(@F) $(@D)
	
$(DIR_OBJ)%.o: $(DIR_UTILS)%.c
	$(CXX) $(CXXFLAGS) -c $< -I$(DIR_INC)
	@mkdir -pv $(DIR_OBJ)
	@mv -v $(@F) $(@D)

$(DIR_OBJ)%.o: $(DIR_PARSER)%.c
	$(CXX) $(CXXFLAGS) -c $< -I$(DIR_INC)
	@mkdir -pv $(DIR_OBJ)
	@mv -v $(@F) $(@D)

$(DIR_OBJ)%.o: $(DIR_HISTORY)%.c
	@$(CXX) $(CXXFLAGS) -c $< -I$(DIR_INC)
	@mkdir -pv $(DIR_OBJ)
	@mv $(@F) $(@D)

clean:
	@rm -rfv $(DIR_OBJ)
	$(MAKE) -C libft clean

fclean: clean
	@rm -fv $(NAME) 
	$(MAKE) -C libft fclean

re: fclean all

%.o: %.c
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)
