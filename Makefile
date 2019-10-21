NAME = lem-in
SRC = create_hill.c\
	  create_rooms.c\
	  hashmap.c\
	  create_links.c\
	  first_path.c\
	  find_path.c\
	  suurballe.c\
	  all_paths.c\
	  move_ants.c\
	  max_turns.c\
	  sort_paths.c\
	  check_errors.c\
	  free_all.c\
	  delete_this_when_finish.c\
	  dead_end.c\
	  parser.c\
	  bfs.c\
	  checker.c\
	  bellman_ford.c\
	  duplicate_rooms.c

OBJ = $(SRC:.c=.o)
CC = gcc

all: $(NAME)

%.o: %.c
	@$(CC) -c -o $@ $^

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a libft/ftprintf/libftprintf.a lemin.c -o $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
