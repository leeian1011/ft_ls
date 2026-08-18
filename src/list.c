#include "../include/ft_ls.h"
#include <dirent.h>
#include <limits.h>

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

int8_t recurse_list(t_llist **directories, int options, char *dirp) {
	DIR *dir = opendir(dirp);
	if (dir == NULL) {
		// char *error = get_errno();
		printf("ls: cannot access \"%s\"\n", dirp);
		return -1;
	}
	struct dirent *dir_entry;
	t_llist *directory_list = NULL;
	size_t dirp_len = strlen(dirp);

	while ((dir_entry = readdir(dir)) != NULL) {
		struct dirent *dirent_copy = malloc(sizeof(struct dirent));
		memcpy(dirent_copy, dir_entry, sizeof(struct dirent));
		if (!strncmp(dir_entry->d_name, ".", 1) && !(options & OPT_ALL_INFO)) continue;
		llist_append(&directory_list, dirent_copy);
	}

	closedir(dir);

	directory_list = llist_sort(directory_list, &compare);
	if (options & OPT_REVERSE) llist_rev(directory_list);
	llist_append(directories, directory_list);

	if (options & OPT_RECURSIVE) {
		t_llist *iterator = directory_list;
		while (iterator) {
			struct dirent *entry = iterator->data;
			if (entry->d_type == DT_DIR) {
				strlcat(dirp, "/", 1024);
				strlcat(dirp, entry->d_name, 1024); 
				recurse_list(directories, options, dirp);
				memset((dirp + dirp_len), 0, 1024); 
			}
			iterator = iterator->next;
		}
	}

	return 0;
}

void print_llist(void *list) {
	t_llist *data = list;
	while (data) {
		printf("%s\n", ((struct dirent *)data->data)->d_name);
		data = data->next;
	}
}

int8_t list(t_arguments args) {
	t_llist *directories = NULL;
	char cwd[PATH_MAX];
	getcwd(cwd, PATH_MAX);

	if (!llist_len(args.dirs)) {
		recurse_list(&directories, args.options, cwd);
		while (directories) {
			print_llist(directories->data);
			directories = directories->next;
		}
		return 0;
	}

	if (args.options & OPT_REVERSE) {
		llist_rev(args.dirs);
	}

	t_llist *iterator = args.dirs;

	while (iterator) {
		strlcat(cwd, "/", PATH_MAX);
		strlcat(cwd, iterator->data, PATH_MAX);
		recurse_list(&directories, args.options, cwd);
		iterator = iterator->next;
	}

	while (directories) {
		print_llist(directories->data);
		directories = directories->next;
	}

	printf("done\n");
	return 0;
}
