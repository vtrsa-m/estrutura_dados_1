#include <stdio.h>

void trocar(int *x,int *y){
  int temp = *x;
  *x = *y;
  *y = temp;   
}

void trocarp(int **x,int **y){
  int *temp = *x;
  *x = *y;
  *y = temp;   
}

int main(){
  int c,d;
  int *a=&c, *b=&d;
  *a = 10;
  *b = 5000;
  trocar(a,b);
  printf("a = %d \nb = %d\n",*a,*b);
}

