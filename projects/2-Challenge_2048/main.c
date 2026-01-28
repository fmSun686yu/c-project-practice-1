/*************************** 定 义 头 文 件 ***************************/

#include <stdio.h>		// 标准输入输出函数库（printf、scanf）
#include <stdbool.h>	// 布尔类型支持
#include <conio.h>  	// 为了读取方向键
#include <windows.h>	// 控制dos界面（获取控制台上坐标位置、设置字体颜色）
#include <math.h>   	// pow() 函数
#include <time.h>   	// time() 函数

/*************************** 定 义 全  局  变  量 ***************************/

int step = 0;           // 记录已执行步数
int score = 0;          // 存储游戏分数
long int Time;          // 记录游戏运行时间
int BOX[4][4] = {0};	// 定义4*4的二维数组表示游戏区域
HANDLE hOut;		    // 定义控制台句柄

/************************** 函 数 声 明 ***************************/

void gotoxy(int x, int y); 		    // 获取屏幕光标位置
int color(int c);               	// 设置文字颜色
int	TextColors(int i);				// 根据数字修改颜色
void DrawTheGameBox(); 			    // 绘制游戏界面
void add(int item[]);   			// 合并数字
bool ifMove(int item[]); 			// 判断是否能够移动数字,返回1能动，0不能动
void RandomlyGenerateNumbers();   	// 随机生成数字2或4
void GamePlay();    				// 开始游戏
void Replay();			       		// 重新游戏
bool if2n(int x);         			// 判断x是否是2的n次方
// 判断是否能够上移    可以上移（格子中的两个数相加是2的n次方），则返回1    不能移动，则返回0
bool ifup();
// 判断是否能够下移    可以下移（格子中的两个数相加是2的n次方），则返回1    不能移动，则返回0	
bool ifdown();
// 判断是否能够左移    可以左移（格子中的两个数相加是2的n次方），则返回1    不能移动，则返回0	
bool ifleft();
// 判断是否能够右移   可以右移（格子中的两个数相加是2的n次方），则返回1    不能移动，则返回0	
bool ifright();					
int BOXmax();						// 返回棋盘最大数
bool ifGameWin();					// 判断是否胜利
bool ifGameFail();					// 判断是否失败
bool KeyBoardControl(int key);   	// 键盘控制移动
void close();                   	// 关闭游戏
void title();                   	// 绘制标题（2048字符画）
void choice();                  	// 选择框
void Rabbit();						// 绘制字符画
void regulation();              	// 游戏规则介绍
void explation();               	// 按键说明
void close();                      	// 关闭游戏



/************************** 主函数 ***************************/

void main(int argc, char* argv[])
{
	while (1)
	{
		title();            // 打印标题
    	Rabbit();           // 打印字符画
    	choice();           // 菜单选项
	}
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
 * @brief 文字颜色函数  
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        // 更改文字颜色
	return 0;
}

/**
 * @brief 设置标题
 */
void title()
{
	color(11);          						// 浅淡绿色
    gotoxy(19,2);
    printf("■■■■   ■■■■    ■  ■     ■■■■"); 	    // 输出2048字符画
    gotoxy(19,3);
    printf("   ■   ■  ■    ■  ■     ■  ■");
    gotoxy(19,4);
    printf("■■■■   ■  ■    ■  ■     ■■■■");
    gotoxy(19,5);
    printf("■      ■  ■    ■■■■■    ■  ■");
    gotoxy(19,6);
    printf("■■■■   ■■■■       ■     ■■■■");
}

/**
 * @brief 菜单选项
 */
void choice()
{
	int n;
    int i,j = 1;

    gotoxy(32,8) ;
    color(13);
    printf("挑 战 2 0 4 8");

	color(14);          					// 黄色边框
    for (i = 9; i <= 20; i++)   			// 输出上下边框 ===
	{
		for (j = 15; j <= 60; j++)  	    // 输出左右边框 ||
		{
			gotoxy(j, i);
			if (i == 9 || i == 20) printf("=");
			else if (j == 15 || j == 59) printf("||");
		}
	}
	
	color(12);                              // 红色字体
	gotoxy(25, 12);                         // 设置显示位置
	printf("1.开始游戏");
	gotoxy(40, 12);
	printf("2.游戏规则");
	gotoxy(25, 16);
	printf("3.按键说明");
	gotoxy(40, 16);
	printf("4.退出");
	gotoxy(21,22);
	color(5);                               // 深紫色字体
	printf("请选择[1 2 3 4]:[ ]\b\b");

    scanf("%d", &n);    					// 输入选项
    switch (n)                              // 分支选择
    {
    	case 1:                             // 输入数字“1”
			GamePlay();                		// 开始游戏
        	break;
    	case 2:                             // 输入数字“2”
			regulation();					// 显示游戏规则
        	break;
    	case 3:                             // 输入数字“3”
			explation();					// 显示按键说明
        	break;
    	case 4:                             // 输入数字“4”
       	 	close();    					// 退出游戏
        	break;
    }
}

/**
 * @brief 绘制小兔子
 */
void Rabbit()
{
	color(3);
	gotoxy(64,10);
	printf("┏--┓   ┏--┓");		        // 打印兔子耳朵
	gotoxy(64,11);
	printf("┃  ┃   ┃  ┃");
	gotoxy(64,12);
	printf("┃  ┃   ┃  ┃");
	gotoxy(63,13);
	printf("_┃");					// 打印兔子脸
	gotoxy(74,13);
	printf("┃_");
	gotoxy(62,14);
	printf("┃");
	gotoxy(76,14);
	printf("┃");
	gotoxy(62,15);
	printf("┃             ┃");	 
	gotoxy(62,16);
	printf("┃");
	gotoxy(76,16);
	printf("┃");
	gotoxy(62,17);
	printf("┃             ┃");	    // 打印兔子脸
	gotoxy(62,18);
	printf("┗━━━━┳━━━┳━━━━┛");	            // 打印下巴
	gotoxy(65,19);
	printf("┏━┫   ┣━┓");		        // 打印胳膊
	gotoxy(62,20);
	printf("———┺━┻━━┻┻━┹———");
	color(5);
	gotoxy(67,13);
	printf("`~ヾ~`");				// 打印刘海
	color(4);
	gotoxy(67,14);
	printf("○   ○");				// 打印眼睛
	color(13);
	gotoxy(65,15);
	printf("〃");					// 打印腮红
	gotoxy(72,15);
	printf("〃");
	color(12);
	gotoxy(69,17);
	printf("┻");					// 打印嘴巴
}

/**
 * @brief 绘制游戏界面4×4的网格
 */
void DrawTheGameBox()
{
	int i,j,k;

	color(14);       					// 黄色

	// 打印棋盘边框
	// 打印棋盘的横向边框
	for(j = 2;j <= 22;j += 5)
	{
		gotoxy(15,j);
		for(k = 1;k<42;k++)
		{
			printf("-");				
		}
		printf("\n");
	}

	// 打印棋盘的纵向边框
	for (i = 3;i < 7;i ++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");	 
	}
	for (i = 8;i<12;i++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");
	}
	for (i = 13;i<17;i++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");
	}
	for (i = 18;i<22;i++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");
	}

	// 输出分数、步数和用时

	gotoxy(16,1);   								// 屏幕坐标位置
	color(11);      								// 淡浅绿色
	printf("游戏分数: %ld",score);

	gotoxy(42,1);   								// 屏幕坐标位置
	color(13);      								// 粉色
	printf("执行步数: %d\n",step);

    gotoxy(44,23);
	color(10);                                  	// 绿色
	printf("已用时：%d s",time(NULL) - Time);   	 // 输出游戏运行时间
}

/**
 * @brief 根据数字修改颜色
 * @note 格子中出现2n（0<n<12）的数字显示为不同颜色
 */
int TextColors(int number)
{
	switch (number)         		
	{
		case 2:						// 数字2
			return color(12);		// 显示色号为12的颜色，红色
			break;
		case 4: 					// 数字4
			return color(11); 		// 显示色号为11的颜色，亮蓝色
			break;
		case 8: 					// 数字8
			return color(10); 		// 显示色号为10的颜色，亮绿色
			break;
		case 16:
			return color(14);
			break;
		case 32:
			return color(6);
			break;
		case 64:
			return color(5);
			break;
		case 128:
			return color(4);
			break;
		case 256:
			return color(3);
			break;
		case 512:
			return color(2);
			break;
		case 1024:
			return color(9);
			break;
		case 2048:
			return color(7);
			break;
	}
	return 0;
}

/**
 * @brief 合并数字
 * @note 向 i 小的方向移动并合并，即从 i 小的方向开始合并
 */
void add(int item[])
{
    int i = 0;
	int j = 0;
    int t[4] = {0};

    for(i = 0; i < 4; i ++)
	{
        if(item[i] != 0)					// 如果这个格子里有数字
		{              
            t[j] = item[i];					// 就把该数字保存到中间数组 t 中
			j++;
        }
    }

	// 把两个相邻且相同的数加起来
    for(i = 0; i < 4; i ++)
	{
        if(t[i] == t[i + 1])			// 如果两个数字相同，则合并
		{
            t[i] *= 2;        			// 一个格子中的数字翻倍，另一个为空
            t[i + 1] = 0;
            score += t[i];				// 加分，加的分数为消除的数字*2
        }
    }

    j = 0;
	memset(item, 0, 4*sizeof(int));		// 将 item 清零
    for(i = 0; i < 4; i ++)
	{
        if(t[i] != 0)
		{
            item[j] = t[i];
			j++;
        }
    }
}

/**
 * @brief 判断能否移动数字,返回1能动；返回0不能动
 * @note 向 i 小的方向移动
 */
bool ifMove(int item[])
{
    int i = 0;

    for(i = 0; i < 3; i ++)
	{
        // 如果两个相邻位置上数字相同，则能移动，返回1
        if(item[i] != 0 && item[i] == item[i + 1])     
        {
        	return 1;
		}

        // 如果两个相邻位置上，i小的一个是空格子，i大的一个上有数字，则也能移动，返回1
        if(item[i] == 0 && item[i + 1] != 0)            
        {
        	return 1;
		}
    }

    return 0;       //不能合并，返回0
}

/**
 * @brief 判断x是否是2的n次方
 * @retval 是2的n次方，返回1，否则返回0
 * @note 计算范围：2-2048
 */
bool if2n(int x)       
{
	int n;

	for(n = 1; n <= 11; n++)			// 2的11次方是2048，游戏目标是达到2048
	{
		if(x == pow(2,n))     		  	// 计算2的n次方，如果是2的n次方，返回1
		{
			return 1;
		}
	}
	return 0;          					// 不是2的n次方，返回0
}

/**
 * @brief 判断是否能够上移
 * @retval 可以上移，则返回1；不能上移，则返回0
 */
bool ifup()
{
	int i, j;

	for(j = 0; j < 4; j ++)			// 遍历每一列
	{
		for(i = 0; i < 3; i ++)
		{
            // 如果上下两个格子相加是2的n次方，并且下面的格子中有数字
			if((if2n(BOX[i][j] + BOX[i+1][j]) == 1) && BOX[i+1][j])
			{
				return 1;    // 可以上移,返回1
			}
		}
	}

	return 0;        	 // 不能上移，返回0
}

/**
 * @brief 判断是否能够下移
 * @retval 可以下移，则返回1；不能下移，则返回0
 */
bool ifdown()
{
	int i, j;

	for(j = 0; j < 4; j ++)			// 遍历每一列
	{
		for(i = 3; i > 0; i --)
		{
            // 如果上下两个格子相加是2的n次方，并且上面的格子中有数字
			if((if2n(BOX[i][j] + BOX[i-1][j]) == 1) && BOX[i-1][j])
			{
				return 1;       // 可以下移，返回1
			}
		}
	}

	return 0;            		// 不能下移，返回0
}

/**
 * @brief 判断是否能够左移
 * @retval 可以左移，则返回1；不能移动，则返回0
 */
bool ifleft()
{
	int i,j;

	for(i = 0; i < 4; i ++)			// 遍历每一行
	{
		for(j = 0; j < 3; j ++)
		{
            // 如果左右两个格子相加是2的n次方，并且右面的格子中有数
			if((if2n(BOX[i][j] + BOX[i][j+1]) == 1) && BOX[i][j+1])     
			{
				return 1;          	// 可以左移，返回1
			}
		}
	}

	return 0;              			// 不能左移，返回0
}

 /**
 * @brief 判断是否能够右移
 * @retval 可以右移，则返回1；不能移动，则返回0
 */
bool ifright()
{
	int i,j;

	for(i = 0; i < 4; i ++)			// 遍历每一行
	{
		for(j = 3; j > 0; j --)
		{
            // 如果左右两个格子相加是2的n次方，并且左面的格子中有数字
			if((if2n(BOX[i][j] + BOX[i][j-1]) == 1) && BOX[i][j-1])     
			{
				return 1;            // 可以右移，返回1
			}
		}
	}

	return 0;                 		// 不能右移，返回0
}

/**
 * @brief 返回棋盘最大数
 */
int BOXmax()
{
	int i, j;
	int max = 0;

	for(i=0; i<4; i++)				// 遍历每一行
	{
		for(j=0; j<4; j++)			// 遍历每一列
		{
			if (BOX[i][j] > max)	// 如果数组中有数值大于max的值
			{
				max = BOX[i][j];	// 将该值赋值给max
			}
		}
	}

	return max;						// 返回max的值
}

/**
 * @brief 判断是否胜利
 */
bool ifGameWin()
{
	if(BOXmax() == 2048)            // 如果棋盘中的最大值为2048，达到目标，则游戏胜利
	{
		Sleep(10000);				// 延时10秒

		system("cls");				// 清屏

		// 输出合并出的最大数
		gotoxy(32,3);
		color(14);
		printf("合并出的最大数是：");

		gotoxy(50,3);
		color(11);
		printf("%d",BOXmax());

		// 输出该局游戏得分
		gotoxy(32,4);
		color(14);
		printf("该局游戏得分：");

		gotoxy(50,4);
		color(11);
		printf("%d",score);

		// 输出该局游戏步数
		gotoxy(32,5);
		color(14);
		printf("该局游戏步数：");

		gotoxy(50,5);
		color(11);
		printf("%d",step);

		// 输出该局游戏用时
		gotoxy(32,6);
		color(14);
		printf("该局游戏用时：");

		gotoxy(50,6);
		color(11);
		printf("%d s",time(NULL) - Time);

		// 输出胜利win的字符画
		gotoxy(1,10);
		color(2);   				// 暗绿色
    	printf("     ■             ■             ■       ■■■■■         ■         ■  \n");  
    	gotoxy(1,11);
    	printf("      ■           ■■           ■           ■           ■ ■       ■  \n");
    	gotoxy(1,12);
        printf("       ■         ■  ■         ■            ■           ■  ■      ■  \n");
        gotoxy(1,13);
		printf("        ■       ■    ■       ■             ■           ■   ■     ■   \n");
		gotoxy(1,14);
        printf("         ■     ■      ■     ■              ■           ■    ■    ■  \n");
        gotoxy(1,15);
        printf("          ■   ■        ■   ■               ■           ■     ■   ■ \n");
        gotoxy(1,16);
		printf("           ■ ■          ■ ■                ■           ■      ■  ■    \n");
		gotoxy(1,17);
		printf("            ■■           ■■                ■           ■       ■ ■  \n");
		gotoxy(1,18);
		printf("            ■             ■              ■■■■■         ■         ■   \n");

		gotoxy(35,22);
		color(13);
		printf("胜利啦，你真棒！！！");

		return 1;
	}

	return 0;                // 没有胜利，返回0
}

/**
 * @brief 判断是否失败，并输出棋盘最大数
 */
bool ifGameFaile()
{
    // 当上下左右都不能移动时，游戏失败
	if(ifup() + ifdown() + ifleft() + ifright() == 0)				
	{
		Sleep(3000);			// 延时3秒

		system("cls");			// 清屏

		// 输出合并出的最大数
		gotoxy(32,3);
		color(14);
		printf("合并出的最大数是：");

		gotoxy(50,3);
		color(11);
		printf("%d",BOXmax());

		// 输出该局游戏得分
		gotoxy(32,4);
		color(14);
		printf("该局游戏得分：");

		gotoxy(50,4);
		color(11);
		printf("%d",score);

		// 输出该局游戏步数
		gotoxy(32,5);
		color(14);
		printf("该局游戏步数：");

		gotoxy(50,5);
		color(11);
		printf("%d",step);

		// 输出该局游戏用时
		gotoxy(32,6);
		color(14);
		printf("该局游戏用时：");

		gotoxy(50,6);
		color(11);
		printf("%d s",time(NULL) - Time);

		// 输出end字符画
		gotoxy(24,10);
		color(4);   			// 暗红色
    	printf("     ■■■■■      ■        ■    ■■■     \n");
    	gotoxy(24,11);
    	printf("     ■          ■■       ■    ■   ■   \n");
    	gotoxy(24,12);
        printf("     ■          ■ ■      ■    ■     ■   \n");
        gotoxy(24,13);
		printf("     ■          ■  ■     ■    ■      ■  \n");
		gotoxy(24,14);
        printf("     ■■■■       ■   ■    ■    ■       ■  \n");
        gotoxy(24,15);
        printf("     ■          ■    ■   ■    ■      ■  \n");
        gotoxy(24,16);
		printf("     ■          ■     ■  ■    ■     ■   \n");
		gotoxy(24,17);
		printf("     ■          ■      ■ ■    ■   ■  \n");
		gotoxy(24,18);
		printf("     ■■■■■      ■       ■■    ■■■     \n");

		// 输出提示文字
		gotoxy(34,22);
		color(13);
		printf("无法移动，游戏失败！");

		return 1;
	}

   	return 0;                // 没有失败，返回0
}

/**
 * @brief 键盘控制移动
 */
bool KeyBoardControl(int key)
{
    int i;
	int j=0;
    int tp[4];

    switch(key)								// LEFT = 75, UP = 72, RIGHT = 77, DOWN = 80
	{	
    	case 72: 							// up，向上键
        	for(i = 0; i < 4; i++)			// 遍历每一列
			{
            	tp[0] = BOX[0][i];      	// 把第 i 列数移到中间变量
            	tp[1] = BOX[1][i];
            	tp[2] = BOX[2][i];
            	tp[3] = BOX[3][i];

				// 判断该列是否可以移动
				if(ifMove(tp))				// 若能移动，则执行移动和合并操作
				{
					add(tp);            	// 获得移动和合并之后的数值

					BOX[0][i] = tp[0];      // 把处理好的中间变量移回来
					BOX[1][i] = tp[1];
					BOX[2][i] = tp[2];
					BOX[3][i] = tp[3];
				}
				else						// 若不能移动，则j加1
				{
					j++;
				}
        	}

			/**
			 * @note 当 j==4 时，说明4列都不能移动，返回0；
			 * 		 j<4 时，可以执行up操作，返回1
			 */
        	return (j != 4);

    	case 80: 							// down，向下键
        	for(i = 0; i < 4; i++)
			{
            	tp[0] = BOX[3][i];
            	tp[1] = BOX[2][i];
            	tp[2] = BOX[1][i];
            	tp[3] = BOX[0][i];

				if(ifMove(tp))				// 如果该列可以移动
				{
					add(tp);

					BOX[3][i] = tp[0];
					BOX[2][i] = tp[1];
					BOX[1][i] = tp[2];
					BOX[0][i] = tp[3];
				}
				else						// 如果不能移动
				{
					j++;
				}
       	 	}

        	return (j != 4);

    	case 75:							// left，向左键
        	for(i = 0; i < 4; i++)
			{
            	tp[0] = BOX[i][0];
            	tp[1] = BOX[i][1];
            	tp[2] = BOX[i][2];
            	tp[3] = BOX[i][3];

				if(ifMove(tp))				// 如果该行可以移动
				{
					add(tp);

					BOX[i][0] = tp[0];
					BOX[i][1] = tp[1];
					BOX[i][2] = tp[2];
					BOX[i][3] = tp[3];
				}
				else						// 如果不能移动
				{
					j++;
				}
        	}

        	return (j != 4);

    	case 77: 							// right，向右键
        	for(i = 0; i < 4; i++)
			{
        	    tp[0] = BOX[i][3];
            	tp[1] = BOX[i][2];
           	 	tp[2] = BOX[i][1];
            	tp[3] = BOX[i][0];

				if(ifMove(tp))				// 如果该行可以移动
				{
					add(tp);

					BOX[i][3] = tp[0];
					BOX[i][2] = tp[1];
					BOX[i][1] = tp[2];
					BOX[i][0] = tp[3];
				}
				else						// 如果不能移动
				{
					j++;
				}
        	}

        	return (j != 4);

		case 27:							// 按 Esc
			gotoxy(20,23);
			color(12);
			printf("确定退出游戏么? (y/n)");

			while (1)
			{
				char c = getch();           				// 获得键盘输入

				if(c == 'y' || c == 'Y')     				// 如果输入的是大写或者小写的 y
				{
					exit(0);                				// 退出游戏
				}
				else if(c == 'n' || c == 'N')      			// 如果输入的是大写或者小写的 n
				{
					gotoxy(20,23);
					printf("                        ");   	// 清除提示文字，并继续游戏
					break;
				}
			}
			break;
			
    	default:
			return 0;
    }
}

/**
 * @brief 随机生成数字2或4
 * @note 调用一次该函数，在一个随机空格中生成数字2或4
 */
void RandomlyGenerateNumbers()
{
	int i, j;

	do
	{
    	i = rand()%4;               	// 获得4×4棋盘中的随机位置
    	j = rand()%4;
	}while(BOX[i][j]!=0);           	// 直到寻找到棋盘中的空格

	if(rand() % 4 == 0)      			// 2或4随机出现在空格处(最开始出现在棋盘上的2或4)
	{
		BOX[i][j] = 4;
    }
	else
	{
		BOX[i][j] = 2;
    }
}

/**
 * @brief 显示4x4网格中的数字
 */
void DisplayNumbers()
{
	int i, j;
	int c;

	// 遍历整个网格
	for(i = 0; i < 4; i ++)         // 遍历每一行
	{
        for(j = 0; j < 4; j ++)		// 遍历每一列
		{
            if(BOX[i][j] == 0)      // 如果网格该位置处数字等于0（没有数字），就跳过（不显示数字）
            {
            	continue;
			}

			gotoxy(15 + j * 10 + 5, 2 + i * 5 + 3);  	// 设置数字显示位置
            c = BOX[i][j];  							// 获得棋盘上BOX[i][j]上的数字
            TextColors(c);  							// 设置数字的颜色，不同数字显示不同颜色
            printf("%d", c);    						// 打印数字
        }
    }
}

/**
 * @brief 开始游戏
 */
void GamePlay()
{
	system("cls");      				// 清屏

	Time = time(NULL);					// 取当前时间为开始时间

	srand(time(NULL)); 					// 设置随机数种子，初始化随机数

    DrawTheGameBox();               	// 绘制游戏界面

	RandomlyGenerateNumbers();      	// 随机生成数字2或4（游戏开始时，出现在棋盘上的两个数字）
	RandomlyGenerateNumbers();

	DisplayNumbers();           		// 显示网格中的数字

	while(1)
	{
        while(kbhit())            			// kbhit() 检查当前是否有键盘输入，有返回1，否则返回0
        {
         	// 如果按下的按键不是在 KeyBoardControl() 函数中定义的，会没有反应，一直到按下定义的按键为止
            if(!KeyBoardControl(getch()))  
            {
				continue;
			}

			RandomlyGenerateNumbers();  	// 随机生成数字2或4

            DrawTheGameBox();       		// 绘制棋盘

            DisplayNumbers();       		// 显示网格中的数字

			step++;                 	  	// 进行计步
	    }

		//只要 ifGamefaile() 或者 ifGamewin() 任意一个函数返回1，也就是成功或是失败都会出现下面的内容
        if(ifGameFaile() || ifGameWin())  
	    {
	    	int n;

	    	gotoxy(20,20);
			color(12);
			printf("我要重新玩一局-------1");

			gotoxy(45,20);
			printf("不玩了，退出吧-------2\n");

			gotoxy(43,21);
			color(11);
			scanf("%d", &n);
    		switch (n)
    		{
    			case 1:
        			Replay();         //重新游戏函数
        			break;
    			case 2:
        			exit(0);    		 //关闭游戏
        			break;
    		}
		}
	}
}

/**
 * @brief 重新游戏
 */
void Replay()
{
	system("cls");                  	// 清屏

	score = 0;							// 分数归零
	step = 0;                 			// 步数归零

	memset(BOX,0,16*sizeof(int));      	// 初始化BOX数组

	GamePlay();                         // 开始游戏
}

/**
 * @brief 游戏规则介绍
 */
void regulation()
{
	int i,j;

    system("cls");			// 清屏

    gotoxy(34,3);
	color(13);
    printf("游戏规则");

    color(2);
    for (i = 6; i <= 18; i++)   		 //输出上下边框 ===
	{
		for (j = 15; j <= 70; j++)  //输出左右边框 ||
		{
			gotoxy(j, i);
			if (i == 6 || i == 18) printf("=");
			else if (j == 15 || j == 69) printf("||");
		}
	}

    gotoxy(18,7);
	color(3);
    printf("tip1: 玩家可以通过↑ ↓ ← →方向键来移动方块");

    gotoxy(18,9);
	color(10);
    printf("tip2: 按ESC退出游戏");

    gotoxy(18,11);
	color(14);
    printf("tip3: 玩家选择的方向上,若有相同的数字则合并");

    gotoxy(18,13);
	color(11);
    printf("tip4: 每移动一步，空位随机出现一个2或4");

    gotoxy(18,15);
	color(4);
    printf("tip5: 棋盘被数字填满，无法进行有效移动，游戏失败");

    gotoxy(18,17);
	color(5);
    printf("tip6: 棋盘上出现2048，游戏胜利");

	gotoxy(18,20);
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
 * @brief 按键说明
 */
void explation()
{
	gotoxy(20,22);
	color(13);
	printf("①、↑、↓、←、→方向键进行游戏操作！");

	gotoxy(20, 24);
	printf("②、ESC键退出游戏");

	gotoxy(20,26);
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
 * @brief 退出游戏
 */
void close()
{
   exit(0);
}