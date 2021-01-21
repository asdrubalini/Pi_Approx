#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>

// fork
#include <sys/types.h>
#include <unistd.h>
// mmap
#include <sys/mman.h>
#include <sys/wait.h>


#define WIDTH 1000
#define HEIGHT 1000
#define PROCESS_COUNT 16

struct point {
    int x;
    int y;
};

bool is_generated_point_in_circle() {
    point p;
    p.x = rand() % WIDTH;
    p.y = rand() % HEIGHT;

    long double distance_from_center = sqrt(pow(p.x - WIDTH / 2, 2) + pow(p.y - HEIGHT / 2, 2));

    return distance_from_center <= 500;
}

void child_compute(long long int *result) {
    srand(time(NULL));

    long long int *total_points = result + 0;
    long long int *circle_points = result + 1;

    for (;;) {
        int is_inside = is_generated_point_in_circle();
        
        *total_points += 1;

        if (is_inside == 1) {
            *circle_points += 1;
        }
    }

}

int main() {

    long long int *results = static_cast<long long int*>(mmap(
        NULL, sizeof (long long int) * PROCESS_COUNT * 2,
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    ));


    for (size_t i = 0; i < PROCESS_COUNT; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            printf("fork() error, unable to fork current process\n");
            exit(1);

        } else if (pid == 0) {  // Child
            child_compute(results + (i * sizeof (long long int) * 2));
            exit(0);

        }
    }

    // Parent

    for (;;) {
        long long int total_points = 0;
        long long int circle_points = 0;

        for (size_t i = 0; i < PROCESS_COUNT; i++) {
            total_points += *(results + (i * sizeof (long long int) * 2));
            circle_points += *(results + (i * sizeof (long long int) * 2 + 1));
        }

        long double pi = (long double) circle_points / total_points * 4;
        // printf("%Lf\n", pi);
        std::cout << "Pi: " << pi << std::endl;
        sleep(1);
    }

    munmap(results, sizeof (long long int) * PROCESS_COUNT * 2);

    return 0;
}
