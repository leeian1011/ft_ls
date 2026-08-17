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

void llist_free_data(t_llist *head, void (*free_data)(void *data)) {
	t_llist *temp = NULL;

	while (head) {
		temp = head;
		head = head->next;
		free_data(temp->data);
		free(temp);
	}
}
