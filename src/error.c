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
