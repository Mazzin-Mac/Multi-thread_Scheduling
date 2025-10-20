#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "train_data_structures.h"

/* Train_data Struct functions:
 * Set train direction as string,
 * Set train priority using enum,
 * Create Train_data and assign values. */
void set_train_direction(Train_data *train, char letter) {
    if (letter == 'E' || letter == 'e') {
        strcpy(train->direction, "East");
    } else {
        strcpy(train->direction, "West");
    }
}

// assing high vs. low priority (enum)
void set_train_priority(Train_data *train, char letter) {
    train->priority = (letter == 'E' || letter == 'W') ? high : low;
}

Train_data* create_new_train_Train_data(int train_count, int letter, int load_time, int cross_time) {
    // ~~~~~~~~~~~~~~~> NEED TO FREE
    Train_data *new_Train_data = (Train_data *)malloc(sizeof(Train_data));
    if (new_Train_data == NULL) {
        printf("Failed to allocate Train_data\n");
        exit(1);
    }

    set_train_direction(new_Train_data, letter);
	set_train_priority(new_Train_data, letter);
    new_Train_data->train_id = train_count;
	new_Train_data->load_time = load_time;
	new_Train_data->cross_time = cross_time;

    return new_Train_data;
}

/* Queue Functions:
 * Initialize queue,
 * add to queue,
 * remove from queue,
 * display the queue. */
void queue_init(Queue *q) {
	q->tail = q->head = NULL;
}

void enqueue(Queue *q, Train_data *train) {
	if (train == NULL) {
		printf("enqueue failed, null train Train_data\n");
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

Train_data* dequeue(Queue *q) {
	if (q->head == NULL) {
		printf("Queue empty\n");
		return NULL;
	}

	Train_data *temp = q->head;
	q->head = q->head->next;
	if (q->head == NULL) {
		q->tail = NULL; //if queue becomes empty
	}

	temp->next = NULL; //disconnect Train_data from queue
	return temp;
}

void display_queue(Queue *q) {
	/* Prints contents of queue */
	if (q->head == NULL) {
		printf("Queue empty\n");
		return;
	}

	Train_data *temp = q->head;
	printf("Queue:\n");
	while (temp != NULL) {
		printf("id: %d, dir: %s, load: %d, cross: %d\n", temp->train_id, temp->direction, temp->load_time, temp->cross_time);
		temp = temp->next;
	}
	printf("\n");
}

/* Train object 
 * This is for the pointer to train data
 * and for the queue data.
 * This is for the pthread_create function */
Train_object* create_new_train_object(Train_data *train_data, Queue *train_data_queue) {
    // ~~~~~~~~~~~~~~> NEED TO FREE
    Train_object *new_train = (Train_object *)malloc(sizeof(Train_object));
    if (new_train == NULL) {
        printf("Failed to allocate train_object");
        exit(1);
    }
    new_train->train = train_data;
    new_train->train_queue = train_data_queue;
    return new_train;
}

