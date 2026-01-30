/************************** 头  文  件 **************************/
#include <stdio.h>			// 标准输入输出函数库
#include <stdbool.h>		// 定义bool变量类型
#include <time.h>			// 用于获得随机数
#include <windows.h>		// 控制dos界面
#include <stdlib.h>			// 即standard library标志库头文件，里面定义了一些宏和通用工具函数
#include <conio.h>			// 接收键盘输入输出

/************************** 宏  定  义 **************************/
#define U 1
#define D 2
#define L 3
#define R 4       // 蛇的状态，U：上 ；D：下；L:左 R：右

/************************** 定  义  全  局  变  量 **************************/
typedef struct Snake		 			// 蛇身的一个节点
{
    int x;						// 节点的x坐标
    int y;						// 节点的y坐标
    struct Snake *next;			// 蛇身的下一节点
} snake;
int score=0, add=10;			// 总得分与每次吃食物得分
int HighScore = 0;				// 最高分
int status, sleeptime=200;		// 蛇前进状态，每次运行的时间间隔
snake *head, *food;				// 蛇头指针，食物指针
snake *q;						// 遍历蛇的时候用到的指针
int endgamestatus=0;			// 游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。
HANDLE hOut;					// 控制台句柄

/************************** 函  数  声  明 **************************/
void gotoxy(int x,int y); 	 	// 设置光标位置
int  color(int c);          	// 更改文字颜色
void PrintSnake();         		// 字符画---蛇
void WelcomeToGame();     		// 开始界面
void CreateMap();         		// 绘制地图
void ScoreAndTips();			// 游戏界面右侧的得分和小提示
void InitSnake();          		// 初始化蛇身，画蛇身
void CreateFood();				// 创建随机出现的食物
bool BiteSelf();            	// 判断是否咬到了自己
void CantCrossWall();       	// 设置蛇撞墙的情况
void SpeedUp();					// 加速
void SpeedDown();				// 减速
void SnakeMove(); 				// 控制蛇前进方向
void KeyboardControl();			// 控制键盘按键
void LostDraw();				// 游戏结束界面
void EndGame(); 				// 游戏结束
void Choose(); 					// 游戏失败之后的选择
void File_out();				// 在文件中读取最高分
void File_in();            		// 储存最高分进文件
void GamePlay();				// 开始游戏
void Explation();				// 游戏说明
void Close();					// 退出游戏



/************************** 主  函  数 ***************************/

void main(int argc, char* argv[])
{
	while (1)
	{
		system("mode con cols=100 lines=30");    	// 设置控制台的宽高
		PrintSnake();								// 绘制字符画--蛇
		WelcomeToGame();							// 开始界面
		EndGame();									// 游戏结束
	}
}



/************************** 函  数  定  义 **************************/

/**
 * @brief 文字颜色函数  
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        // 更改文字颜色
	return 0;
}

/**
 * @brief 设置光标位置
 */
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

/**
 * @brief 字符画---蛇
 */
void PrintSnake()
{
	gotoxy(35,1);
	color(6);
	printf("/^\\/^\\");      	// 蛇眼睛

	gotoxy(34,2);
	printf("|__|  O|");      	// 蛇眼睛

	gotoxy(33,2);
	color(2);
	printf("_");

	gotoxy(25,3);
	color(12);
	printf("\\/");      		// 蛇信

	gotoxy(31,3);
	color(2);
	printf("/");

	gotoxy(37,3);
	color(6);
	printf(" \\_/");     		// 蛇眼睛

	gotoxy(41,3);
	color(10);
	printf(" \\");

	gotoxy(26,4);
	color(12);
	printf("\\____");   		// 舌头

	gotoxy(32,4);
	printf("_________/");

	gotoxy(31,4);
	color(2);
	printf("|");

	gotoxy(43,4);
	color(10);
	printf("\\");

	gotoxy(32,5);
	color(2);
	printf("\\_______");     	// 蛇嘴

	gotoxy(44,5);
	color(10);
	printf("\\");

	gotoxy(39,6);
	printf("|     |                  \\");  		// 下面都是画蛇身

	gotoxy(38,7);
	printf("/      /                   \\");

	gotoxy(37,8);
	printf("/      /                    \\ \\");

	gotoxy(35,9);
	printf("/      /                       \\ \\");

	gotoxy(34,10);
	printf("/     /                          \\  \\");

	gotoxy(33,11);
	printf("/     /             _----_         \\   \\");

	gotoxy(32,12);
	printf("/     /           _-~      ~-_         |  |");

	gotoxy(31,13);
	printf("(      (        _-~    _--_    ~-_     _/  |");

	gotoxy(32,14);
	printf("\\     ~-____-~    _-~    ~-_    ~-_-~    /");

	gotoxy(33,15);
	printf("~-_           _-~          ~-_       _-~");

	gotoxy(35,16);
	printf("~--______-~                ~-___-~");
}

/**
 * @brief 开始界面
 */
void WelcomeToGame()
{
	int n;
	int i,j;

	gotoxy(43,18);
	color(11);
	printf("贪 吃 蛇 大 作 战");

	color(14);          					// 黄色边框
	for (i = 20; i <= 26; i++)   			// 输出上下边框┅
	{
		for (j = 27; j <= 74; j++)   		// 输出左右边框┇
		{
			gotoxy(j, i);
			if (i == 20 || i == 26)
			{
				printf("-");
            }
			else if (j == 27 || j == 74)
            {
				printf("|");
            }
		}
	}

	gotoxy(35, 22);
	color(12);
	printf("1.开始游戏");

	gotoxy(55, 22);
	printf("2.游戏说明");

	gotoxy(35, 24);
	printf("3.退出游戏");

	gotoxy(29,27);
	color(3);
	printf("请选择[1 2 3]:[ ]\b\b");        	 // \b为退格，使得光标处于[]中间

	color(14);
    scanf("%d", &n);  	 						// 输入选项
    switch (n)									// 三个选项
    {
    	case 1:									// 开始游戏
    		GamePlay();
        	break;
    	case 2: 								// 游戏说明
			Explation();
        	break;
    	case 3: 								// 退出游戏
        	Close();							// 退出程序
        	break;
		default:			 					// 输入非1~3之间的数
			gotoxy(40,28);
			color(12);
			printf("请输入1~3之间的数!");
    }
}

/**
 * @brief 创建地图
 */
void CreateMap()
{
    int i,j;

    for(i=0;i<58;i+=2)			// 打印上下边框
    {
        gotoxy(i,0);
		color(5);				// 深紫色的边框
        printf("□");
        gotoxy(i,26);
        printf("□");
    }

    for(i=1;i<26;i++)			// 打印左右边框
    {
        gotoxy(0,i);
        printf("□");
        gotoxy(56,i);
        printf("□");
    }

	for(i = 2;i<56;i+=2)		// 打印中间网格
	{
		for(j = 1;j<26;j++)
		{
			gotoxy(i,j);
			color(3);
			printf("■\n\n");
		}
	}
}

/**
 * @brief 在文件中读取最高分
 */
void File_out()
{
	FILE *fp;

	fp = fopen("save.txt", "a+");       // 打开文件save.txt
	fscanf(fp, "%d", &HighScore);       // 把文件中的最高分读出来
	fclose(fp);                         // 关闭文件
}

/**
 * @brief 储存最高分进文件
 */
void File_in()
{
	FILE *fp;

	fp = fopen("save.txt", "w+");       // 以读写的方式建立一个名为save.txt的文件
	fprintf(fp, "%d", score);           // 把分数写进文件中
	fclose(fp);                         // 关闭文件
}

/**
 * @brief 游戏界面右侧的得分和小提示
 */
void ScoreAndTips()
{
	File_out();										// 调用File_out()，读取文件save.txt中的内容

	gotoxy(64,4);									// 确定打印输出的位置
	color(11);										// 设置颜色
	printf("☆最高记录☆：%d",HighScore);			   // 打印游戏最高分

	gotoxy(64,8);
	color(14);
	printf("得分：%d  ",score);

	gotoxy(73,11);
	color(13);
	printf("小 提 示");

	gotoxy(60,13);
	color(6);
	printf("╬ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ╬");					// 打印边框
	gotoxy(60,25);
	printf("╬ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ╬");

	gotoxy(64,14);
	color(3);
	printf("每个食物得分：%d分",add);

	gotoxy(64,16);
	printf("不能撞墙，不能咬到自己");

	gotoxy(64,18);
	printf("用↑ ↓ ← →分别控制蛇的移动");

	gotoxy(64,20);
	printf("F1 为加速，F2 为减速");

	gotoxy(64,22);
	printf("space：暂停游戏");

	gotoxy(64,24);
    printf("ESC ：退出游戏");
}

/**
 * @brief 初始化蛇身，画蛇身
 */
void InitSnake()
{
    snake *tail;
    int i;

	// 从蛇尾开始，头插法，以x,y设定开始的位置，逐步向前画蛇头
    tail = (snake*)malloc(sizeof(snake));		// 初始化蛇头（分配内存）

    tail->x = 24;         						// 蛇的初始位置（24,5）
    tail->y = 5;
    tail->next = NULL;

    for(i=1; i<=4; i++)       					// 设置蛇身，长度为5
    {
        head = (snake*)malloc(sizeof(snake)); 	// 初始化蛇头（分配内存）

        head->x = 24+2*i;         				// 设置蛇头位置
        head->y = 5;
		head->next = tail;        				// 蛇头的下一位为蛇尾

        tail = head;             	 			// 蛇头变成蛇尾，然后重复循环
    }

    while(tail!=NULL)							// 从头到尾，输出蛇身
    {
        gotoxy(tail->x, tail->y);
		color(14);
        printf("★");       					   // 输出蛇身，蛇身使用★组成
        tail = tail->next;   	 				// 蛇头输出完毕，输出蛇头的下一位，一直输出到蛇尾
    }
}

/**
 * @brief 随机出现食物
 */
void CreateFood()
{
    snake *food_1;
	bool c1=0, c2=0;

    srand((unsigned)time(NULL));        		// 初始化随机数

    food_1 = (snake*)malloc(sizeof(snake));   	// 初始化food_1（分配内存）

	do
	{
		// 食物随机出现
		food_1->x = rand()%52+2;
		food_1->y = rand()%24+1;

		/**
		 * @note 随机出现的食物需要同时满足两个条件：
		 * 		 1. 食物坐标 x 需要是偶数，使得食物能与蛇头对齐，然后食物会出现在网格线上
		 * 		 2. 蛇身与食物不能重合
		 */ 
		c1 = ((food_1->x%2)!=0);

		q = head;									// 获得蛇头指针

		// 遍历蛇身
		while(q->next != NULL)
		{
			// 判断蛇身是否与食物重合
			if(q->x==food_1->x && q->y==food_1->y)	    // 如果重合
			{
				c2 = 1;
				break;
			}

			q = q->next;
		}

		/**
		 * @note c1 和 c2 同时为0时，得到满足要求的食物随机坐标，跳出循环
		 * 		 若 c1 和 c2 中有一个为1，则不满足条件，重新生成食物随机坐标
		 */
	} while (c1||c2);

	// 绘制食物
    gotoxy(food_1->x, food_1->y);				    // 设置食物的位置
    food = food_1;
	color(12);
    printf("●");           							// 输出食物
}

/**
 * @brief 判断是否咬到了自己
 */
bool BiteSelf()
{
    snake *self;            	// 定义self为蛇身上的一个节点
    self = head->next;        	// self是蛇头之外的蛇身上的节点

    while(self!=NULL)
    {
        if(self->x==head->x && self->y==head->y)    // 如果self和蛇头上的节点重合
        {
            return 1;       	// 返回1，蛇咬到自己，游戏失败
        }
        self = self->next;		// 循环蛇身上的每一个节点
    }

    return 0;
}

/**
 * @brief 设置蛇撞墙的情况
 */
void CantCrossWall()
{
    if(head->x==0 || head->x==56 || head->y==0 || head->y==26) 	// 如果蛇头碰到了墙壁
    {
        endgamestatus=1;        	// 返回第一种情况
		EndGame();					// 游戏结束
    }
}

/**
 * @brief 加速，吃食物得分+2
 * @note 蛇吃到食物，或按F1，则调用该函数，会自动提速
 */
void SpeedUp()
{
	if(sleeptime>=50)				// 如果时间间隔大于等于50（小于50则不再提速）
	{		
		sleeptime-=10;				// 时间间隔减10
		add+=2;						// 每吃一次食物的得分加2
    }
}

/**
 * @brief 减速，吃食物得分-2
 * @note 按F2，则调用该函数，会自动减速
 */
void SpeedDown()
{
	if(sleeptime<350)				// 如果时间间隔小于350
	{
		sleeptime+=30;				// 时间间隔加上30
		add-=2;						// 每吃一次食物的得分减2
		if(add<=0)						
		{
			add=1;					// 保证最低分为1
		}
    }
}

/**
 * @brief 控制蛇的移动
 */
void SnakeMove()
{
	snake *nexthead;

    CantCrossWall();

    nexthead = (snake*)malloc(sizeof(snake)); 		// 为下一步开辟空间

    if(status==U)									// 向上前进时
    {
        nexthead->x = head->x;        				// x坐标不变，y坐标-1
        nexthead->y = head->y-1;
        nexthead->next = head;

        head = nexthead;

        q = head;                 					// 指针q指向蛇头
        // 如果下一个有食物 下一个位置的坐标和食物的坐标相同
        if(nexthead->x==food->x && nexthead->y==food->y)
        {
            while(q!=NULL)
            {
                gotoxy(q->x, q->y);
				color(14);
                printf("★");       				   // 原来食物的位置，从●换成★
                q = q->next;          				// 指针q指向的蛇身的下一位也执行循环里的操作
            }
			
            score+=add;        						// 吃了一个食物，在总分上加上食物的分
			SpeedUp();
            CreateFood();           				// 创建食物
        }
        else										// 如果没遇到食物
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");           			   // 蛇正常往前走，输出当前位置的蛇身
                q = q->next;              			// 继续输出整个蛇身
            }

            // 经过上面的循环，q 指向移动后的蛇尾；蛇尾的下一位（q->next）指向移动前的蛇尾
            gotoxy(q->next->x, q->next->y);
			color(3);
            printf("■");
            free(q->next);      					// 进行输出■之后，释放移动前的蛇尾（q->next->next）
            q->next = NULL;       					// 指针下一位指向空
        }
    }

    else if(status==D)								// 向下前进时
    {
        nexthead->x = head->x;        				// x坐标不动，y坐标+1
        nexthead->y = head->y+1;
        nexthead->next = head;

        head = nexthead;

        q = head;
        if(nexthead->x==food->x && nexthead->y==food->y)  // 有食物
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;
            }

            score+=add;
			SpeedUp();
            CreateFood();
        }
        else                               // 没有食物
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q = q->next;
            }

            gotoxy(q->next->x,q->next->y);	// 蛇走过的路线变回棋盘原有的图案
			color(3);		
            printf("■");
            free(q->next);					// 释放指针
            q->next = NULL;
        }
    }

    else if(status==L)								// 向左前进时
    {
        nexthead->x = head->x-2;        		// x坐标向左移动-2，y坐标不动
        nexthead->y = head->y;
        nexthead->next = head;

        head = nexthead;

        q = head;
        if(nexthead->x==food->x && nexthead->y==food->y)	// 有食物
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;
            }

            score+=add;
			SpeedUp();
            CreateFood();
        }
        else                                			// 没有食物
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q = q->next;
            }

            gotoxy(q->next->x,q->next->y);
			color(3);
            printf("■");
            free(q->next);
            q->next = NULL;
        }
    }

    else if(status==R)								// 向右前进时
    {
        nexthead->x = head->x+2;        					// x坐标向右移动+2，y坐标不动
        nexthead->y = head->y;
        nexthead->next = head;

        head = nexthead;

        q = head;
        if(nexthead->x==food->x && nexthead->y==food->y)	// 有食物
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;
            }

            score+=add;
			SpeedUp();
            CreateFood();
        }
        else                                         	// 没有食物
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q = q->next;
            }

            gotoxy(q->next->x,q->next->y);
			color(3);
            printf("■");
            free(q->next);
            q->next = NULL;
        }
    }

    if(BiteSelf())       							// 判断是否会咬到自己
    {
        endgamestatus = 2;
		EndGame();									// 游戏结束
    }
}

/**
 * @brief 控制键盘按键
 */
void KeyboardControl()
{
	status = R;       						// 初始蛇向右移动

    while(1)
    {
		ScoreAndTips();						// 游戏界面右侧的得分和小提示

        // GetAsyncKeyState()函数用来判断函数调用时指定虚拟键的状态

		// 如果蛇不是向下前进的时候，按上键，执行向上前进操作
        if(GetAsyncKeyState(VK_UP) && status!=D)            	
        {
            status=U;
        }
        // 如果蛇不是向上前进的时候，按下键，执行向下前进操作
        else if(GetAsyncKeyState(VK_DOWN) && status!=U)     	
        {
            status=D;
        }
        // 如果蛇不是向右前进的时候，按左键，执行向左前进
        else if(GetAsyncKeyState(VK_LEFT) && status!=R)      	
        {
            status=L;
        }
        // 如果蛇不是向左前进的时候，按右键，执行向右前进
        else if(GetAsyncKeyState(VK_RIGHT) && status!=L)     	
        {
            status=R;
        }
		// 按空格键暂停，执行Sleep()函数暂停进程
        else if(GetAsyncKeyState(VK_SPACE))
        {
            while(1)
			{
                // Sleep()函数，头文件#include <unistd.h>，令进程暂停，直到达到里面设定的参数的时间。
				Sleep(300);
				if(GetAsyncKeyState(VK_SPACE))   // 按空格键取消暂停
				{
					break;
				}

			}
        }
		// 按esc键，直接跳转到结束界面
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus = 3;
            break;
        }
		// 按F1键，加速
        else if(GetAsyncKeyState(VK_F1))
        {
            SpeedUp();							// 调用加速函数
        }
		// 按F2键，减速
        else if(GetAsyncKeyState(VK_F2))
        {
            SpeedDown();						// 调用减速函数
        }

		SnakeMove();

        Sleep(sleeptime);
    }
}

/**
 * @brief 失败界面
 */
void LostDraw()
{
	int i;

	system("cls");

	gotoxy(45,2);
	color(6);
	printf("\\\\\\|///");			// 小人的头发
	gotoxy(43,3);
	printf("\\\\");

	gotoxy(47,3);
	color(15);
	printf(".-.-");					// 眉毛

	gotoxy(54,3);
	color(6);
	printf("//");

	gotoxy(44,4);
	color(14);
	printf("(");					// 左耳

	gotoxy(47,4);
	color(15);
	printf(".@.@");					// 眼睛

	gotoxy(54,4);
	color(14);
	printf(")");					// 右耳

	gotoxy(17,5);
	color(11);
	printf("+------------------------");		//上边框

	gotoxy(35,5);
	color(14);
	printf("oOOo");					// 左手

	gotoxy(39,5);
	color(11);
	printf("----------");			// 上边框

	gotoxy(48,5);
	color(14);
	printf("(_)");					// 嘴

	gotoxy(51,5);
	color(11);
	printf("----------");			// 上边框

	gotoxy(61,5);
	color(14);
	printf("oOOo");					// 右手

	gotoxy(65,5);
	color(11);
	printf("-----------------+");	// 上边框
	
	for(i=6; i<=19; i++)        	// 竖边框
	{
		gotoxy(17,i);
		printf("|");
		gotoxy(82,i);
		printf("|");
	}

	gotoxy(17,20);
	printf("+---------------------------------");		// 下边框
 	gotoxy(52,20);
	color(14);
	printf("☆☆☆〃");

	gotoxy(60,20);
	color(11);
	printf("----------------------+");					// 下边框
}

/**
 * @brief 结束游戏
 */
void EndGame()
{
    system("cls");

    if(endgamestatus==1)			// 如果蛇撞到了墙
    {
        
		LostDraw();
		gotoxy(35,9);
    	color(12);
		printf("对不起，您撞到墙了。游戏结束！");
    }
    else if(endgamestatus==2)		// 如果蛇咬到了自己
    {
        
        LostDraw();
        gotoxy(35,9);
    	color(12);
        printf("对不起，您咬到自己了。游戏结束！");
    }
    else if(endgamestatus==3)		// 如果按了Esc键退出
    {
		LostDraw();
		gotoxy(40,9);
    	color(12);
        printf("您已经结束了游戏。");
    }

    gotoxy(43,12);
    color(13);
    printf("您的得分是 %d",score);

	if(score >= HighScore)			// 如果分数高于最高分
	{
		color(10);
		gotoxy(33,16);
		printf("创纪录啦！最高分被你刷新啦，真棒！！！");
		File_in();             		// 把最高分写进文件
	}
	else							// 如果分数低于最高分
	{
		color(10);
		gotoxy(33,16);
		printf("继续努力吧~ 你离最高分还差：%d",HighScore-score);
	}

	Choose();						// 边框下面的分支选项
}

/**
 * @brief 边框下面的分支选项
 */
void Choose()
{
	int n;

	gotoxy(25,23);
	color(12);
	printf("我要重新玩一局-------1");

	gotoxy(52,23);
	printf("不玩了，退出吧-------2");

	gotoxy(46,25);
	color(11);
	printf("选择：");

	scanf("%d", &n);
    switch (n)
    {
		case 1:
			system("cls");          // 清屏
			score = 0;             	// 分数归零
			sleeptime = 200;		// 设定初始速度
			add = 10;				// 使add设定为初值，吃一个食物得分10，然后累加
			PrintSnake();           // 返回欢迎界面
			WelcomeToGame();
			break;
		case 2:
			exit(0);                // 退出游戏
			break;
		default:					// 输入1或2以外的数字
			gotoxy(35,27);
			color(12);
			printf("※※您的输入有误，请重新输入※※");
			system("pause > nul");	// 按任意键
			EndGame();
			Choose();				// 边框下面的分支选项
			break;
	}
}

/**
 * @brief 开始游戏
 */
void GamePlay()
{
	system("cls");						// 清屏
	File_out();							// 在文件中读取最高分
	CreateMap();						// 创建地图
	InitSnake();						// 初始化蛇身
	CreateFood();						// 创建随机出现的食物
	KeyboardControl();					// 控制键盘按键
}

/*
* @brief 游戏说明
*/
void Explation()
{
	int i, j;

    system("cls");

    gotoxy(44,3);
	color(13);
    printf("游戏说明");

    color(2);
    for (j = 6; j <= 22; j++)   			//输出上下边框 ===
	{
		for (i = 20; i <= 75; i++)  	//输出左右边框 ||
		{
			gotoxy(i, j);
			if (j == 6 || j == 22) printf("=");
			else if (i == 20 || i == 75) printf("||");
		}
	}

    gotoxy(30,8);
	color(3);
    printf("tip1: 不能穿墙，不能咬到自己");
    
    gotoxy(30,11);
	color(10);
    printf("tip2: 用↑.↓.←.→分别控制蛇的移动");
    
    gotoxy(30,14);
	color(14);
    printf("tip3: F1 为加速，F2 为减速");
    
    gotoxy(30,17);
	color(11);
    printf("tip4: 按空格键暂停游戏，再按空格键继续");
    
    gotoxy(30,20);
	color(4);
    printf("tip5: ESC ：退出游戏");

	gotoxy(30,25);
	color(8);
    printf("在当前界面，按除 ESC 以外的任意键返回主界面，按 ESC 退出游戏");

	if(getch() == 27)		// 按 ESC 键退出游戏
	{
		Close();
	}
	else					// 否则清屏并重新进入主循环中的 WelcomeToGame() 函数
	{
		system("cls");		// 清屏
	}
}

/**
 * @brief 退出游戏
 */
void Close()
{
	exit(0);
}