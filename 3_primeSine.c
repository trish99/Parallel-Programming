#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double sines[1000];
int primes[1000];

void prime_table(int prime_num)
{
  int i, j, n, prime;
  // i - number
  // n - to keep a check no of prime numbers
  // prime - used for 'True or False'
  i = 2;
  n = 0;
  while(n < prime_num)
  {
    prime = 1;
    for(j = 2; j < i; j++)
      if((i % j) == 0)
      {
        prime = 0;
        break;
      }
    if(prime)
    {
      primes[n] = i;
      n++;
    }
    i++;
  }
}

void sine_table(int sine_num)
{
  int i,j;
  double a;
  for(i = 0; i < sine_num; i++)
    sines[i] = sin(i * M_PI/180);
}


int main(){
	int size, y, z;
	printf("Enter the the number of primes and sine table values required : \n");
	scanf("%d", &size);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			prime_table(size);
			for(y = 0; y < size; y++){
				printf("%d \n",primes[y]);
			}
		}

		#pragma omp section
		{
			sine_table(size);
			for(z = 0; z < size; z++){
				printf("%lf \n",sines[z]);
			}
		}
	}
  return 0;
}
