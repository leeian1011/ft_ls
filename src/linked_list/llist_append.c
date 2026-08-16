#include "../../include/linkedlist.h"
#include <stdlib.h>

t_llist *llist_new_node(void *data) {
	t_llist *node = malloc(sizeof(t_llist));
	node->data = data;
	node->next = NULL;
	return node;
}

void llist_append(t_llist **head, void *data) {
	t_llist *new_node = llist_new_node(data);
	if (!*head) {
		*head = new_node;
	} else {
		t_llist *iterator = *head;
		while (iterator->next != NULL) {
			iterator = iterator->next;
		}
		iterator->next = new_node;
	}
}
