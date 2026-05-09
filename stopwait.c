#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, noOfFrames, x, x1 = 10, x2;

    for (i = 0; i < 200; i++)
        rand();

    noOfFrames = rand() % 100;

    i = 1;
    j = 1;

    noOfFrames = noOfFrames / 8;

    printf("\nNumber of frames is %d", noOfFrames);

    while (noOfFrames > 0)
    {
        printf("\nSending frame %d", i);

        srand(x1++);
        x = rand() % 10;

        if (x % 2 == 0)
        {
            for (x2 = 1; x2 < 2; x2++)
            {
                printf("waiting for %d seconds \n", x2);
            }

            printf("\nSending frame %d", i);

            srand(x1++);
            x = rand() % 10;
        }

        printf("\nAck for frame %d", j);

        noOfFrames -= 1;
        i++;
        j++;
    }

    printf("\nEnd of Stop and Wait Protocol");

    return 0;
}
