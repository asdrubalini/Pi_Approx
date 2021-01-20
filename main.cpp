#include <stdio.h>
#include <math.h>
#include <time.h>

#define WIDTH 1000
#define HEIGHT 1000


bool is_generated_point_in_circle() {
    int pointX = rand() % WIDTH;
    int pointY = rand() % HEIGHT;

    long double distance_from_center = sqrt(pow(pointX - WIDTH / 2, 2) + pow(pointY - HEIGHT / 2, 2));

    return distance_from_center <= 500;
}


int main(const int argc, const char **argv) {
    srand(time(NULL));

    long long int total_points = 0;
    long long int circle_points = 0;
    long double pi = 0;

    for (;;) {
        int is_inside = is_generated_point_in_circle();
        
        total_points++;
        if (is_inside == 1) {
        circle_points++;
        }

        pi = (long double) circle_points / total_points * 4;

        printf("%Lf\n", pi);
    }

  return 0;
}
