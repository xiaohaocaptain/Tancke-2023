#include<stdio.h>
#include<stdbool.h>
#include<windows.h> 
#include<conio.h>
#include<time.h>

//ȫ�ֱ���
struct Bullet//�ӵ��ṹ�� 
{
	int x,y;//�ӵ�����
	int direction;//���������U72,D80,L75,R77
	bool player;//���ַ����ӵ���һ����TRUEΪ��ң�FALSEΪAI 
	bool isnew;//��¼�ӵ��Ƿ�Ϊ��һ�ν�����TRUEΪ��һ�Σ�FALSEΪ�ǵ�һ�� 
	bool exit;//�ж��ӵ��Ƿ���ڣ�TRUEΪ���ڣ�FALSEΪ������ 
}bullet[20];//ȫ���ӵ��������飬��Ϸʵ�ʲ���ͬʱ����20���ӵ� 
struct Tank//̹�˽ṹ�� 
{
	int x,y;//̹����������
	int direction;//���������U72,D80,L75,R77 
	int color;//̹����ɫ��AI̹����ɫ�Ӻ쵽�Ƶ��̵��� 
	int CD;//�����ӵ���ȴʱ�� 
	int type;//̹�˱�ţ�AIר�� 
	int heart;//̹��ʣ��������AIר�� 
	int move;//AI̹���ƶ�һ�������ξ�ֹͣ�ƶ���AIר�� 
	int isrebirth;//AI�Ƿ񸴻AIר�� 
	bool player;//���ֲ���̹�˵Ķ���TRUEΪ��ң�FALSEΪAI 
	bool alive;//�ж�̹���Ƿ��TRUEΪ��FALSEΪ���� 
}AItank[4],mytank;
struct Rank
{
	char name[25];
	int score;
}rank[100];//��100λ����ֻչʾǰ10�� 
int choose_homepage;//��ҳ��ѡ����� 
char input;
int bullet_num;//�����ӵ���� 
int map_num;//��ͼ��� 
int lastmap=100;//��¼��ͼ���ʹ�������ε�ͼ���ظ� 
int stright[3];//AI̹��ֱ�д��� 
int num_rank;//��ǰ���������������Ϊ10�� 
int level;//ͨ���ؿ��� 
int score;//�÷� 
int map[49][87];//ȫ�������ͼ 
int temp_tank[3][3];//ȫ�����̹�� 
//�����ܺ��� 
void frame();//��Ϸ���
void frame_choose();//��ҳ��ѡ���� 
void clean();//���ָ������ 
//���ִ�ӡ����
void maintitle();//��Ϸ��ҳ����� 
void mainchoose();//��Ϸ��ҳ��ѡ�������� 
void datacharacters();//��ʼ��Ϸ���Ҳര������ 
//ϵͳ���ú���
void HideCursor();//���ع��
void gotoxy();//�����ת 
void color();//�Զ��庯���ı�������ɫ 
void initialize();//��ʼ��Ϸ��ʼ�� 
void gameover();//��Ϸ������� 
void pause();//��Ϸ��ͣ���� 
void gamecheck();//��Ϸ��ɼ�� 
void nextlevel();//��һ����ת 
void lookforrank();//�鿴���а� 
void isnewrank();//�Ƿ��ܼ������а� 
//��ת����Ϻ��� 
void operation_homepage();//��ҳ�������ת 
void gameinput();//��Ϸ�а�����ȡ 
void homepage();//��ҳ����� 
void gamepage();//��ʼ��Ϸҳ����� 
//̹��
void tanklibrary();//̹�˿� 
void printmytank();//��ӡ̹�� 
void printAItank();//��ӡAI̹�� 
void cleartank();//ͨ�����̹�� 
void movemytank();//���̹���ƶ� 
void moveAItank();//AI̹���ƶ�  
bool tankcheck();//���̹��ת�����������ϰ���,TRUEΪ���ϰ���FALSEΪ���ϰ� 
//�ӵ�
void buildbullet();//�����ӵ� 
void buildAIbullet();//����AI�ӵ� 
void bulletfly();//�ӵ��˶�����
void bullethit();//�ӵ�������� 
void bullethit_tank();//�ӵ����̹�� 
void printbullet();//�ӵ���ӡ���� 
void clearbullet();//�ӵ�������� 
void bullet_bullet();//�ӵ�����ײ������  
//��ͼ��� 
void printhome();//��ӡ���� 
void printmap();//��ӡ��ͼ 
void maplibrary();//��ͼ�� 
void square();//����ש�� 
//�ļ������� 
void creatfile();//�����ļ����򿪶�ȡ��������Ϣ 
void sort();//����ṹ������ 
int main()
{
	creatfile();//�����ļ����򿪶�ȡ��������Ϣ 
	srand(time(NULL)); //������������� 
	HideCursor();//���ع�� 
	SetConsoleOutputCP(437);//����CMD��ӡ��չASCII���ַ� 
	system("mode con cols=120 lines=50");//������ʾ���ڴ�С 
	homepage();//��ҳ�����
	return 0;
}
void frame(int x)//��Ϸ��� 
{
	int hors=205,vers=186,clus=201,clds=200,crus=187,crds=188,r3s=204,l3s=185,cnt_h,cnt_v;
	switch(x) 
	{
		case 1://������� 
			color(4); gotoxy(0,0);
			printf("%c",clus); for(cnt_h=0;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crus);
			for(cnt_v=1;cnt_v<48;cnt_v++){printf("%c",vers); gotoxy(119,cnt_v); printf("%c",vers);}
			printf("%c",clds); for(cnt_h=0;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crds);
			color(7); break; 
		case 2://��Ϸ����� 
			color(14); gotoxy(0,0);
			printf("%c",clus); for(cnt_h=0;cnt_h<85;cnt_h++){printf("%c",hors);} printf("%c",crus);
			for(cnt_v=1;cnt_v<48;cnt_v++){gotoxy(0,cnt_v); printf("%c",vers); gotoxy(86,cnt_v); printf("%c",vers);}
			gotoxy(0,48); printf("%c",clds); for(cnt_h=0;cnt_h<85;cnt_h++){printf("%c",hors);} printf("%c",crds);
			color(7); break;
		case 3://��������� 
			color(9); gotoxy(87,0);
			printf("%c",clus); for(cnt_h=87;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crus);
			for(cnt_v=1;cnt_v<48;cnt_v++){gotoxy(87,cnt_v); printf("%c",vers); gotoxy(119,cnt_v); printf("%c",vers);}
			gotoxy(87,48); printf("%c",clds); for(cnt_h=87;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crds);
			gotoxy(87,18); printf("%c",r3s);for(cnt_h=88;cnt_h<119;cnt_h++){printf("%c",hors);} printf("%c",l3s);
			color(7); break;
			break;
		case 4://���а��Ҳ���
			color(9); gotoxy(87,0);
			printf("%c",clus); for(cnt_h=87;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crus);
			for(cnt_v=1;cnt_v<48;cnt_v++){gotoxy(87,cnt_v); printf("%c",vers); gotoxy(119,cnt_v); printf("%c",vers);}
			gotoxy(87,48); printf("%c",clds); for(cnt_h=87;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crds);
			color(7); break;
			break;
	}
}
void frame_choose(int x)//��ҳ��ѡ���� 
{
	int vers=186,hors=205,clus=201,clds=200,crus=187,crds=188,cnt_hor;
	switch(x)
	{
		case 0://δѡ��ʱȫ�� 
			color(11);
			gotoxy(50,26); printf("%c",vers); gotoxy(67,26); printf("%c",vers);
			gotoxy(50,25); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,27); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds);
			gotoxy(50,30); printf("%c",vers); gotoxy(67,30); printf("%c",vers);
			gotoxy(50,29); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,31); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds);
			gotoxy(50,34); printf("%c",vers); gotoxy(67,34); printf("%c",vers);
			gotoxy(50,33); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,35); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds); color(7); break;
		case 11://ѡ��1
			color(14);
			gotoxy(50,26); printf("%c",vers); gotoxy(67,26); printf("%c",vers);
			gotoxy(50,25); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,27); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds); color(7); choose_homepage=1; break;
		case 12://ѡ��2
			color(14);
			gotoxy(50,30); printf("%c",vers); gotoxy(67,30); printf("%c",vers);
			gotoxy(50,29); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,31); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds); color(7); choose_homepage=2; break;
		case 13://ѡ��3
			color(14);
			gotoxy(50,34); printf("%c",vers); gotoxy(67,34); printf("%c",vers);
			gotoxy(50,33); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,35); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds); color(7); choose_homepage=3; break;
	}
}
void clean(int c)//���ָ������
{
	int h,v;
	switch(c){
		case 100://���ȫ������ 
			gotoxy(0,0); for(v=0;v<=50;v++){ for(h=0;h<=119;h++){ putchar(32);}} break;
	}
} 
void maintitle()//��Ϸ��ҳ����� 
{
	int d3=194,u3=193,r3=195,ver=179,hor=196,hors=205,cru=191,crd=217,clu=218,cld=192;
	color(15);
	gotoxy(25,10); printf("%c%c%c%c%c%c%c",hor,hor,hor,d3,hor,hor,hor);//��ӡT 
	gotoxy(28,11); printf("%c",ver); gotoxy(28,12); printf("%c",ver); gotoxy(28,13); printf("%c",ver); gotoxy(28,14); printf("%c",ver);
	gotoxy(39,11); printf("%c%c%c%c%c%c",hor,hor,hor,hor,hor,cru); gotoxy(38,11); printf("%c",clu); //��ӡa 
	gotoxy(38,12); printf("%c",ver); gotoxy(38,13); printf("%c",ver); gotoxy(44,12); printf("%c",ver); gotoxy(44,13); printf("%c",ver);
	gotoxy(38,14); printf("%c%c%c%c%c%c%c%c",cld,hor,hor,hor,hor,hor,u3,hor);
	gotoxy(52,11); printf("%c%c%c%c%c",hor,hor,hor,hor,hor);//��ӡn
	gotoxy(51,11); printf("%c",clu); gotoxy(51,12); printf("%c",ver); gotoxy(51,13); printf("%c",ver); gotoxy(51,14); printf("%c",ver);
	gotoxy(57,11); printf("%c",cru); gotoxy(57,12); printf("%c",ver); gotoxy(57,13); printf("%c",ver); gotoxy(57,14); printf("%c",ver);
	gotoxy(65,11); printf("%c%c%c%c%c",hor,hor,hor,hor,hor);//��ӡc
	gotoxy(64,11); printf("%c",clu); gotoxy(64,12); printf("%c",ver); gotoxy(64,13); printf("%c",ver); 
	gotoxy(64,14); printf("%c%c%c%c%c%c",cld,hor,hor,hor,hor,hor); 
	gotoxy(76,11); printf("%c",ver); gotoxy(76,12); printf("%c",ver); gotoxy(76,13); printf("%c",ver); gotoxy(76,14); printf("%c",ver);//��ӡk 
	gotoxy(79,11); printf("/"); gotoxy(77,12); printf("/"); gotoxy(78,13); printf("\\"); gotoxy(79,14); printf("\\");
	gotoxy(89,11); printf("%c%c%c%c%c",hor,hor,hor,hor,cru);//��ӡe
	gotoxy(88,11); printf("%c",clu); gotoxy(88,12); printf("%c",ver); gotoxy(88,13); printf("%c",r3); 
	gotoxy(89,13); printf("%c%c%c%c%c",hor,hor,hor,hor,crd); gotoxy(93,12); printf("%c",ver);
	gotoxy(88,14); printf("%c%c%c%c%c%c",cld,hor,hor,hor,hor,hor); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6|8|128|64); gotoxy(95,16); printf("2 0 2 3"); color(7);
	gotoxy(48,37); color(6); printf("Choose: %c , %c and Enter",24,25); color(7);
}
void mainchoose()//��Ϸ��ҳ��ѡ������ 
{
	color(10); gotoxy(54,26); printf("Start Game"); gotoxy(53,30); printf(" Rank List"); gotoxy(53,34); printf(" Exit Game"); color(7);
}
void datacharacters()//��ʼ��Ϸ���Ҳര������ 
{
	//�ϰ벿�� 
	gotoxy(89,4); color(6); printf("Level:"); color(7);
	gotoxy(89,6); color(15); printf("Socre:"); color(7);
	gotoxy(89,8); color(2); printf("Num of Left Heart:"); color(7);
	gotoxy(89,10); color(4); printf("Num of Left enemy's tank:"); color(7);
	gotoxy(89,14); color(13); printf("Current State of Game:"); color(7);
	//�°벿�� 
	gotoxy(101,20); color(10); printf("Tips"); color(7);
	gotoxy(92,23); color(11); printf("%c is UP",24); color(7);
	gotoxy(92,25); color(11); printf("%c is DOWN",25); color(7);
	gotoxy(92,27); color(11); printf("%c is LEFT",27); color(7);
	gotoxy(92,29); color(11); printf("%c is RIGHT",26); color(7);
	gotoxy(92,31); color(11); printf("Space is FIRE"); color(7);
	gotoxy(92,33); color(11); printf("P is PAUSE"); color(7);
	gotoxy(92,35); color(11); printf("O is CONINUE"); color(7);
	gotoxy(92,37); color(11); printf("Esc is Return Homepage"); color(7);
}
void HideCursor()//���ع��
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y)//�����ת 
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void color(int x)//�ı�������ɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
void initialize()//��ʼ��Ϸ��ʼ��
{
	int i; bullet_num=0;//ȫ���ӵ������� 	
	for(i=0;i<3;i++){stright[i]=3;}//AI̹��ֱ�д������� 
	for(i=0;i<20;i++){//�ӵ���ʼ��
		bullet[i].exit=0;
		bullet[i].isnew=0;
	} 
	for(i=0;i<4;i++){
		AItank[i].player=0;//����̹�˿��Ʒ� 
		AItank[i].alive=0;//����̹�˳�ʼΪ��� 
		AItank[i].color=12;//����̹����ɫ
		AItank[i].isrebirth=0; 
		AItank[i].heart=4;//����AI̹������ 
		AItank[i].direction=80;//ΪAI̹�˳�ʼ������
		AItank[i].type=21+i;//ΪAI̹�˱�� 
		AItank[i].move=1;//ʹAI̹�˳�ʼ�����ƶ� 
		AItank[i].CD=12;//����AI����CD 
	}
	AItank[0].x=15,AItank[0].y=5;
	AItank[1].x=33,AItank[1].y=5;
	AItank[2].x=57,AItank[2].y=5;
	AItank[3].x=74,AItank[3].y=5;
	mytank.player=1,mytank.alive=1,mytank.heart=4,mytank.color=14,mytank.CD=2,mytank.direction=72;//���̹�˳�ʼ������ 
	mytank.x=37,mytank.y=46;//��ʼ�����̹��λ�� 
	gotoxy(96,4); color(15); printf("%d",level); color(7);//��ӡ 
	gotoxy(96,6); color(11); printf("%d",score); color(7);
	gotoxy(108,8); color(2); printf("%d",mytank.heart); color(7);
	gotoxy(115,10); color(4); printf("%d",AItank[0].heart+AItank[1].heart+AItank[2].heart+AItank[3].heart); color(7);
	color(10); gotoxy(95,15); printf("Game is Underway"); color(7);//��ӡ��Ϸ״̬ 
}
void gameover() 
{
	int vers=186,hors=205,clus=201,clds=200,crus=187,crds=188,i,j;
	for(i=22;i<=26;i++){gotoxy(30,i); for(j=31;j<=55;j++){printf(" "); }}//�����ָ������ 
	gotoxy(38,23); color(12); printf("Game Over!");
	gotoxy(32,25); color(10); printf("Esc is Return Homepage"); color(7);
	gotoxy(30,21); printf("%c",clus); for(i=1;i<25;i++){printf("%c",hors);} printf("%c",crus);
	for(i=22;i<=26;i++){ gotoxy(30,i); printf("%c",vers); gotoxy(55,i); printf("%c",vers);}
	gotoxy(30,27); printf("%c",clds); for(i=1;i<25;i++){printf("%c",hors);} printf("%c",crds);
	while(1){if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){homepage();}}
}
void pause()//��Ϸ��ͣ����
{
	gotoxy(95,15); printf("                "); color(12); gotoxy(95,15); printf("Game is Pasuing"); color(7);//��ӡ��Ϸ״̬ 
	while(1){
		if(GetAsyncKeyState('O')& 0x8000){
			gotoxy(95,15); printf("                "); color(10); gotoxy(95,15); printf("Game is Underway"); color(7); break;//��ӡ��Ϸ״̬ 
		}else if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){homepage();}}
	Sleep(3);//�ָ���Ϸ��ȴ����� 
}
void gamecheck()//��Ϸ��ɼ�� 
{
	if(AItank[0].heart==0&&AItank[1].heart==0&&AItank[2].heart==0&&AItank[3].heart==0){
		level++; nextlevel();//AI̹��ȫ������ʱ������һ�� 
	}
	if(mytank.heart==0){
		gameover();
	}
}
void nextlevel()//��һ����ת 
{
	int vers=186,hors=205,clus=201,clds=200,crus=187,crds=188,i,j;
	for(i=22;i<=26;i++){gotoxy(30,i); for(j=31;j<=55;j++){printf(" "); }}//�����ָ������ 
	gotoxy(33,23); color(12); printf("  Game Completed!"); color(7);
	gotoxy(33,24); color(14); printf(" Enter is Next Level");
	gotoxy(33,25); printf("Esc is Game Clearing"); color(7);
	gotoxy(30,21); printf("%c",clus); for(i=1;i<25;i++){printf("%c",hors);} printf("%c",crus);
	for(i=22;i<=26;i++){ gotoxy(30,i); printf("%c",vers); gotoxy(55,i); printf("%c",vers);}
	gotoxy(30,27); printf("%c",clds); for(i=1;i<25;i++){printf("%c",hors);} printf("%c",crds);
	while(1){
		if(GetAsyncKeyState(VK_RETURN)& 0x8000){
			Sleep(10); gamepage();
		}else if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){
			isnewrank();//�ж��Ƿ��ܽ������а�ǰʮ�� 
			homepage();}//δ������ֱ�ӷ�����ҳ�� 
	}
}
void lookforrank()//�鿴���а� 
{
	sort();
	int row,cnt; //��ӡ����UI 
	clean(100);frame(1);
	gotoxy(53,5); color(10); printf("Rank List"); color(7);
	gotoxy(45,8); color(14); printf("Name                    Score"); color(7);
	for(row=11,cnt=0;cnt<10;row+=3,cnt++){
		gotoxy(37,row); color(12); printf("%d.",cnt+1);
	}
	if(num_rank<10){
		for(cnt=0,row=11;cnt<num_rank;cnt++,row+=3){
			gotoxy(44,row); color(15); printf("%s",rank[cnt].name); gotoxy(70,row); color(11); printf("%d",rank[cnt].score); color(7);
		}
	}else if(num_rank>=10){
		for(cnt=0,row=11;cnt<10;cnt++,row+=3){
			gotoxy(44,row); color(15); printf("%s",rank[cnt].name); gotoxy(70,row); color(11); printf("%d",rank[cnt].score); color(7);
		}
	}
	gotoxy(47,44); color(13); printf("Esc is Return Homepage");
	while(1){if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){homepage();}}//����������ѡ�� 
}
void isnewrank()//�Ƿ��ܼ������а� 
{
	if(level>=2){//����ͨ��һ�زſ��Խ������а� 
		int position,i;
		bool is=0;
		if(num_rank!=0){
			for(i=0;i<10;i++){
				if(score>rank[i].score){
					is=1;//���Լ������а�
					position=i;//λ�� 
					break;
				}	
			}
		}else if(num_rank==0){//��Ϊ�������а�ĵ�һλ 
			is=1;
			position=0;
		}
		if(is){
			num_rank++;
			if(num_rank>=10){num_rank=10;}
			for(i=num_rank-1;i>=position;i--){//��λ��֮��������κ��� 
				rank[i]=rank[i-1];
			}
			//չʾ��Ϣ 
			int row,cnt; //��ӡ����UI 
			clean(100);frame(1);
			gotoxy(53,5); color(10); printf("Rank List"); color(7);
			gotoxy(45,8); color(14); printf("Name                    Score"); color(7);
			gotoxy(44,44); color(13); printf("Please Enter Player's Name");
			for(row=11,cnt=0;cnt<10;row+=3,cnt++){//��� 
				gotoxy(37,row); color(12); printf("%d.",cnt+1);
			}
			for(cnt=0,row=11;cnt<position;cnt++,row+=3){//λ��֮ǰ����Ϣ 
				gotoxy(44,row); color(15); printf("%s",rank[cnt].name); gotoxy(70,row); color(11); printf("%d",rank[cnt].score); color(7);
			}
						
			for(cnt=position+1,row=11+3*(position+1);cnt<num_rank;cnt++,row+=3){//λ��֮�����Ϣ 
				gotoxy(44,row); color(15); printf("%s",rank[cnt].name); gotoxy(70,row); color(11); printf("%d",rank[cnt].score); color(7);
			}
			
			rank[position].score=score;  gotoxy(70,11+3*position); color(11); printf("%d",rank[position].score); color(7);//��λ���ȴ�ӡ���� 

		
			gotoxy(44,11+3*position); color(15); gets(rank[position].name); color(7);
			//�����µ���Ϣ
			FILE *q1,*q2;
			q1=fopen("Num of rank.txt","w");
			if(num_rank>=10){num_rank=10;}
			fprintf(q1,"%d",num_rank);
			fclose(q1);
			q2=fopen("Rank List.txt","w");
			for(i=0;i<num_rank;i++){fprintf(q2,"%s %d\n",rank[i].name,rank[i].score);}
			fclose(q2);
		}	
	}
}
void operation_homepage(int get)//��ҳ�������ת 
{
	switch(get){
		case 1:gamepage(); break;//��ʼ��Ϸ 
		case 2:lookforrank(); break;//�鿴���а� 
		case 3: exit(0);//�˳���Ϸ 
	}
}
void gameinput()//��Ϸ�а�����ȡ 
{
	int keyboard,cnt=0;
	if(GetAsyncKeyState(VK_UP)& 0x8000){movemytank(72);}//�� 
	else if(GetAsyncKeyState(VK_DOWN)& 0x8000){movemytank(80);}//�� 
	else if(GetAsyncKeyState(VK_LEFT)& 0x8000){movemytank(75);}//�� 
	else if(GetAsyncKeyState(VK_RIGHT)& 0x8000){movemytank(77);}//�� 
	else if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){pause();homepage();} //ͨ��������1���ҷ������Խ����а�ʱ���������а��ٷ�����ҳ�� 
	else if(GetAsyncKeyState(VK_SPACE)& 0x8000){
		if(mytank.CD==2){//���𣬲����ÿ����� 
			buildbullet(&mytank);
			mytank.CD=0;
		}else{mytank.CD++;}}
	else if(GetAsyncKeyState('P')& 0x8000){pause();}//��ͣ 
}
void homepage()//��ҳ�����
{
	level=1; score=0;//ͨ���ؿ����ͷ���  
	clean(100); frame(1); maintitle(); mainchoose(); frame_choose(0); frame_choose(11);
	input=getch();
	while(input!=13){
		if(input==80&&choose_homepage==1){
			frame_choose(0); frame_choose(12);
		}else if(input==80&&choose_homepage==2){
			frame_choose(0); frame_choose(13);
		}else if(input==80&&choose_homepage==3){
			frame_choose(0); frame_choose(11);
		}
		if(input==72&&choose_homepage==1){
			frame_choose(0); frame_choose(13);
		}else if(input==72&&choose_homepage==2){
			frame_choose(0); frame_choose(11);
		}else if(input==72&&choose_homepage==3){
			frame_choose(0); frame_choose(12);
		}
		input=getch();	
	}
	operation_homepage(choose_homepage);
}
void gamepage()//��ʼ��Ϸҳ����� 
{
	int i,interval1=1,interval2=1,intervalAI[3];
	intervalAI[0]=1,intervalAI[1]=1,intervalAI[2]=1,intervalAI[3]=1;
	clean(100); frame(2); frame(3);//��� 
	initialize();//��Ϸ��ʼ��
	if(lastmap==100){lastmap=2;}do{ map_num=rand()%3;}while(lastmap==map_num);//ʹ�������ε�ͼ���ظ� 
	lastmap=map_num; maplibrary(map_num); printmap(map_num);//�����ͼ 
	if(map_num==0){printhome();}//��ӡ���أ�Ŀǰֻ��map1��Ҫ 
	printmytank(mytank);//��ӡ���̹�� 
	datacharacters();//����������

	for(;;){
		gamecheck();//�����Ϸ�Ƿ�������Ƿ������һ�� 
		if(interval1++%2==0){
			bulletfly(bullet);//�����ӵ��˶� 

			for(i=0;i<20;i++){
				bullethit_tank(&bullet[i]);//����ӵ��Ƿ����̹�� 
			}
					
			if(!AItank[0].alive&&AItank[0].heart>0&&AItank[0].isrebirth==1&&intervalAI[0]++%89==0){AItank[0].x=15,AItank[0].y=5;AItank[0].isrebirth=11;}//��ʼ������̹�˵�λ�ã�����ǿ������ֹ����ˢ��
			if(!AItank[1].alive&&AItank[1].heart>0&&AItank[1].isrebirth==1&&intervalAI[1]++%89==0){AItank[1].x=33,AItank[1].y=5;AItank[1].isrebirth=11;}
			if(!AItank[2].alive&&AItank[2].heart>0&&AItank[2].isrebirth==1&&intervalAI[2]++%89==0){AItank[2].x=57,AItank[2].y=5;AItank[2].isrebirth=11;}
			if(!AItank[3].alive&&AItank[3].heart>0&&AItank[3].isrebirth==1&&intervalAI[3]++%89==0){AItank[3].x=74,AItank[3].y=5;AItank[3].isrebirth=11;}
			
			for(i=0;i<=3;i++){//AI̹���ƶ� 
				moveAItank(&AItank[i]);
				if(AItank[i].alive&&AItank[i].heart>=1){printAItank(&AItank[i]);}	
			}
			
			for(i=0;i<=3;i++){//����������AI̹�� 
				if(AItank[i].alive==0&&AItank[i].heart==4){ printAItank(&AItank[i]);}//��ʼ����AI 
				if(AItank[i].alive==0&&AItank[i].heart>=1&&AItank[i].isrebirth==11&&intervalAI[i]++%90==0){ printAItank(&AItank[i]);AItank[i].isrebirth=0;}//����AI 
			}
			
			for(i=0;i<=3;i++) {//AI�������� 
				if(AItank[i].alive&&intervalAI[i]++%2==0){//AI̹�˴��ʱ�Ž��з����ӵ� 
					buildAIbullet(&AItank[i]);
				}
			}
		
			if(mytank.alive&&interval2++%3==0){//���뺯�� 
				gameinput();
			}
		
			if(!mytank.alive&&mytank.heart<4){//������̹������ 
				mytank.x=37,mytank.y=46;//��ʼ�����̹��λ��
				printmytank(&mytank);
			}
		}
		Sleep(3);
	}
}
void tanklibrary(int player,int direction)//̹�˿⣬x1���ϣ�x2���£�x3����x4���� 
{
	int i,j;
	int tank11[3][3]={{201,179,187},{204,79,185},{200,207,188}};//���tank 
	int tank12[3][3]={{201,209,187},{204,79,185},{200,179,188}};
	int tank13[3][3]={{201,203,187},{196,79,182},{200,202,188}};
	int tank14[3][3]={{201,203,187},{199,79,196},{200,202,188}};
	int tank21[3][3]={{201,179,187},{79,203,79},{200,79,188}};//AItank1 
	int tank22[3][3]={{201,79,187},{79,202,79},{200,179,188}};
	int tank23[3][3]={{201,79,187},{196,204,79},{200,79,188}};
	int tank24[3][3]={{201,79,187},{79,185,196},{200,79,188}};
	int tank31[3][3]={{32,179,32},{198,254,181},{192,208,217}};//AItank2
	int tank32[3][3]={{218,210,191},{198,254,181},{32,179,32}};
	int tank33[3][3]={{32,210,191},{196,254,181},{32,208,217}};
	int tank34[3][3]={{218,210,32},{198,254,196},{192,208,32}};
	int tank41[3][3]={{254,179,254},{204,30,185},{200,207,188}};//AItank3
	int tank42[3][3]={{201,209,187},{204,31,185},{254,179,254}};
	int tank43[3][3]={{254,203,187},{196,17,182},{254,202,188}};
	int tank44[3][3]={{201,203,254},{199,16,196},{200,202,254}};
	int tank51[3][3]={{218,193,191},{195,79,180},{192,193,190}};//AItank4
	int tank52[3][3]={{218,194,191},{195,79,180},{192,194,190}};
	int tank53[3][3]={{218,194,191},{180,79,180},{192,193,190}};
	int tank54[3][3]={{218,194,191},{195,79,195},{192,193,190}};
	if(player==1){//��̹��Ϊ��� 
		switch(direction){
			case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank11[i][j];}} break;
			case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank12[i][j];}} break;
			case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank13[i][j];}} break;
			case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank14[i][j];}} break;}}
	else{//��̹��Ϊ���� 
		if(player==21){//1��AItank 
			switch(direction){
				case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank21[i][j];}} break;
				case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank22[i][j];}} break;
				case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank23[i][j];}} break;
				case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank24[i][j];}} break;}}
		if(player==22){//2��AItank 
			switch(direction){
				case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank31[i][j];}} break;
				case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank32[i][j];}} break;
				case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank33[i][j];}} break;
				case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank34[i][j];}} break;}}
		if(player==23){//3��AItank 
			switch(direction){
				case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank41[i][j];}} break;
				case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank42[i][j];}} break;
				case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank43[i][j];}} break;
				case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank44[i][j];}} break;}}
		if(player==24){//4��AItank 
			switch(direction){
				case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank51[i][j];}} break;
				case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank52[i][j];}} break;
				case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank53[i][j];}} break;
				case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank54[i][j];}} break;}}
	}
}
void printmytank(struct Tank *tank)//��ӡ̹�� 
{
	tanklibrary(1,tank->direction);//������򴫵�1����������򴫵�AI̹�˱�� 

	color(tank->color);
	gotoxy(tank->x-1,tank->y-1);printf("%c%c%c",temp_tank[0][0],temp_tank[0][1],temp_tank[0][2]);
	gotoxy(tank->x-1,tank->y);printf("%c%c%c",temp_tank[1][0],temp_tank[1][1],temp_tank[1][2]);
	gotoxy(tank->x-1,tank->y+1);printf("%c%c%c",temp_tank[2][0],temp_tank[2][1],temp_tank[2][2]); color(7);
}
void printAItank(struct Tank *tank)//��ӡAI̹�� 
{
	tank->alive=1;
	int x=tank->x,y=tank->y;
	tanklibrary(tank->type,tank->direction);
	if(tank->heart==4){color(12);}//�� 
	else if(tank->heart==3){color(6);}//�� 
	else if(tank->heart==2){color(10);}//�� 
	else if(tank->heart==1){color(15);}//��
	gotoxy(x-1,y-1);printf("%c%c%c",temp_tank[0][0],temp_tank[0][1],temp_tank[0][2]);
	gotoxy(x-1,y);printf("%c%c%c",temp_tank[1][0],temp_tank[1][1],temp_tank[1][2]);
	gotoxy(x-1,y+1);printf("%c%c%c",temp_tank[2][0],temp_tank[2][1],temp_tank[2][2]); color(7);
}
void cleartank(int x,int y)//ͨ�����̹�� 
{
	gotoxy(x-1,y-1);printf("   ");
	gotoxy(x-1,y);printf("   ");
	gotoxy(x-1,y+1);printf("   "); 
}
void movemytank(int move)//���̹���ƶ� 
{
	cleartank(mytank.x,mytank.y);//���ԭ��λ�õ�̹��
	mytank.direction=move;
	if(tankcheck(mytank.x,mytank.y,mytank.direction)){//����ҵ�̹��ת�����������ϰ��� 
		switch(mytank.direction){
			case 72: mytank.y--;break;//����һ�� 
			case 80: mytank.y++;break;//����һ�� 
			case 75: mytank.x--;break;//����һ�� 
			case 77: mytank.x++;break;//����һ�� 
		}
	}//���޷��ƶ����ӡת����̹�� 
	printmytank(&mytank);
}
void moveAItank(struct Tank *tank)//AI̹���ƶ�  
{
	int t=rand()%4;

	if(tank->alive){//���̹�˴��Ž��в��� 
		if(tank->move==0){//̹�˿����ƶ�ʱ���в���
			cleartank(tank->x,tank->y);//���ԭ��λ�õ�̹��
			if(tankcheck(tank->x,tank->y,tank->direction)&&stright[tank->type-21]==4){//ǰ�����ϰ�����ֱ�иտ�ʼʱ 
				if(t==0){tank->direction=72;}//����ƶ�һ������ 
				else if(t==1){tank->direction=80;}
				else if(t==2){tank->direction=75;}
				else if(t==3){tank->direction=77;}
				stright[tank->type-21]--;
			}else if(!tankcheck(tank->x,tank->y,tank->direction)&&stright[tank->type-21]!=0){//���ֱ������ǰ�����ϰ���ת�� 
				if(tank->direction==72){tank->direction=80;} 
				else if(tank->direction==80){tank->direction=72;}
				else if(tank->direction==75){tank->direction=77;}
				else if(tank->direction==77){tank->direction=75;}
				stright[tank->type-21]--; 
			}else if(tankcheck(tank->x,tank->y,tank->direction)&&stright[tank->type-21]!=0){//���ǰ�����ϰ�����Ҫ����ֱ��ʱ 
				switch(tank->direction){
					case 72: tank->y--;break;//����һ�� 
					case 80: tank->y++;break;//����һ�� 
					case 75: tank->x--;break;//����һ�� 
					case 77: tank->x++;break;//����һ�� 
				}
				stright[tank->type-21]--;
			}
			tank->move=5;//ֹͣ�ƶ� 
		}else{tank->move--;}
	}
	if(stright[tank->type-21]==0){stright[tank->type-21]=4;}//����ֱ�д��� 
}
bool tankcheck(int x,int y,int direction)//���̹��ת�����������ϰ���,TRUEΪ���ϰ���FALSEΪ���ϰ� 
{
	switch(direction){
		case 72: if(map[y-2][x]==0&&map[y-2][x-1]==0&&map[y-2][x+1]==0){return 1;}else{return 0;} break;//����Ϸ����� 
		case 80: if(map[y+2][x]==0&&map[y+2][x-1]==0&&map[y+2][x+1]==0){return 1;}else{return 0;} break;//����·����� 
		case 75: if(map[y][x-2]==0&&map[y-1][x-2]==0&&map[y+1][x-2]==0){return 1;}else{return 0;} break;//��������� 
		case 77: if(map[y][x+2]==0&&map[y-1][x+2]==0&&map[y+1][x+2]==0){return 1;}else{return 0;} break;//����ҷ����� 
	}
}
void buildbullet(struct Tank *tank)//�����ӵ� U72,D80,L75,R77
{
	if(tank->direction==72){bullet[bullet_num].x=tank->x,bullet[bullet_num].y=tank->y-2,bullet[bullet_num].direction=72;}
	else if(tank->direction==80){bullet[bullet_num].x=tank->x,bullet[bullet_num].y=tank->y+2,bullet[bullet_num].direction=80;}
	else if(tank->direction==75){bullet[bullet_num].x=tank->x-2,bullet[bullet_num].y=tank->y,bullet[bullet_num].direction=75;}
	else if(tank->direction==77){bullet[bullet_num].x=tank->x+2,bullet[bullet_num].y=tank->y,bullet[bullet_num].direction=77;}
	bullet[bullet_num].exit=1,bullet[bullet_num].isnew=1;//�����ӵ�����״̬�ͳ�ʼ״̬
	if(tank->player){ bullet[bullet_num].player=1;}else if(!tank->player){ bullet[bullet_num].player=0;}//��¼�ӵ�����һ������ 
	if(map[bullet[bullet_num].y][bullet[bullet_num].x]!=0){bullethit(&bullet[bullet_num]);}//�ӵ���ʼλ�����ϰ���ʱ���̴�����ײ 
	if(bullet[bullet_num].exit){ printbullet(bullet[bullet_num].x,bullet[bullet_num].y);} //�ӵ�����ʱ�Ŵ�ӡ�ӵ� 
	bullet_num++;  if(bullet_num==20){bullet_num=0;}//�ӵ���ŵ�20ʱ�����¼��� 
}
void buildAIbullet(struct Tank *tank)//����AI�ӵ� 
{
	int high,low,right,left,i;
	if(tank->CD==12){//AI����CD����ҳ� 
		if(rand()%21==0){//���������������ÿ��CD��ʱ������ʮ��֮һ�� 
			buildbullet(&*tank);
			tank->CD=0;
		}
	}else{tank->CD++;} 
	if(tank->CD>=11){//AIǿ��,ǿ�������ȼ� 
		if(tank->y>=44){//AI̹���ڵ�ͼ�����ʱ,����AIֱ�ӳ�������� 
			if(tank->direction==75){//��AI̹�˳��� 
				buildbullet(&*tank);
				tank->CD=0;
			}
			else if(tank->direction==77){//��AI̹�˳��� 
				buildbullet(&*tank);
				tank->CD=0;
			}
		}else if(tank->x==mytank.x||tank->x==mytank.x-1||tank->x==mytank.x+1){//���AI̹�˺������ͬһ���� 
			if(tank->direction==72&&tank->y>mytank.y||tank->direction==80&&tank->y<mytank.y){//���AI̹�˳��ϲ�����������Ϸ������AI̹�˳��²�����������·� 
				if(tank->y>mytank.y){ high=mytank.y; low=tank->y;}else{ low=mytank.y; high=tank->y;}//�ڵ�ͼ�ߴ���̹�����긳Ϊ�Ӿ��ϵ�high 
				for(i=high;i<=low-2;i++){ if(map[i][tank->x]==6){break;}}//�м����ϰ�ʱ 
				if(i=low-2){//�ɷ���ʱ 
					buildbullet(&*tank);
					tank->CD=0;}
			} 
		}else if(tank->y==mytank.y||tank->y==mytank.y-1||tank->x==mytank.y+1){//���AI̹�˺������ͬһ���� 
			if(tank->direction==75&&tank->x>mytank.x||tank->direction==77&&tank->x<mytank.x){//���AI̹�˳�������������ҷ������AI̹�˳��Ҳ������������ 
				if(tank->x<mytank.x){ right=mytank.y; left=tank->y;}else{ left=mytank.y; right=tank->y;}//�ڵ�ͼ��ߵ�̹�����긳Ϊ�Ӿ��ϵ�left 
				for(i=left;i<=right-2;i++){ if(map[tank->y][i]==6){break;}}//�м����ϰ�ʱ 
				if(i=right-2){//�ɷ���ʱ 
					buildbullet(&*tank);
					tank->CD=0;}
			} 
		}
	}
}
void bulletfly(struct Bullet bullet[])//�ӵ��˶�����
{	
	int i;
	for(i=0;i<20;i++){
		if(bullet[i].exit){//����ӵ����� 
			if(!bullet[i].isnew){//����ӵ����ǳ����� 
				clearbullet(bullet[i].x,bullet[i].y);
				if(bullet[i].direction==72){(bullet[i].y)--;}
				else if(bullet[i].direction==80){(bullet[i].y)++;}
				else if(bullet[i].direction==75){(bullet[i].x)--;}
				else if(bullet[i].direction==77){(bullet[i].x)++;}
				if(map[bullet[i].y][bullet[i].x]!=0){ bullethit(&bullet[i]);} else{printbullet(bullet[i].x,bullet[i].y);}//����ӵ�����ײ���������ײ���� 
			}else if(bullet[i].isnew){bullet[i].isnew=0;} //����ӵ��ǳ�������ı��״̬ 
			bullet_bullet(bullet);//�ӵ�����ײ���� 
		}
	}
}
void bullethit(struct Bullet *bullet)//�ӵ�������� 
{
	int x=bullet->x,y=bullet->y;
	bullet->exit=0;  
	if(map[y][x]!=6&&map[y][x]!=5){//�ӵ��򵽿��ƻ�����ʱ 
		clearbullet(x,y); map[y][x]=0;
		if(bullet->direction==72){
			if(map[y][x-1]!=6&&map[y][x-1]!=5){gotoxy(x-1,y);printf(" "); map[y][x-1]=0;}
			if(map[y][x+1]!=6&&map[y][x+1]!=5){gotoxy(x+1,y);printf(" "); map[y][x+1]=0;}} 
		else if(bullet->direction==80){
			if(map[y][x-1]!=6&&map[y][x-1]!=5){gotoxy(x-1,y);printf(" "); map[y][x-1]=0;}
			if(map[y][x+1]!=6&&map[y][x+1]!=5){gotoxy(x+1,y);printf(" "); map[y][x+1]=0;}} 	
		else if(bullet->direction==75){
			if(map[y-1][x]!=6&&map[y-1][x]!=5){gotoxy(x,y-1);printf(" "); map[y-1][x]=0;}
			if(map[y+1][x]!=6&&map[y+1][x]!=5){gotoxy(x,y+1);printf(" "); map[y+1][x]=0;}} 
		else if(bullet->direction==77){
			if(map[y-1][x]!=6&&map[y-1][x]!=5){gotoxy(x,y-1);printf(" "); map[y-1][x]=0;}
			if(map[y+1][x]!=6&&map[y+1][x]!=5){gotoxy(x,y+1);printf(" "); map[y+1][x]=0;}}
	}else if(map[y][x]==6){ bullet->exit=0;//�����߿�򲻿ɴݻ��ϰ�ʱ�ӵ�������ʧ 
	}else if(map[y][x]==5){//����˭���ӵ��򵽻��أ���Ϸ����
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|8);//�򵽻���ʱ����ʾ���ر��ݻ� 
		gotoxy(42,45); printf("---");
		gotoxy(42,46); printf("\\*/");
		gotoxy(42,47); printf("nnn");color(7);
		gameover();}
	if(!bullet->player&&x>=mytank.x-1&&x<=mytank.x+1&&y>=mytank.y-1&&y<=mytank.y+1){//����з��ӵ�������� 
		clearbullet(x,y); bullet->exit=0;//����ӵ� 
	}
	
}
 void bullethit_tank(struct Bullet *bullet)//�ӵ����̹�� 
{
	int i,x=bullet->x,y=bullet->y;
	if(!bullet->player&&x>=mytank.x-1&&x<=mytank.x+1&&y>=mytank.y-1&&y<=mytank.y+1&&bullet->exit){//����з��ӵ�������� 
		bullet->exit=0; clearbullet(x,y);//����ӵ� 
		cleartank(mytank.x,mytank.y); mytank.x=37,mytank.y=46;//����ҷ�̹�˲���ʼ�����̹��λ�� 
		mytank.heart--; /*���̹��������1*/ score--; /*������÷ּ�1*/
	}
	for(i=0;i<4;i++){
		if(bullet->player&&AItank[i].alive&&x>=AItank[i].x-1&&x<=AItank[i].x+1&&y>=AItank[i].y-1&&y<=AItank[i].y+1&&bullet->exit){//�����Ҵ��еط�̹��1 
			bullet->exit=0; clearbullet(x,y);//����ӵ� 
			cleartank(AItank[i].x,AItank[i].y); AItank[i].alive=0;AItank[i].isrebirth=1; AItank[i].x=88,AItank[i].y=48;//���AI̹��
			AItank[i].heart--; score++;//������÷ּ�1 
		}
	}
	gotoxy(96,6); printf("    "); color(11); gotoxy(96,6); printf("%d",score); color(7);//��ӡ�µĵ÷� 
	gotoxy(108,8);	color(2); printf("%d",mytank.heart); color(7);//��ӡ�µ�������� 
	gotoxy(115,10); printf("  "); color(4); gotoxy(115,10); printf("%d",AItank[0].heart+AItank[1].heart+AItank[2].heart+AItank[3].heart); color(7);//��ӡ�µĵط�ʣ������ 
}
void printbullet(int x,int y)//�ӵ���ӡ���� 
{
	gotoxy(x,y); color(8); printf("o"); color(7);
}
void clearbullet(int x,int y)//�ӵ��������
{
	gotoxy(x,y); printf(" ");
}
void bullet_bullet(struct Bullet bullet[])//�ӵ�����ײ������ 
{
	int m,n;
	for(m=0;m<20;m++){
		if(bullet[m].exit){
			for(n=m+1;n<20;n++){
				if(bullet[n].exit&&m!=n&&bullet[m].x==bullet[n].x&&bullet[m].y==bullet[n].y){//�ӵ���ײʱ,�ж������ӵ��Ż�һ����ʧ 
					if(bullet[m].player!=bullet[n].player){
						bullet[m].exit=0; bullet[n].exit=0;
						clearbullet(bullet[m].x,bullet[m].y); clearbullet(bullet[n].x,bullet[n].y);
					}
				}
			}
		}
	}
}
void printhome()//��ӡ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|8);
	gotoxy(42,45); printf(" |*");
	gotoxy(42,46); printf("\\U/");
	gotoxy(42,47); printf("nHn");color(7);
}
void printmap(int num)//��ӡ��ͼ 
{
	int i,j;
	switch(num){
		case 0:
			for(i=1;i<48;i++){ gotoxy(1,i); for(j=1;j<86;j++){
				if(map[i][j]==1){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8|15|32|64); square(2);}
				else if(map[i][j]==0||map[i][j]==5){color(15); printf(" ");} 
				else if(map[i][j]==6){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|128|32); square(0);}
				else if(map[i][j]==3){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14|32|16); square(8);}
				else if(map[i][j]==2){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8|14|128|16); square(9);}}}color(7);/*���ñ���ɫ */break;
		case 1:
			for(i=1;i<48;i++){ gotoxy(1,i); for(j=1;j<86;j++){
				if(map[i][j]==0||map[i][j]==5){color(15); printf(" ");} 
				else if(map[i][j]==6){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14|64|32); square(8);}
				else if(map[i][j]==3){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14|32|16); square(8);}}}color(7);/*���ñ���ɫ */break;
		case 2:
			for(i=1;i<48;i++){ gotoxy(1,i); for(j=1;j<86;j++){
				if(map[i][j]==0||map[i][j]==5){color(15); printf(" ");} 
				else if(map[i][j]==2){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|64|32|16); square(9);}
				else if(map[i][j]==1){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),128|64); square(3);}
				else if(map[i][j]==3){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6|16|32); square(4);}
				else if(map[i][j]==4){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8|64|32); square(7);}}}color(7);/*���ñ���ɫ */break;
	}
}
void maplibrary(int num_map)//��ͼ�� 
{
	int i,j;
	int map1[49][87]={
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,6},
	{6,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,0,0,0,0,6},
	{6,0,0,0,0,6,6,1,6,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,2,6,2,6,0,0,0,0,6},
	{6,0,2,2,0,6,6,1,6,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,6,1,6,6,0,2,2,0,6},
	{6,0,1,1,0,6,1,2,1,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,1,2,1,6,0,1,1,0,6},
	{6,0,2,2,0,6,1,2,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,2,1,6,0,2,2,0,6},
	{6,0,1,1,0,6,2,1,2,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,2,1,2,6,0,1,1,0,6},
	{6,0,2,2,0,6,1,2,1,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,1,2,1,6,0,2,2,0,6},
	{6,0,0,0,0,6,1,2,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,2,1,6,0,0,0,0,6},
	{6,0,0,0,0,6,6,1,6,6,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,6,6,1,6,6,0,0,0,0,6},
	{6,0,0,0,0,6,2,6,2,6,0,2,2,2,2,2,2,2,0,6,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,6,0,2,2,2,2,2,2,2,0,6,2,6,2,6,0,0,0,0,6},
	{6,0,0,0,0,6,6,6,6,6,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,6,6,6,6,6,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,2,2,2,2,0,6,2,2,0,0,0,2,0,0,0,0,6,0,0,0,0,2,0,0,0,2,2,6,0,2,2,2,2,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,1,1,1,1,6,0,0,0,0,0,0,6,2,0,0,0,0,0,2,0,0,0,6,0,0,0,2,0,0,0,0,0,2,6,0,0,0,0,0,0,6,1,1,1,1,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,6,0,1,0,0,0,0,0,2,0,0,6,0,0,2,0,0,0,0,0,1,0,6,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,0,2,6,0,0,0,0,0,0,6,0,0,1,0,0,0,0,0,2,0,6,0,2,0,0,0,0,0,1,0,0,6,0,0,0,0,0,0,6,2,0,0,0,2,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,2,0,2,0,6,0,0,0,0,0,0,6,0,0,0,1,0,0,0,0,0,2,6,2,0,0,0,0,0,1,0,0,0,6,0,0,0,0,0,0,6,0,2,0,2,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,1,1,1,1,0,6,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,6,0,1,1,1,1,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,2,0,2,0,6,0,0,0,0,0,0,6,0,0,0,1,0,0,0,0,0,2,6,2,0,0,0,0,0,1,0,0,0,6,0,0,0,0,0,0,6,0,2,0,2,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,0,2,6,0,0,0,0,0,0,6,0,0,1,0,0,0,0,0,2,0,6,0,2,0,0,0,0,0,1,0,0,6,0,0,0,0,0,0,6,2,0,0,0,2,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,6,0,1,0,0,0,0,0,2,0,0,6,0,0,2,0,0,0,0,0,1,0,6,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,1,1,1,1,6,0,0,0,0,0,0,6,2,0,0,0,0,0,2,0,0,0,6,0,0,0,2,0,0,0,0,0,2,6,0,0,0,0,0,0,6,1,1,1,1,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,2,2,2,2,0,6,2,2,0,0,0,2,0,0,0,0,6,0,0,0,0,2,0,0,0,2,2,6,0,2,2,2,2,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,6,6,6,6,6,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,2,0,0,6,0,0,0,0,0,0,0,0,0,6,6,6,6,6,0,0,0,0,6},
	{6,0,0,0,0,6,2,6,2,6,0,2,2,2,2,2,2,2,0,6,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,6,0,2,2,2,2,2,2,2,0,6,2,6,2,6,0,0,0,0,6},
	{6,0,0,0,0,6,6,1,6,6,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,6,6,1,6,6,0,0,0,0,6},
	{6,0,0,0,0,6,1,2,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,2,1,6,0,0,0,0,6},
	{6,0,2,2,0,6,1,2,1,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,1,2,1,6,0,2,2,0,6},
	{6,0,1,1,0,6,2,1,2,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,2,1,2,6,0,1,1,0,6},
	{6,0,2,2,0,6,1,2,1,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,1,2,1,6,0,2,2,0,6},
	{6,0,1,1,0,6,1,2,1,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,1,2,1,6,0,1,1,0,6},
	{6,0,2,2,0,6,6,1,6,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,6,1,6,6,0,2,2,0,6},
	{6,0,0,0,0,6,2,6,2,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,2,6,2,6,0,0,0,0,6},
	{6,0,0,0,0,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,5,5,5,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,6},
	{6,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,5,5,5,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,5,5,5,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}};
	int map2[49][87]={
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,6,6,6,6,6,6,6,6,6,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,6,6,6,6,6,6,6,6,6,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,6,6,6,6,6,6,6,6,6,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,6,6,6,6,6,6,6,6,6,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}};
	int map3[49][87]={
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,0,4,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,0,0,0,1,1,1,0,0,0,2,2,0,0,0,0,2,2,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,0,0,1,1,1,0,0,0,2,2,0,0,0,0,2,2,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,1,1,1,0,0,0,2,2,0,0,0,0,2,2,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3,0,0,3,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,0,0,3,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,0,0,0,3,0,0,3,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,4,4,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}};
	switch(num_map)
	{
		case 0: for(i=0;i<49;i++){ for(j=0;j<87;j++){ map[i][j]=map1[i][j];}} break;
		case 1: for(i=0;i<49;i++){ for(j=0;j<87;j++){ map[i][j]=map2[i][j];}} break;
		case 2: for(i=0;i<49;i++){ for(j=0;j<87;j++){ map[i][j]=map3[i][j];}} break;
	}
}
void square(int style,int color,int back)//����ש��
{
	int zfx=254,round=2,diamond=29,dbl=126,zsjx=30,xin=3;
	switch(style)
	{
		case 0: printf("%c",zfx); break;//������ש�����ɴݻ�
		case 1:	printf("*"); break;//��ש 
		case 2: printf("+"); break;//ʮ��ש 	
		case 3: printf("-"); break;//����ש 
		case 4:	printf("="); break; //˫����ש 
		case 5:	printf("%c",round); break;//Բ��ש 
		case 6:	printf("%c",dbl); break;//~ש 
		case 7: printf("%c",zsjx); break;//��������ש 
		case 8: printf("%c",xin); break;//��ש 
		case 9: printf("x"); break;//xש
	}
}
void creatfile()//�����ļ����򿪶�ȡ��������Ϣ 
{
	FILE *p1,*p2;
	int i;
	if((p2=fopen("Num of rank.txt","r"))==NULL){//��ʼû���ļ���Ҫ���� 
		p2=fopen("Num of rank.txt","w");
		fputc('0',p2);
	}else{//��ȡ��Ϣ���ȶ���������һ���ļ���ȡҪ�õ� 
		fscanf(p2,"%d",&num_rank);
	} fclose(p2);
	if((p1=fopen("Rank List.txt","r"))==NULL){//��ʼû���ļ���Ҫ���� 
		p1=fopen("Rank List.txt","w");
	}else{//��ȡ��ʷ���а����Ϣ 
		if(num_rank!=0&&num_rank<10){
			for(i=0;i<num_rank;i++){fscanf(p1,"%s %d",rank[i].name,&rank[i].score);}
		}else if(num_rank!=0&&num_rank>=10){
			for(i=0;i<10;i++){fscanf(p1,"%s %d",rank[i].name,&rank[i].score);}
		}
	}fclose(p1);

}
void sort()//ð������ṹ������ 
{
	int i,j;
	struct Rank temp; 
	for(i=1;i<=num_rank-1;i++){
		for(j=0;j<num_rank-i;j++){
			if(rank[j].score<rank[j+1].score){
				temp=rank[j]; rank[j]=rank[j+1]; rank[j+1]=temp;
			}
		}
	}
}
