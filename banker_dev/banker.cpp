#include<cstring>
#include <vector>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
#define max 30

int Alloc[max][max];  //已分配的资源 
int Avail[max];    //可用资源 
int resc[max];      //资源总数 
int Max[max][max];    //最大需求量 
int Need[max][max];   //还需要资源数 
int resc_size;   //资源种类 
int client_num;  //用户（进程）总数， 
bool isSecure;
bool SecureCheck();//系统是否安全
bool SecureDFS(bool *security,int *temp,int k);    //递归函数 
vector<int> ans;        //安全队列
int sum; //安全序列的个数
 
void initialize()  //初始化各数据 
{

	printf("资源种数：");     //输入必要数据 
	scanf("%d",&resc_size);
	printf("\n各个资源的数量：\n");
	for (int i = 0; i < resc_size; i++)
	{
		printf("资源%d=", i); 
		scanf("%d", &resc[i]);
	}
	printf("\n用户个数：");
	scanf("%d", &client_num);
	
	printf("每个用户的资源分配情况：\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("已对用户%d分配资源%d的数量=", i, j);
			scanf("%d", &Alloc[i][j]);
		}
		printf("\n");
	}
	
	printf("各个用户对资源的最大需求\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("用户%d对资源%d的最大需求=", i, j);
			scanf("%d", &Max[i][j]);
		}
		printf("\n");
	}
	
	for (int i = 0; i < client_num; i++)   //生成其他数据 
	{
		for (int j = 0; j < resc_size; j++)
		{
			Need[i][j] = Max[i][j] - Alloc[i][j]; 
		}
	}
	for (int j = 0; j < resc_size; j++)
	{
		Avail[j] = resc[j];  
		for (int i = 0; i < client_num; i++)
		{
			Avail[j] -= Alloc[i][j];
		}	
	}
}
bool SecureCheck()
{
	bool security[client_num];        //[i]表示对用户i的分配是否安全
	int temp[resc_size];                  //记录原Avail数组的值 
	for (int i = 0; i < resc_size; i++)
	{
		temp[i] = Avail[i];
	}
	int k = 0;     //安全进程的个数 
	return SecureDFS(security,temp,k);    //递归检测 
}
bool SecureDFS(bool *security,int *temp,int k)   //深度优先递归检测死锁并打印安全系列 
{
    if(k == client_num){     //找到了一种安全性序列，打印输出
	if(sum==0)printf("\n安全序列如下:\n"); 
        printf("%d:",++sum);      //安全序列数加一 
        int i;
        printf("%d",ans[0]);
        for(i=1; i<ans.size(); i++)
        {
            printf("->%d",ans[i]);
        }
        printf("\n");
        return true;
    }   

    int i;
    for(i=0; i<client_num; i++){
        if(!security[i])
        {
            int j;
            bool client_ifsec = true;  
            for(j=0; j<resc_size; j++)
            {
                if(Need[i][j] > temp[j])
                {
                    client_ifsec = false;        //该进程不安全 
                }
            }
            if(client_ifsec){        //第i个进程满足要求，暂时放入安全性队列 
                for(j=0; j<resc_size; j++)
                {
                    temp[j] += Alloc[i][j];    //归还资源 
                }
                security[i] = true;
                ans.push_back(i);
                SecureDFS(security,temp,k+1);     //搜索下一层 

                ans.pop_back();       //回溯，将第i个进程所做的改变恢复 
                for(j=0; j<resc_size; j++)
                {
                    temp[j] -= Alloc[i][j];
                }
                security[i] = false;
            }
        }
    }
}
bool answerQuest()
{
	int Request[resc_size];
	printf("输入哪个用户的资源请求？\n");
	int process;
	scanf("%d", &process);
	for (int j = 0; j < resc_size; j++)
	{
		printf("输入用户%d对资源%d的请求=", process, j);
		scanf("%d", &Request[j]);
	}

	//对资源请求后不能多于最大请求
	for (int j = 0; j < resc_size; j++)
	{
		if (Request[j] + Alloc[process][j] > Max[process][j]) {
			printf("用户%d对资源%d的请求不合理，超出所宣布的最大值！", process, j);
			return false;
		}
	}
	//没有大于最大请求，但是当前系统可能还没有这么资源分配他们
	for (int j = 0; j < resc_size; j++)
	{
		if (Request[j] > Avail[j])
		{
			printf("系统还没有足够的资源%d提供用户%d的请求", j, process);
		}
	}
	//尝试分配
	printf("尝试分配资源\n");
	for (int j = 0; j < resc_size; j++)
	{
		Alloc[process][j] += Request[j];
		Need[process][j] -= Request[j];
	}
	for (int j = 0; j < resc_size; j++)
	{
		Avail[j] -= Request[j];
	}
	if (!SecureCheck()) {//如果系统不处于安全状态。则本次分配作废，恢复原来的资源分配状态
		printf("分配作废，恢复原来的状态\n");
		for (int j = 0; j < resc_size; j++)
		{

			Alloc[process][j] -= Request[j];
			Need[process][j] += Request[j];
		}
		for (int j = 0; j < resc_size; j++)
		{
			Avail[j] += Request[j];
		}
		return false;
	}
	return true;

}
void look()     //显示目前资源分配情况 
{
	printf("最大资源需求(Max)：\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("%d\t", Max[i][j]);
		}
		printf("\n");
	}
	printf("已分配资源(Allocation)：\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("%d\t", Alloc[i][j]);
		}
		printf("\n");
	}
	printf("目前资源需求(Need)：\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("%d\t", Need[i][j]);
		}
		printf("\n");
	}
	printf("现有资源(Resources)：\n");
	for (int j = 0; j < resc_size; j++)
	{
		printf("%d\t", Avail[j]);
	}
	printf("\n");

}
void menu()
{
	printf("\n\n1.继续对用户进行资源的分配？\n");
	printf("2.查看资源情况\n");
	printf("3.退出\n");
}
int main()
{
	printf("\n★基于银行家算法的资源分配系统★\n\n");
	printf("1.请输入系统的初始状态\n\n");
	initialize();
	SecureCheck();  
	if(sum==0) printf("当前系统不安全！");   //没有产生安全序列，表明当前分配不安全 
	int choose;
	while (1)
	{
		menu();
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			if (answerQuest())
				printf("请求成功！");
			else
				printf("请求失败！");
			break;
		case 2:look(); break;
		case 3:
			exit(0);
		}
	}
	return 0;
}

