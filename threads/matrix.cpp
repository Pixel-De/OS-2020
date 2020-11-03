#include<stdio.h> 
#include<pthread.h> 
#include<unistd.h> 
#include<stdlib.h> 

void *mult(void* arg) 
{ 
	int *data = (int *)arg; 
	int k = 0, i = 0; 
	int x = data[0]; 
	for (i = 1; i <= x; i++) 
		k += data[i]*data[i+x]; 
	int *p = (int*)malloc(sizeof(int)); 
		*p = k; 
	pthread_exit(p); 
} 

int main(){ 
	int MAX,r1,c1,r2,c2;
	printf("hemjeesee oruulna uu'\n A(r,c),B(r,c)\n");
	scanf("%d%d%d%d", &r1, &c1,&r2,&c2);
	int A[r1][c1], B[r2][c2],i,j,k, max=r1*c2, s=0; 
	pthread_t *t; 
	for (i = 0; i < r1; i++) 
		for (j = 0; j < c1; j++) {
			printf("a[%d][%d]: ",i,j);
				scanf("%d", &A[i][j]);
		}
		
	for (i = 0; i < r2; i++) 
		for (j = 0; j < c2; j++) 
		{
			printf("b[%d][%d]: ",i,j);
			scanf("%d", &B[i][j]);
		}
		
			
//	for (i = 0; i < r1; i++){ 
//		for(j = 0; j < c1; j++) 
//			printf("%d ",A[i][j]); 
//		printf("\n"); 
//	} 		 
//	for (i = 0; i < r2; i++){ 
//		for(j = 0; j < c2; j++) 
//			printf("%d ",B[i][j]); 
//		printf("\n");	 
//	} 
	t = (pthread_t*)malloc(max*sizeof(pthread_t)); 
	int* data = NULL; 
	for (i = 0; i < r1; i++) 
		for (j = 0; j < c2; j++) 
			{
			data = (int *)malloc((20)*sizeof(int)); 
			data[0] = c1; 
			for (k = 0; k < c1; k++) 
				data[k+1] = A[i][k]; 
			for (k = 0; k < r2; k++) 
				data[k+c1+1] = B[k][j]; 
				pthread_create(&t[s++], NULL, mult, (void*)(data));
			} 
	for (i = 0; i < max; i++) 
	{ 
	void *k;
	pthread_join(t[i], &k); 
		int *p = (int *)k; 
	printf("%d ",*p); 
	if ((i + 1) % c2 == 0) 
		printf("\n"); 
	} 
return 0; 
} 

