#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<string.h>
#define WIDTH 60
#define SPEED 25  //��ֵԽСԽ�� 
int main(){
	system("mode con cols=60 lines=20");  //�ı����̨���ڳߴ� 
	//�Ϸ��������60��ΪWIDTH�������֪����ν�� 
	int i,j,n;
	char A[WIDTH] ;
	gets(A);
	n=strlen(A);
	int blank=WIDTH-n;   //�հ״��ܳ�blank���� 
	while(1){
		for(i=0;i<2*blank;i++){
			if(i<blank){
				for(j=0;j<i;j++){
					printf(" ");
				}
			}
			else{
				for(j=blank;j>i-blank;j--){
					printf(" ");
				}
			}
			for(j=0;j<n;j++){
				printf("%c",A[j]);
			}
			Sleep(SPEED);
			system("cls");
	}
	}
} 
