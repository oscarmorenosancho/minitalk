# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 10:34:11 by omoreno-          #+#    #+#              #
#    Updated: 2022/12/15 17:40:10 by omoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minitalk
NAMEC := client
NAMES := server
NAMECB := ${addsuffix _bonus, $(NAMEC)}
NAMESB := ${addsuffix _bonus, $(NAMES)}

SRCC_R:= client.c\
	send_to_server.c
SRCS_R := server.c

SRCCB_R:= client_bonus.c\
	send_to_server_bonus.c
SRCSB_R := server_bonus.c

SRCU_R :=check_args.c\
	ft_show_pid.c\
	ft_append_bit_to_byte.c\
	ft_take_bit_from_byte.c\
	ft_crc.c

SRCSU_R := ft_process_sig_ev.c\
	sig_event_queue.c\
	clients_list.c
 
SRCCU_R := flow_control.c\
	ft_show_kill_error_n_exit.c

SRC_PATH := src/
SRCB_PATH := src_bonus/
SRCU_PATH := src_utils/
SRCCU_PATH := src_cli_utils/
SRCSU_PATH := src_svr_utils/
LIBFT_PATH := libft/

SRCC := ${addprefix $(SRC_PATH), $(SRCC_R)}
SRCS := ${addprefix $(SRC_PATH), $(SRCS_R)}

SRCCB := ${addprefix $(SRCB_PATH), $(SRCCB_R)}
SRCSB := ${addprefix $(SRCB_PATH), $(SRCSB_R)}

SRCU := ${addprefix $(SRCU_PATH), $(SRCU_R)}
SRCCU := ${addprefix $(SRCCU_PATH), $(SRCCU_R)}
SRCSU := ${addprefix $(SRCSU_PATH), $(SRCSU_R)}

OBJC := $(SRCC:.c=.o)
OBJS := $(SRCS:.c=.o)
OBJCB := $(SRCCB:.c=.o)
OBJSB := $(SRCSB:.c=.o)
OBJU := $(SRCU:.c=.o)
OBJSU := $(SRCSU:.c=.o)
OBJCU := $(SRCCU:.c=.o)

DEPSC := $(SRCC:.c=.d)
DEPSS := $(SRCS:.c=.d)
DEPSCB := $(SRCCB:.c=.d)
DEPSSB := $(SRCSB:.c=.d)
DEPSU := $(SRCU:.c=.d)
DEPSSU := $(SRCSU:.c=.d)
DEPSCU := $(SRCCU:.c=.d)

CC	:= 	gcc
CFLAGS := -Wall -Werror -Wextra
CFD := -MMD
RM	:= 	rm -f

HEADER := ${addprefix $(SRC_PATH), minitalk.h}
HEADERB := ${addprefix $(SRCB_PATH), minitalk_bonus.h}
HEADERU := ${addprefix $(SRCU_PATH), minitalk_utils.h}
HEADERCU := ${addprefix $(SRCCU_PATH), minitalk_cli_utils.h}
HEADERSU := ${addprefix $(SRCSU_PATH), minitalk_svr_utils.h}
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

src_cli_utils/%.o : src_cli_utils/%.c ${HEADERCU}
	${CC} ${CFLAGS} ${CFD} -I ${HEADERCU} -I ${LIBFT_H} -c $< -o $@

src_svr_utils/%.o : src_svr_utils/%.c ${HEADERSU}
	${CC} ${CFLAGS} ${CFD} -I ${HEADERSU} -I ${LIBFT_H} -c $< -o $@

all : $(NAME)

$(NAME) : $(NAMEC) $(NAMES)
	@touch $@

bonus : $(NAMECB) $(NAMESB)
	@touch $@

-include $(DEPSC)
$(NAMEC) : ${LIBFT_A} ${OBJC} ${OBJU} ${OBJCU}
	${CC} ${CFLAGS} -I ${HEADER} -I ${HEADERCU} ${OBJC} ${OBJU} ${OBJCU} \
	${LIBFT_A} ${LIBS_FLAGS} -o $@

-include $(DEPSS)
$(NAMES) : ${LIBFT_A} ${OBJS} ${OBJU} ${OBJSU}
	${CC} ${CFLAGS} -I ${HEADER} -I ${HEADERSU} ${OBJS} ${OBJU} ${OBJSU} \
	${LIBFT_A} ${LIBS_FLAGS} -o $@

-include $(DEPSCB)
$(NAMECB) : ${LIBFT_A} ${OBJCB} ${OBJU} ${OBJCU}
	${CC} ${CFLAGS} -I ${HEADERB} -I ${HEADERCU} ${OBJCB} ${OBJU} ${OBJCU} \
	${LIBFT_A} ${LIBS_FLAGS} -o $@

-include $(DEPSSB)
$(NAMESB) : ${LIBFT_A} ${OBJSB} ${OBJU} ${OBJSU}
	${CC} ${CFLAGS} -I ${HEADERB} -I ${HEADERSU} ${OBJSB} ${OBJU} ${OBJSU} \
	${LIBFT_A} ${LIBS_FLAGS} -o $@

${LIBFT_A} : ${LIBFT_D_CONT}
	make bonus -C libft

clean :
	$(RM) $(OBJC)
	$(RM) $(OBJS)
	$(RM) $(OBJCB)
	$(RM) $(OBJSB)
	$(RM) $(OBJU)
	$(RM) $(OBJCU)
	$(RM) $(OBJSU)
	$(RM) $(DEPSC)
	$(RM) $(DEPSS)
	$(RM) $(DEPSCB)
	$(RM) $(DEPSSB)
	$(RM) $(DEPSU)
	$(RM) $(DEPSCU)
	$(RM) $(DEPSSU)
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