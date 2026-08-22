#include "../include/linkedlist.h"
#include "../include/ft_ls.h"

int handle_errno_parsing(char *dir, t_llist **non_dir) {
	switch (errno) {
		case ENOENT:
			fprintf(stderr, "ls: cannot access \"%s\": File or directory does not exist\n", dir);
			return 0;
		// ignore no access.
		case EACCES:
			return 1;
		default:
			llist_append(non_dir, dir);
			return 0;
	}
}

void handle_errno_listing(t_rls_ctx *context) {
	switch (errno) {
		case ENOENT:
			fprintf(stderr, "ls: cannot access \"%s\": No such file or directory\n", context->dirp);
			break;
		case EACCES:
			fprintf(stderr, "ls: cannot access \"%s\": Permission denied", context->dirp);
			break;
	}
}
