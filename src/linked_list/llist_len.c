#include "../../include/linkedlist.h"

size_t llist_len(t_llist *head) {
	size_t res = 0;
	while (head) {
		head = head->next;
		res++;
	}
	return res;
}
