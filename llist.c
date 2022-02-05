#include "llist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct node *head = NULL;
    for (int i = 1; i < argc; i++) {
        char *current = argv[i];

        if (strcmp(current, "ih") == 0) {
            int num = atoi(argv[i + 1]);
            llist_insert_head(&head, node_alloc(num));
        } else if (strcmp(current, "it") == 0) {
            int num = atoi(argv[i + 1]);
            llist_insert_tail(&head, node_alloc(num));
        } else if (strcmp(current, "dh") == 0)
            llist_delete_head(&head);
        else if (strcmp(current, "f") == 0)
            llist_free(&head);
        else if (strcmp(current, "p") == 0) {
            llist_print(head);
        }
    }

    return 0;
}

void llist_insert_head(struct node **head, struct node *n) {
    struct node *oldHead = *head;
    n->next = oldHead;
    *head = n;
}

struct node *llist_delete_head(struct node **head) {
    if (*head == NULL) return NULL;
    struct node *oldHead = *head;
    struct node *next = (*head)->next;
    *head = next;
    return oldHead;
}

void llist_insert_tail(struct node **head, struct node *n) {
    if (*head == NULL)
        *head = n;
    else {
        struct node *pointer = *head;
        while (pointer->next != NULL) pointer = pointer->next;
        pointer->next = n;
    }
}

void llist_print(struct node *head) {
    struct node *pointer = head;
    if (head == NULL) printf("[empty]");
    while (pointer != NULL) {
        int value = pointer->value;
        printf("%d", value);
        if (pointer->next != NULL) printf(" -> ");
        pointer = pointer->next;
    }
    printf("\n");
}

void llist_free(struct node **head) {
    if (*head == NULL) return;

    llist_free(&(*head)->next);
    node_free(*head);
    *head = NULL;
}

struct node *node_alloc(int value) {
    struct node *head = malloc(sizeof(struct node));
    head->value = value;
    head->next = NULL;
    return head;
}

void node_free(struct node *n) {
    free(n);
}

// Bonus Questions

struct node *rem_llist_middle(struct node **head) {
    if (*head == NULL) return NULL;
    struct node *slow = *head;
    struct node *fast = *head;
    struct node *prev = slow;
    while (fast != NULL && fast->next != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (prev == slow)
        *head = NULL;
    else
        prev->next = slow->next;
    return slow;
}

int length(struct node *head) {
    if (head == NULL) return 0;
    return 1 + length(head->next);
}

struct node *reverse(struct node *head) {
    if (head == NULL || head->next == NULL) return head;
    struct node *relative_head = reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return relative_head;
}