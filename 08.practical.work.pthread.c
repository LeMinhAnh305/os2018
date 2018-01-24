#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 10
#include<pthread.h>
#include<unistd.h>
typedef struct {
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last) {
		// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}
int pthread_create(
	pthread_t *thread,
	const pthread_attr_t *attr,
	void *(*start_routine) (void *),
	void *arg);
//Create a new thread for producer, produce 3 items
void *threadproduceFunction(void *param) {
	item i1,i2,i3;

	i1.type = '0';
	i1.amount = 1000;
	i1.unit = '0';

	i2.type = '1';
	i2.amount = 2;
	i2.unit = '1';

	i3.type = '0';
	i3.amount = 6;
	i3.unit = '0';
	produce(&i1);
	printf("Type: %c Amount: %d Unit: %c \n", i1.type, i1.amount, i1.unit);
	produce(&i2);
	printf("Type: %c Amount: %d Unit: %c \n", i2.type, i2.amount, i2.unit);
	produce(&i3);
	printf("Type: %c Amount: %d Unit: %c \n", i3.type, i3.amount, i3.unit);
}
//Create another thread for consumer, consume 2 items
void *threadFunction(void *param) {
	consume();
	printf("After consume: First: %d Last %d \n", first, last);
	consume();
	printf("After consume: First: %d Last %d \n", first, last);
}

int main() {
	pthread_t tid1;
	pthread_create(
	    &tid1,
	    NULL,
	    threadproduceFunction,
	    NULL);
	pthread_join(tid1, NULL);
	pthread_t tid2;
	pthread_create(
	    &tid2,
     	    NULL,
	    threadFunction,
	    NULL);
	pthread_join(tid2, NULL);
	return 0;
}


