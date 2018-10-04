#include <stdio.h>

/*
两个错误示例
swap1最容易犯错，因为int基础数据类型，作为形参是传值操作，相当于对a,b进行的备份进行操作，而不是传值操作,所以交换后，并不会改变原来的两个数
void swap1(int a,int b){
    int m;
    m=a;
    a=b;
    b=m;
    }
    
swap2交换的是指针的备份，也并不会改变两个数
void swap2(int *a,int *b){
    int *m;
    m=*a;
    *a=*b;
    *b=m;
    }
*/

//唯一正确的交换方法，采用指针作为形参进行传址操作，然后用一个实参值进行交换，最终真正改变两个值
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