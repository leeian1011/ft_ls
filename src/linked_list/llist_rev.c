#include "../../include/linkedlist.h"

t_llist *llist_rev(t_llist *head) {
	t_llist *tmp = NULL;
	t_llist *prev = NULL;

	while (head) {
		tmp = head->next;
		head->next = prev;
		prev = head;
		head = tmp;
	}

	return prev;
}
