#include<stdio.h>
#include<stdlib.h>

int main(){
    ABC:
    int n;
    scanf("%d",&n);
    printf("%d",n);
    if(n==12){
        return 0;
    }
    else{
        goto ABC;
    }
}