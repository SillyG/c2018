#include <stdio.h>
#include <stdlib.h>
#define LEN 60 

FILE *fp;
typedef struct node{
	int id;
	char A[22]; 
	struct node *next;
}node; 

node *head,*p,*r;

void node_creat(){
	int i;
	head=malloc(sizeof(node));
	head->next=NULL;
	r=head;
	fp=fopen("list.txt","r+");
	p=malloc(sizeof(node));   
	while(fscanf(fp,"%d",&p->id)!=EOF){
		fgets(p->A,LEN,fp);
		p->next=NULL;
		r->next=p;
		r=p; 
		p=malloc(sizeof(node));
	} 
	free(p);
	fclose(fp);
}

void node_delete(int a){
	p=head;
	while(p->next!=NULL&&p->next->id!=a){
		p=p->next; 
	}
	r=p->next;
	p->next=r->next;
	free(r);
} 

int main(){
	int i=0;
	node_creat();
	while(1){
		system("cls");
		printf("1.��ʾ����б�\n2.���\n3.����\n4.�˳�����\n");
		node_creat();
		int x;
		scanf("%d",&x);
		switch(x){
			case 1:
				system("cls");
				p=head->next;
				if(head->next==NULL){
					printf("The list is empty!");
					system("pause");
					break;
				} 
				while(p->next!=NULL){
					printf("%d%s",p->id,p->A);
					p=p->next;
				}
				printf("%d%s",p->id,p->A);
				system("pause");
				break;
			case 2:
				system("cls");
				printf("��Ҫ������ٻ��\n");
				scanf("%d",&x); 
				printf("����������ź��ͺź�����(�м��Կո����)��\n");
				char A[51];
				int N,i,gid;
				i=0;
				fp = fopen("list.txt","a+");
				while(i<x){
					i++;
					scanf("%d %s %d",&gid,A,&N);
					fprintf(fp,"%d �ͺţ�%s ������%d\n",gid,A,N);
				}
				fclose(fp);
				break;
			case 3:
				system("cls");
				printf("��������Ҫ�����Ļ�����(����0���������������):\n");
				while(1){
					int y;
					scanf("%d",&y);
					if(y==0) break; 
					node_delete(y);
				}
				p=head->next;
				while(p->next!=NULL){ 
					fprintf(fp,"%d%s",p->id,p->A);
					p=p->next;
				} 
				break;
			case 4:
				return 0;
				break;
			default:
				system("cls");
				printf("Input error!");
				system("pause");
				break;
		}
	}
	return 0; 
} 
