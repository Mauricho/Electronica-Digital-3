#include <stdio.h>

/*
    Switch funcionando mal!!
*/

void divide(int *x, int *y, int by)
{
    *x /= by;
    *y /= by;
}

int main()
{
    int position = 2;

    // switch (position)
    // {
    // case 1:
    //     printf("Gold");
    // case 2:
    //     printf("Silver");
    // case 3:
    //     printf("Bronze");
    // default:
    //     printf("No medal");
    // }

    // for (int i = 1; i < 10; i++)
    // {
    //     if (i == 5)
    //     {
    //         break;
    //         //continue;
    //     }
    //     printf("%d\n", i);
    // }
    // for (int i = 3; i < 10; i++)
    // {
    //     if (i == 5)
    //     {
    //         continue;
    //     }
    //     if (i == 7)
    //     {
    //         break;
    //     }
    //     printf("%d\n", i);
    // }

    // int ages[2][4] = {
    //     {1, 2, 3, 4},
    //     {5, 6, 7, 8}};
    // printf("%d", ages[1][2]);

    // char text[] = "some text\n";
    // printf("%s", text);

    // char word[20];
    // scanf("%s", word);
    // printf("%s", word);

    // char name[50];
    // fgets(name, 50, stdin);
    // printf("Hi %s.", name);

    // int age = 24;

    // int* p = &age;

    // printf("%d", *p);

    // int x = 4200, y = 670;

    // divide(&x, &y, 10);

    // printf("%d %d", x, y);

    int x[] = {1, 2, 3, 4};
    int *p = x;

    for (int i = 0; i < 4; i++)
    {
        printf("%d \n", *p);
        p++;
    }

    // printf("%d", *x);

    return 0;
}
