#ifndef TRAIN_DATA_STRUCTURES_H
#define TRAIN_DATA_STRUCTURES_H

enum Priority { low, high };

/* Train_data for storing info in the queue */
typedef struct Train_data {
	int train_id;
	enum Priority priority;
	char direction[5];
	//char letter;
	int load_time;
	int cross_time;

	struct Train_data *next;
} Train_data;

typedef struct Queue {
    Train_data *head;
    Train_data *tail;
} Queue;

typedef struct Train_object {
    Train_data *train;
    Queue *train_queue;
} Train_object;


void set_train_direction(Train_data *train_data, char letter);

Train_data* create_new_train_Train_data(int train_count, int letter, int load_time, int cross_time);

void queue_init(Queue *q);

void enqueue(Queue *q, Train_data *train);

Train_data* dequeue(Queue *q);

void display_queue(Queue *q);

Train_object* create_new_train_object(Train_data *train_data, Queue *train_data_queue);

#endif