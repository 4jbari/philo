SRC = philo.c mutex_handlers.c

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

NAME = philo

all :

	$(CC) $(FLAGS) -o $(OBJ)

%.o:%c

