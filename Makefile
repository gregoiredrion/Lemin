NAME = lem-in
SRC = create_anthill.c\
	  create_rooms.c\
	  hashmap.c\
	  create_links.c\
	  short_path.c
OBJ = $(SRC:.c=.o)
CC = gcc

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) libft/libft.a lemin.c -o $(NAME)

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
