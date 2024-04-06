#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define BUFFER_SIZE 2

struct shared_data {
    char buffer[BUFFER_SIZE];
    sem_t mutex, full, empty;
};

int main() {
    int shm_fd;
    struct shared_data *shared_memory;

    // Open shared memory
    shm_fd = shm_open("/myshm", O_RDWR, 0666);
    shared_memory = (struct shared_data *) mmap(NULL, sizeof(struct shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Consumer loop
    char item;
    for (int i = 0; i < 20; ++i) {
        sem_wait(&shared_memory->full);
        sem_wait(&shared_memory->mutex);

        item = shared_memory->buffer[i % BUFFER_SIZE];
        printf("Consumed item: %c\n", item);

        sem_post(&shared_memory->mutex);
        sem_post(&shared_memory->empty);
    }

    // Cleanup
    munmap(shared_memory, sizeof(struct shared_data));
    return 0;
}