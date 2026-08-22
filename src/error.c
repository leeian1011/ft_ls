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

void handle_errno_listing(t_rls_ctx *ctx) {
	switch (errno) {
		case ENOENT:
			fprintf(stderr, "ls: cannot access \"%s\": No such file or directory\n", &ctx->dirp[ctx->cwd_len + 1]);
			break;
		case EACCES:
			fprintf(stderr, "ls: cannot access \"%s\": Permission denied\n", &ctx->dirp[ctx->cwd_len + 1]);
			break;
	}
}
