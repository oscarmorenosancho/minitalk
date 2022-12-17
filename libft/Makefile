# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 11:10:43 by omoreno-          #+#    #+#              #
#    Updated: 2022/12/14 11:58:22 by omoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
SRC := ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strncmp.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_memchr.c\
	ft_strnstr.c\
	ft_atoi.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c

SRCB := ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstmap_bonus.c

SRCGNL := get_next_line_utils.c\
		get_next_line.c

SRCX := ft_copy_pos.c\
	ft_linelen.c\
	ft_lstdeletewhere.c\
	ft_lstreverse.c\
	ft_every_in_line.c\
	ft_log_error.c\
	ft_lstevery.c\
	ft_lstrreduce.c\
	ft_findfirst_with_pos.c\
	ft_lstdeletenode.c\
	ft_lstfindfirst.c\
	ft_strreduce.c\
	ft_str_merge.c\
	ft_str_join_char.c

LIBFT_PATH := libft/
SRC_PATH := src/
BONUS_PATH := src_bonus/
GNL_PATH := get_next_line/
X_PATH := src_extra/

SRC_F := $(addprefix $(SRC_PATH), $(SRC))
SRCB_F := $(addprefix $(BONUS_PATH), $(SRCB))
SRCGNL_F := $(addprefix $(GNL_PATH), $(SRCGNL))
SRCX_F := $(addprefix $(X_PATH), $(SRCX))

SRC_FP := $(addprefix $(LIBFT_PATH), $(SRC_F))
SRCB_FP := $(addprefix $(LIBFT_PATH), $(SRCB_F))
SRCGNL_FP := $(addprefix $(LIBFT_PATH), $(SRCGNL_F))
SRCX_FP := $(addprefix $(LIBFT_PATH), $(SRCX_F))

OBJ := $(SRC_F:.c=.o)
OBJB := $(SRCB_F:.c=.o)
OBJGNL := $(SRCGNL_F:.c=.o)
OBJX := $(SRCX_F:.c=.o)

DEPS := $(SRC_F:.c=.d)
DEPSB := $(SRCB_F:.c=.d)
DEPSGNL := $(SRCGNL_F:.c=.d)
DEPSX := $(SRCX_F:.c=.d)

CC	:= 	gcc
CFLAGS := -Wall -Werror -Wextra -MMD
RM	:= 	rm -f
LIBC	:= 	ar -rcs
HEADER := libft.h 
MAND_H := $(addprefix $(SRC_PATH), libft_mand.h)
BONUS_H := $(addprefix $(BONUS_PATH), libft_bonus.h)
GNL_H := $(addprefix $(GNL_PATH), get_next_line.h)
X_H := $(addprefix $(X_PATH), libft_extra.h)
MAND_HP := $(addprefix $(LIBFT_PATH), $(MAND_H))
BONUS_HP := $(addprefix $(LIBFT_PATH), $(BONUS_H))
GNL_HP := $(addprefix $(LIBFT_PATH), $(GNL_H))
X_HP := $(addprefix $(LIBFT_PATH), $(X_H))
HEADER_FP := $(addprefix $(LIBFT_PATH), $(HEADER)) 

%.o : %.c ${HEADER}
	${CC} ${CFLAGS} -I ${HEADER} -c $< -o $@

all : $(NAME)

-include $(DEPS)
$(NAME) : $(OBJ) $(HEADER) $(MAND_H)
	$(LIBC) $(NAME) $(OBJ)
	@echo $(SRC_FP) $(HEADER_FP) $(MAND_HP) > $(NAME:.a=.d)

-include $(DEPSB)
bonus: $(OBJ) $(OBJB) $(OBJGNL) $(OBJX) $(HEADER) $(MAND_H) $(GNL_H) $(X_H) $(BONUS_H)
	$(LIBC) $(NAME) $(OBJ) $(OBJB) $(OBJX) $(OBJGNL)
	@echo $(SRC_FP) $(SRCB_FP) $(SRCGNL_FP) $(SRCX_FP) \
		$(HEADER_FP) $(MAND_HP) $(BONUS_HP) $(GNL_HP) $(X_HP) > $(NAME:.a=.d)
	@touch $@

clean :
	$(RM) $(OBJ)
	$(RM) $(OBJB)
	$(RM) $(OBJGNL)
	$(RM) $(OBJX)
	$(RM) $(DEPS)
	$(RM) $(DEPSB)
	$(RM) $(DEPSGNL)
	$(RM) $(DEPSX)

fclean : clean
	$(RM) $(NAME)
	$(RM) bonus
	$(RM) *.d

re: fclean all

.PHONY : clean fclean re all
