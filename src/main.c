#include "../include/ft_ls.h"

int main(int argc, char *const *argv) {
	t_arguments args = parse_arguments(argc, argv);
	if (args.execute_list) {
		// list(args);
		temp_list_all(args);
	}
	llist_free(args.dirs);
	return 0;
}
