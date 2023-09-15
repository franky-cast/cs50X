// P-set 1
#include "cs50.h"
#include "cs50.c"
#include <stdio.h>
#include <string.h>

void mario();

int main(void)
{   
    mario();
    return 0;
}


// problem 2 - mario
void mario()
{
    int n;
    do
    {
        n = get_int("How tall pyramid (enter between 1 and 8 - inclusive): ");
    }
    while (n < 1 || n > 8);
    // printf("\n \n");

    int countPyr1 = n - 1;
    int secondLoopCount = n;
    for (int i = 0; i < n; i++)
    {
        for (int l = 0; l < secondLoopCount + 3; l++)
        {
            if (l < countPyr1 || l == n || l == n + 1)
            {
                printf(" ");        
            }
            else 
            {
                printf("#");
            }
        }

        if (secondLoopCount <= n + 6)
        {
            secondLoopCount++;
        }
        countPyr1 = countPyr1 - 1;
        printf("\n");
    }
}