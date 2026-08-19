#include "../include/ft_ls.h"
#include <dirent.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdbool.h>

int compare(t_llist *a, t_llist *b) {
	struct dirent *a_entry = a->data;
	struct dirent *b_entry = b->data;
	return strcmp(a_entry->d_name, b_entry->d_name);
}

void free_dirent(void *data) {
	t_llist *list = data;
	t_llist *temp = NULL;
	
	while (list) {
		temp = list;
		list = list->next;
		free(temp->data);
		free(temp);
	}
}

// char *get_errno() {
// 	// handle errno
// }

// int8_t recurse_list(t_rls_ctx *context) {
// 	static bool first_invocation = true;
// 	size_t dirp_len = strlen(context->dirp);
// 	DIR *dir = opendir(context->dirp);
// 	if (dir == NULL) {
// 		if (first_invocation) {
// 			first_invocation = false;
// 		}
//
// 		if (errno == ENOTDIR) {
// 			printf("%s\n", &context->dirp[context->cwd_len + 1]);
// 		} else if (dirp_len != context->cwd_len && !(context->options & OPT_PASSED_PATH)) {
// 			fprintf(stderr, "ls: cannot access \".%s\": sum ting won\n", &context->dirp[context->cwd_len]);
// 		} else {
// 			fprintf(stderr, "ls: cannot access \"%s\": sum ting wong\n", &context->dirp[context->cwd_len + 1]);
// 		}
// 		return -1;
// 	}
//
// 	struct dirent *dir_entry;
// 	t_llist *directory_list = NULL;
//
// 	while ((dir_entry = readdir(dir)) != NULL) {
// 		struct dirent *dirent_copy = malloc(sizeof(struct dirent));
// 		memcpy(dirent_copy, dir_entry, sizeof(struct dirent));
// 		if (!strncmp(dir_entry->d_name, ".", 1) && !(context->options & OPT_ALL_INFO)) continue;
// 		llist_append(&directory_list, dirent_copy);
// 	}
//
// 	closedir(dir);
//
// 	directory_list = llist_sort(directory_list, &compare);
// 	if (context->options & OPT_REVERSE) {
// 		directory_list = llist_rev(directory_list);
// 	}
// 	llist_append(context->directories, directory_list);
// 	t_llist *print_itr = directory_list;
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
// 	}
//
// 	if (first_invocation) {
// 		first_invocation = false;
// 	}
//
// 	if (options & OPT_RECURSIVE) {
// 		t_llist *iterator = directory_list;
// 		while (iterator) {
// 			struct dirent *entry = iterator->data;
// 			iterator = iterator->next;
// 			if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
// 			if (entry->d_type == DT_DIR) {
// 				printf("\n");
// 				strlcat(dirp, "/", PATH_MAX);
// 				strlcat(dirp, entry->d_name, PATH_MAX); 
// 				recurse_list(directories, options, dirp, cwd_len);
// 				memset((dirp + dirp_len), 0, PATH_MAX - dirp_len); 
// 			}
// 		}
// 	}
//
// 	return 0;
// }

void print_llist(void *list) {
	t_llist *data = list;
	while (data) {
		printf("%s\n", ((struct dirent *)data->data)->d_name);
		data = data->next;
	}
}

void build_dispatch(t_rls_dispatch *dispatch, void *data, int reset_len) {
	strlcat(dispatch->context.dirp, "/", PATH_MAX);
	strlcat(dispatch->context.dirp, (char *)data, PATH_MAX);
	dispatch->recurse_list(&dispatch->context);
	memset(dispatch->context.dirp + reset_len, 0, PATH_MAX - reset_len);
}

void free_dirent_fr(void *data) {
	struct dirent *tdata = data;
	if (!tdata) return;
	printf("freeing %s\n", tdata->d_name);
	free(tdata);
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
	printf("checking up on %s\n", ctx->dirp);
	while ((dir_entry = readdir(dir)) != NULL) {
		struct dirent *dirent_copy = malloc(sizeof(struct dirent));
		memcpy(dirent_copy, dir_entry, sizeof(struct dirent));
		if (!strncmp(dir_entry->d_name, ".", 1) && !(ctx->options & OPT_ALL_INFO)) {
			free(dirent_copy);
			continue;
		}
		llist_append(&dir_list, dirent_copy);
	}
	closedir(dir);
	dir_list = llist_sort(dir_list, &compare);
	if (ctx->options & OPT_REVERSE) {
		dir_list = llist_rev(dir_list);
	}

	t_llist *pitr = dir_list;
	while (pitr) {
		printf("%s\n", ((struct dirent *)pitr->data)->d_name);
		pitr = pitr->next;
	}

	// print the list
	if (first_invoc) {
		first_invoc = false;
	}
	
	// recurse the function
	if (ctx->options & OPT_RECURSIVE) {
		t_llist *itr = dir_list;
		while (itr) {
			struct dirent *entry = itr->data;
			itr = itr->next;
			if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
			if (entry->d_type == DT_DIR) {
				build_dispatch(&(t_rls_dispatch) {
					.recurse_list = &recurse_list_temp,
					.context = *ctx
				}, entry->d_name, dirp_len);
			}
		}
	}
	llist_free_data(dir_list, &free_dirent_fr);
}


void temp_list_all(t_arguments args) {
	t_rls_ctx rls_ctx;
	char cwd[PATH_MAX];
	getcwd(cwd, PATH_MAX);
	rls_ctx.dirp = cwd;
	rls_ctx.cwd_len = strlen(cwd);
	rls_ctx.directories = NULL;
	rls_ctx.options = args.options;
	t_rls_dispatch rls_dispatch = {
		&recurse_list_temp,
		rls_ctx
	};

	if (!llist_len(args.dirs)) {
		rls_dispatch.recurse_list(&rls_dispatch.context);
		if (rls_ctx.directories) {
			llist_free_data(*rls_ctx.directories, &free_dirent);
		}
		return;
	}

	if (args.options & OPT_REVERSE) {
		llist_rev(args.dirs);
	}

	t_llist *iterator = llist_sort(args.dirs, &compare);
	while (iterator) {
		build_dispatch(&rls_dispatch, iterator->data, rls_ctx.cwd_len);
		iterator = iterator->next;
	}
	llist_free_data(*rls_ctx.directories, &free_dirent);
}


// int8_t list(t_arguments args) {
// 	t_llist *directories = NULL;
// 	char cwd[PATH_MAX];
// 	getcwd(cwd, PATH_MAX);
// 	size_t cwd_len = strlen(cwd);
//
// 	if (!llist_len(args.dirs)) {
// 		recurse_list(&directories, args.options, cwd, cwd_len);
// 		return 0;
// 	}
//
// 	if (args.options & OPT_REVERSE) {
// 		llist_rev(args.dirs);
// 	}
//
// 	t_llist *iterator = llist_sort(args.dirs, &compare);
//
// 	while (iterator) {
// 		strlcat(cwd, "/", PATH_MAX);
// 		strlcat(cwd, iterator->data, PATH_MAX);
// 		recurse_list(&directories, args.options, cwd, cwd_len);
// 		memset(cwd + cwd_len, 0, PATH_MAX - cwd_len);
// 		iterator = iterator->next;
// 	}
//
// 	return 0;
// }
