#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;
int a[100][100];
int array6_6[6][6];
int array6_8[6][8];
int array8_6[8][6];
int array8_8[8][8];
int array8_10[8][10];
int array10_8[10][8];
int array10_10[10][10];
int array10_12[10][12];
int array12_10[12][10];
bool ni = false;
void fuzhi(int x0, int y0, int x1, int y1)
{
	if(x1 - x0 == 5)
	{
		if(y1 - y0 == 5)
		{
			for(int i = 0; i < 6; i++)
				for(int j = 0; j < 6; j++)
					a[x0 + i][y0 + j] = array6_6[i][j];
		}
		else if(y1 - y0 == 7)
		{
			for(int i = 0; i < 6; i++)
				for(int j = 0; j < 8; j++)
					a[x0 + i][y0 + j] = array6_8[i][j];
		}
	}
	else if(x1 - x0 == 7)
	{
		if(y1 - y0 == 5)
		{
			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 6; j++)
					a[x0 + i][y0 + j] = array8_6[i][j];
		}
		else if(y1 - y0 == 7)
		{
			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 8; j++)
					a[x0 + i][y0 + j] = array8_8[i][j];
		}
		else if(y1 - y0 == 9)
		{
			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 10; j++)
					a[x0 + i][y0 + j] = array8_10[i][j];
		}
	}
	else if(x1 - x0 == 9)
	{
		if(y1 - y0 == 7)
		{
			for(int i = 0; i < 10; i++)
				for(int j = 0; j < 8; j++)
					a[x0 + i][y0 + j] = array10_8[i][j];
		}
		else if(y1 - y0 == 9)
		{
			for(int i = 0; i < 10; i++)
				for(int j = 0; j < 10; j++)
					a[x0 + i][y0 + j] = array10_10[i][j];
		}
		else if(y1 - y0 == 11)
		{
			for(int i = 0; i < 10; i++)
				for(int j = 0; j < 12; j++)
					a[x0 + i][y0 + j] = array10_12[i][j];
		}
	}
	else
	{
		for(int i = 0; i < 12; i++)
				for(int j = 0; j < 10; j++)
					a[x0 + i][y0 + j] = array12_10[i][j];
	}
}
void opp(int x0, int y0, int x1, int y1)
{
	int num = (x1 - x0 + 1)*(y1 - y0 + 1);
	for(int i = 0; i <= x1 - x0; i++)
	{
		for(int j = 0; j <= y1 - y0; j++)
		{
			a[x0 + i][y0 + j] = num - a[x0 + i][y0 + j] + 1;
		}
	}
}
void Link(int x0, int y0, int mid_x, int mid_y, int x1, int y1)
{
	//连接前调整顺序 
	if(a[mid_x - 1][mid_y] > a[mid_x][mid_y - 2])
	{
		opp(x0, y0, mid_x, mid_y); ni = true;
	}
	if(a[mid_x][mid_y + 1] > a[mid_x - 2][mid_y + 2])
		opp(x0, mid_y + 1, mid_x, y1);
	
	if(a[mid_x + 2][mid_y + 1] > a[mid_x + 1][mid_y + 3])
		opp(mid_x + 1, mid_y + 1, x1, y1); 
		
	if(a[mid_x + 1][mid_y] > a[mid_x + 3][mid_y - 1])
		opp(mid_x + 1, y0, x1, mid_y);
//从左上开始顺时针连接
	//右上连接左上前半段 
	int add_num = a[mid_x - 1][mid_y] - a[mid_x - 2][mid_y + 2] + 1;
	int xiuzheng_num = a[mid_x - 2][mid_y + 2];
	for(int i = x0; i <= mid_x;i++)
	{
		for(int j = mid_y + 1; j <= y1; j++)
		{
			if(a[i][j] < xiuzheng_num)
				a[i][j] = a[i][j] + (mid_x + 1 - x0)*(y1 - mid_y);
			a[i][j] = a[i][j] + add_num; 
		}
	}
	//右下连接右上 
	add_num = a[mid_x][mid_y + 1] - a[mid_x + 1][mid_y + 3] + 1;
	xiuzheng_num = a[mid_x + 1][mid_y + 3];
	for(int i = mid_x + 1; i <= x1;i++)
	{
		for(int j = mid_y + 1; j <= y1; j++)
		{
			if(a[i][j] < xiuzheng_num)
				a[i][j] = a[i][j] + (x1 - mid_x)*(y1 - mid_y);
			a[i][j] = a[i][j] + add_num;
		}
	}
	//左下连接右下 
	add_num = a[mid_x + 2][mid_y + 1] - a[mid_x + 3][mid_y - 1] + 1;
	xiuzheng_num = a[mid_x + 3][mid_y - 1];
	for(int i = mid_x + 1; i <= x1; i++)
	{
		for(int j = y0; j <= mid_y; j++)
		{
			if(a[i][j] < xiuzheng_num)
				a[i][j] = a[i][j] + (x1 - mid_x)*(mid_y - y0 + 1);
			a[i][j] = a[i][j] + add_num;
		}
	}
	//左上后半段连接右下
	add_num = a[mid_x + 1][mid_y] - a[mid_x][mid_y - 2] + 1;
	xiuzheng_num = a[mid_x][mid_y - 2];
	for(int i = x0; i <= mid_x;i++)
	{
		for(int j = y0; j <= mid_y; j++)
		{
			if(a[i][j] < xiuzheng_num)
				continue;
			a[i][j] = a[i][j] + add_num;
		}
	}
}
void fenzhi(int x0, int y0, int x1, int y1)
{
	if( (x1 - x0 < 11) || (y1 - y0 < 11))
	{
		fuzhi(x0, y0, x1, y1);
	}
	else
	{
		if((x1 - x0 + 1)%4 == 0)
		{
			if((y1 - y0 + 1)%4 == 0)
			{
				fenzhi(x0, y0, (x0 + x1)/2, (y0 + y1)/2);
				fenzhi(x0,(y0 + y1)/2 + 1, (x0 + x1)/2, y1);
				fenzhi((x0 + x1)/2 + 1,(y0 + y1)/2 + 1, x1, y1);
				fenzhi((x0 + x1)/2 + 1, y0, x1, (y0 + y1)/2);
				Link(x0, y0,(x0 + x1)/2, (y0 + y1)/2,x1, y1);
			}
			else
			{
				fenzhi(x0, y0, (x0 + x1)/2, (y0 + y1)/2 - 1);
				fenzhi(x0,(y0 + y1)/2, (x0 + x1)/2, y1);
				fenzhi((x0 + x1)/2 + 1,(y0 + y1)/2, x1, y1);
				fenzhi((x0 + x1)/2 + 1, y0, x1, (y0 + y1)/2 - 1);
				Link(x0, y0,(x0 + x1)/2, (y0 + y1)/2 - 1,x1, y1);
			}
		}
		else
		{
			if((y1 - y0 + 1)%4 == 0)
			{
				fenzhi(x0, y0, (x0 + x1)/2 - 1, (y0 + y1)/2);
				fenzhi(x0,(y0 + y1)/2 + 1, (x0 + x1)/2 - 1, y1);
				fenzhi((x0 + x1)/2,(y0 + y1)/2 + 1, x1, y1);
				fenzhi((x0 + x1)/2, y0, x1, (y0 + y1)/2);
				Link(x0, y0,(x0 + x1)/2 - 1, (y0 + y1)/2,x1, y1);
			}
			else
			{
				fenzhi(x0, y0, (x0 + x1)/2 - 1, (y0 + y1)/2 - 1);
				fenzhi(x0,(y0 + y1)/2, (x0 + x1)/2 - 1, y1);
				fenzhi((x0 + x1)/2,(y0 + y1)/2, x1, y1);
				fenzhi((x0 + x1)/2, y0, x1, (y0 + y1)/2 - 1);
				Link(x0, y0,(x0 + x1)/2 - 1, (y0 + y1)/2 - 1,x1, y1);
			}
		}
	}
}
int main()
{
	ifstream input("input.txt",ios::in);
	ifstream infile6_6("result_6_6.txt",ios::in);
	ifstream infile6_8("result_6_8.txt",ios::in);
	ifstream infile8_8("result_8_8.txt",ios::in);
	ifstream infile8_10("result_8_10.txt",ios::in);
	ifstream infile10_10("result_10_10.txt",ios::in);
	ifstream infile10_12("result_10_12.txt",ios::in);
	ofstream outfile("answer.txt",ios::out);
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
			infile6_6 >> array6_6[i][j];
		for(int j = 0;j < 8; j++)
		{
			infile6_8 >> array6_8[i][j];
			array8_6[j][i] = array6_8[i][j];
		}
	}
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
			infile8_8 >> array8_8[i][j];
		for(int j = 0; j < 10; j++)
		{
			infile8_10 >> array8_10[i][j];
			array10_8[j][i] = array8_10[i][j];
		}
			
	}
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
			infile10_10 >> array10_10[i][j];
		for(int j = 0; j < 12; j++)
		{
			infile10_12 >> array10_12[i][j];
			array12_10[j][i] = array12_10[i][j];
		}
	}
	int hang, lie;
	input >> hang >> lie;
	fenzhi(0,0,hang - 1, lie - 1);
	if(ni)
	{
		opp(0, 0, hang - 1, lie - 1);
	}
	int ans[hang*lie][2];
	for(int i = 0; i < hang; i++)
	{
		for(int j = 0; j < lie; j++)
		{
			ans[a[i][j] - 1][0] = i;
			ans[a[i][j] - 1][1] = j;
		}
	}
	for(int i = 0; i < hang; i++)
	{
		for(int j = 0; j < lie; j++)
		{
			cout << '(' << ans[i*hang + j][0] << ',' << ans[i*hang + j][1] << ')' << ' ';
			outfile << '(' << ans[i*hang + j][0] << ',' << ans[i*hang + j][1] << ')' << ' ';
		}
		cout << endl;
		outfile << endl;
	}	 
	for(int i = 0; i < hang; i++)
	{
		for(int j = 0; j < lie; j++)
		{
			cout << a[i][j] << ' ';
			outfile  << a[i][j] << ' ';
		}
		cout << endl;
		outfile << endl;
	}
	outfile.close();
	return 0;
}
