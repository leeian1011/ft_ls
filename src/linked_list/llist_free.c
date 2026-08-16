#include "../../include/linkedlist.h"
#include <stdlib.h>

void llist_free(t_llist *head) {
	t_llist *temp = NULL;

	while (head) {
		temp = head;
		head = head->next;
		free(temp);
	}
}
