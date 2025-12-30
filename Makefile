CC  			= cc
CFLAGS	= -Wall -Werror -Wextra

NAME 			= git-acp
SRC 			= git-acp.c
OBJ 			= ${SRC:.cpp=.o}

all:		 $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: 		 %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

c: 			 clean

fclean:  clean
	rm -f $(NAME)

f: 			 fclean

re: 		 fclean all

.PHONY: all clean c fclean f re
