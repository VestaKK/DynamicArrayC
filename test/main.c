#include "defines.h"
#include "containers/darray.h"

typedef struct Point {
    real32 x;
    real32 y;
} Point;

int main(void) {
    uint32* int_darray = darray_create(uint32);

    for (int i=0; i<10; i++) {
        darray_push(int_darray, i*3);
    }

    for (int i=0; i<darray_count(int_darray); i++) {
        printf("%d ", int_darray[i]);
    }

    printf("\n");

    Point* point_Array = darray_create(Point);

    for (int i=0; i<10; i++) {
        Point newPoint = {i, i+1};
        darray_push(point_Array, newPoint);
    }

    for (int i=0; i<darray_count(point_Array); i++) {
        printf("X: %f, Y: %f \n", point_Array[i].x, point_Array[i].y);
    }

    darray_destroy(int_darray);

    darray_destroy(point_Array);
}