#include <stdio.h>
#include <stdlib.h>

unsigned int seed = 10;

int str[5] = {-1,1,-1,1,-1};
int res[5] = {1,-1,1,1,1};

float *w;

int deep = 1000;

int sign(float f)
{
    if (f>=0.0f)  return 1;
    else return -1;
}

int initialize()
{
    w = calloc(25, sizeof(float));

    for (int i=0 ; i<5 ; i++)
    {
        for (int j=0 ; j<5 ; j++)
        {
            if (i != j)
            {
                *(w + 5*i + j) = (*(str + i) * (float)*(str + j)) / 5.0f;
            }
        }
    }
}

int recall()
{
    float sgn;
    int rnd;
    for (int t=0 ; t<deep ; t++)
    {
        rnd = rand() % 5;
        sgn = 0.0f;
        for (int j=0 ; j<5 ; j++)
        {
            if (rnd != j)
            {
                sgn += (float)*(w +5*rnd + j) * *(res + j);
            }
        }
        *(res + rnd) = sign(sgn);
    }
}

void print_array(int arr[5])
{
    for (int i=0 ; i<5 ; i++)
    {
        printf("\n%d,", *(arr + i));
    }
}

int main() 
{
    srand(seed);

    printf("stored array:");
    print_array(str);
    printf("\n\ninitial nn condition:");
    print_array(res);

    initialize();
    recall();

    printf("\n\nmemory response");
    print_array(res);

    free(w);

    return 0;
}