#include <stdio.h>

void swap(int *a,int *b){
    int m;
    m=*a;
    *a=*b;
    *b=m;
    }

 
int main(){
       
        int j=0,k=8;
        
        swap(&j,&k);
        printf("%d  %d",j,k);
     }