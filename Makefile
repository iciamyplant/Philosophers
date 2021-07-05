NAME		=	philo

HEADER		=	./include/

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) -pthread

SRCS		=	srcs/main.c \
				srcs/activity.c \
				srcs/threads.c \
				srcs/init_and_parse.c \
				srcs/utils_philo.c \
				srcs/utils_lib.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all