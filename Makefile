# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 10:34:11 by omoreno-          #+#    #+#              #
#    Updated: 2022/12/13 19:20:35 by omoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minitalk
NAMEC := client
NAMES := server
NAMECB := ${addsuffix _bonus, $(NAMEC)}
NAMESB := ${addsuffix _bonus, $(NAMES)}

SRCC_R:= client.c
SRCS_R := server.c

SRCCB_R:= client_bonus.c
SRCSB_R := server_bonus.c

SRCU_R :=check_args.c\
	ft_show_pid.c\
	ft_append_bit_to_byte.c\
	ft_take_bit_from_byte.c\
	sig_event_queue.c\
	clients_list.c\
	ft_process_sig_ev.c\
	flow_control.c

SRC_PATH := src/
SRCB_PATH := src_bonus/
SRCU_PATH := src_utils/
LIBFT_PATH := libft/

SRCC := ${addprefix $(SRC_PATH), $(SRCC_R)}
SRCS := ${addprefix $(SRC_PATH), $(SRCS_R)}

SRCCB := ${addprefix $(SRCB_PATH), $(SRCCB_R)}
SRCSB := ${addprefix $(SRCB_PATH), $(SRCSB_R)}

SRCU := ${addprefix $(SRCU_PATH), $(SRCU_R)}

OBJC := $(SRCC:.c=.o)
OBJS := $(SRCS:.c=.o)
OBJCB := $(SRCCB:.c=.o)
OBJSB := $(SRCSB:.c=.o)
OBJU := $(SRCU:.c=.o)

DEPSC := $(SRCC:.c=.d)
DEPSS := $(SRCS:.c=.d)
DEPSCB := $(SRCCB:.c=.d)
DEPSSB := $(SRCSB:.c=.d)
DEPSU := $(SRCU:.c=.d)

CC	:= 	gcc
CFLAGS := -Wall -Werror -Wextra
CFD := -MMD
RM	:= 	rm -f

HEADER := ${addprefix $(SRC_PATH), minitalk.h}
HEADERB := ${addprefix $(SRCB_PATH), minitalk_bonus.h}
HEADERU := ${addprefix $(SRCU_PATH), minitalk_utils.h}
LIBFT_H := ${addprefix $(LIBFT_PATH), libft.h}
LIBFT_A := ${addprefix $(LIBFT_PATH), libft.a}
LIBFT_D := ${addprefix $(LIBFT_PATH), libft.d}
LIBS_FLAGS := -I ${LIBFT_H}
LIBFT_D_CONT := $(shell cat ${LIBFT_D})

src/%.o : src/%.c ${HEADER}
	${CC} ${CFLAGS} ${CFD} -I ${HEADER} -I ${LIBFT_H} -c $< -o $@

src_bonus/%.o : src_bonus/%.c ${HEADERB}
	${CC} ${CFLAGS} ${CFD} -I ${HEADERB} -I ${LIBFT_H} -c $< -o $@

src_utils/%.o : src_utils/%.c ${HEADERU}
	${CC} ${CFLAGS} ${CFD} -I ${HEADERU} -I ${LIBFT_H} -c $< -o $@

all : $(NAME)

$(NAME) : $(NAMEC) $(NAMES)
	@touch $@

bonus : $(NAMECB) $(NAMESB)
	@touch $@

-include $(DEPSC)
$(NAMEC) : ${LIBFT_A} ${OBJC} ${OBJU}
	${CC} ${CFLAGS} -I ${HEADER} ${OBJC} ${OBJU} ${LIBFT_A} ${LIBS_FLAGS} -o $@

-include $(DEPSS)
$(NAMES) : ${LIBFT_A} ${OBJS} ${OBJU}
	${CC} ${CFLAGS} -I ${HEADER} ${OBJS} ${OBJU} ${LIBFT_A} ${LIBS_FLAGS} -o $@

-include $(DEPSCB)
$(NAMECB) : ${LIBFT_A} ${OBJCB} ${OBJU}
	${CC} ${CFLAGS} -I ${HEADERB} ${OBJCB} ${OBJU} ${LIBFT_A} ${LIBS_FLAGS} -o $@

-include $(DEPSSB)
$(NAMESB) : ${LIBFT_A} ${OBJSB} ${OBJU}
	${CC} ${CFLAGS} -I ${HEADERB} ${OBJSB} ${OBJU} ${LIBFT_A} ${LIBS_FLAGS} -o $@

${LIBFT_A} : ${LIBFT_D_CONT}
	make bonus -C libft

clean :
	$(RM) $(OBJC)
	$(RM) $(OBJS)
	$(RM) $(OBJCB)
	$(RM) $(OBJSB)
	$(RM) $(OBJU)
	$(RM) $(DEPSC)
	$(RM) $(DEPSS)
	$(RM) $(DEPSCB)
	$(RM) $(DEPSSB)
	$(RM) $(DEPSU)
	make clean -C libft

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAMEC)
	$(RM) $(NAMES)
	$(RM) bonus
	$(RM) $(NAMECB)
	$(RM) $(NAMESB)
	make fclean -C libft

re: fclean all

.PHONY : clean fclean re all