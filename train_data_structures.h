#ifndef TRAIN_DATA_STRUCTURES_H
#define TRAIN_DATA_STRUCTURES_H

enum Priority { low, high };

/* Train node for storing info in the queue */
typedef struct Node {
	int train_id;
	enum Priority priority;
	char direction[5];
	char letter;
	int load_time;
	int cross_time;

	struct Node *next;
} Node;

typedef struct Queue {
	Node *head;
	Node *tail;
} Queue;

void set_train_direction(Node *node, char letter);

void queue_init(Queue *q);

void enqueue(Queue *q, Node *train);

Node* dequeue(Queue *q);

void display_queue(Queue *q);

#endif