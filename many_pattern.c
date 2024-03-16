#include <stdio.h>
#include <stdlib.h>

unsigned int seed = 10;

int *str;
int res[5] = {1,-1,1,1,1};

float *w;

int deep = 1000;

int define_stored()
{
    str = calloc(5*3, sizeof(int));

    for (int i=0 ; i<3 ; i++)
    {
        for (int j=0 ; j<5 ; j++)
        {
            int rnd = rand() % 2;
            *(str + 3*i + j) = (rand() % 2)*2 - 1;
        }
    }
}

int sign(float f)
{
    if (f>=0.0f)  return 1;
    else return -1;
}

int hebb_single_pattern()
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

int hopfield_nn()
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

void print_stored(int *arr)
{
    for (int i=0 ; i<3 ; i++)
    {
        for (int j=0 ; j<5 ; j++)
        {
            printf("%d,", *(arr + 3*i + j));
        }
        printf("\n");
    }
}

int main() 
{
    define_stored();

    srand(seed);

    printf("stored array:\n");
    print_stored(str);
    printf("\n\ninitial nn condition:");
    print_array(res);

    hebb_single_pattern();
    hopfield_nn();

    printf("\n\nmemory response");
    print_array(res);

    free(w);

    return 0;
}