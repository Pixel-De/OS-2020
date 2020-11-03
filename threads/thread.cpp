#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include<strsafe.h>
#include<process.h>

void f(void *a){
int h=*((int*)a);
    printf("%d\n",h);
    _endthread();
}
int main(){ 
int ut;
int i,s=0,j;
HANDLE t;
for(i=2;i<100;i++){
	for(j=2;j<=i/2;j++){
		if(i%j==0) s++;		
	} if(s==0){
		ut=i;
        t = (HANDLE) _beginthread(f,0,&ut);
        WaitForSingleObject(t,INFINITE);	
	} s=0;
}
if (t == NULL)
printf("Thread uusgej chadsangui, aldaa ni: %d.\n", GetLastError());
if (CloseHandle(t) != 0)
printf("Amjillttai.\n");
return 0;
}
