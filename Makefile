TARGET = ft_ls
CFLAGS = -Wall -Werror -Wextra
DEBUGFLAGS = -g
SRC_DIR = src
OBJ_DIR = obj
DEBUG_OBJ_DIR = debug_obj
SRCS = src/main.c src/linked_list/llist_append.c src/linked_list/llist_free.c src/parser/parse_arg.c\
	   src/list.c src/linked_list/llist_len.c src/linked_list/llist_sort.c src/linked_list/llist_rev.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEBUG_OBJS = $(patsubst $(SRC_DIR)/%.c, $(DEBUG_OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
# $^ refers to all prerequisites.
	cc $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
# $< refers to every %.c value
# | *prerequisite* denotes that this prerequisite must be ran (order-only prerequisite). This prevents unnecessary compilation
# as each time obj_dir is appended to it's timestamp is updated.
# $@ refers to command name (i.e: %.o)
	mkdir -p $(dir $@)
	cc $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

debug: $(DEBUG_OBJS)
	cc $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET)_debug $^

$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DEBUG_OBJ_DIR)
	mkdir -p $(dir $@)
	cc $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@


$(DEBUG_OBJ_DIR):
	mkdir -p $@


fclean: clean
	rm $(TARGET)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(DEBUG_OBJ_DIR)

re: fclean all
