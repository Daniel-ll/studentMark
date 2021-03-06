// manageStudentSystem.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#define N 1000

#pragma warning(disable : 4996)
struct clerk
{
	int num;
	char name[20];
	int yuwen;   //语文
	int gaoshu;   //高数
	int yingyu;     //英语
	int dawu;     //大物
	int cyuyan;    //C语言
	int ave;  //平均分

}em[1000];

void menu();      //主页面
void input();     //输入记录
void save(int, int);   //保存记录
void display();   //显示记录
void del();       //删除记录
void search();    //查找记录
void search_num(); //按照id查找学生记录
void search_name(); //按照名字查找学生记录
void modify();    //修改记录
void sta();       //统计记录
void start();     //定义各函数
int load();       //从本地文件加载


void main()
{
	int n, button;    //n代表选择功能（1---7）  button 用来判断输入是否正确       
	start();
	getch();
	menu();
	do
	{
		printf("功能选择 (1--7):\n");
		scanf("%d", &n);
		if (n >= 1 && n <= 7)
		{
			button = 1;
			break;
		}
		else
		{
			button = 0;
			printf("错误输入，请再次输入 ！！");
		}
	} while (button == 0);

	while (button == 1)
	{
		switch (n)
		{
		case 1: input(); break;
		case 2: display(); break;
		case 3: search(); break;
		case 4: del(); break;
		case 5: modify(); break;
		case 6: sta(); break;
		case 7: exit(0); break;
		default:break;
		}
		getchar();
		printf("\n");
		printf("press any key to continue\n");
		getch();
		system("cls");  /*清屏*/
		menu(); /*调用菜单函数*/
		printf("功能选择 (1--7):\n");
		scanf("%d", &n);
		printf("\n");
	}
}


//界面初始化
void start()
{
	printf("\n\n\n");
	printf("************************************************************************************************************************\n\n");
	printf("******************************************************    Welcome    ***************************************************\n\n");
	printf("************************************************************************************************************************\n\n");
	printf("\n\n\n\n");
	printf("                 通信172  陈淑文  08070317219\n\n");
	printf("                                                                                                    2019.1.12\n\n\n\n\n");
	printf("                                              ***   please click enter   ***\n");
}

//主界面
void menu()
{
	system("cls");
	printf("\n\n\n");
	printf("**********************************    menu    *********************************\n\n\n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  1  输入学生成绩   \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  2  显示所有学生成绩  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  3  查找指定学生成绩  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  4  删除指定学生成绩  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  5  修改指定学生成绩  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  6  统计所有学生成绩  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  7  退出  \n\n");
	printf("提示:*请输入数据. \n        *数据会自动保存.\n\n");
}

//
void input()   /*输入记录*/
{
	system("cls");
	//int z = 0;
	int z = load();
	int i, m;
	do {
		if (z >= 1000)
			printf("本地储存大小已有1000条");
		printf("请输入要输入的学生数目 number(1--1000):\n");  //输入学生的人数
		scanf("%d", &m);
		if (z + m>1000)
			printf("已超出了储存大小1000条");
	} while (m + z > 1000);

	for (i = z; i<m + z; i++)
	{
		printf("ID number:");
		scanf("%d", &em[i].num);
		printf("姓 名:");
		scanf("%s", &em[i].name);
		getchar();
		printf("语 文:");
		scanf("%d", &em[i].yuwen);
		printf("高 数:");
		scanf("%d", &em[i].gaoshu);
		printf("英 语:");
		scanf("%d", &em[i].yingyu);
		printf("大 物:");
		scanf("%d", &em[i].dawu);
		printf("C语言:");
		scanf("%d", &em[i].cyuyan);
		em[i].ave = ((em[i].yuwen) + (em[i].gaoshu) + (em[i].yingyu) + (em[i].dawu) + (em[i].cyuyan)) / 5;
		printf("\n");
	}
	printf("\n\nComplete\n");
	getch();
	getch();
	save(m, z);
}


void save(int m, int all)  /*保存文件函数*/
{
	int initNum = 0;
	//if (m != 0)
	//	initNum = all;
	//else
		initNum = all;
	int allNum = initNum + m;

	int i;
	FILE*fp;
	if ((fp = fopen("clerk_list", "wb")) == NULL)
	{
		printf("Open the failure!\n");
		getch();
		exit(0);
	}
	for (i = 0; i<allNum; i++) /*将内存中职工的信息输出到磁盘文件中去*/
		if (fwrite(&em[i], sizeof(struct clerk), 1, fp) != 1)
			printf("Read and write error!\n");
	fclose(fp);
}


int load()  /*导入函数  int型*/
{
	FILE*fp;
	int i = 0;
	if ((fp = fopen("clerk_list", "rb")) == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	else
	{
		do
		{
			fread(&em[i], sizeof(struct clerk), 1, fp);
			i++;
		} while (feof(fp) == 0);
	}

	fclose(fp);
	return(i - 1);
}

void display()  /*显示记录*/
{
	int i, count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;
	int m = load();
	system("cls");
	printf("ID number     姓 名     语 文   高 数   英 语   大 物   C语言   平均分\n");
	for (i = 0; i<m; i++) /*m为输入部分的学生人数*/
	{
		printf("\n%-9d     %-4s     %-6d   %-6d   %-6d   %-4d   %-5d   %-4d", em[i].num, em[i].name, em[i].yuwen, em[i].gaoshu, em[i].yingyu, em[i].dawu, em[i].cyuyan, em[i].ave);
		count1 += em[i].yuwen;
		count2 += em[i].gaoshu;
		count3 += em[i].yingyu;
		count4 += em[i].dawu;
		count5 += em[i].cyuyan;
	}
	if (m > 0) {
		printf("\n---------------------------------------------------------------------------------------------\n");
		printf("\naverage 语文:%d \n", count1 / m);
		printf("\naverage 高数:%d \n", count2 / m);
		printf("\naverage 英语:%d \n", count3 / m);
		printf("\naverage 大物:%d \n", count4 / m);
		printf("\naverage C语言:%d \n", count5 / m);
	}
}


void del()   /*删除记录 */
{
	system("cls");
	int m = load();
	int i, j, n, t, button;
	char name[20];
	printf("\n所有学生成绩信息 :\n");
	display();
	printf("\n");
	printf("输入需要删除的学生名字 :\n");
	scanf("%s", name);
	for (button = 1, i = 0; button&&i<m; i++)
	{
		if (strcmp(em[i].name, name) == 0)
		{
			printf("\n此学生的成绩记录如下 :\n");
			printf("ID number     姓 名     语 文   高 数   英 语   大 物   C语言   平均分\n");
			printf("\n%-9d     %-4s     %-6d   %-6d   %-6d   %-4d   %-5d   %-4d", em[i].num, em[i].name, em[i].yuwen, em[i].gaoshu, em[i].yingyu, em[i].dawu, em[i].cyuyan, em[i].ave);
			printf("\n确认,please click 1.\n放弃,please click 0:\n");
			scanf("%d", &n);
			if (n == 1)   //确认删除
			{
				for (j = i; j<m - 1; j++)     //删除这条记录后，把后面的数据前移
				{
					strcpy(em[j].name, em[j + 1].name);
					em[j].num = em[j + 1].num;
					em[j].yuwen = em[j + 1].yuwen;
					em[j].gaoshu = em[j + 1].gaoshu;
					em[j].yingyu = em[j + 1].yingyu;
					em[j].dawu = em[j + 1].dawu;
					em[j].cyuyan = em[j + 1].cyuyan;
					em[j].ave = em[j + 1].ave;
				}
				button = 0;
			}
		}
 	}
	if (button)
		printf("\nNo such person!\n");
	printf("\n 删除后所有学生成绩记录如下 :\n");
	save(-1, m);
	display();
	printf("\n继续删除 ,please click 1.\n退出删除 ,please click 0.\n");
	printf("输入你的选择 (1/0):");
	scanf("%d", &t);
	switch (t)
	{
	case 1:del(); break;
	case 0: break;
	default:break;
	}
}


void search()   /*查找记录*/
{
	system("cls");
	int t, button;
	do
	{
		printf("\nClick 1:根据 ID 查询.\nClick 2:根据 名字 查询.\nClick 3:返回主菜单.\n");
		printf("输入你的选择(1/2/3):");
		scanf("%d", &t);
		if (t >= 1 && t <= 3)
		{
			button = 1;
			break;
		}
		else
		{
			button = 0;
			printf("错误");
		}
	} while (button == 0);

	while (button == 1)
	{
		switch (t)
		{
		case 1:printf("根据 ID 查询学生\n"); search_num(); break;
		case 2:printf("根据 名字 查询学生\n"); search_name(); break;
		case 3:main(); break;
		default:break;
		}
	}
}


void search_num()  /*用ID号查找*/
{
	int a;
	int i, t;
	int m = load();
	boolean is = true;   //初始默认需要查询的用户不存在
	printf("请输入 ID :\n");
	scanf("%d", &a);
	for (i = 0; i<m; i++)
		if (a == em[i].num)
		{
			is = false;  //用户存在
			printf("\n*****************************************************\n\n");
			printf("ID number     姓 名     语 文   高 数   英 语   大 物   C语言   平均分\n");
			printf("\n%-9d     %-4s     %-6d   %-6d   %-6d   %-4d   %-5d   %-4d", em[i].num, em[i].name, em[i].yuwen, em[i].gaoshu, em[i].yingyu, em[i].dawu, em[i].cyuyan, em[i].ave);
			printf("\n*****************************************************\n\n");
			break;
		}
	if (is)   //当用户不存在
		printf("\nNo such person!\n");
	printf("\n");
	printf("返回查询选择界面,click 1.\n继续 ID 查询,click 2.\n返回主菜单,click 3\n");
	printf("输入你的选择 (1/2/3):");
	scanf("%d", &t);
	switch (t)
	{
	case 1:search(); break;
	case 2: break;
	case 3:main(); break;
	default:break;
	}
}


void search_name()   /*用名字查找*/
{
	char name[30];
	int i, t;
	int m = load();
	boolean is = true;    //初始默认需要查询的用户不存在
	printf("输入名字 :\n");
	scanf("%s", name);
	for (i = 0; i<m; i++)
		if (strcmp(em[i].name, name) == 0)
		{
			is = false;   //用户存在
			printf("\n*****************************************************\n\n");
			printf("\n已经查询到结果,这条记录如下 ：\n");
			printf("ID number     姓 名     语 文   高 数   英 语   大 物   C语言   平均分\n");
			printf("\n%-9d     %-4s     %-6d   %-6d   %-6d   %-4d   %-5d   %-4d", em[i].num, em[i].name, em[i].yuwen, em[i].gaoshu, em[i].yingyu, em[i].dawu, em[i].cyuyan, em[i].ave);
			printf("\n*****************************************************\n\n");
		}
	if (is)     //用户不存在
		printf("\nNo such person!\n");
	printf("\n");
	printf("返回查询选择界面,click 1.\n继续  查询,click 2.\n返回主菜单,click 3\n");
	printf("输入你的选择 (1/2/3):");
	scanf("%d", &t);
	switch (t)
	{
	case 1:search(); break;
	case 2:search_name(); break;
	case 3:main(); break;
	default:break;
	}
}


void modify()  /*修改记录*/
{
	int num;
	char name[20];
	int yuwen;
	int gaoshu;
	int yingyu;
	int dawu;
	int cyuyan;
	int b, c, i, n, t, button;
	int m = load();
	system("cls");
	printf("\n所有学生成绩信息  :\n");
	display();
	printf("\n");
	printf("输入需要修改的学生信息的名字  :\n");
	scanf("%s", name);
	for (button = 1, i = 0; button&&i<m; i++)
	{
		if (strcmp(em[i].name, name) == 0)
		{
			printf("\n此学生记录如下 :\n");
			printf("ID number     姓 名     语 文   高 数   英 语   大 物   C语言   平均分\n");
			printf("\n%-9d     %-4s     %-6d   %-6d   %-6d   %-4d   %-5d   %-4d", em[i].num, em[i].name, em[i].yuwen, em[i].gaoshu, em[i].yingyu, em[i].dawu, em[i].cyuyan, em[i].ave);
			printf("\n 修改,click 1.\n不修改,click 0.\n");
			printf("输入你的选择(1/0):");
			scanf("%d", &n);
			if (n == 1)
			{
				printf("\n*****************************************************\n\n");
				printf("\n需要修改的序号\n 1.ID number    2. 姓 名    3. 语 文   4. 高 数   5. 英 语   6. 大 物   7. C语言  8.return to top\n");
				printf("\n*****************************************************\n\n");
				printf("选择序号 1-8 :\n");
				scanf("%d", &c);
				if (c>8 || c<1)
					printf("\n错误，请重新选择！！\n");
			}
			button = 0;
		}
	}

	if (button == 1)
		printf("\nNo such person!\n");
	do
	{
		switch (c)      /*因为当找到第i个职工时,for语句后i自加了1,所以下面的应该把改后的信息赋值给第i-1个人*/
		{
		case 1:printf("new ID number: ");
			scanf("%d", &num);
			em[i - 1].num = num;
			break;
		case 2:printf("new 名字: ");
			scanf("%s", name);
			strcpy(em[i - 1].name, name);
			break;
		case 3:printf("new 语文分数: ");
			getchar();
			scanf("%d", &yuwen);
			em[i - 1].yuwen = yuwen;
			em[i - 1].ave = (em[i - 1].yuwen + em[i - 1].gaoshu + em[i - 1].yingyu - em[i - 1].dawu - em[i - 1].cyuyan) / 5;
			break;
		case 4:printf("new 高数成绩: ");
			scanf("%d", &gaoshu);
			em[i - 1].gaoshu = gaoshu;
			em[i - 1].ave = (em[i - 1].yuwen + em[i - 1].gaoshu + em[i - 1].yingyu - em[i - 1].dawu - em[i - 1].cyuyan) / 5;
			break;
		case 5:printf("new 英语成绩: ");
			scanf("%d", &yingyu);
			em[i - 1].yingyu = yingyu;
			em[i - 1].ave = (em[i - 1].yuwen + em[i - 1].gaoshu + em[i - 1].yingyu - em[i - 1].dawu - em[i - 1].cyuyan) / 5;
			break;
		case 6:printf("new 大物成绩: ");
			scanf("%d", &dawu);
			em[i - 1].dawu = dawu;
			em[i - 1].ave = (em[i - 1].yuwen + em[i - 1].gaoshu + em[i - 1].yingyu - em[i - 1].dawu - em[i - 1].cyuyan) / 5;
			break;
		case 7:printf("new C语言成绩: ");
			scanf("%d", &cyuyan);
			em[i - 1].cyuyan = cyuyan;
			em[i - 1].ave = (em[i - 1].yuwen + em[i - 1].gaoshu + em[i - 1].yingyu - em[i - 1].dawu - em[i - 1].cyuyan) / 5;
			break;
		case 8:modify();
			break;
		default:break;
		}
		printf("\n");
		printf("\n\n 确认,please click 1.\n重新修改,please click 2.\n");
		printf("输入你的选择 (1/2):");
		scanf("%d", &b);

	} while (b == 2);
	printf("\n修改后的学生成绩如下 :\n");
	printf("\n");
	save(0, m);
	display();
	printf("\n继续修改 ,click 1.\n退出修改,click 0.\n");
	printf("输入你的选择 (1/0):");
	scanf("%d", &t);
	switch (t)
	{
	case 1:modify(); break;
	case 0:break;
	default:break;
	}
}


void sta()   /*统计记录*/
{
	int i;
	int jbgzNum = 0;
	int zwgzNum = 0;
	int jtNum = 0;
	int ybNum = 0;
	int gjjNum = 0;
	int m = load();
	system("cls");
	display();
	for (i = 0; i<m; i++) /*m为输入部分的学生人数*/
	{

		if (em[i].yuwen >= 60)
			jbgzNum++;
		if (em[i].gaoshu >= 60)
			zwgzNum++;
		if (em[i].yingyu >= 60)
			jtNum++;
		if (em[i].dawu >= 60)
			ybNum++;
		if (em[i].cyuyan >= 60)
			gjjNum++;

	}
	printf("\n*****************************************************\n\n");
	printf("各科成绩合格人数如下：\n");
	printf("     语 文   高 数   英 语   大 物   C语言\n");
	printf("      %-6d   %-6d   %-6d   %-4d   %-5d\n\n", jbgzNum, zwgzNum, jtNum, ybNum, gjjNum);
	printf("\n*****************************************************\n\n");
	printf("\n press any key to continue");
	getch();
	getch();
	menu();
}





