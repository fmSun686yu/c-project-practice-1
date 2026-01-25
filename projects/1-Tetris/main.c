/**
 * @file main.c
 * 
 * @details 本文件用于实现俄罗斯方块游戏
 * 
 * @version 1.0.0
 * @author ForeverMySunyu
 * @date 2026.1.17 - 2026.1.25
 */

/* ============================== 头文件 ============================== */
#include <stdbool.h>		// 定义变量类型 bool 的头文件
#include <stdio.h>        	// 标准输入输出库函数（printf、scanf）
#include <windows.h>      	// 控制 DOS 界面（获取控制台上坐标位置、设置字体颜色）
#include <conio.h>        	// 接收键盘输入输出（kbhit()、getch()）
#include <time.h>         	// 用于获得随机数

/* ============================== 宏定义 ============================== */
#define FrameX 13           // 游戏窗口左上角的 X 轴坐标为 13
#define FrameY 3            // 游戏窗口左上角的 Y 轴坐标为 3
#define Frame_height 36     // 游戏窗口的高度为 36
#define Frame_width 22      // 游戏窗口的宽度为 22
#define NumberOfEachLine (Frame_width-2)		// 每行具有的最多方格数（满行时的方格数）

/* ============================== 定义全局变量 ============================== */
int i, j;
int Temp, Temp1;      // Temp, Temp1 用于记住和转换方块变量的值
int a[80][80]={0};    // 标记游戏屏幕的图案：2,1,0分别表示该位置为游戏边框、方块、无图案;初始化为无图案
int b[4];       	  //标记4个"口"方块：1表示有方块，0表示无方块
struct Tetris					// 声明俄罗斯方块的结构体
{
 	int x;     					// 中心方块的x轴坐标
 	int y;     					// 中心方块的y轴坐标
 	int flag;    				// 标记方块类型的序号
 	int next;    				// 下一个俄罗斯方块类型的序号
 	int speed;    				// 俄罗斯方块移动的速度
 	int number;    			    // 产生俄罗斯方块的个数
 	int score;    				// 游戏的分数
 	int level;    				// 游戏的等级
};
HANDLE hOut;					// 控制台句柄

/* ============================== 函数声明 ============================== */

int color(int c);					        // 设置文字颜色
void gotoxy(int x, int y);				    // 光标移到指定位置
void DrawGameFrame();						// 绘制游戏边框
void Flag(struct Tetris *);				    // 随机产生方块类型的序号
void MakeTetris(struct Tetris *);		    // 制作俄罗斯方块
void PrintTetris(struct Tetris *);	        // 打印俄罗斯方块
void CleanTetris(struct Tetris *);	        // 清除俄罗斯方块的痕迹
bool ifMove(struct Tetris *);				// 判断是否能移动到指定位置，返回值为1，能移动，否则，不能移动
void Del_Fullline(struct Tetris *);	        // 判断是否满行，并删除满行的俄罗斯方块
void GamePlay();							// 开始游戏
void regulation();                  	    // 游戏规则
void explation();                   	    // 按键说明
void welcom();                    			// 欢迎界面
void Replay(struct Tetris * tetris);  	    // 重新开始游戏
void title();                       		// 欢迎界面上方的标题
void flower();                     		    // 欢迎界面上的字符装饰花
void close();                      		    // 关闭游戏



/* ============================== 主函数 ============================== */

void main(int argc, char* argv[])
{
	while(1)
	{
		welcom();   // 欢迎界面
	}
}



/* ============================== 函数定义 ============================== */

/**
 * @brief 文字颜色函数
 * @attention 此函数的局限性：1、只能Windows系统下使用   2、不能改变背景颜色
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        // 更改文字颜色
	return 0;
}

/**
 * @brief 获取屏幕光标位置
 */
void gotoxy(int x, int y)
{
 	COORD pos;
 	pos.X = x;  	// 横坐标
 	pos.Y = y;  	// 纵坐标
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/**
 * @brief 欢迎界面上方的标题
 */
void title()
{
	color(15);						// 亮白色
	gotoxy(24,3);
    printf("趣  味  俄  罗  斯  方  块\n"); // 输出标题
	color(11); 						// 亮蓝色
	gotoxy(18,5);
    printf("■");					// ■
    gotoxy(18,6); 					// ■■
    printf("■■");					// ■
    gotoxy(18,7);
    printf("■");

    color(14); 						// 黄色
	gotoxy(26,6);
    printf("■■");					// ■■
    gotoxy(27,7);					//  ■■
    printf("■■");

    color(10); 						// 绿色
	gotoxy(36,6);					// ■■
    printf("■■");				    // ■■
    gotoxy(36,7);
    printf("■■");

    color(13); 						// 粉色
	gotoxy(45,5);
    printf("■");					// ■
    gotoxy(45,6);					// ■
	printf("■");					// ■
	gotoxy(45,7);					// ■
	printf("■");
	gotoxy(45,8);
	printf("■");

	color(12); 						// 亮红色
	gotoxy(54,6);
    printf("■");					//   ■
    gotoxy(52,7); 					// ■■■
	printf("■■■");
}

/**
 * @brief 绘制字符花
 */
void flower()
{
	gotoxy(66,11);   	// 确定屏幕上要输出的位置
	color(12);			// 设置颜色
	printf("(_)");  	// 红花上边花瓣

	gotoxy(64,12);
	printf("(_)");      // 红花左边花瓣

	gotoxy(68,12);
	printf("(_)");      // 红花右边花瓣

	gotoxy(66,13);
	printf("(_)");      // 红花下边花瓣

	gotoxy(67,12);      // 红花花蕊
	color(6);
	printf("@");
	
	gotoxy(72,10);
	color(13);
	printf("(_)");      // 粉花左边花瓣

	gotoxy(76,10);
	printf("(_)");      // 粉花右边花瓣

	gotoxy(74,9);
	printf("(_)");      // 粉花上边花瓣
	
	gotoxy(74,11);
	printf("(_)");      // 粉花下边花瓣
	
	gotoxy(75,10);
	color(6);
	printf("@");        // 粉花花蕊
	
	gotoxy(71,12);
	printf("|");      	// 两朵花之间的连接

	gotoxy(72,11);
	printf("/");      	// 两朵花之间的连接

	gotoxy(70,13);
	printf("\\|");      // 注意：\为转义字符。想要输入\，必须在前面需要转义

	gotoxy(70,14);
	printf("`|/");

	gotoxy(70,15);
	printf("\\|");

	gotoxy(71,16);
	printf("| /");

	gotoxy(71,17);
	printf("|");
	
	gotoxy(67,17);
	color(10);
	printf("\\\\\\\\");      // 草地
	gotoxy(73,17);
	printf("//");

	gotoxy(67,18);
	color(2);
	printf("^^^^^^^^");
	
	gotoxy(66,19);			
	color(5);
	printf("大连理工大学");      // 公司名称
	
	gotoxy(65,20);
	printf("ForeverMySunyu");   // 开发者的名字，读者练习时，可以换成自己的名字
}

/**
 * @brief 欢迎界面的菜单选项边框和文字
 * @details 包括：
 * - 欢迎界面上方的标题
 * - 欢迎界面右方的字符花和公司、作者信息
 * - 欢迎界面的菜单选项边框和文字
 */
void welcom()
{
	int n;
	int i,j = 1;

	system("cls");			// 清屏

    title();    // 欢迎界面上方的标题
    flower();   // 欢迎界面右方的字符装饰花和公司、作者信息

	color(14);          								    // 黄色边框
	for (i = 9; i <= 20; i++)   							// 循环y轴坐标，打印输出上下边框 ===
	{
		for (j = 15; j <= 60; j++)  					    // 循环x轴坐标，打印输出左右边框 ║
		{
			gotoxy(j, i);
			if (i == 9 || i == 20) printf("=");			    // 输出上下边框 ===
			else if (j == 15 || j == 60) printf("║");	    // 输出左右边框 ║
		}
	}

    color(12);				        // 设置字体颜色为红色
	gotoxy(25, 12);				    // 设置显示位置
	printf("1.开始游戏");			 // 输出文字“1.开始游戏”
	gotoxy(40, 12);
	printf("2.按键说明");
	gotoxy(25, 17);
	printf("3.游戏规则");
	gotoxy(40, 17);
	printf("4.退出");
	gotoxy(21,22);
	color(3);
	printf("请选择[1 2 3 4]:[ ]\b\b");

	color(14);
    scanf("%d", &n);    			// 输入选项
    switch (n)
    {
    	case 1: 					// 输入1
    		system("cls");			// 清屏
			DrawGameFrame();		// 制作游戏窗口
			GamePlay();				// 开始游戏
        	break;
    	case 2: 					// 输入2
			explation();			// 显示按键说明
        	break;
    	case 3: 					// 输入3
			regulation();			// 显示游戏规则
        	break;
    	case 4: 					// 输入4
			close();				// 关闭游戏
        	break;
    }
}

/**
 * @brief 制作游戏窗口
 */
void DrawGameFrame()
{
 	gotoxy(FrameX+Frame_width-7,FrameY-2);			//设置游戏名称的显示位置
	color(11);										//将字体颜色设置为亮蓝色
	printf("趣味俄罗斯方块");						 //打印游戏名称

	gotoxy(FrameX,FrameY);
	color(12);
	printf("╔");									//打印框角
 	gotoxy(FrameX+2*Frame_width-2,FrameY);
 	printf("╗");
 	gotoxy(FrameX,FrameY+Frame_height);
 	printf("╚");
 	gotoxy(FrameX+2*Frame_width-2,FrameY+Frame_height);
 	printf("╝");
	a[FrameX][FrameY+Frame_height]=2;       		//记住该处（左下角和右下角）已有图案
 	a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;

	for(i=1;i<2*Frame_width-2;i++)
 	{
  		gotoxy(FrameX+i,FrameY);
  		printf("═");         						//打印上横框
 	}

 	for(i=1;i<2*Frame_width-2;i++)
 	{
  		gotoxy(FrameX+i,FrameY+Frame_height);
  		printf("═");         						//打印下横框
  		a[FrameX+i][FrameY+Frame_height]=2;    		//标记下横框为游戏边框，防止方块出界
 	}

 	for(i=1;i<Frame_height;i++)
	{
  		gotoxy(FrameX,FrameY+i);
  		printf("║");        	 					//打印左竖框
  		a[FrameX][FrameY+i]=2;       				//标记左竖框为游戏边框，防止方块出界
 	}

 	for(i=1;i<Frame_height;i++)
 	{
  		gotoxy(FrameX+2*Frame_width-2,FrameY+i);
  		printf("║");         						//打印右竖框
  		a[FrameX+2*Frame_width-2][FrameY+i]=2;   	//标记右竖框为游戏边框，防止方块出界	
    }

 	gotoxy(FrameX+2*Frame_width+3,FrameY+16); 		//设置上边框的显示位置
 	color(2);										//将字体颜色设置为深绿色
	printf("*****************");					//打印下一个出现方块的上边框

	gotoxy(FrameX+2*Frame_width+5,FrameY+17); 
 	color(3);										//将字体颜色设置为深蓝绿色
	printf("下一出现方块：");

 	gotoxy(FrameX+2*Frame_width+3,FrameY+23);
 	color(2);
	printf("*****************");					//打印下一个出现方块的下边框

	gotoxy(FrameX+2*Frame_width+3,FrameY+25);
	color(14);										//将字体颜色设置为黄色
 	printf("Esc ：退出游戏");

	gotoxy(FrameX+2*Frame_width+3,FrameY+27);
	printf("↑键：旋转");

	gotoxy(FrameX+2*Frame_width+3,FrameY+29);
	printf("空格：暂停游戏");
}

/**
 * @brief 制作俄罗斯方块
 */
void MakeTetris(struct Tetris *tetris)
{
 	a[tetris->x][tetris->y]=b[0];    		//中心方块位置的图形状态
 	switch(tetris->flag)      				//共7大类，19种类型
 	{
		/* 田字方块 ■ ■
		  		   ■ ■ */
  		case 1:         
   		{
			color(10);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x+2][tetris->y-1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
   			break;
   		}

		/* 直线方块 ■ ■ ■ ■ */
  		case 2:
   		{
		   	color(13);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x+2][tetris->y]=b[2];
    		a[tetris->x+4][tetris->y]=b[3];
    		break;
   		}

		/* 直线方块 ■
		  		   ■
				   ■
				   ■ */
  		case 3:         
   		{
		   	color(13);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x][tetris->y+2]=b[3];
    		break;
   		}

		/* T字方块 ■ ■ ■
		            ■  */
  		case 4:         
   		{
		   	color(11);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x+2][tetris->y]=b[2];
    		a[tetris->x][tetris->y+1]=b[3];
    		break;
   		}

		/* 顺时针90°T字方块    ■
		  	                ■ ■
						      ■ */
  		case 5:         
   		{
		   	color(11);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x-2][tetris->y]=b[3];
    		break;
   		}

		/* 顺时针180°T字方块    ■
		  			         ■ ■ ■ */
  		case 6:         
   		{
		   	color(11);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x-2][tetris->y]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}

		/* 顺时针270°T字方块 ■
		  			        ■ ■
							■    */
  		case 7:
   		{
		   	color(11);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}

		/* Z字方块  ■ ■
		  			  ■ ■ */
  		case 8:
   		{
		   	color(14);
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x-2][tetris->y]=b[2];
    		a[tetris->x+2][tetris->y+1]=b[3];
    		break;
   		}

		/* 顺时针Z字方块   ■
		  			    ■ ■
						■    */
  		case 9:
   		{
		   	color(14);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x-2][tetris->y]=b[2];
    		a[tetris->x-2][tetris->y+1]=b[3];
    		break;
   		}

		/* 反转Z字方块    ■ ■
		  			   ■ ■    */
  		case 10:
   		{
		   	color(14);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x+2][tetris->y-1]=b[2];
    		a[tetris->x-2][tetris->y]=b[3];
    		break;
   		}

		/* 顺时针反转Z字方块 ■
		  			        ■ ■
						      ■  */
  		case 11:
   		{
		   	color(14);
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x-2][tetris->y]=b[2];
    		a[tetris->x-2][tetris->y-1]=b[3];
    		break;
   		}

		/* 7字方块   ■ ■
		  			  ■
				      ■ */
  		case 12:
   		{
		   	color(12);
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x][tetris->y-1]=b[2];
    		a[tetris->x-2][tetris->y-1]=b[3];
    		break;
   		}

		/* 顺时针90°7字方块      ■
		  			        ■ ■ ■  */
  		case 13:        
   		{
		   	color(12);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x+2][tetris->y]=b[2];
    		a[tetris->x+2][tetris->y-1]=b[3];
    		break;
   		}

		/* 顺时针180°7字方块   ■
		  			          ■
							  ■ ■  */
  		case 14:
   		{
		   	color(12);
    		a[tetris->x][tetris->y-1]=b[1];
   		 	a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x+2][tetris->y+1]=b[3];
    		break;
   		}

		/* 顺时针270°7字方块  ■ ■ ■
		  			         ■     */
  		case 15:
   		{
		   	color(12);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x-2][tetris->y+1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}

		/* 反转7字方块  ■ ■
		  			   ■
	 			       ■    */
  		case 16:
   		{
		   	color(12);
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x][tetris->y-1]=b[2];
    		a[tetris->x+2][tetris->y-1]=b[3];
    		break;
   		}

		/* 顺时针转90°反转7字方块  ■ ■ ■
		  			                 ■  */
  		case 17:
   		{
		   	color(12);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x+2][tetris->y]=b[2];
    		a[tetris->x+2][tetris->y+1]=b[3];
    		break;
   		}

		/* 顺时针转180°反转7字方块    ■
		  			                ■
								  ■ ■    */
  		case 18:
   		{
		   	color(12);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x-2][tetris->y+1]=b[3];
    		break;
   		}

		/* 顺时针转270°反转7字方块  ■
		  			              ■ ■ ■ */
  		case 19:
  		{
		  	color(12);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x-2][tetris->y-1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
  	 	}

		default:
			break;
 	}
}

/**
 * @brief 打印俄罗斯方块
 */
void PrintTetris(struct Tetris *tetris)
{
 	for(i=0;i<4;i++)					//数组b[4]中有4个元素，循环这4个元素，让每个元素的值都为1
 	{
  		b[i]=1;         				//数组b[4]的每个元素的值都为1
 	}

 	MakeTetris(tetris);      			//制作俄罗斯方块

 	for( i=tetris->x-2; i<=tetris->x+4; i+=2 )
 	{
  		for(j=tetris->y-1;j<=tetris->y+2;j++)		//循环方块所有可能出现的位置
  		{
   			if( a[i][j]==1 && j>FrameY ) 			//如果这个位置上有方块
   			{
    			gotoxy(i,j);
				printf("■");     					//打印边框内的方块
   			}
  		}
	}

 	//打印菜单信息
	gotoxy(FrameX+2*Frame_width+3,FrameY+9); 		//设置打印位置
	color(4);
 	printf("level : ");
 	color(12);
 	printf(" %d",tetris->level); 					//输出等级

	gotoxy(FrameX+2*Frame_width+3,FrameY+11);
	color(4);
 	printf("score : ");
 	color(12);
 	printf(" %d",tetris->score); 					//输出分数

	gotoxy(FrameX+2*Frame_width+3,FrameY+13);
	color(4);
 	printf("speed : ");
 	color(12);
	printf(" %dms",tetris->speed); 					//输出速度
}

/**
 * @brief 判断方块是否可移动到指定位置
 * @retval 0 - 不可移动
 * @retval 1 - 可移动
 */
bool ifMove(struct Tetris *tetris)
{
	/* 当中心方块位置上有图案时，返回值为0，即不可移动 */
	if(a[tetris->x][tetris->y]!=0)
 	{
  		return 0;
 	}
	/**
	 * 继续判断除中心方块以外的方块位置，
	 * 如果这些位置都没有图案，则返回1，即可移动
	 */
	else
	{
		switch (tetris->flag)
		{
			/* 田字方块 ■ ■
		  		       ■ ■ */
			case 1:
				if((a[tetris->x][tetris->y-1]==0) &&
				(a[tetris->x+2][tetris->y-1]==0) &&
				(a[tetris->x+2][tetris->y]==0))
					return 1;
				break;
			
			/* 直线方块 ■ ■ ■ ■ */
			case 2:
				if((a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x+2][tetris->y]==0) &&
    			(a[tetris->x+4][tetris->y]==0))
					return 1;
				break;

			/* 直线方块 ■
		  		   	   ■
				       ■
				       ■ */
			case 3:
				if((a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x][tetris->y+2]==0))
					return 1;
				break;

			/* T字方块 ■ ■ ■
		                 ■  */
			case 4:
				if((a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x+2][tetris->y]==0) &&
    			(a[tetris->x][tetris->y+1]==0))
					return 1;
				break;

			/* 顺时针90°T字方块    ■
		  	                    ■ ■
						          ■ */
			case 5:
				if((a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x-2][tetris->y]==0))
					return 1;
				break;

			/* 顺时针180°T字方块    ■
		  			             ■ ■ ■ */
			case 6:
				if((a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x+2][tetris->y]==0))
					return 1;
				break;

			/* 顺时针270°T字方块 ■
		  			            ■ ■
							    ■    */
			case 7:
				if((a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x+2][tetris->y]==0))
					return 1;
				break;

			/* Z字方块  ■ ■
		  			      ■ ■ */
			case 8:
				if((a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x+2][tetris->y+1]==0))
					return 1;
				break;

			/* 顺时针Z字方块   ■
		  			        ■ ■
						    ■    */
			case 9:
				if((a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x-2][tetris->y+1]==0))
					return 1;
				break;

			/* 反转Z字方块    ■ ■
		  			       ■ ■    */
			case 10:
				if((a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x+2][tetris->y-1]==0) &&
    			(a[tetris->x-2][tetris->y]==0))
					return 1;
				break;

			/* 顺时针反转Z字方块 ■
		  			            ■ ■
						          ■  */
			case 11:
				if((a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x-2][tetris->y-1]==0))
					return 1;
				break;

			/* 7字方块   ■ ■
		  			      ■
				          ■ */
			case 12:
				if((a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x-2][tetris->y-1]==0))
					return 1;
				break;

			/* 顺时针90°7字方块      ■
		  			            ■ ■ ■  */
			case 13:
				if((a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x+2][tetris->y]==0) &&
    			(a[tetris->x+2][tetris->y-1]==0))
					return 1;
				break;

			/* 顺时针180°7字方块   ■
		  			              ■
							      ■ ■  */
			case 14:
				if((a[tetris->x][tetris->y-1]==0) &&
   		 		(a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x+2][tetris->y+1]==0))
					return 1;
				break;

			/* 顺时针270°7字方块  ■ ■ ■
		  			             ■     */
			case 15:
				if((a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x-2][tetris->y+1]==0) &&
    			(a[tetris->x+2][tetris->y]==0))
					return 1;
				break;

			/* 反转7字方块  ■ ■
		  			       ■
	 			           ■    */
			case 16:
				if((a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x+2][tetris->y-1]==0))
					return 1;
				break;

			/* 顺时针转90°反转7字方块  ■ ■ ■
		  			                     ■  */
			case 17:
				if((a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x+2][tetris->y]==0) &&
    			(a[tetris->x+2][tetris->y+1]==0))
					return 1;
				break;

			/* 顺时针转180°反转7字方块    ■
		  			                    ■
								      ■ ■    */
			case 18:
				if((a[tetris->x][tetris->y-1]==0) &&
    			(a[tetris->x][tetris->y+1]==0) &&
    			(a[tetris->x-2][tetris->y+1]==0))
					return 1;
				break;

			/* 顺指针转270°反转7字方块  ■
		  			                  ■ ■ ■ */
			case 19:
				if((a[tetris->x-2][tetris->y]==0) &&
    			(a[tetris->x-2][tetris->y-1]==0) &&
    			(a[tetris->x+2][tetris->y]==0))
					return 1;
				break;

			default:
				break;
		}
	}

	/* 除中心方块以外的方块位置有图案，返回0，即不可移动 */
	return 0;
}

/**
 * @brief 清除俄罗斯方块的痕迹
 */
void CleanTetris(struct Tetris *tetris)
{
 	for(i=0; i<4; i++)			//数组b[4]中有4个元素，循环这4个元素，让每个元素的值都为0
 	{
  		b[i]=0;         		//数组b[4]的每个元素的值都为0
 	}

	MakeTetris(tetris);      	//制作俄罗斯方块

	/* 循环方块所有可能出现的位置 */
	/* ■ X ■ ■  X为中心方块 */
	for(i=tetris->x-2; i<=tetris->x+4; i+=2)
	{
		/* ■
		   X
		   ■
		   ■	
		X为中心方块*/
  		for(j=tetris->y-1; j<=tetris->y+2; j++)
  		{
   			if( a[i][j] == 0 && j > FrameY ) 	//如果这个位置上没有图案，并且处于游戏界面当中
   			{
    			gotoxy(i,j);
    			printf("  ");    					//清除方块
   			}
  		}
 	}
}

/**
 * @brief 判断是否满行并删除满行的俄罗斯方块
 * @note 当某行有Frame_width-2个方块时，则满行消除
 */
void Del_Fullline(struct Tetris *tetris)
{
 	int n;					// 用于记录某行方块的个数
	int del_rows = 0;		// 用于记录删除方块的行数的变量
	int j1;

	/**
	 * 纵坐标 y 依次**从下往上**，横坐标 x 依次**由左至右**判断是否满行
	 * i - 横坐标 x
	 * j, j1 - 纵坐标 y
	 */
 	for(j=FrameY+Frame_height-1; j>=FrameY+1; j--)
 	{
  		n=0;
  		for(i=FrameX+2; i<FrameX+2*Frame_width-2; i+=2)
  		{
   			if(a[i][j]==1)
   			{
    			n++;  				// 记录此行方块的个数
			}
		}

		if(n==NumberOfEachLine)  		// 如果满行
		{
			for(i=FrameX+2; i<FrameX+2*Frame_width-2; i+=2)		// 删除满行的方块
			{
				a[i][j]=0;
				gotoxy(n,j);
				printf("  ");
			}

			// 如果删除行以上的位置有方块，则先清除，再将方块下移一个位置
			for(j1=j-1; j1>FrameY; j1--) 
			{
				for(i=FrameX+2; i<FrameX+2*Frame_width-2; i+=2)
				{
					if(a[i][j1]==1)
					{
						a[i][j1]=0;
						gotoxy(i,j1);
						printf("  ");
						a[i][j1+1]=1;
						gotoxy(i,j1+1);
						printf("■");
					}
				}
			}
			j++;   				// 方块下移后，重新判断删除行是否满行
			del_rows++;			// 记录删除方块的行数
		}
 	}

 	tetris->score+=del_rows*NumberOfEachLine; 		// 每删除一行，得分为删除的方块个数

	// 如果累计删除10行即得 10*NumberOfEachLine 分，速度加快20ms并升一级
 	if(del_rows>0)
 	{
		if(tetris->score%(10*NumberOfEachLine)==0 || tetris->score/(10*NumberOfEachLine) > tetris->level-1)
		{
			tetris->speed-=20;
  			tetris->level++;
		}
 	}
}

/**
 * @brief 随机产生俄罗斯方块类型的序号
 */
void Flag(struct Tetris *tetris)
{
 	tetris->number++;     				// 记住产生方块的个数

	srand(time(NULL));  				// 初始化随机数

	if(tetris->number==1)
 	{
  		tetris->flag = rand()%19+1;  	// 记住第一个方块的序号
 	}
 	tetris->next = rand()%19+1;   		// 记住下一个方块的序号
}

/**
 * @brief 开始游戏
 */
void GamePlay()
{
	int n;
	struct Tetris t;
	struct Tetris *tetris = &t;			// 定义结构体的指针并指向结构体变量
	unsigned char keyboard;  			// 定义接收键盘输入的变量
	tetris->number = 0;					// 初始化俄罗斯方块数为0个
	tetris->speed = 300;				// 初始移动速度为300ms
	tetris->score = 0;					// 初始游戏的分数为0分
	tetris->level = 1;					// 初始游戏为第1关

	// 循环产生方块，直至游戏结束
	while(1)
	{
		Flag(tetris);								// 得到产生俄罗斯方块类型的序号

		Temp = tetris->flag;						// 记住当前俄罗斯方块序号

		tetris->x = FrameX+2*Frame_width+11;		// 获得下一出现方块预览界面方块的 x 坐标
  		tetris->y = FrameY+20;                      // 获得下一出现方块预览界面方块的 y 坐标
		tetris->flag = tetris->next;				// 获得下一个俄罗斯方块的序号
		PrintTetris(tetris);						// 调用打印俄罗斯方块方法，打印下一出现方块

		tetris->x = FrameX+Frame_width;  			// 获得游戏窗口中心方块 x 坐标
  		tetris->y = FrameY-1;     					// 获得游戏窗口中心方块 y 坐标
		tetris->flag = Temp;						// 重新得到当前俄罗斯方块序号

		// 控制方块方向和移动，直至方块不再下移
		while(1)
		{
			label:PrintTetris(tetris);				// 打印俄罗斯方块
			Sleep(tetris->speed);					// 延缓下落时间
			CleanTetris(tetris);					// 清除当前方块痕迹
			Temp1 = tetris->flag;					// 记住当前俄罗斯方块序号

			if(kbhit())								// 如果键盘有输入
			{
				keyboard = getch();					// 使用变量 keyboard 接收键盘输入
				if(keyboard == 224)					// 处理方向键
				{
					keyboard = getch();				// 再次使用变量 keyboard 接收键盘输入
				}

				if(keyboard == 75)					// 按 ← 键，向左动，中心横坐标减2
				{
					tetris->x-=2;

					if(ifMove(tetris))				// 如果可以移动到该位置
					{
						goto label;
					}
					else							// 否则取消移动
					{
						tetris->x+=2;
					}
				}
				else if(keyboard == 77)				// 按 → 键，向右动，中心横坐标加2
				{
					tetris->x+=2;

					if(ifMove(tetris))				// 如果可以移动到该位置
					{
						goto label;
					}
					else							// 否则取消移动
					{
						tetris->x-=2;
					}
				}
				else if(keyboard == 80)				// 按 ↓ 键，加速下落
				{
					tetris->y+=2;

					if(ifMove(tetris))				// 如果可以移动到该位置
					{
						goto label;
					}
					else							// 如果不可向下移动2格
					{
						tetris->y--;				// 尝试向下移动1格

						if(ifMove(tetris))			// 如果可以移动到该位置
						{
							goto label;
						}
						else						// 如果不可向下移动1格
						{
							tetris->y--;			// 回到原位置
						}
					}
				}
				else if(keyboard == 72)				// 按 ↑ 键则变体，即当前方块顺时针转90度
				{
					switch (tetris->flag)
					{
						/* 田字方块 ■ ■
									■ ■ */
						case 1:         
							break;

						/* 直线方块 ■ ■ ■ ■ */
						case 2:
							tetris->flag = 3;
							break;

						/* 直线方块 ■
								   ■
								   ■
								   ■ */
						case 3:         
							tetris->flag = 2;
							break;

						/* T字方块 ■ ■ ■
									■  */
						case 4:         
							tetris->flag = 5;
							break;

						/* 顺时针90°T字方块    ■
											■ ■
											  ■ */
						case 5:         
							tetris->flag = 6;
							break;

						/* 顺时针180°T字方块    ■
											 ■ ■ ■ */
						case 6:         
							tetris->flag = 7;
							break;

						/* 顺时针270°T字方块 ■
											■ ■
											■    */
						case 7:
							tetris->flag = 4;
							break;

						/* Z字方块  ■ ■
									  ■ ■ */
						case 8:
							tetris->flag = 9;
							break;

						/* 顺时针Z字方块   ■
										■ ■
										■    */
						case 9:
							tetris->flag = 8;
							break;

						/* 反转Z字方块    ■ ■
									   ■ ■    */
						case 10:
							tetris->flag = 11;
							break;

						/* 顺时针反转Z字方块 ■
											■ ■
											  ■  */
						case 11:
							tetris->flag = 10;
							break;

						/* 7字方块   ■ ■
									   ■
									   ■ */
						case 12:
							tetris->flag = 13;
							break;

						/* 顺时针90°7字方块      ■
											■ ■ ■  */
						case 13:        
							tetris->flag = 14;
							break;

						/* 顺时针180°7字方块   ■
											  ■
											  ■ ■  */
						case 14:
							tetris->flag = 15;
							break;

						/* 顺时针270°7字方块  ■ ■ ■
											 ■     */
						case 15:
							tetris->flag = 12;
							break;

						/* 反转7字方块  ■ ■
									   ■
									   ■    */
						case 16:
							tetris->flag = 17;
							break;

						/* 顺时针转90°反转7字方块  ■ ■ ■
													  ■  */
						case 17:
							tetris->flag = 18;
							break;

						/* 顺时针转180°反转7字方块    ■
													■
												  ■ ■    */
						case 18:
							tetris->flag = 19;
							break;

						/* 顺时针转270°反转7字方块  ■
												  ■ ■ ■ */
						case 19:
							tetris->flag = 16;
							break;
						
						default:
							break;
					}

					if(ifMove(tetris))				// 如果可以旋转到该位置
					{
						goto label;
					}
					else							// 否则取消旋转
					{
						tetris->flag = Temp1;
					}
				}
				else if(keyboard == 32)				// 按空格键，暂停
				{
					while(1)
					{
						if(kbhit())
						{
							keyboard = getch();

							if(keyboard == 32)					// 再按空格键，继续游戏
							{
								goto label;
							}
							else if(keyboard == 27)				// 按 Esc 键，退出游戏
							{
								system("cls");					// 清屏
								memset(a,0,6400*sizeof(int));	// 初始化数组 a
								welcom();						// 欢迎界面
							}
						}
					}
				}
				else if(keyboard == 27)				// 按 Esc 键，退出游戏
				{
					system("cls");					// 清屏
					memset(a,0,6400*sizeof(int));	// 初始化数组 a
					welcom();						// 欢迎界面
				}
			}

			// 如果没有键盘操作指令或键盘操作指令无效
			tetris->y++;							// 方块正常向下移动1格
			if(!ifMove(tetris))						// 如果不可移动
			{
				tetris->y--;
    			PrintTetris(tetris);
    			Del_Fullline(tetris);
    			break;
			}
		}

		// 游戏结束条件：方块触到框顶位置
		for (j=tetris->y-2; j<tetris->y+1; j++)		// 循环方块可能出现的位置
		{
			for (i=tetris->x-2; i<=tetris->x+4; i+=2)
			{
				if (a[i][j]==1 && j<=FrameY)		// 如果方块位置上有图案，且位置在框顶位置及以上
				{
					gotoxy(FrameX+Frame_width-6,FrameY+Frame_height/2-1); 	// 设置打印位置
					printf("=============");				 				// 打印空格
					gotoxy(FrameX+Frame_width-6,FrameY+Frame_height/2+1); 	// 设置打印位置
					printf("=============");				 				// 打印空格
					gotoxy(FrameX+Frame_width-6,FrameY+Frame_height/2); 	// 设置打印位置
					color(4);
					printf("║ 游戏结束！║");			 // 打印游戏结束信息
					Sleep(3000);						// 延时3秒

					system("cls");						// 清屏
					gotoxy(16,7);						// 设置显示位置
					color(12);							// 红色
					printf("■■■■■■    ■     ■    ■■■     ");
					gotoxy(16,8);
					printf("■         ■■    ■    ■   ■   ");
					gotoxy(16,9);
					printf("■■■■■     ■  ■  ■    ■    ■  ");
					gotoxy(16,10);
					printf("■         ■    ■■    ■   ■   ");
					gotoxy(16,11);
					printf("■■■■■■    ■     ■    ■■■     ");

					gotoxy(16,18);
					color(14);
					printf("我要重新玩一局 ------- 请按 1");

					gotoxy(16,19);
					printf("不玩了，退出吧 ------- 请按 2");

					gotoxy(16,21);
					printf("选择【1/2】：");

					color(11);
					scanf("%d", &n);					//输入1或2

					// 判断输入
					switch(n)
					{
						case 1:
							system("cls");				// 清屏
							Replay(tetris);       		//重新开始游戏
							break;
						case 2:
							exit(0);					// 退出程序
							break;
						default:
							exit(0);					// 退出程序
							break;
					}
				}
			}
		}
		
		// 清除下一个俄罗斯方块的图形(右边窗口)
		tetris->flag = tetris->next;
  		tetris->x=FrameX+2*Frame_width+11;
  		tetris->y=FrameY+20;
  		CleanTetris(tetris);
	}
}

/**
 * @brief 重新开始游戏
 */
void Replay(struct Tetris *tetris)
{
	system("cls");                  	//清屏
	memset(a,0,6400*sizeof(int)); 		//初始化a数组，否则不会正常显示方块，导致游戏直接结束
	DrawGameFrame();       				//制作游戏窗口
	GamePlay(); 						//开始游戏
}

/**
 * @brief 显示按键说明
 */
void explation()
{
    system("cls");			//清屏

	gotoxy(32,3);			//设置显示位置
    color(13);				//粉色
    printf("按键说明");

    color(2);
    for (i = 6; i <= 16; i++)   			//输出上下边框 ===
	{
		for (j = 15; j <= 60; j++)  		//输出左右边框 ║
		{
			gotoxy(j, i);
			if (i == 6 || i == 16) printf("=");
			else if (j == 15 || j == 60) printf("║");
		}
	}

	gotoxy(18,7);
    color(3);
    printf("tip1: 玩家可以通过 ← → 方向键来移动方块");

    gotoxy(18,9);
	color(10);
    printf("tip2: 通过 ↑ 使方块旋转");

	gotoxy(18,11);
    color(14);
    printf("tip3: 通过 ↓ 加速方块下落");
    
    gotoxy(18,13);
	color(11);
    printf("tip4: 按空格键暂停游戏，再按空格键继续");

    gotoxy(18,15);
	color(4);
    printf("tip5: 按 ESC 退出游戏");

	gotoxy(10,19);
	color(8);
    printf("在当前界面，按除 ESC 以外的任意键返回主界面，按 ESC 退出游戏");

	if(getch() == 27)		// 按 ESC 键退出游戏
	{
		close();
	}
	else					// 否则清屏并重新进入主循环中的 welcom() 函数
	{
		system("cls");		// 清屏
	}
}

/**
 * @brief 显示游戏规则
 */
void regulation()
{
    system("cls");			// 清屏

	gotoxy(34,3);
    color(13);
    printf("游戏规则");

    color(2);
    for (i = 6; i <= 18; i++)   		//输出上下边框 ===
	{
		for (j = 12; j <= 70; j++)  	//输出左右边框 ║
		{
			gotoxy(j, i);
			if (i == 6 || i == 18) printf("=");
			else if (j == 12 || j == 70) printf("║");
		}
	}

	gotoxy(16,7);
    color(12);
    printf("tip1: 不同形状的小方块从屏幕上方落下，玩家通过调整");

    gotoxy(22,9);
    printf("方块的位置和方向，使他们在屏幕底部拼出完整的");

    gotoxy(22,11);
    printf("一行或几行");

    gotoxy(16,13);
	color(14);
    printf("tip2: 每消除一行，积分增加100");

    gotoxy(16,15);
	color(11);
    printf("tip3: 每累计1000分，会提升一个等级");

	gotoxy(16,17);
    color(10);
    printf("tip4: 提升等级会使方块下落速度加快，游戏难度加大");

	gotoxy(12,21);
	color(8);
    printf("在当前界面，按除 ESC 以外的任意键返回主界面，按 ESC 退出游戏");

	if(getch() == 27)		// 按 ESC 键退出游戏
	{
		close();
	}
	else					// 否则清屏并重新进入主循环中的 welcom() 函数
	{
		system("cls");		// 清屏
	}
}

/**
 * @brief 退出
 */
void close()
{
   exit(0);
}






