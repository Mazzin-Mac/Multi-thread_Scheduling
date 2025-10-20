#include <stdio.h>
#include <string.h>

#include "train_data_structures.h"

/* Node Struct functions:
 * Set train direction as string,
 * Set train priority using enum. */
void set_train_direction(Node *train, char letter) {
    if (letter == 'E' || letter == 'e') {
        strcpy(train->direction, "East");
    } else {
        strcpy(train->direction, "West");
    }
}

// assing high vs. low priority (enum)
void set_train_priority(Node *train, char letter) {
    train->priority = (letter == 'E' || letter == 'W') ? high : low;
}

/* Queue Functions:
 * Initialize queue,
 * add to queue,
 * remove from queue,
 * display the queue. */
void queue_init(Queue *q) {
	q->tail = q->head = NULL;
}

void enqueue(Queue *q, Node *train) {
	if (train == NULL) {
		printf("enqueue failed, null train node\n");
		return;
	}
	// Queue is empty
	if (q->head == NULL) {
		q->head = q->tail = train;
	}
	// Not empty, add to back;
	q->tail->next = train;
	q->tail = train;
}

Node* dequeue(Queue *q) {
	if (q->head == NULL) {
		printf("Queue empty\n");
		return NULL;
	}

	Node *temp = q->head;
	q->head = q->head->next;
	if (q->head == NULL) {
		q->tail = NULL; //if queue becomes empty
	}

	temp->next = NULL; //disconnect node from queue
	return temp;
}

void display_queue(Queue *q) {
	/* Prints contents of queue */
	if (q->head == NULL) {
		printf("Queue empty\n");
		return;
	}

	Node *temp = q->head;
	printf("Queue:\n");
	while (temp != NULL) {
		printf("id: %d, dir: %c, load: %d, cross: %d\n", temp->train_id, temp->letter, temp->load_time, temp->cross_time);
		temp = temp->next;
	}
	printf("\n");
}
