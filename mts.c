#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "train_data_structures.h"

// basic thread function
void* run_train(void* arg) {
	Train_object *train_obj = (Train_object*)arg;
	printf("my train id: %d, my direction: %s\n", train_obj->train->train_id, train_obj->train->direction);

	free(train_obj->train);
	free(train_obj);
	return NULL;
}

int main(int argc, char *argv[]) {
	/*~~~ File setup ~~~*/

	// Ensure file is given
	if (argc < 2) {
		printf("Usage: %s <input file>\n", argv[0]);
		return 1;
	}

	// Open file and check for errors
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	/*~~~ Input file parsing setup ~~~*/

	int train_count = 0; // Used for tracking train id's during input parsing.
	
	// Initialize Queues for each train station.
	/* Low priority East,
	 * High priority East,
	 * Low priority West,
	 * High priority West. */
	Queue low_east_queue;
	Queue high_east_queue;
	queue_init(&low_east_queue);
	queue_init(&high_east_queue);
	
	Queue low_west_queue;
	Queue high_west_queue;
	queue_init(&low_west_queue);
	queue_init(&high_west_queue);
	
	char input_direction_letter;
	int input_load_time;
	int input_cross_time;

	pthread_t *tids = NULL;
	int tids_size = 0;

	// Space before %c allows fscanf to handle new line characters.
	while(fscanf(file, " %c %d %d", &input_direction_letter, &input_load_time, &input_cross_time) == 3) {
		/*~~~  Create new train object. ~~~*/
		Train_data *new_train_data = create_new_train_Train_data(train_count, input_direction_letter, input_load_time, input_cross_time);
		Train_object *new_train = NULL;
		switch(input_direction_letter) {
			case 'e':
				new_train = create_new_train_object(new_train_data, &low_east_queue);
				break;
			case 'E':
				new_train = create_new_train_object(new_train_data, &high_east_queue);
				break;
			case 'w':
				new_train = create_new_train_object(new_train_data, &low_west_queue);
				break;
			case 'W':
				new_train = create_new_train_object(new_train_data, &high_west_queue);
				break;
		}
		
		/*~~~ Organize for thread creation  ~~~*/
		// manage dynamic array sizing
		if (train_count >= tids_size) {
			tids_size = (tids_size == 0) ? 4 : tids_size * 2;
			tids = realloc(tids, sizeof(pthread_t) * tids_size);
			if (!tids) { perror("realloc"); exit(1); }
		}
		
		// Create new train thread, store tid
		if (pthread_create(&tids[train_count], NULL, run_train, new_train) != 0) {
			perror("pthread create failed");
			free(new_train->train);
			free(new_train);
			exit(1);
		}
		train_count += 1; // train id tracker.
	}

	// join all train threads
	for (int i=0; i<train_count; i++) {
		pthread_join(tids[i], NULL);
	}

	fclose(file);
	return 0;
}
