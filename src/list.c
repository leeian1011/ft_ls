#include "../include/ft_ls.h"
#include <dirent.h>
#include <linux/limits.h>

int compare(t_llist *a, t_llist *b) {
	struct dirent *a_entry = a->data;
	struct dirent *b_entry = b->data;
	return strcmp(a_entry->d_name, b_entry->d_name);
}

int8_t list(t_arguments args) {
	t_llist *iterator = args.dirs;
	t_llist *dirent_list = NULL;
	DIR *dir;

	if (!iterator) {
		char cwd[PATH_MAX];
		getcwd(cwd, PATH_MAX);
		dir = opendir(cwd);
		struct dirent *x;
		while ((x = readdir(dir)) != NULL) {
			llist_append(&dirent_list, x);
		}
		//closedir(dir);
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
	//llist_free(dirent_list);

	return 0;
}
