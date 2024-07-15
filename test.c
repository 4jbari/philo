#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 0;

void *increment(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        counter++;  // Increment the shared counter
    }
    return NULL;
}

int main() {
    pthread_t threads[2];

    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Counter value: %d\n", counter);
    return 0;
}
