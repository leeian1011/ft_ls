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

void output_opterr(t_opt opts) {
	if (opts == '?') {
		fprintf(stderr, "Try ft_ls --help for more information.\n");
		exit(2);
	} else if (opts == 255) {
		//print help
		printf("Usage: ft_ls [OPTION]... [FILE]...\n"
				"List information about the FILEs (the current directory by default).\n"
				"Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n"
				"\nMandatory arguments to long options are mandatory for short options too.\n"
			  );
		exit(0);
	}
}

void output_nondir(t_llist *non_dir, t_arguments *args, int argc) {
	size_t nondir_len = llist_len(non_dir);
	non_dir = llist_sort(non_dir, &compare_dirstr);

	if (args->options & OPT_REVERSE) {
		non_dir = llist_rev(non_dir);
	}
	t_llist *itr = non_dir;
	while (itr) {
		printf("%s ", (char *)itr->data);
		itr = itr->next;
	}

	if (nondir_len) {
		printf("\n");
	}

	if (non_dir || (optind < argc)) {
		if (args->dirs == NULL) {
			args->execute_list = false;
		} else if (nondir_len) {
			printf("\n");
		}
	}
	llist_free(non_dir);
}
