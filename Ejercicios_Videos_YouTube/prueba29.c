#include <stdio.h>
#define VERY_LONG_CONSTANT \
23.678901

#define MAX 100
#define MIN 0
#       define SQUARE(x) \
        x*x
int main(){
    printf("%f\n", VERY_LONG_CONSTANT*SQUARE(2));
    return 0;
}