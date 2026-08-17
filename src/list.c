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

void recurse_list(t_llist **directories, int options, char *dirp) {
	t_llist *directory_list = NULL;
	DIR *dir = opendir(dirp);
	size_t orig_dirp_len = strlen(dirp);

	struct dirent *dir_entry;
	while ((dir_entry = readdir(dir)) != NULL) {
		if (!(!strcmp(dir_entry->d_name, ".") || !strcmp(dir_entry->d_name, "..")) && dir_entry->d_type == DT_DIR && (options & OPT_RECURSIVE)) {
			if (!strncmp(dir_entry->d_name, ".", 1) && !(options & OPT_ALL_INFO)) continue;
			strlcat(dirp, "/", 1024);
			strlcat(dirp, dir_entry->d_name, 1024); 
			printf("new => %s\n", dirp);
			recurse_list(directories, options, dirp);
			memset((dirp + orig_dirp_len), 0, 1024); 
			printf("post memset => %s\n", dirp);
		}
		if (!strncmp(dir_entry->d_name, ".", 1) && !(options & OPT_ALL_INFO)) continue;
		llist_append(&directory_list, dir_entry);
	}
	llist_append(directories, directory_list);
}

void print_llist(void *list) {
	t_llist *data = list;
	while (data) {
		printf("%s\n", ((struct dirent *)data->data)->d_name);
		data = data->next;
	}
}

int8_t list(t_arguments args) {
	// t_llist *iterator = args.dirs;
	// t_llist *dirent_list = NULL;
	// DIR *dir;

	t_llist *directories = NULL;

	char cwd[PATH_MAX];
	getcwd(cwd, PATH_MAX);
	recurse_list(&directories, args.options, cwd);

	while (directories) {
		print_llist(directories->data);
		directories = directories->next;
	}
	printf("done\n");
	return 0;

	/*if (!iterator) {
		char cwd[PATH_MAX];
		getcwd(cwd, PATH_MAX);
		dir = opendir(cwd);
		struct dirent *x;
		while ((x = readdir(dir)) != NULL) {
			llist_append(&dirent_list, x);
		}
	} else {
	}
	dirent_list = llist_sort(dirent_list, &compare);
	if (args.options & OPT_REVERSE) {
		dirent_list = llist_rev(dirent_list);
	}
	t_llist *tmp = dirent_list;
	while (dirent_list) {
		printf("%s  ", ((struct dirent *)dirent_list->data)->d_name);
		dirent_list = dirent_list->next;
	}
	closedir(dir);
	printf("\n");
	llist_free(tmp);

	return 0;*/
}
