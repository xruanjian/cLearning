#include <stdio.h>

#define LEN 5
//几种经典的排序方法汇总
//1:插入排序法

//打印数组的函数
void printArray(int a[],int length){
      for(int j=0;j<length;j++){
        printf("%d   ",a[j]);
        }
        printf("\n");
    }
    
    
//插入排序
void insertion_sort(int a[],int length){
    void printArray(int a[],int length);
    int i,j,key;
    for(j=1;j<length;j++){
        printArray(a,length);
        key=a[j];
        i=j-1;
        while(i>=0 && a[i]>key){
            a[i+1]=a[i];
            i--;
            }
            a[i+1]=key;
        }
        printArray(a,length);
    }
    
int main(){
    int a[]={12,88,976,94,125};
    insertion_sort(a,sizeof(a)/4);
     
    }