#include <stdio.h>
#include "mymalloc.h"

int main()
{
    int *ptr1 = (int *)MyMalloc(sizeof(int));                      // 4
    printf("ptr1 : %d\tAllocated size : %d\n", ptr1, sizeof(int)); // 24

    double *ptr2 = (double *)MyMalloc(sizeof(double));                // 8
    printf("ptr2 : %d\tAllocated size : %d\n", ptr2, sizeof(double)); // 28+24=52

    char *ptr3 = (char *)MyMalloc(100 * sizeof(char));     // 100
    printf("ptr3 : %d\tAllocated size : %d\n", ptr3, 100); // 52+120=172

    struct node *ptr4 = (struct node *)MyMalloc(10 * sizeof(struct node)); // 200
    printf("ptr4 : %d\tAllocated size : %d\n", ptr4, 200);                 // 220+172=392

    float *ptr5 = (float *)MyMalloc(10 * sizeof(float));  // 40
    printf("ptr5 : %d\tAllocated size : %d\n", ptr5, 40); // 392+60=452

    // myFree(ptr1); // free 4
    // myFree(ptr2); // free 4+8+32=44
    // myFree(ptr3); // free 44+100+32=176

    int *ptr6 = (int *)MyMalloc(24000);                      // 24000
    printf("ptr6 : %d\tAllocated size : %d\n", ptr6, 24000); // 452+24020=24472

    int *ptr7 = (int *)MyMalloc(500);                      // 500
    printf("ptr7 : %d\tAllocated size : %d\n", ptr7, 500); // 24472+520=24992

    int *ptr8 = (int *)MyMalloc(200);                      // 200
    printf("ptr8 : %d\tAllocated size : %d\n", ptr8, 200); // 24992+220=25212 overflow

    int *ptr9 = (int *)MyMalloc(200);                      // 200
    printf("ptr9 : %d\tAllocated size : %d\n", ptr9, 200); // overflow

    int *ptr10 = (int *)MyMalloc(50);
    printf("ptr10 : %d\tAllocated size : %d\n", ptr10, 50); // overflows

    // myFree(ptr4); // free

    int *ptr11 = (int *)MyMalloc(220);
    printf("ptr11 : %d\tAllocated size : %d\n", ptr11, 220);

    int *ptr12 = (int *)MyMalloc(100);
    printf("ptr12 : %d\tAllocated size : %d\n", ptr12, 100);

    int *ptr13 = (int *)MyMalloc(30);
    printf("ptr13 : %d\tAllocated size : %d\n", ptr13, 30);

    int *ptr14 = (int *)MyMalloc(500);
    printf("ptr14 : %d\t\tAllocated size : %d\n", ptr14, 500);

    return 0;
}