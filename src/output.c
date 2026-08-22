#include "../include/ft_ls.h"

void output_dirlist(t_rls_ctx *ctx, t_llist *dir_list, bool first_invoc) {
	int move_forward = ctx->cwd_len == 0 ? 0 : 1;
	char *target = &ctx->dirp[ctx->cwd_len + move_forward];

	if (!first_invoc) {
		printf("\n");
	}

	if (ctx->options & OPT_RECURSIVE) {
		if (!(ctx->options & OPT_PASSED_PATH) && !(ctx->options & OPT_MULTI_PP)) {
			printf(".%s:\n", --target);
		} else {
			printf("%s:\n", target);
		}
	} else if (ctx->options & OPT_MULTI_PP) {
		printf("%s:\n", target);
	}

	size_t list_len = llist_len(dir_list);
	while (dir_list) {
		struct dirent *entry = ((t_dirdata *)dir_list->data)->dirent;
		printf("%s ", entry->d_name);
		dir_list = dir_list->next;
	}
	if (list_len) {
		printf("\n");
	}
}
