#include <stdio.h>

//两个数因为是int基础类型，所以形参是传值，然后实例化的是一个备份并不会改变原来的值

void swap(int a,int b){   
    int m;    
    m=a;  
    *a=*b;     
    *b=m;     
}








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
