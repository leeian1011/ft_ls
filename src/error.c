#include "../include/linkedlist.h"
#include "../include/ft_ls.h"

void handle_errno_parsing(char *dir, t_llist **non_dir) {
	switch (errno) {
		case ENOENT:
			fprintf(stderr, "ls: cannot access \"%s\": File or directory does not exist\n", dir);
			break;
		case EACCES:
			fprintf(stderr, "ls: cannot access \"%s\": Permission denied\n", dir);
			break;
		default:
			llist_append(non_dir, dir);
			break;
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
