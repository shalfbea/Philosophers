HEADER := include/philo.h

CC := clang

TestingFlags := -fsanitize=address

FLAGS := -Wall -Wextra -Werror -I./include -g3 -pthread

PHILO := philo

SRC = main.c parser.c utils.c philo_life.c

OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC)))

RM := rm -rf

all: $(OBJ_DIR) $(HEADER) $(PHILO)

$(PHILO): $(HEADER) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(PHILO)

$(LIBFT) :
	make -C ./libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir obj

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(PHILO)

re: fclean all

norm: $(SRC_FILES)
	norminette $<

.PHONY: all clean fclean re norm bonus
