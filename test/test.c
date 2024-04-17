#include <stdio.h>

int main(){
    int test; 
    test = 1;

    #define TEST 1

    #ifndef TEST
    #define TEST
        test = 2;
    #endif

    printf("%d\n", test);

    return 0;
}