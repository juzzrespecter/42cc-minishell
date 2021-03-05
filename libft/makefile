# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danrodri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 15:49:46 by danrodri          #+#    #+#              #
#    Updated: 2021/03/05 16:08:54 by danrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:		all clean fclean re

NAME		= libft.a

SRCS		= ft_memset.c \
			  ft_bzero.c \
			  ft_calloc.c \
			  ft_memcpy.c \
			  ft_memccpy.c \
			  ft_memmove.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_strlen.c \
			  ft_strdup.c \
			  ft_strlcat.c \
			  ft_strlcpy.c \
			  ft_strchr.c \
			  ft_strrchr.c \
			  ft_strnstr.c \
			  ft_strncmp.c \
			  ft_atoi.c \
			  ft_isalpha.c \
			  ft_isdigit.c \
			  ft_isalnum.c \
			  ft_isascii.c \
			  ft_isprint.c \
			  ft_toupper.c \
			  ft_tolower.c \
			  ft_strmapi.c \
			  ft_substr.c \
			  ft_strjoin.c \
			  ft_strtrim.c \
			  ft_split.c \
			  ft_itoa.c \
			  ft_putchar_fd.c \
			  ft_putstr_fd.c \
			  ft_putendl_fd.c \
			  ft_putnbr_fd.c \
			  ft_putchar.c \
			  ft_putstr.c \
			  ft_lltoa_base.c \
			  ft_lstnew.c \
			  ft_lstdelone.c \
			  ft_lstclear.c \
			  ft_lstadd_front.c \
			  ft_lstadd_back.c \
			  ft_lstsize.c \
			  ft_lstiter.c \
			  ft_lstmap.c \
			  ft_lstlast.c \
			  ft_split_str.c \
			  get_next_line.c

SRCS_DIR	= ./srcs/

OBJS		= $(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))

OBJS_DIR	= ./objs/

INC_DIR		= ./includes/

RM			= rm -rf

CFLAGS		= -Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rc $(NAME) $(OBJS)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
			@gcc $(CFLAGS) -c -I$(INC_DIR) $<
			@mkdir -p $(OBJS_DIR)
			@mv -f $(@F) $(OBJS_DIR)

clean:
			@$(RM) $(OBJS_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

