#include<stdio.h>
#include<stdbool.h>
#include<windows.h> 
#include<conio.h>
#include<time.h>

//全局变量
struct Bullet//子弹结构体 
{
	int x,y;//子弹坐标
	int direction;//方向变量，U72,D80,L75,R77
	bool player;//区分发射子弹的一方，TRUE为玩家，FALSE为AI 
	bool isnew;//记录子弹是否为第一次建立，TRUE为第一次，FALSE为非第一次 
	bool exit;//判断子弹是否存在，TRUE为存在，FALSE为不存在 
}bullet[20];//全场子弹公用数组，游戏实际不会同时存在20个子弹 
struct Tank//坦克结构体 
{
	int x,y;//坦克中心坐标
	int direction;//方向变量，U72,D80,L75,R77 
	int color;//坦克颜色，AI坦克颜色从红到黄到绿到白 
	int CD;//发射子弹冷却时间 
	int type;//坦克编号，AI专用 
	int heart;//坦克剩余生命，AI专用 
	int move;//AI坦克移动一次下三次就停止移动，AI专用 
	int isrebirth;//AI是否复活，AI专用 
	bool player;//区分操作坦克的对象，TRUE为玩家，FALSE为AI 
	bool alive;//判断坦克是否存活，TRUE为存活，FALSE为阵亡 
}AItank[4],mytank;
struct Rank
{
	char name[25];
	int score;
}rank[100];//存100位但是只展示前10名 
int choose_homepage;//主页面选择参数 
char input;
int bullet_num;//场上子弹编号 
int map_num;//地图编号 
int lastmap=100;//记录地图编号使连续两次地图不重复 
int stright[3];//AI坦克直行次数 
int num_rank;//当前排名的人数，最多为10人 
int level;//通过关卡数 
int score;//得分 
int map[49][87];//全局输出地图 
int temp_tank[3][3];//全局输出坦克 
//界面框架函数 
void frame();//游戏框架
void frame_choose();//主页面选择框架 
void clean();//清空指定区域 
//文字打印函数
void maintitle();//游戏主页面大字 
void mainchoose();//游戏主页面选择项字体 
void datacharacters();//开始游戏后右侧窗口文字 
//系统设置函数
void HideCursor();//隐藏光标
void gotoxy();//光标跳转 
void color();//自定义函数改变字体颜色 
void initialize();//开始游戏初始化 
void gameover();//游戏结束检查 
void pause();//游戏暂停函数 
void gamecheck();//游戏完成检查 
void nextlevel();//下一关跳转 
void lookforrank();//查看排行榜 
void isnewrank();//是否能加入排行榜 
//跳转和组合函数 
void operation_homepage();//主页面操作跳转 
void gameinput();//游戏中按键读取 
void homepage();//主页面组合 
void gamepage();//开始游戏页面组合 
//坦克
void tanklibrary();//坦克库 
void printmytank();//打印坦克 
void printAItank();//打印AI坦克 
void cleartank();//通用清楚坦克 
void movemytank();//玩家坦克移动 
void moveAItank();//AI坦克移动  
bool tankcheck();//检查坦克转向方向上有无障碍物,TRUE为无障碍，FALSE为有障碍 
//子弹
void buildbullet();//创建子弹 
void buildAIbullet();//创建AI子弹 
void bulletfly();//子弹运动函数
void bullethit();//子弹打击函数 
void bullethit_tank();//子弹打击坦克 
void printbullet();//子弹打印函数 
void clearbullet();//子弹清除函数 
void bullet_bullet();//子弹间碰撞处理函数  
//地图设计 
void printhome();//打印基地 
void printmap();//打印地图 
void maplibrary();//地图库 
void square();//地形砖块 
//文件和排序 
void creatfile();//创建文件并打开读取人数即信息 
void sort();//排序结构体数组 
int main()
{
	creatfile();//创建文件并打开读取人数即信息 
	srand(time(NULL)); //设置随机数种子 
	HideCursor();//隐藏光标 
	SetConsoleOutputCP(437);//更改CMD打印扩展ASCII码字符 
	system("mode con cols=120 lines=50");//设置显示窗口大小 
	homepage();//主页面组合
	return 0;
}
void frame(int x)//游戏框架 
{
	int hors=205,vers=186,clus=201,clds=200,crus=187,crds=188,r3s=204,l3s=185,cnt_h,cnt_v;
	switch(x) 
	{
		case 1://整体大框架 
			color(4); gotoxy(0,0);
			printf("%c",clus); for(cnt_h=0;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crus);
			for(cnt_v=1;cnt_v<48;cnt_v++){printf("%c",vers); gotoxy(119,cnt_v); printf("%c",vers);}
			printf("%c",clds); for(cnt_h=0;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crds);
			color(7); break; 
		case 2://游戏区框架 
			color(14); gotoxy(0,0);
			printf("%c",clus); for(cnt_h=0;cnt_h<85;cnt_h++){printf("%c",hors);} printf("%c",crus);
			for(cnt_v=1;cnt_v<48;cnt_v++){gotoxy(0,cnt_v); printf("%c",vers); gotoxy(86,cnt_v); printf("%c",vers);}
			gotoxy(0,48); printf("%c",clds); for(cnt_h=0;cnt_h<85;cnt_h++){printf("%c",hors);} printf("%c",crds);
			color(7); break;
		case 3://数据区框架 
			color(9); gotoxy(87,0);
			printf("%c",clus); for(cnt_h=87;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crus);
			for(cnt_v=1;cnt_v<48;cnt_v++){gotoxy(87,cnt_v); printf("%c",vers); gotoxy(119,cnt_v); printf("%c",vers);}
			gotoxy(87,48); printf("%c",clds); for(cnt_h=87;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crds);
			gotoxy(87,18); printf("%c",r3s);for(cnt_h=88;cnt_h<119;cnt_h++){printf("%c",hors);} printf("%c",l3s);
			color(7); break;
			break;
		case 4://排行榜右侧框架
			color(9); gotoxy(87,0);
			printf("%c",clus); for(cnt_h=87;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crus);
			for(cnt_v=1;cnt_v<48;cnt_v++){gotoxy(87,cnt_v); printf("%c",vers); gotoxy(119,cnt_v); printf("%c",vers);}
			gotoxy(87,48); printf("%c",clds); for(cnt_h=87;cnt_h<118;cnt_h++){printf("%c",hors);} printf("%c",crds);
			color(7); break;
			break;
	}
}
void frame_choose(int x)//主页面选择框架 
{
	int vers=186,hors=205,clus=201,clds=200,crus=187,crds=188,cnt_hor;
	switch(x)
	{
		case 0://未选择时全体 
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
		case 11://选择1
			color(14);
			gotoxy(50,26); printf("%c",vers); gotoxy(67,26); printf("%c",vers);
			gotoxy(50,25); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,27); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds); color(7); choose_homepage=1; break;
		case 12://选择2
			color(14);
			gotoxy(50,30); printf("%c",vers); gotoxy(67,30); printf("%c",vers);
			gotoxy(50,29); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,31); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds); color(7); choose_homepage=2; break;
		case 13://选择3
			color(14);
			gotoxy(50,34); printf("%c",vers); gotoxy(67,34); printf("%c",vers);
			gotoxy(50,33); printf("%c",clus); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crus);
			gotoxy(50,35); printf("%c",clds); for(cnt_hor=0;cnt_hor<16;cnt_hor++){printf("%c",hors);} printf("%c",crds); color(7); choose_homepage=3; break;
	}
}
void clean(int c)//清空指定区域
{
	int h,v;
	switch(c){
		case 100://清空全部界面 
			gotoxy(0,0); for(v=0;v<=50;v++){ for(h=0;h<=119;h++){ putchar(32);}} break;
	}
} 
void maintitle()//游戏主页面大字 
{
	int d3=194,u3=193,r3=195,ver=179,hor=196,hors=205,cru=191,crd=217,clu=218,cld=192;
	color(15);
	gotoxy(25,10); printf("%c%c%c%c%c%c%c",hor,hor,hor,d3,hor,hor,hor);//打印T 
	gotoxy(28,11); printf("%c",ver); gotoxy(28,12); printf("%c",ver); gotoxy(28,13); printf("%c",ver); gotoxy(28,14); printf("%c",ver);
	gotoxy(39,11); printf("%c%c%c%c%c%c",hor,hor,hor,hor,hor,cru); gotoxy(38,11); printf("%c",clu); //打印a 
	gotoxy(38,12); printf("%c",ver); gotoxy(38,13); printf("%c",ver); gotoxy(44,12); printf("%c",ver); gotoxy(44,13); printf("%c",ver);
	gotoxy(38,14); printf("%c%c%c%c%c%c%c%c",cld,hor,hor,hor,hor,hor,u3,hor);
	gotoxy(52,11); printf("%c%c%c%c%c",hor,hor,hor,hor,hor);//打印n
	gotoxy(51,11); printf("%c",clu); gotoxy(51,12); printf("%c",ver); gotoxy(51,13); printf("%c",ver); gotoxy(51,14); printf("%c",ver);
	gotoxy(57,11); printf("%c",cru); gotoxy(57,12); printf("%c",ver); gotoxy(57,13); printf("%c",ver); gotoxy(57,14); printf("%c",ver);
	gotoxy(65,11); printf("%c%c%c%c%c",hor,hor,hor,hor,hor);//打印c
	gotoxy(64,11); printf("%c",clu); gotoxy(64,12); printf("%c",ver); gotoxy(64,13); printf("%c",ver); 
	gotoxy(64,14); printf("%c%c%c%c%c%c",cld,hor,hor,hor,hor,hor); 
	gotoxy(76,11); printf("%c",ver); gotoxy(76,12); printf("%c",ver); gotoxy(76,13); printf("%c",ver); gotoxy(76,14); printf("%c",ver);//打印k 
	gotoxy(79,11); printf("/"); gotoxy(77,12); printf("/"); gotoxy(78,13); printf("\\"); gotoxy(79,14); printf("\\");
	gotoxy(89,11); printf("%c%c%c%c%c",hor,hor,hor,hor,cru);//打印e
	gotoxy(88,11); printf("%c",clu); gotoxy(88,12); printf("%c",ver); gotoxy(88,13); printf("%c",r3); 
	gotoxy(89,13); printf("%c%c%c%c%c",hor,hor,hor,hor,crd); gotoxy(93,12); printf("%c",ver);
	gotoxy(88,14); printf("%c%c%c%c%c%c",cld,hor,hor,hor,hor,hor); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6|8|128|64); gotoxy(95,16); printf("2 0 2 3"); color(7);
	gotoxy(48,37); color(6); printf("Choose: %c , %c and Enter",24,25); color(7);
}
void mainchoose()//游戏主页面选择字体 
{
	color(10); gotoxy(54,26); printf("Start Game"); gotoxy(53,30); printf(" Rank List"); gotoxy(53,34); printf(" Exit Game"); color(7);
}
void datacharacters()//开始游戏后右侧窗口文字 
{
	//上半部分 
	gotoxy(89,4); color(6); printf("Level:"); color(7);
	gotoxy(89,6); color(15); printf("Socre:"); color(7);
	gotoxy(89,8); color(2); printf("Num of Left Heart:"); color(7);
	gotoxy(89,10); color(4); printf("Num of Left enemy's tank:"); color(7);
	gotoxy(89,14); color(13); printf("Current State of Game:"); color(7);
	//下半部分 
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
void HideCursor()//隐藏光标
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y)//光标跳转 
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void color(int x)//改变字体颜色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
void initialize()//开始游戏初始化
{
	int i; bullet_num=0;//全场子弹书重置 	
	for(i=0;i<3;i++){stright[i]=3;}//AI坦克直行次数重置 
	for(i=0;i<20;i++){//子弹初始化
		bullet[i].exit=0;
		bullet[i].isnew=0;
	} 
	for(i=0;i<4;i++){
		AItank[i].player=0;//设置坦克控制方 
		AItank[i].alive=0;//设置坦克初始为存活 
		AItank[i].color=12;//设置坦克颜色
		AItank[i].isrebirth=0; 
		AItank[i].heart=4;//设置AI坦克生命 
		AItank[i].direction=80;//为AI坦克初始方向朝下
		AItank[i].type=21+i;//为AI坦克编号 
		AItank[i].move=1;//使AI坦克初始即可移动 
		AItank[i].CD=12;//设置AI开火CD 
	}
	AItank[0].x=15,AItank[0].y=5;
	AItank[1].x=33,AItank[1].y=5;
	AItank[2].x=57,AItank[2].y=5;
	AItank[3].x=74,AItank[3].y=5;
	mytank.player=1,mytank.alive=1,mytank.heart=4,mytank.color=14,mytank.CD=2,mytank.direction=72;//玩家坦克初始方向朝上 
	mytank.x=37,mytank.y=46;//初始化玩家坦克位置 
	gotoxy(96,4); color(15); printf("%d",level); color(7);//打印 
	gotoxy(96,6); color(11); printf("%d",score); color(7);
	gotoxy(108,8); color(2); printf("%d",mytank.heart); color(7);
	gotoxy(115,10); color(4); printf("%d",AItank[0].heart+AItank[1].heart+AItank[2].heart+AItank[3].heart); color(7);
	color(10); gotoxy(95,15); printf("Game is Underway"); color(7);//打印游戏状态 
}
void gameover() 
{
	int vers=186,hors=205,clus=201,clds=200,crus=187,crds=188,i,j;
	for(i=22;i<=26;i++){gotoxy(30,i); for(j=31;j<=55;j++){printf(" "); }}//先清空指定区域 
	gotoxy(38,23); color(12); printf("Game Over!");
	gotoxy(32,25); color(10); printf("Esc is Return Homepage"); color(7);
	gotoxy(30,21); printf("%c",clus); for(i=1;i<25;i++){printf("%c",hors);} printf("%c",crus);
	for(i=22;i<=26;i++){ gotoxy(30,i); printf("%c",vers); gotoxy(55,i); printf("%c",vers);}
	gotoxy(30,27); printf("%c",clds); for(i=1;i<25;i++){printf("%c",hors);} printf("%c",crds);
	while(1){if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){homepage();}}
}
void pause()//游戏暂停函数
{
	gotoxy(95,15); printf("                "); color(12); gotoxy(95,15); printf("Game is Pasuing"); color(7);//打印游戏状态 
	while(1){
		if(GetAsyncKeyState('O')& 0x8000){
			gotoxy(95,15); printf("                "); color(10); gotoxy(95,15); printf("Game is Underway"); color(7); break;//打印游戏状态 
		}else if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){homepage();}}
	Sleep(3);//恢复游戏后等待三秒 
}
void gamecheck()//游戏完成检查 
{
	if(AItank[0].heart==0&&AItank[1].heart==0&&AItank[2].heart==0&&AItank[3].heart==0){
		level++; nextlevel();//AI坦克全部死亡时进入下一关 
	}
	if(mytank.heart==0){
		gameover();
	}
}
void nextlevel()//下一关跳转 
{
	int vers=186,hors=205,clus=201,clds=200,crus=187,crds=188,i,j;
	for(i=22;i<=26;i++){gotoxy(30,i); for(j=31;j<=55;j++){printf(" "); }}//先清空指定区域 
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
			isnewrank();//判断是否能进入排行榜前十名 
			homepage();}//未进入则直接返回主页面 
	}
}
void lookforrank()//查看排行榜 
{
	sort();
	int row,cnt; //打印文字UI 
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
	while(1){if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){homepage();}}//返回主界面选项 
}
void isnewrank()//是否能加入排行榜 
{
	if(level>=2){//至少通过一关才可以进入排行榜 
		int position,i;
		bool is=0;
		if(num_rank!=0){
			for(i=0;i<10;i++){
				if(score>rank[i].score){
					is=1;//可以加入排行榜
					position=i;//位次 
					break;
				}	
			}
		}else if(num_rank==0){//若为进入排行榜的第一位 
			is=1;
			position=0;
		}
		if(is){
			num_rank++;
			if(num_rank>=10){num_rank=10;}
			for(i=num_rank-1;i>=position;i--){//将位次之后的人依次后移 
				rank[i]=rank[i-1];
			}
			//展示信息 
			int row,cnt; //打印文字UI 
			clean(100);frame(1);
			gotoxy(53,5); color(10); printf("Rank List"); color(7);
			gotoxy(45,8); color(14); printf("Name                    Score"); color(7);
			gotoxy(44,44); color(13); printf("Please Enter Player's Name");
			for(row=11,cnt=0;cnt<10;row+=3,cnt++){//编号 
				gotoxy(37,row); color(12); printf("%d.",cnt+1);
			}
			for(cnt=0,row=11;cnt<position;cnt++,row+=3){//位次之前的信息 
				gotoxy(44,row); color(15); printf("%s",rank[cnt].name); gotoxy(70,row); color(11); printf("%d",rank[cnt].score); color(7);
			}
						
			for(cnt=position+1,row=11+3*(position+1);cnt<num_rank;cnt++,row+=3){//位次之后的信息 
				gotoxy(44,row); color(15); printf("%s",rank[cnt].name); gotoxy(70,row); color(11); printf("%d",rank[cnt].score); color(7);
			}
			
			rank[position].score=score;  gotoxy(70,11+3*position); color(11); printf("%d",rank[position].score); color(7);//本位次先打印分数 

		
			gotoxy(44,11+3*position); color(15); gets(rank[position].name); color(7);
			//存入新的信息
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
void operation_homepage(int get)//主页面操作跳转 
{
	switch(get){
		case 1:gamepage(); break;//开始游戏 
		case 2:lookforrank(); break;//查看排行榜 
		case 3: exit(0);//退出游戏 
	}
}
void gameinput()//游戏中按键读取 
{
	int keyboard,cnt=0;
	if(GetAsyncKeyState(VK_UP)& 0x8000){movemytank(72);}//上 
	else if(GetAsyncKeyState(VK_DOWN)& 0x8000){movemytank(80);}//下 
	else if(GetAsyncKeyState(VK_LEFT)& 0x8000){movemytank(75);}//左 
	else if(GetAsyncKeyState(VK_RIGHT)& 0x8000){movemytank(77);}//右 
	else if(GetAsyncKeyState(VK_ESCAPE)& 0x8000){pause();homepage();} //通关数大于1并且分数可以进排行榜时，先上排行榜再返回主页面 
	else if(GetAsyncKeyState(VK_SPACE)& 0x8000){
		if(mytank.CD==2){//开火，并设置开火间隔 
			buildbullet(&mytank);
			mytank.CD=0;
		}else{mytank.CD++;}}
	else if(GetAsyncKeyState('P')& 0x8000){pause();}//暂停 
}
void homepage()//主页面组合
{
	level=1; score=0;//通过关卡数和分数  
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
void gamepage()//开始游戏页面组合 
{
	int i,interval1=1,interval2=1,intervalAI[3];
	intervalAI[0]=1,intervalAI[1]=1,intervalAI[2]=1,intervalAI[3]=1;
	clean(100); frame(2); frame(3);//框架 
	initialize();//游戏初始化
	if(lastmap==100){lastmap=2;}do{ map_num=rand()%3;}while(lastmap==map_num);//使连续两次地图不重复 
	lastmap=map_num; maplibrary(map_num); printmap(map_num);//随机地图 
	if(map_num==0){printhome();}//打印基地，目前只有map1需要 
	printmytank(mytank);//打印玩家坦克 
	datacharacters();//副窗口文字

	for(;;){
		gamecheck();//检查游戏是否结束或是否进入下一关 
		if(interval1++%2==0){
			bulletfly(bullet);//所有子弹运动 

			for(i=0;i<20;i++){
				bullethit_tank(&bullet[i]);//检查子弹是否打中坦克 
			}
					
			if(!AItank[0].alive&&AItank[0].heart>0&&AItank[0].isrebirth==1&&intervalAI[0]++%89==0){AItank[0].x=15,AItank[0].y=5;AItank[0].isrebirth=11;}//初始化死亡坦克的位置，二重强化，防止连续刷分
			if(!AItank[1].alive&&AItank[1].heart>0&&AItank[1].isrebirth==1&&intervalAI[1]++%89==0){AItank[1].x=33,AItank[1].y=5;AItank[1].isrebirth=11;}
			if(!AItank[2].alive&&AItank[2].heart>0&&AItank[2].isrebirth==1&&intervalAI[2]++%89==0){AItank[2].x=57,AItank[2].y=5;AItank[2].isrebirth=11;}
			if(!AItank[3].alive&&AItank[3].heart>0&&AItank[3].isrebirth==1&&intervalAI[3]++%89==0){AItank[3].x=74,AItank[3].y=5;AItank[3].isrebirth=11;}
			
			for(i=0;i<=3;i++){//AI坦克移动 
				moveAItank(&AItank[i]);
				if(AItank[i].alive&&AItank[i].heart>=1){printAItank(&AItank[i]);}	
			}
			
			for(i=0;i<=3;i++){//建立及复活AI坦克 
				if(AItank[i].alive==0&&AItank[i].heart==4){ printAItank(&AItank[i]);}//初始创建AI 
				if(AItank[i].alive==0&&AItank[i].heart>=1&&AItank[i].isrebirth==11&&intervalAI[i]++%90==0){ printAItank(&AItank[i]);AItank[i].isrebirth=0;}//复活AI 
			}
			
			for(i=0;i<=3;i++) {//AI开火设置 
				if(AItank[i].alive&&intervalAI[i]++%2==0){//AI坦克存活时才进行发射子弹 
					buildAIbullet(&AItank[i]);
				}
			}
		
			if(mytank.alive&&interval2++%3==0){//输入函数 
				gameinput();
			}
		
			if(!mytank.alive&&mytank.heart<4){//如果玩家坦克死亡 
				mytank.x=37,mytank.y=46;//初始化玩家坦克位置
				printmytank(&mytank);
			}
		}
		Sleep(3);
	}
}
void tanklibrary(int player,int direction)//坦克库，x1朝上，x2朝下，x3朝左，x4朝右 
{
	int i,j;
	int tank11[3][3]={{201,179,187},{204,79,185},{200,207,188}};//玩家tank 
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
	if(player==1){//若坦克为玩家 
		switch(direction){
			case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank11[i][j];}} break;
			case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank12[i][j];}} break;
			case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank13[i][j];}} break;
			case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank14[i][j];}} break;}}
	else{//若坦克为电脑 
		if(player==21){//1号AItank 
			switch(direction){
				case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank21[i][j];}} break;
				case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank22[i][j];}} break;
				case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank23[i][j];}} break;
				case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank24[i][j];}} break;}}
		if(player==22){//2号AItank 
			switch(direction){
				case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank31[i][j];}} break;
				case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank32[i][j];}} break;
				case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank33[i][j];}} break;
				case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank34[i][j];}} break;}}
		if(player==23){//3号AItank 
			switch(direction){
				case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank41[i][j];}} break;
				case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank42[i][j];}} break;
				case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank43[i][j];}} break;
				case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank44[i][j];}} break;}}
		if(player==24){//4号AItank 
			switch(direction){
				case 72: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank51[i][j];}} break;
				case 80: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank52[i][j];}} break;
				case 75: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank53[i][j];}} break;
				case 77: for(i=0;i<3;i++){ for(j=0;j<3;j++){ temp_tank[i][j]=tank54[i][j];}} break;}}
	}
}
void printmytank(struct Tank *tank)//打印坦克 
{
	tanklibrary(1,tank->direction);//是玩家则传递1，不是玩家则传递AI坦克编号 

	color(tank->color);
	gotoxy(tank->x-1,tank->y-1);printf("%c%c%c",temp_tank[0][0],temp_tank[0][1],temp_tank[0][2]);
	gotoxy(tank->x-1,tank->y);printf("%c%c%c",temp_tank[1][0],temp_tank[1][1],temp_tank[1][2]);
	gotoxy(tank->x-1,tank->y+1);printf("%c%c%c",temp_tank[2][0],temp_tank[2][1],temp_tank[2][2]); color(7);
}
void printAItank(struct Tank *tank)//打印AI坦克 
{
	tank->alive=1;
	int x=tank->x,y=tank->y;
	tanklibrary(tank->type,tank->direction);
	if(tank->heart==4){color(12);}//红 
	else if(tank->heart==3){color(6);}//黄 
	else if(tank->heart==2){color(10);}//绿 
	else if(tank->heart==1){color(15);}//白
	gotoxy(x-1,y-1);printf("%c%c%c",temp_tank[0][0],temp_tank[0][1],temp_tank[0][2]);
	gotoxy(x-1,y);printf("%c%c%c",temp_tank[1][0],temp_tank[1][1],temp_tank[1][2]);
	gotoxy(x-1,y+1);printf("%c%c%c",temp_tank[2][0],temp_tank[2][1],temp_tank[2][2]); color(7);
}
void cleartank(int x,int y)//通用清除坦克 
{
	gotoxy(x-1,y-1);printf("   ");
	gotoxy(x-1,y);printf("   ");
	gotoxy(x-1,y+1);printf("   "); 
}
void movemytank(int move)//玩家坦克移动 
{
	cleartank(mytank.x,mytank.y);//清除原来位置的坦克
	mytank.direction=move;
	if(tankcheck(mytank.x,mytank.y,mytank.direction)){//检查我的坦克转向方向上有无障碍物 
		switch(mytank.direction){
			case 72: mytank.y--;break;//上移一格 
			case 80: mytank.y++;break;//下移一格 
			case 75: mytank.x--;break;//左移一格 
			case 77: mytank.x++;break;//右移一格 
		}
	}//若无法移动则打印转向后的坦克 
	printmytank(&mytank);
}
void moveAItank(struct Tank *tank)//AI坦克移动  
{
	int t=rand()%4;

	if(tank->alive){//如果坦克存活才进行操作 
		if(tank->move==0){//坦克可以移动时进行操作
			cleartank(tank->x,tank->y);//清除原来位置的坦克
			if(tankcheck(tank->x,tank->y,tank->direction)&&stright[tank->type-21]==4){//前方无障碍并且直行刚开始时 
				if(t==0){tank->direction=72;}//随机移动一个方向 
				else if(t==1){tank->direction=80;}
				else if(t==2){tank->direction=75;}
				else if(t==3){tank->direction=77;}
				stright[tank->type-21]--;
			}else if(!tankcheck(tank->x,tank->y,tank->direction)&&stright[tank->type-21]!=0){//如果直行中正前方有障碍则转向 
				if(tank->direction==72){tank->direction=80;} 
				else if(tank->direction==80){tank->direction=72;}
				else if(tank->direction==75){tank->direction=77;}
				else if(tank->direction==77){tank->direction=75;}
				stright[tank->type-21]--; 
			}else if(tankcheck(tank->x,tank->y,tank->direction)&&stright[tank->type-21]!=0){//如果前方无障碍并且要继续直行时 
				switch(tank->direction){
					case 72: tank->y--;break;//上移一格 
					case 80: tank->y++;break;//下移一格 
					case 75: tank->x--;break;//左移一格 
					case 77: tank->x++;break;//右移一格 
				}
				stright[tank->type-21]--;
			}
			tank->move=5;//停止移动 
		}else{tank->move--;}
	}
	if(stright[tank->type-21]==0){stright[tank->type-21]=4;}//重置直行次数 
}
bool tankcheck(int x,int y,int direction)//检查坦克转向方向上有无障碍物,TRUE为无障碍，FALSE为有障碍 
{
	switch(direction){
		case 72: if(map[y-2][x]==0&&map[y-2][x-1]==0&&map[y-2][x+1]==0){return 1;}else{return 0;} break;//检查上方三格 
		case 80: if(map[y+2][x]==0&&map[y+2][x-1]==0&&map[y+2][x+1]==0){return 1;}else{return 0;} break;//检查下方三格 
		case 75: if(map[y][x-2]==0&&map[y-1][x-2]==0&&map[y+1][x-2]==0){return 1;}else{return 0;} break;//检查左方三格 
		case 77: if(map[y][x+2]==0&&map[y-1][x+2]==0&&map[y+1][x+2]==0){return 1;}else{return 0;} break;//检查右方三格 
	}
}
void buildbullet(struct Tank *tank)//创建子弹 U72,D80,L75,R77
{
	if(tank->direction==72){bullet[bullet_num].x=tank->x,bullet[bullet_num].y=tank->y-2,bullet[bullet_num].direction=72;}
	else if(tank->direction==80){bullet[bullet_num].x=tank->x,bullet[bullet_num].y=tank->y+2,bullet[bullet_num].direction=80;}
	else if(tank->direction==75){bullet[bullet_num].x=tank->x-2,bullet[bullet_num].y=tank->y,bullet[bullet_num].direction=75;}
	else if(tank->direction==77){bullet[bullet_num].x=tank->x+2,bullet[bullet_num].y=tank->y,bullet[bullet_num].direction=77;}
	bullet[bullet_num].exit=1,bullet[bullet_num].isnew=1;//设置子弹存在状态和初始状态
	if(tank->player){ bullet[bullet_num].player=1;}else if(!tank->player){ bullet[bullet_num].player=0;}//记录子弹由哪一方发射 
	if(map[bullet[bullet_num].y][bullet[bullet_num].x]!=0){bullethit(&bullet[bullet_num]);}//子弹初始位置有障碍物时立刻处理碰撞 
	if(bullet[bullet_num].exit){ printbullet(bullet[bullet_num].x,bullet[bullet_num].y);} //子弹存在时才打印子弹 
	bullet_num++;  if(bullet_num==20){bullet_num=0;}//子弹编号到20时，重新计数 
}
void buildAIbullet(struct Tank *tank)//创建AI子弹 
{
	int high,low,right,left,i;
	if(tank->CD==12){//AI开火CD比玩家长 
		if(rand()%21==0){//考虑正常化情况，每次CD够时都会有十分之一的 
			buildbullet(&*tank);
			tank->CD=0;
		}
	}else{tank->CD++;} 
	if(tank->CD>=11){//AI强化,强化有优先级 
		if(tank->y>=44){//AI坦克在地图下五格时,避免AI直接朝基地射击 
			if(tank->direction==75){//若AI坦克朝左 
				buildbullet(&*tank);
				tank->CD=0;
			}
			else if(tank->direction==77){//若AI坦克朝右 
				buildbullet(&*tank);
				tank->CD=0;
			}
		}else if(tank->x==mytank.x||tank->x==mytank.x-1||tank->x==mytank.x+1){//如果AI坦克和玩家在同一纵列 
			if(tank->direction==72&&tank->y>mytank.y||tank->direction==80&&tank->y<mytank.y){//如果AI坦克朝上并且玩家在其上方或如果AI坦克朝下并且玩家在其下方 
				if(tank->y>mytank.y){ high=mytank.y; low=tank->y;}else{ low=mytank.y; high=tank->y;}//在地图高处的坦克坐标赋为视觉上的high 
				for(i=high;i<=low-2;i++){ if(map[i][tank->x]==6){break;}}//中间有障碍时 
				if(i=low-2){//可发射时 
					buildbullet(&*tank);
					tank->CD=0;}
			} 
		}else if(tank->y==mytank.y||tank->y==mytank.y-1||tank->x==mytank.y+1){//如果AI坦克和玩家在同一横排 
			if(tank->direction==75&&tank->x>mytank.x||tank->direction==77&&tank->x<mytank.x){//如果AI坦克朝左并且玩家在其右方或如果AI坦克朝右并且玩家在其左方 
				if(tank->x<mytank.x){ right=mytank.y; left=tank->y;}else{ left=mytank.y; right=tank->y;}//在地图左边的坦克坐标赋为视觉上的left 
				for(i=left;i<=right-2;i++){ if(map[tank->y][i]==6){break;}}//中间有障碍时 
				if(i=right-2){//可发射时 
					buildbullet(&*tank);
					tank->CD=0;}
			} 
		}
	}
}
void bulletfly(struct Bullet bullet[])//子弹运动函数
{	
	int i;
	for(i=0;i<20;i++){
		if(bullet[i].exit){//如果子弹存在 
			if(!bullet[i].isnew){//如果子弹不是初建立 
				clearbullet(bullet[i].x,bullet[i].y);
				if(bullet[i].direction==72){(bullet[i].y)--;}
				else if(bullet[i].direction==80){(bullet[i].y)++;}
				else if(bullet[i].direction==75){(bullet[i].x)--;}
				else if(bullet[i].direction==77){(bullet[i].x)++;}
				if(map[bullet[i].y][bullet[i].x]!=0){ bullethit(&bullet[i]);} else{printbullet(bullet[i].x,bullet[i].y);}//如果子弹有碰撞，则进行碰撞处理 
			}else if(bullet[i].isnew){bullet[i].isnew=0;} //如果子弹是初建立则改变次状态 
			bullet_bullet(bullet);//子弹间碰撞处理 
		}
	}
}
void bullethit(struct Bullet *bullet)//子弹打击函数 
{
	int x=bullet->x,y=bullet->y;
	bullet->exit=0;  
	if(map[y][x]!=6&&map[y][x]!=5){//子弹打到可破坏方块时 
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
	}else if(map[y][x]==6){ bullet->exit=0;//碰到边框或不可摧毁障碍时子弹立刻消失 
	}else if(map[y][x]==5){//无论谁的子弹打到基地，游戏结束
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|8);//打到基地时，显示基地被摧毁 
		gotoxy(42,45); printf("---");
		gotoxy(42,46); printf("\\*/");
		gotoxy(42,47); printf("nnn");color(7);
		gameover();}
	if(!bullet->player&&x>=mytank.x-1&&x<=mytank.x+1&&y>=mytank.y-1&&y<=mytank.y+1){//如果敌方子弹打中玩家 
		clearbullet(x,y); bullet->exit=0;//清除子弹 
	}
	
}
 void bullethit_tank(struct Bullet *bullet)//子弹打击坦克 
{
	int i,x=bullet->x,y=bullet->y;
	if(!bullet->player&&x>=mytank.x-1&&x<=mytank.x+1&&y>=mytank.y-1&&y<=mytank.y+1&&bullet->exit){//如果敌方子弹打中玩家 
		bullet->exit=0; clearbullet(x,y);//清除子弹 
		cleartank(mytank.x,mytank.y); mytank.x=37,mytank.y=46;//清除我方坦克并初始化玩家坦克位置 
		mytank.heart--; /*玩家坦克生命减1*/ score--; /*死亡则得分减1*/
	}
	for(i=0;i<4;i++){
		if(bullet->player&&AItank[i].alive&&x>=AItank[i].x-1&&x<=AItank[i].x+1&&y>=AItank[i].y-1&&y<=AItank[i].y+1&&bullet->exit){//如果玩家打中地方坦克1 
			bullet->exit=0; clearbullet(x,y);//清除子弹 
			cleartank(AItank[i].x,AItank[i].y); AItank[i].alive=0;AItank[i].isrebirth=1; AItank[i].x=88,AItank[i].y=48;//清除AI坦克
			AItank[i].heart--; score++;//死亡则得分加1 
		}
	}
	gotoxy(96,6); printf("    "); color(11); gotoxy(96,6); printf("%d",score); color(7);//打印新的得分 
	gotoxy(108,8);	color(2); printf("%d",mytank.heart); color(7);//打印新的玩家生命 
	gotoxy(115,10); printf("  "); color(4); gotoxy(115,10); printf("%d",AItank[0].heart+AItank[1].heart+AItank[2].heart+AItank[3].heart); color(7);//打印新的地方剩余生命 
}
void printbullet(int x,int y)//子弹打印函数 
{
	gotoxy(x,y); color(8); printf("o"); color(7);
}
void clearbullet(int x,int y)//子弹清除函数
{
	gotoxy(x,y); printf(" ");
}
void bullet_bullet(struct Bullet bullet[])//子弹间碰撞处理函数 
{
	int m,n;
	for(m=0;m<20;m++){
		if(bullet[m].exit){
			for(n=m+1;n<20;n++){
				if(bullet[n].exit&&m!=n&&bullet[m].x==bullet[n].x&&bullet[m].y==bullet[n].y){//子弹碰撞时,敌对两方子弹才会一起消失 
					if(bullet[m].player!=bullet[n].player){
						bullet[m].exit=0; bullet[n].exit=0;
						clearbullet(bullet[m].x,bullet[m].y); clearbullet(bullet[n].x,bullet[n].y);
					}
				}
			}
		}
	}
}
void printhome()//打印基地
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|8);
	gotoxy(42,45); printf(" |*");
	gotoxy(42,46); printf("\\U/");
	gotoxy(42,47); printf("nHn");color(7);
}
void printmap(int num)//打印地图 
{
	int i,j;
	switch(num){
		case 0:
			for(i=1;i<48;i++){ gotoxy(1,i); for(j=1;j<86;j++){
				if(map[i][j]==1){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8|15|32|64); square(2);}
				else if(map[i][j]==0||map[i][j]==5){color(15); printf(" ");} 
				else if(map[i][j]==6){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|128|32); square(0);}
				else if(map[i][j]==3){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14|32|16); square(8);}
				else if(map[i][j]==2){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8|14|128|16); square(9);}}}color(7);/*重置背景色 */break;
		case 1:
			for(i=1;i<48;i++){ gotoxy(1,i); for(j=1;j<86;j++){
				if(map[i][j]==0||map[i][j]==5){color(15); printf(" ");} 
				else if(map[i][j]==6){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14|64|32); square(8);}
				else if(map[i][j]==3){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14|32|16); square(8);}}}color(7);/*重置背景色 */break;
		case 2:
			for(i=1;i<48;i++){ gotoxy(1,i); for(j=1;j<86;j++){
				if(map[i][j]==0||map[i][j]==5){color(15); printf(" ");} 
				else if(map[i][j]==2){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|64|32|16); square(9);}
				else if(map[i][j]==1){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),128|64); square(3);}
				else if(map[i][j]==3){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6|16|32); square(4);}
				else if(map[i][j]==4){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8|64|32); square(7);}}}color(7);/*重置背景色 */break;
	}
}
void maplibrary(int num_map)//地图库 
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
void square(int style,int color,int back)//地形砖块
{
	int zfx=254,round=2,diamond=29,dbl=126,zsjx=30,xin=3;
	switch(style)
	{
		case 0: printf("%c",zfx); break;//正方形砖，不可摧毁
		case 1:	printf("*"); break;//星砖 
		case 2: printf("+"); break;//十字砖 	
		case 3: printf("-"); break;//横线砖 
		case 4:	printf("="); break; //双横线砖 
		case 5:	printf("%c",round); break;//圆形砖 
		case 6:	printf("%c",dbl); break;//~砖 
		case 7: printf("%c",zsjx); break;//正三角形砖 
		case 8: printf("%c",xin); break;//心砖 
		case 9: printf("x"); break;//x砖
	}
}
void creatfile()//创建文件并打开读取人数即信息 
{
	FILE *p1,*p2;
	int i;
	if((p2=fopen("Num of rank.txt","r"))==NULL){//初始没有文件则要创建 
		p2=fopen("Num of rank.txt","w");
		fputc('0',p2);
	}else{//读取信息，先读人数，下一个文件读取要用到 
		fscanf(p2,"%d",&num_rank);
	} fclose(p2);
	if((p1=fopen("Rank List.txt","r"))==NULL){//初始没有文件则要创建 
		p1=fopen("Rank List.txt","w");
	}else{//读取历史排行榜的信息 
		if(num_rank!=0&&num_rank<10){
			for(i=0;i<num_rank;i++){fscanf(p1,"%s %d",rank[i].name,&rank[i].score);}
		}else if(num_rank!=0&&num_rank>=10){
			for(i=0;i<10;i++){fscanf(p1,"%s %d",rank[i].name,&rank[i].score);}
		}
	}fclose(p1);

}
void sort()//冒泡排序结构体数组 
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
