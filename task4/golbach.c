#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculate_primes.c"
int calculate_primes(int primes[], int n);
int golbach(int primes[],int n,int length);
int counter,x,y;

int main()
{
    int g;
    printf("Enter the number: ");
    scanf("%d",&g);
    int *primes;
    primes = (int*)malloc(g * sizeof(int));
    calculate_primes(primes, g);
    int n;
    int m;
    printf("Введите первое число:");
    scanf("%d",&n);
    printf("Введите второе число:");
    scanf("%d",&m);
    if ((4 <= n < m < 10000000) == 0){
        return -1;
    }
    int chetnum[m-n];
    for (int count = 0,i = n; count < m-n; count++,i++){
        chetnum[count] = i;
        
    }
    int testlen = (m-n)/2;
    for (int count = 0; count < sizeof(chetnum)/sizeof(chetnum[0]);count++ ){
        if (chetnum[count] % 2  != 0 || chetnum[count] == 2){
            chetnum[count] = 0;
        }  
    } 
    for (int i = 0; i < sizeof(primes)/sizeof(primes[0]); i++){
        if (primes[i] == 0)
            continue;
        printf("%d ",primes[i]);
    }
    for (int count = 0; count < sizeof(chetnum)/sizeof(chetnum[0]);count++){
        golbach(primes,chetnum[count],chetnum[count]);

        if (chetnum[count] == 0)
            continue;
        else{printf("%d %d %d %d\n",chetnum[count],counter,x,y);}

    }


} 
int golbach(int primes[], int n,int length)
{
    int passvar = 10000;
    x = 0;
    counter = 0;
    y = 0;
    for (int i = 0; i <= length/2;i++){
        for (int j = 0;j <= length;j++) {
            if (primes[i] + primes[j] == n){
                if (passvar == primes[i] + primes[j])
                    counter ++;
                if (passvar > primes[i] + primes[j]){
                    passvar = primes[i] + primes[j];
                    counter ++;
                    x = primes[i];
                    y = primes[j];
                
                }
            }
        }
    }  
}

