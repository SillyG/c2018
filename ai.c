#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 
#include <conio.h>
#define WID 100			//������ȵ����ޣ���Լ������̣� 
#define BOTTOM 4		//��ͨ��������
#define KILLB 4
#define BLANK 0			//��λ 
#define BLACK 1			//�ٶ��ڷ�Ϊ���ԣ���һ�����֣� 
#define WHITE 2			//�׷�������ң���һ�����֣� 
#define TOFIVE 1000000 //���� 
#define LIVEFOUR 100000	//���� 
#define	LIVETHREE 49000	//���������� ��˫������ͬ�ڻ���,�����������ڻ����� 
#define LIVETWO 900	//��������������ǰ�ں���Ҫ�������и��������� 
#define LIVEONE 10		//��һ 
#define MAX(A,B) (((A)-(B))>>31 ? (B) : (A))  //>>31��ȡ��ֵ�ķ���λ
#define MIN(A,B) (((A)-(B))>>31 ? (A) : (B))
const int INF = 1e9 + 7;//�����  
int tbl[15][15];		//����
struct node{			//�������ڵ� 
	int x,y;
	int point;
	int flg;			//��flg=1��ΪҪ��֦�Ľڵ� 
}; 
struct axis{			//���ڼ�¼��������� 
	int x,y;
}last[235];
int peak[BOTTOM+1];		//��¼dfsÿһ��ļ�ֵ  
HANDLE hout; 

void qusort(struct node array[], int maxlen, int begin, int end){  
    int i, j;  
    if(begin < end){  
        i = begin + 1;  // ��array[begin]��Ϊ��׼������˴�array[begin+1]��ʼ���׼���Ƚϣ�  
        j = end;        // array[end]����������һλ  
        while(i < j){  
            if(array[i].point < array[begin].point){  // ����Ƚϵ�����Ԫ�ش��ڻ�׼�����򽻻�λ�á�    
                struct node tmp;
				tmp = array[i];
				array[i]=array[j];
				array[j]=tmp; 
                j--;  
            }  
            else{  
                i++;  // �����������һλ���������׼���Ƚϡ�  
            }  
        }  
        if(array[i].point <= array[begin].point){  
            i--;  
        }  
        struct node tmp;
		tmp = array[i];
		array[i]=array[begin];
		array[begin]=tmp;  
        qusort(array, maxlen, begin, i);  
        qusort(array, maxlen, j, end);  
    }  
}
int isin(int a,int b){	//�ж��ǲ��ǳ��������� 
	if(a<0||a>14){
		return 0;
	} 
	if(b<0||b>14){
		return 0;
	}
	return 1;
}
int pot(int x){	 //��� 
	if(x==5)	return TOFIVE;
	if(x==4)	return LIVEFOUR;
	if(x==3)	return LIVETHREE;
	if(x==2)	return LIVETWO;
	if(x==1)    return LIVEONE;
	return 0;
}
int ops(int x){  //	������ɫ 
 	if(x==BLACK) return WHITE;
	if(x==WHITE) return BLACK;
}
int whowin(){
	for(int turn=1;turn<=2;turn++){ 
		for(int i=0;i<15;i++){
		
			for(int j=0;j<15;j++){	//ˮƽ 
				if(tbl[i][j]==turn){
					int count=1;
					int k=j+1;
					while(isin(i,k)&&tbl[i][k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					j=k; //��k��ʼ�������� 
					if(count>=5) return turn;
				}
			} 
			
			for(int j=0;j<15;j++){	//��ֱ 
				if(tbl[j][i]==turn){
					int count=1;
					int k=j+1;
					while(isin(k,i)&&tbl[k][i]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					j=k; //��k��ʼ�������� 
					if(count>=5) return turn;
				}
			}
			
			for(int j=0;j<15-i;j++){	//��������������б����
				 if(tbl[i+j][j]==turn){
					int count=1;
					int k=j+1;
					while(isin(i+k,k)&&tbl[i+k][k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					j=k; //��k��ʼ�������� 
					if(count>=5) return turn;
				}
			}
			
			for(int j=1;j<15-i;j++){	//��������������б����
				 if(tbl[j][i+j]==turn){
					int count=1;
					int k=j+1;
					while(isin(k,i+k)&&tbl[k][i+k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					j=k; //��k��ʼ�������� 
					if(count>=5) return turn;
				}
			}
			
			for(int j=0;j<=i;j++){	//��������������б����
				 if(tbl[i-j][j]==turn){
					int count=1;
					int k=j+1;
					while(isin(i-k,k)&&tbl[i-k][k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					j=k; //��k��ʼ�������� 
					if(count>=5) return turn;
				}
			}
			
			for(int j=1;j<15-i;j++){	//��������������б����
				 if(tbl[15-j][i+j]==turn){
					int count=1;
					int k=j+1;
					while(isin(15-k,i+k)&&tbl[15-k][i+k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					j=k; //��k��ʼ�������� 
					if(count>=5) return turn;
				}
			}
		}
	}
	return 0;
}
int judge(){	//�жϾ��ƣ�����Ϊȫ�ֱ���tbl 
	int score[2]={};
	for(int turn=1;turn<=2;turn++){	//��Ĭ�ϵ����Ǻ�ɫ 
		for(int i=0;i<15;i++){
		
			for(int j=0;j<15;j++){	//ˮƽ��� 
				if(tbl[i][j]==turn){
					int count=1;
					int k=j+1;
					while(isin(i,k)&&tbl[i][k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					if(tbl[i][j-1]==ops(turn)||!isin(i,j-1)){
						count--;
						if(tbl[i][k]==ops(turn)||!isin(i,k)){
							count=0;
						} 
					}
					else if(tbl[i][k]==ops(turn)||!isin(i,k)){
						count--;
					} 
					j=k; //��k��ʼ�������� 
					score[turn-1]+=pot(count);
				}
			} 
			
			for(int j=0;j<15;j++){	//��ֱ��� 
				if(tbl[j][i]==turn){
					int count=1;
					int k=j+1;
					while(isin(k,i)&&tbl[k][i]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					if(tbl[j-1][i]==ops(turn)||!isin(j-1,i)){
						count--;
						if(tbl[k][i]==ops(turn)||!isin(k,i)){
							count=0;
						} 
					}
					else if(tbl[k][i]==ops(turn)||!isin(k,i)){
						count--;
					} 
					j=k; //��k��ʼ�������� 
					score[turn-1]+=pot(count);
				}
			}
			
			for(int j=0;j<15-i;j++){	//��������������б����
				 if(tbl[i+j][j]==turn){
					int count=1;
					int k=j+1;
					while(isin(i+k,k)&&tbl[i+k][k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					if(tbl[i+j-1][j-1]==ops(turn)||!isin(i+j-1,j-1)){
						count--;
						if(tbl[i+k][k]==ops(turn)||!isin(i+k,k)){
							count=0;
						} 
					}
					else if(tbl[i+k][k]==ops(turn)||!isin(i+k,k)){
						count--;
					} 
					j=k; //��k��ʼ�������� 
					score[turn-1]+=pot(count);
				}
			}
			
			for(int j=1;j<15-i;j++){	//��������������б����
				 if(tbl[j][i+j]==turn){
					int count=1;
					int k=j+1;
					while(isin(k,i+k)&&tbl[k][i+k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					if(tbl[j-1][i+j-1]==ops(turn)||!isin(j-1,i+j-1)){
						count--;
						if(tbl[k][i+k]==ops(turn)||!isin(k,i+k)){
							count=0;
						} 
					}
					else if(tbl[k][i+k]==ops(turn)||!isin(k,i+k)){
						count--;
					} 
					j=k; //��k��ʼ�������� 
					score[turn-1]+=pot(count);
				}
			}
			
			for(int j=0;j<=i;j++){	//��������������б����
				 if(tbl[i-j][j]==turn){
					int count=1;
					int k=j+1;
					while(isin(i-k,k)&&tbl[i-k][k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					if(tbl[i-j+1][j-1]==ops(turn)||!isin(i-j+1,j-1)){
						count--;
						if(tbl[i-k][k]==ops(turn)||!isin(i-k,k)){
							count=0;
						} 
					}
					else if(tbl[i-k][k]==ops(turn)||!isin(i-k,k)){
						count--;
					} 
					j=k; //��k��ʼ�������� 
					score[turn-1]+=pot(count);
				}
			}
			
			for(int j=1;j<15-i;j++){	//��������������б����
				 if(tbl[15-j][i+j]==turn){
					int count=1;
					int k=j+1;
					while(isin(15-k,i+k)&&tbl[15-k][i+k]==turn){ //�ж�������Ŀ 
						count++;
						k++;
					}
					if(tbl[15-j+1][i+j-1]==ops(turn)||!isin(15-j+1,i+j-1)){
						count--;
						if(tbl[15-k][i+k]==ops(turn)||!isin(15-k,i+k)){
							count=0;
						} 
					}
					else if(tbl[15-k][i+k]==ops(turn)||!isin(15-k,i+k)){
						count--;
					} 
					j=k; //��k��ʼ�������� 
					score[turn-1]+=pot(count);
				}
			}
		}
	}
	return score[0]-score[1];
}
int evalute(int x,int y,int turn){
	int ANS=0,ob=2,cnt=1; //ANS��¼�÷֣�ops��¼�����Ķ������Ӹ��� 
	for(int j=1;j<=4;j++){	//ˮƽ�����ж� 
		if(isin(x+j,y)){
			if(tbl[x+j][y]==turn){
				cnt++;
				if(cnt>=5){
					if(turn == BLACK)
						return TOFIVE;
					if(turn == WHITE)
						return -TOFIVE;
				}
			}
			if(tbl[x+j][y]==ops(turn)){
				ob--;
				cnt--;
				break;
			}
			if(tbl[x+j][y]==BLANK){
				break;	
			}
		}
		else{
			cnt--;
			ob--;
			break;
		}		
	}
	for(int j=-1;j>=-4;j--){	//���� 
		if(isin(x+j,y)){
			if(tbl[x+j][y]==turn){
				cnt++;
				if(cnt>=5) {
					break;
				}
			} 
			if(tbl[x+j][y]==ops(turn)){
				cnt--;
				ob--;
				break;
			}
			if(tbl[x+j][y]==BLANK){
				break;
			}
		}
		else{
			cnt--;
			ob--;
			break;
		}
	}
	if(ob<=0||cnt<0) cnt=0;
	if(cnt>5) cnt=5;
	ANS+=pot(cnt);
	
	ob=2;
	cnt=1; 
	for(int j=1;j<=4;j++){	//��ֱ�����ж� 
		if(isin(x,y+j)){
			if(tbl[x][y+j]==turn){
				cnt++;
				if(cnt>=5) {
					break;
				}	
			}
			if(tbl[x][y+j]==ops(turn)){
				ob--;
				cnt--;
				break;
			}
			if(tbl[x][y+j]==BLANK){
				break;	
			}
		}
		else{
			cnt--;
			ob--;
			break;
		}		
	}
	for(int j=-1;j>=-4;j--){	//���� 
		if(isin(x,y+j)){
			if(tbl[x][y+j]==turn){
				cnt++;
				if(cnt>=5) {
					break;
				}
			} 
			if(tbl[x][y+j]==ops(turn)){
				cnt--;
				ob--;
				break;
			}
			if(tbl[x][y+j]==BLANK){
				break;
			}
		}
		else{
			cnt--;
			ob--;
			break;
		}
	}
	if(ob<=0||cnt<0) cnt=0;
	if(cnt>5) cnt=5;
	ANS+=pot(cnt);

	ob=2;
	cnt=1;
	for(int j=1;j<=4;j++){	
		if(isin(x+j,y-j)){
			if(tbl[x+j][y-j]==turn){
				cnt++;
				if(cnt>=5) {
					break;
				}
			}
			if(tbl[x+j][y-j]==ops(turn)){
				ob--;
				cnt--;
				break;
			}
			if(tbl[x+j][y-j]==BLANK){
				break;	
			}
		}
		else{
			cnt--;
			ob--;
			break;
		}		
	}
	for(int j=-1;j>=-4;j--){	 
		if(isin(x+j,y-j)){
			if(tbl[x+j][y-j]==turn){
				cnt++;
				if(cnt>=5) {
					break;
				}
			} 
			if(tbl[x+j][y-j]==ops(turn)){
				cnt--;
				ob--;
				break;
			}
			if(tbl[x+j][y-j]==BLANK){
				break;
			}
		}
		else{
			cnt--;
			ob--;
			break;
		}
	}
	if(ob<=0||cnt<0) cnt=0;
	if(cnt>5) cnt=5;
	ANS+=pot(cnt);
	
	ob=2;
	cnt=1;
	for(int j=1;j<=4;j++){	
		if(isin(x+j,y+j)){
			if(tbl[x+j][y+j]==turn){
				cnt++;
				if(cnt>=5) {
					break;
				}
			}
			if(tbl[x+j][y+j]==ops(turn)){
				ob--;
				cnt--;
				break;
			}
			if(tbl[x+j][y+j]==BLANK){
				break;	
			}
		}
		else{
			cnt--;
			ob--;
			break;
		}		
	}
	for(int j=-1;j>=-4;j--){	 
		if(isin(x+j,y+j)){
			if(tbl[x+j][y+j]==turn){
				cnt++;
				if(cnt>=5) {
					break;
				}
			} 
			if(tbl[x+j][y+j]==ops(turn)){
				cnt--;
				ob--;
				break;
			}
			if(tbl[x+j][y+j]==BLANK){
				break;
			}
		}
		else{
			cnt--;
			ob--;
			break;
		}
	}
	if(ob<=0||cnt<0) cnt=0;
	if(cnt>5) cnt=5;
	ANS+=pot(cnt);
	
	return ANS;
}
int generator(struct node s[],int turn){	//���ɿ������ӵĵ㼯����book��¼ 
	int pc=0;
	int note[15][15]={};
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			if(tbl[i][j]!=BLANK){
				for(int k=-2;k<=2;k++){
					if(k==0) continue;
					if(isin(i+k,j)){
						if(tbl[i+k][j]==BLANK&&!note[i+k][j]){
							s[pc].point = evalute(i+k,j,turn);
							s[pc].x=i+k;
							s[pc++].y=j;
							note[i+k][j] = 1;
						} 
					}
					if(isin(i,j+k)){
						if(tbl[i][j+k]==BLANK&&!note[i][j+k]){
							s[pc].point = evalute(i,j+k,turn);
							s[pc].x=i;
							s[pc++].y=j+k;
							note[i][j+k] = 1;
						} 
					}
					if(isin(i+k,j+k)){
						if(tbl[i+k][j+k]==BLANK&&!note[i+k][j+k]){
							s[pc].point = evalute(i+k,j+k,turn);
							s[pc].x=i+k;
							s[pc++].y=j+k;
							note[i+k][j+k] = 1;
						} 
					}
					if(isin(i+k,j-k)){
						if(tbl[i+k][j-k]==BLANK&&!note[i+k][j-k]){
							s[pc].point = evalute(i+k,j-k,turn);
							s[pc].x=i+k;
							s[pc++].y=j-k;
							note[i+k][j-k] = 1;
						} 
					}
				}
			}
		}
	}
	return pc;
}
struct node dfs(int turn,int deep){	//dfs���� 
	struct node now;
	now.flg=0;
	if(deep>BOTTOM){ 
		now.point = judge();
		return now;
	} 
	struct node mark[235];				//��СҪ����  
	int range = generator(mark,turn);	//�����ӽڵ���WID���� 
	qusort(mark,range,0,range-1);		//����ʽ�����Ż�
	range = MIN(WID,range); 
	int u,v;
	for(int i=0;i<range;i++){
		u=mark[i].x;
		v=mark[i].y;
		tbl[u][v] = turn;
		if(whowin()==turn){
			if(turn == WHITE){
				tbl[u][v] = BLANK;
				now.point=-TOFIVE;
				return now;
			}
			if(turn==BLACK){
				tbl[u][v] = BLANK;
				if(deep==1){
					now.x=u;
					now.y=v;
				}
				now.point=TOFIVE;
				return now;
			}
		}
		struct node tmp = dfs(ops(turn),deep+1);
		//if(deep==1){
		//	printf("%d %d %d %d\n",tmp.point,tmp.x,tmp.y,tmp.flg);
		//}
		if(tmp.flg==1){		//AB��֦ 
			tbl[u][v]=BLANK;
			if(turn == BLACK){
				now.point = INF; //����һ����Ӱ�츸�׵�ֵ 
			}
			if(turn == WHITE){
				now.point = -INF;
			}
			return now;
		}
		if(i==0){
			now.x = u;
			now.y = v;
			now.point = tmp.point;
			peak[deep]=tmp.point;
		}
		else if(turn==BLACK){
			if(now.point<tmp.point){		//���ڵ����δ����
				peak[deep] = MAX(tmp.point,peak[deep]); 
				if(deep==1){
					now.x = u;
					now.y = v;
				}
				now.point = tmp.point;
			}
		}
		else {
			if(now.point>tmp.point){
				peak[deep] = MIN(tmp.point,peak[deep]); 
				if(deep==1){
					now.x = u;
					now.y = v;
				}
				now.point = tmp.point;
			}
		}
		tbl[u][v] = BLANK; //ͬ�ڵ����ȡ�����Ӳ��� 
	}
	
	if(deep>turn){	//AB��֦�ж� 
		if(turn==BLACK&&peak[deep-2]>now.point){
			now.flg=1; 
		}
		if(turn==WHITE&&peak[deep-2]<now.point){
			now.flg=1;
		}
	}
	return now;
}
void display(){
	system("cls");
	printf("  1 2 3 4 5 6 7 8 9 A B C D E F\n");
	for(int i=0;i<15;i++){
		if(i<9)
			printf("%d ",i+1);
		else
			printf("%c ",'A'+i-9);
		for(int j=0;j<15;j++){
			if(tbl[i][j]==BLACK) printf("# ");
			if(tbl[i][j]==WHITE) printf("@ ");
			if(tbl[i][j]==BLANK) printf("0 ");
		}
		printf("\n");
	}
}

void play(int first){
	int step=0;	 			//�ܲ���
	struct node p;
	double t1,t2; 			//��¼��ʱ 
	
	while(1){
		
	if(step==0&&first%2==0){
		tbl[7][7]=BLACK;
	}
	
	display();
	printf("���������@,�����ʽΪ15��������1~F�����������к��������кţ�����RS�������䣬����RR���Է���ʱ�����ħ��(���������ˣ��Ƥ)\n��ǰ�ܲ�����%d\n",(step+1)/2); 
	printf("��һ����ʱ��%.3lf ��\n",(t2-t1)/1000);
	
	if(step>1){
		char m,n;
		if(p.x+1>9){
			m='A'+p.x+1-10;
		} 
		else m='0'+p.x+1;
		if(p.y+1>9){
			n='A' +p.y+1-10;
		}
		else n = '0'+p.y+1;
		printf("�Է����ӵ�Ϊ: %c %c\n",m,n);
	}
	 
	int jud = whowin();
	if(jud == BLACK){
		 printf("�ޣ�����!");
		 system("pause");
		 break;
	} 
	if(jud == WHITE){
		printf("��Ӯ�ˣ�����2018��ʥ�˵ñ��Ͽյ�����˹��ӥһ��!");
		system("pause");
		break;
	}
	
	char a,b;
	int cx,cy;
	printf("��Ļغϣ�\n");
	t1 = clock();
	scanf(" %c %c",&a,&b);
	t2 = clock();
	if(a=='R'&&b=='S'){
		system("cls");
		printf("�㶯����ħ���뿪\n");
		return;
	} 
	
	if(a=='R'&&b=='R'){
		if(step>2){
			tbl[last[step-1].x][last[step-1].y]=BLANK;
			tbl[last[step-2].x][last[step-2].y]=BLANK;
			step-=2;
			continue;
		}
		else{
			printf("�����Ѿ���ʱ��ԭ��!");
			system("pause");
			continue;
		}
	}
	if(a>'9'){
		cx=a-'A'+10;
	}
	else cx = a-'0';
	if(b>'9'){
		cy=b-'A'+10;
	}
	else cy = b-'0';
	if(tbl[cx-1][cy-1]!=BLANK){
		printf("����δ���մ۸����ӵ�ħ��!\n");
		system("pause");
		continue;
	}
	tbl[cx-1][cy-1] = WHITE;
	display();
	jud = whowin();
	if(jud == BLACK){
		 printf("�ޣ�����!");
		 system("pause");
		 break;
	} 
	if(jud == WHITE){
		printf("��Ӯ�ˣ�����2018��ʥ�˵ñ��Ͽյ�����˹��ӥһ��!");
		system("pause");
		break;
	}
	printf("�Է�����˼��-��-\n");
	t1 = clock();
	p=dfs(BLACK,1);
	t2 = clock();
	tbl[p.x][p.y] = BLACK;
	last[step].x=cx-1;
	last[step++].y=cy-1;
	last[step].x=p.x;
	last[step++].y=p.y;
}
} 
void meun(){
	system("cls");
	printf("��һ��������ɣ�");
	system("pause");
}
int main() {
	srand(time(0));
	printf("�ҵ���ʦ���˻������񶯣����︽��һ������������֣�"); 
	system("pause");
	meun();
	int k=rand();	//��������  
	play(k);
	return 0;
}

/*
srand(time(0));
	printf("�ҵ���ʦ���˻������񶯣����︽��һ������������֣�"); 
	system("pause");
	meun();
	int k=rand();	//��������  
	play(k);
	return 0;
	
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			scanf("%d",&tbl[i][j]);
		}
	}
	struct node p;
	int x=judge();
	p = dfs(BLACK,1);
	tbl[p.x][p.y] = BLACK;
	display();
*/

