#include<stdio.h>
#define N 6

int main(){

int T[N];
int j;

for(j=0;j<N;j++)
{
	T[j]=4;
}

int i;
int T2[N];
for(i=0; i<N; i++)
{
    memcpy(T2[i], T[i], N*sizeof(int));
}

for(j=0;j<N;j++)
{
	printf("| %d |",T2[j]);
}


	return 0;
}