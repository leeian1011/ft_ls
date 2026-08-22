#include "../include/ft_ls.h"

// 	if (context->options & OPT_RECURSIVE || context->options & OPT_PASSED_PATH) {
// 		// not original directory.
// 		if (context->options & OPT_PASSED_PATH) {
// 			if (!first_invocation) {
// 				printf("\n");
// 			}
// 			if (context->options & OPT_MULTI_PP || context->options & OPT_RECURSIVE) {
// 				printf("%s:\n", &context->dirp[context->cwd_len + 1]);
// 			}
// 		// is original dir
// 		} else {
// 			if (dirp_len != context->cwd_len) {
// 				printf("\n");
// 			}	
// 			printf(".%s:\n", &context->dirp[context->cwd_len]);
// 		}
// 	}
// 	while (print_itr) {
// 		char *e = ((struct dirent *)print_itr->data)->d_name;
// 		printf("%s", e);
// 		printf("  ");
// 		print_itr = print_itr->next;
// 	
void output_dirlist(t_rls_ctx *ctx, t_llist *dir_list, bool first_invoc) {
	if (!first_invoc) {
		printf("\n");
	}

	if (ctx->options & OPT_RECURSIVE) {
		if (!(ctx->options & OPT_PASSED_PATH) && !(ctx->options & OPT_MULTI_PP)) {
			printf(".%s:\n", &ctx->dirp[ctx->cwd_len]);
		} else {
			printf("%s:\n", &ctx->dirp[ctx->cwd_len + 1]);
		}
	} else if (ctx->options & OPT_MULTI_PP) {
		printf("%s:\n", &ctx->dirp[ctx->cwd_len + 1]);
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
