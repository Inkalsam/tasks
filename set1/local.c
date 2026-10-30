#include <stdio.h>
#include "tasks.h"

void local_tests(void) {
    // You can use this file for testing functions locally
        int x = 42;
    if (is_odd(x)) {
        printf("%d is odd\n", x);
    } else {
        printf("%d is even\n", x);
    }

    // Calculates the area of a rectangle
// Example: calc_area(2, 3) -> 6
long area = calc_area(2, 3);
printf("The area is: %ld\n", area);



}

