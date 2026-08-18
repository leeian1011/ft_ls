#include <errno.h>
#include <stdio.h>
#include "../include/linkedlist.h"
#include "../include/ft_ls.h"

void handle_errno_parsing(char *dir, t_llist **non_dir) {
	if (errno == ENOENT) {
		fprintf(stderr, "ls: %s does not exist brah\n", dir);
	} else {
		llist_append(non_dir, dir);
	}
}
