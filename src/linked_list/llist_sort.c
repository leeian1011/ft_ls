#include "../../include/linkedlist.h"


// Uses Merge sort recursively achieving O(n log n) compute time and O(n) for space complexity.
t_llist *llist_sort(t_llist *head, int (*compare)(t_llist *a, t_llist *b)) {
	if (!head || !head->next) return head;

	t_llist *right = head,
			*middle = head,
			*left = head,
			*result = NULL,
			*next = NULL,
			*tail = NULL;

	// get middle of list (split in half)
	while (middle && middle->next) {
		left = right;
		right = right->next;
		middle = middle->next->next;
	}
	left->next = NULL;

	head = llist_sort(head, compare);
	right = llist_sort(right, compare);

	while (head || right) {
		// identify 'next' value.
		if (!right) {
			next = head;
			head = head->next;
		} else if (!head) {
			next = right;
			right = right->next;
		} else if (compare(head, right) < 0) {
			next = head;
			head = head->next;
		} else {
			next = right;
			right = right->next;
		}
		// assign result to chosen value if first and retain a pointer to chosen value,
		// update pointer->next to value and refresh pointer to chosen value again
		if (!result) {
			result = next;
		} else {
			tail->next = next;
		}
		tail = next;
	}

	return result;
}
