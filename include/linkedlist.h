#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stddef.h>

typedef struct t_llist {
	struct t_llist *next;
	void *data;
} t_llist;

void llist_append(t_llist **head, void *data);
void llist_free(t_llist *head);
size_t llist_len(t_llist *head);
t_llist *llist_sort(t_llist *head, int (*compare)(t_llist *a, t_llist *b));
t_llist *llist_rev(t_llist *head);
#endif
