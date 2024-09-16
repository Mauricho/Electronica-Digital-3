#include <stdio.h>

int main()
{
    printf("I like pizza!\n");
    printf("It's really good!\n");

    int x;   // declaration
    x = 123; // initialization

    int y = 321; // declaration + initialization

    int age = 21;        // integer
    float gpa = 2.05;    // floating point number
    char grade = 'C';    // single character
    char name[] = "Bro"; // array of characters

    printf("Hello %s\n", name);
    printf("You are %d years old\n", age);
    printf("Your average grade is %c\n", grade);
    printf("Your gpa is %f \n", gpa);

    float item1 = 5.75;
    float item2 = 10.00;
    float item3 = 100.99;

    printf("Item 1: $%.2f\n", item1);
    printf("Item 1: $%.2f\n", item1);
    printf("Item 1: $%.2f\n", item1);

    return 0;
}