#include "../include/ft_ls.h"


void free_dirent_list(void *data) {
	t_llist *list = data;
	t_llist *temp = NULL;
	
	while (list) {
		temp = list;
		list = list->next;
		t_dirdata *tf = temp->data;
		free(tf->dirent);
		free(tf->stat);
		free(tf);
		free(temp);
	}
}

void free_dirent(void *data) {
	t_dirdata *tf = data;
	if (!tf) return;
	free(tf->dirent);
	free(tf->stat);
	free(tf);
}

void build_dispatch(t_rls_dispatch *dispatch, void *data, int reset_len) {
	strlcat(dispatch->context.dirp, "/", PATH_MAX);
	strlcat(dispatch->context.dirp, (char *)data, PATH_MAX);
	dispatch->recurse_list(&dispatch->context);
	memset(dispatch->context.dirp + reset_len, 0, PATH_MAX - reset_len);
}

void recurse_list_temp(t_rls_ctx *ctx) {
	static bool first_invoc = true;
	size_t dirp_len = strlen(ctx->dirp);
	DIR *dir = opendir(ctx->dirp);
	if (!dir) {
		handle_errno_listing(ctx);
		return;
	}
	t_llist *dir_list = NULL;
	struct dirent *dir_entry;
	while ((dir_entry = readdir(dir)) != NULL) {
		struct dirent *dirent_copy = malloc(sizeof(struct dirent));
		struct stat *stat = malloc(sizeof(struct stat));

		memcpy(dirent_copy, dir_entry, sizeof(struct dirent));
		if (!strncmp(dir_entry->d_name, ".", 1) && !(ctx->options & OPT_ALL_INFO)) {
			free(dirent_copy);
			free(stat);
			continue;
		}
		BUILD_RESET(false, ctx->dirp, dirent_copy->d_name, dirp_len, {
			lstat(ctx->dirp, stat);
		});
		// strlcat(ctx->dirp, "/", PATH_MAX);
		// strlcat(ctx->dirp, dirent_copy->d_name, PATH_MAX);
		// lstat(ctx->dirp, stat);
		// memset(ctx->dirp + dirp_len, 0, PATH_MAX - dirp_len);
		t_dirdata *dirdata = malloc(sizeof(t_dirdata));
		dirdata->stat = stat;
		dirdata->dirent = dirent_copy;
		llist_append(&dir_list, dirdata);
	}
	closedir(dir);

	if (ctx->options & OPT_TIME_ORDERED) {
		dir_list = llist_sort(dir_list, &compare_time);
	} else {
		dir_list = llist_sort(dir_list, &compare_dirent);
	}

	if (ctx->options & OPT_REVERSE) {
		dir_list = llist_rev(dir_list);
	}

	// print the list
	output_dirlist(ctx, dir_list, first_invoc);
	if (first_invoc) {
		first_invoc = false;
	}
	
	// recurse the function
	if (ctx->options & OPT_RECURSIVE) {
		t_llist *itr = dir_list;
		while (itr) {
			struct dirent *entry = ((t_dirdata *)itr->data)->dirent;
			itr = itr->next;
			if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
			if (entry->d_type == DT_DIR) {
				BUILD_RESET(false, ctx->dirp, entry->d_name, dirp_len, {
					recurse_list_temp(ctx);
				});
				// build_dispatch(&(t_rls_dispatch) {
				// 	.recurse_list = &recurse_list_temp,
				// 	.context = *ctx
				// }, entry->d_name, dirp_len);
			}
		}
	}
	llist_free_data(dir_list, &free_dirent);
}

// void temp_list_all(t_arguments args) {
// 	t_rls_ctx rls_ctx;
// 	char cwd[PATH_MAX];
// 	getcwd(cwd, PATH_MAX);
// 	rls_ctx.dirp = cwd;
// 	rls_ctx.cwd_len = strlen(cwd);
// 	rls_ctx.options = args.options;
// 	t_rls_dispatch rls_dispatch = {
// 		&recurse_list_temp,
// 		rls_ctx
// 	};
//
// 	if (!llist_len(args.dirs)) {
// 		rls_dispatch.recurse_list(&rls_dispatch.context);
// 		return;
// 	}
//
// 	if (args.options & OPT_REVERSE) {
// 		args.dirs = llist_rev(args.dirs);
// 	}
//
// 	t_llist *iterator;
// 	iterator = llist_sort(args.dirs, &compare_dirstr);
//
// 	while (iterator) {
// 		build_dispatch(&rls_dispatch, iterator->data, rls_ctx.cwd_len);
// 		iterator = iterator->next;
// 	}
// }

void temp_list_all(t_arguments args) {
	t_rls_ctx rls_ctx;
	char cwd[PATH_MAX];
	getcwd(cwd, PATH_MAX);
	rls_ctx.dirp = cwd;
	rls_ctx.cwd_len = strlen(cwd);
	rls_ctx.options = args.options;

	if (!llist_len(args.dirs)) {
		recurse_list_temp(&rls_ctx);
		return;
	}

	args.dirs = llist_sort(args.dirs, &compare_dirstr);

	if (args.options & OPT_REVERSE) {
		args.dirs = llist_rev(args.dirs);
	}

	t_llist *iterator = args.dirs;
	while (iterator) {
		BUILD_RESET(!strncmp(iterator->data, "/", 1), rls_ctx.dirp, iterator->data, rls_ctx.cwd_len, {
			recurse_list_temp(&rls_ctx);
		});
		iterator = iterator->next;
	}
}
