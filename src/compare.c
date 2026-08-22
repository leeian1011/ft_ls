#include "../include/ft_ls.h"

int8_t compare_dirstr(t_llist *a, t_llist *b) {
	return strcmp(a->data, b->data);
}

int8_t compare_dirent(t_llist *a, t_llist *b) {
	struct dirent *a_entry = ((t_dirdata *) a->data)->dirent;
	struct dirent *b_entry = ((t_dirdata *)b->data)->dirent;
	return strcmp(a_entry->d_name, b_entry->d_name);
}

int8_t compare_time(t_llist *a, t_llist *b) {
	struct timespec a_entry = ((t_dirdata *)a->data)->stat->st_mtim;
	struct timespec b_entry = ((t_dirdata *)b->data)->stat->st_mtim;

	if (a_entry.tv_sec == b_entry.tv_sec) {
		if (a_entry.tv_nsec > b_entry.tv_nsec) {
			return -1;
		} else {
			return 0;
		}
	} else if (a_entry.tv_sec > b_entry.tv_sec) {
		return -1;
	} else {
		return 0;
	}
}
