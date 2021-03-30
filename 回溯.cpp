#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <fstream>
using namespace std;
#define hang 10		//定义目标棋盘的行和列（分别设置为 (6,6) (6,8) (8,8) (8,10) (10,10) (10,12)）求出基本解 
#define lie 12
bool is_ok;
int mapp[hang][lie];			//记录地图标号
bool vis[hang][lie];			//记录地图的点是否已经到达
int ans[hang*lie];			//地图点数 
int dir[8][2] = {-2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2,-2,-1};
int order_i, order_j;
int guifan[hang][lie];
void make_map()			//填充地图 
{
	for(int i = 0; i < hang; i++)
	{
		for(int j = 0; j < lie;j++)
		{
			mapp[i][j] = lie * i + j + 1;
		}
	}
}
bool is_valid(int i, int j)		//判端(i,j)是否可走 
{
	if((i < 0) || (j < 0) || (i > hang - 1) || (j > lie - 1) || (vis[i][j]))
		return false;
	return true;
}

int cal_roads(int ii, int jj)	//(ii,jj)的下一步有几种走法 
{
	int counter = 0;
	for(int i = 0; i < 8; i++)	//8种走法分别判断 
	{
		int next_i = ii + dir[i][0];
		int next_j = jj + dir[i][1];
		if(is_valid(next_i, next_j))
			counter++; 
	}
	return counter;
}
bool return_start(int ii, int jj) // 判断(ii, jj) 可否到达起点  
{
	for(int i = 0; i < 8; i++)
	{
		if( (ii + dir[i][0] == hang/2 )&&(jj + dir[i][1] == lie/2))
			return true;
	}
	return false; 
}
bool order(int ii, int jj)
{
	//左上 
	if((ii == 0)&&(jj == 1))
	{
		if(!vis[2][0])
		{
			order_i = 2;  order_j = 0;  return true;
		}
	}
	else if((ii == 2)&&(jj == 0))
	{
		if(!vis[2][0])
		{
			order_i = 2;  order_j = 0;  return true;
		}
	}
	else if((ii == 0)&&(jj == 2))
	{
		if(!vis[1][0])
		{
			order_i = 1;  order_j = 0;  return true;
		}
	}
	else if((ii == 1)&&(jj == 0))
	{
		if(!vis[0][2])
		{
			order_i = 0;  order_j = 2;  return true;
		}
	}
	
//右上 
	else if((ii == 0)&&(jj == lie - 3))
	{
		if(!vis[1][lie - 1])
		{
			order_i = 1;  order_j = lie - 1;  return true;
		}
	}
	else if((ii == 1)&&(jj == lie - 1))
	{
		if(!vis[0][lie - 3])
		{
			order_i = 0;  order_j = lie - 3;  return true;
		}
	}
	else if((ii == 0)&&(jj == lie - 2))
	{
		if(!vis[2][lie - 1])
		{
			order_i = 2;  order_j = lie - 1;  return true;
		}
	}
	else if((ii == 2)&&(jj == lie - 1))
	{
		if(!vis[0][lie - 2])
		{
			order_i = 0;  order_j = lie - 2;  return true;
		}
	}

//右下 
	else if((ii == hang - 3)&&(jj == lie - 1))
	{
		if(!vis[hang - 1][lie - 2])
		{
			order_i = hang - 1;  order_j = lie - 2;  return true;
		}
	}
	else if((ii == hang - 1)&&(jj == lie - 2))
	{
		if(!vis[hang - 3][lie - 1])
		{
			order_i = hang - 3;  order_j = lie - 1;  return true;
		}
	}
	else if((ii == hang - 2)&&(jj == lie - 1))
	{
		if(!vis[hang - 1][lie - 3])
		{
			order_i = hang - 1;  order_j = lie - 3;  return true;
		}
	}
	else if((ii == hang - 1)&&(jj == lie - 3))
	{
		if(!vis[hang - 2][lie - 1])
		{
			order_i = hang - 2;  order_j = lie - 1;  return true;
		}
	}

//左下 
	else if((ii == hang - 3)&&(jj == 0))
	{
		if(!vis[hang - 1][1])
		{
			order_i = hang - 1;  order_j = 1;  return true;
		}
	}
	else if((ii == hang - 1)&&(jj == 1))
	{
		if(!vis[hang - 3][0])
		{
			order_i = hang - 3;  order_j = 0;  return true;
		}
	}
	else if((ii == hang - 2)&&(jj == 0))
	{
		if(!vis[hang - 1][2])
		{
			order_i = hang - 1;  order_j = 2;  return true;
		}
	}
	else if((ii == hang - 1)&&(jj == 2))
	{
		if(!vis[hang - 2][0])
		{
			order_i = hang - 2;  order_j = 0;  return true;
		}
	}
	
	return false;
}
struct choose
{
	int ii;
	int jj;
	int roads;
	choose() {}
	choose(int i, int j)
	{
		ii = i;
		jj = j;
		roads = cal_roads(i, j);
	}
};

bool cmp(choose a, choose b)
{
	return a.roads < b.roads;
}
void DFS(int from_i, int from_j, int num)
{
	vector<choose> cho;
	for(int i = 0; i < 8; i++)
	{
		int next_i = from_i + dir[i][0];
		int next_j = from_j + dir[i][1];
		if(is_valid(next_i, next_j))
			cho.push_back(choose(next_i, next_j));
	}
	if(cho.empty())
		return;
	sort(cho.begin(), cho.end(), cmp);
	
	if(num == hang*lie - 1)
	{
		if(return_start(cho[0].ii, cho[0].jj))
		{
			ans[num] = mapp[cho[0].ii][cho[0].jj];
			is_ok = true;
		}
		
		return;
	}
	if(order(from_i, from_j))
	{
		int ii = order_i;
		int jj = order_j;
		vis[ii][jj] = true;
		DFS(ii,jj, num + 1);
		if(is_ok)
		{
			ans[num] = mapp[ii][jj];
			return;
		}
		else
			vis[ii][jj] = false;
	}
	else
	{
		for(int i = 0; i < (int)cho.size(); i++)
		{
			vis[cho[i].ii][cho[i].jj] = true;
			DFS(cho[i].ii,cho[i].jj, num + 1);
			if(is_ok)
			{
				ans[num] = mapp[cho[i].ii][cho[i].jj];
				return;
			}
			else
				vis[cho[i].ii][cho[i].jj] = false;
		}
	}
}
void guifanhua()
{
	int guifan1[hang][lie];
	int k = 0;
	for(;k < hang*lie; k++)
	{
		if(ans[k] == 1)
			break;
	}	
	for(int i = 0; i < hang; i++)
	{
		for(int j = 0; j < lie; j++, k++)
		{
			k = k%(hang*lie);
			guifan[(ans[k] -1)/lie][(ans[k] - 1)%lie]  = i * lie + j + 1;
//			guifan[i][j] = ans[k];
		}
	}
	
}
void change(int num)
{
	cout << '(' << (num - 1)/lie << ',' << (num - 1)%lie << ')';
}
int main()
{
	ofstream outfile("result_10_12.txt",ios::out);
	cout << "这是行为：" << hang << "，列为：" << lie << " 的一种符合条件的哈密顿回路情况！" << endl; 
	make_map();
	memset(vis, false, sizeof(vis));
	vis[hang/2][lie/2] = true;
	memset(ans, 0, sizeof(ans));
	ans[0] = mapp[hang/2][lie/2];
	is_ok = false;
	DFS(hang/2,lie/2, 1);
	if(is_ok)
	{
		guifanhua();
//		for(int i = 0; i < hang; i++)
//		{
//			for(int j = 0; j < lie; j++)
//			{
//				change(guifan[i][j]); cout << ' ';
//			}
//			cout << endl;
//		}
//		cout << endl;
		for(int i = 0; i < hang; i++)
		{
			for(int j = 0; j < lie; j++)
			{
				outfile << guifan[i][j] << ' '; 
				cout << guifan[i][j] << ' ';
			}
			cout << endl;
		}
	}
	else
		cout << "不行！" << endl;
	outfile.close(); 
	return 0;
} 
