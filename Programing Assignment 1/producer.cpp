//producer.cpp
//This is the producer of the prpoducer consumer problem. 
//  It produces characters starting at 'a' and incrimenting 20 times
//Matthew Crosby
//4/5/2024


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define TABLE_SIZE 2

struct shared_data {
    char buffer[TABLE_SIZE];
    sem_t mutex, full, empty;
};


int main() {
    int shm_fd;
    struct shared_data *shared_memory;

    // Create shared memory
    shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(struct shared_data));
    shared_memory = (struct shared_data *) mmap(NULL, sizeof(struct shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize semaphores
    sem_init(&shared_memory->mutex, 1, 1);
    sem_init(&shared_memory->full, 1, 0);
    sem_init(&shared_memory->empty, 1, TABLE_SIZE);

    // Producer loop
    char item = 'A';
    for (int i = 0; i < 20; ++i) {
        sem_wait(&shared_memory->empty);
        sem_wait(&shared_memory->mutex);

        shared_memory->buffer[i % TABLE_SIZE] = item++;
        printf("Produced item: %c\n", shared_memory->buffer[i % TABLE_SIZE]);

        sem_post(&shared_memory->mutex);
        sem_post(&shared_memory->full);
    }

    // Cleanup
    munmap(shared_memory, sizeof(struct shared_data));
    shm_unlink("/myshm");
    return 0;
}
