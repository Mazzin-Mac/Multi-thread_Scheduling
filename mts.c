#include <stdio.h>
#include <stdlib.h>

#include "train_data_structures.h"

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

	int train_count = 0;
	char letter2;
	int number1;
	int number2;

	Queue q;
	queue_init(&q);

	// Space before %c allows fscanf to handle new line characters.
	while(fscanf(file, " %c %d %d", &letter2, &number1, &number2) == 3) {
		/* queue testing */
		Node *new_node = (Node *)malloc(sizeof(Node));
		if (new_node == NULL) {
			printf("failed to allocate node\n");
			exit(1);
		}
		set_train_direction(new_node, letter2);
		set_train_priority(new_node, letter2);
		printf("train direction: %s\n", new_node->direction);
		printf("train priority: %d\n", new_node->priority);
		new_node->train_id = train_count;
		new_node->letter = letter2;
		new_node->load_time = number1;
		new_node->cross_time = number2;
		enqueue(&q, new_node);
		train_count += 1; // train id tracker.
	}
	
	display_queue(&q); // queue testing
	


	return 0;
}
