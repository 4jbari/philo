SRC = philo.c parser.c initiator.c utils.c mutex_handlers.c routine.c
FLAGS =  -fsanitize=thread -Wall -Wextra -Werror 

OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME) 

$(NAME): $(OBJ)
	$(CC)  $(FLAGS)  $(OBJ) -o $(NAME) 

%.o:%.c
	$(CC)  $(FLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean