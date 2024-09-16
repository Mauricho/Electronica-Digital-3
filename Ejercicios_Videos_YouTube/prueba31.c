#include <stdio.h>

//defino una macro RATE
//#define RATE 0.08      

#ifndef TERM                
//defino una macro TERM                     
    #define TERM 24                              
#endif

int main() {
    #ifdef RATE  // pregunto si esta definida RATE
        #undef RATE                         // indico que voy a redefinir una macro
        printf("Redefining RATE\n");
        // defino nuevamente la macro RATE
        #define RATE 0.068                 
    #else       // this branch will not be compiled
        #define RATE 0.05
    #endif

    printf("%f %d\n", RATE, TERM);

    return 0;
}