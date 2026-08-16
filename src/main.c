#include "../include/ft_ls.h"

int main(int argc, char *const *argv) {
	t_arguments args = parse_arguments(argc, argv);

	/*printf("%d\n", args.options);
	t_llist *iterator = args.dirs;
	while (iterator != NULL) {
		printf("%s\n", (char *)iterator->data);
		iterator = iterator->next;
	}*/

	list(args);
	llist_free(args.dirs);
	return 0;
}
