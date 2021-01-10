NAME			= TuppersGraph
CC				= gcc
RM				= rm -f
_SRCS			= main.c
SRCS			= $(addprefix srcs/, $(_SRCS))
OBJS			= $(SRCS:.c=.o)
CFLAGS			= -Wall -Wextra -Werror
%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -lSDL2 -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

all:		$(NAME)

.PHONY: clean fclean re all