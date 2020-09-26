#include <bits/stdc++.h>
#define MAXN 101

#pragma GCC optimize(3)

#ifdef WIN32
	#include <windows.h>
#endif

using namespace std;

struct coordinate
{
	double x,z;
} loc[MAXN][2],res[MAXN*(MAXN-1)/2],circle;

double radius=0,matrix[3][3];
int n,cnt;

coordinate calc()
{
	matrix[0][1]=matrix[1][0]*matrix[2][2]-matrix[2][0]*matrix[1][2];
	matrix[0][2]=matrix[1][1]*matrix[2][0]-matrix[2][1]*matrix[1][0];
	return (coordinate)
	{
		matrix[0][1]/matrix[0][0],matrix[0][2]/matrix[0][0]
	};
}

double get_distance(coordinate a,coordinate b)
{
	return sqrt(pow(a.x-b.x,2)+pow(a.z-b.z,2));
}

bool In_Cir(coordinate point)
{
	return get_distance(point,circle)<=radius+0.001;
}

coordinate solve(double A1,double B1,double C1,double A2,double B2,double C2)
{
	if(A1*B2-A2*B1==0) return circle;
	return (coordinate)
	{
		(C1*B2-C2*B1)/(A1*B2-A2*B1),(A1*C2-A2*C1)/(A1*B2-A2*B1)
	};
}

void get_MinCir()
{
	double temp;
	for(int i=1; i<=cnt; i++)
		if(!In_Cir(res[i]))
		{
			circle.x=res[i].x,circle.z=res[i].z,radius=0;
			for(int j=1; j<i; j++)
				if(!In_Cir(res[j]))
				{
					circle.x=(res[i].x+res[j].x)/2.0,circle.z=(res[i].z+res[j].z)/2.0,radius=get_distance(res[i],circle);
					for(int k=1; k<j; k++)
						if(!In_Cir(res[k]))
						{
							circle=solve(2*(res[j].x-res[i].x),2*(res[j].z-res[i].z),pow(res[j].x,2)+pow(res[j].z,2)-pow(res[i].x,2)-pow(res[i].z,2),
							             2*(res[k].x-res[j].x),2*(res[k].z-res[j].z),pow(res[k].x,2)+pow(res[k].z,2)-pow(res[j].x,2)-pow(res[j].z,2));
							radius=get_distance(circle,res[k]);
						}

				}
		}

}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	fstream fin;
	fstream fout;
	fin.open(".\\api-mc l Be StrongHolder.in");
	if(!fin.is_open())
	{
		system("echo.>\"api-mc l Be StrongHolder.in\"");
		exit(-1);
	}
	fout.open(".\\api-mc l Be StrongHolder.ans");
	fin>>n;
	if(n<1)
	{
		fout<<"[IOS/ERR]Invalid input operation: number out of expect!\n";
		exit(-2);
	}
	if(n>100)
	{
		cout<<"[IOS/ERR]Invalid input operation: number out of expect!\n";
		exit(-2);
	}
	for(int i=1; i<=n; i++)
	{
		fin>>loc[i][0].x>>loc[i][0].z>>loc[i][1].x>>loc[i][1].z;
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<i; j++)
		{
			matrix[1][1]=loc[i][0].z-loc[i][1].z;
			matrix[1][2]=loc[i][1].x-loc[i][0].x;
			matrix[2][1]=loc[j][0].z-loc[j][1].z;
			matrix[2][2]=loc[j][1].x-loc[j][0].x;
			matrix[1][0]=loc[i][1].x*loc[i][0].z-loc[i][0].x*loc[i][1].z;
			matrix[2][0]=loc[j][1].x*loc[j][0].z-loc[j][0].x*loc[j][1].z;
			matrix[0][0]=matrix[1][1]*matrix[2][2]-matrix[1][2]*matrix[2][1];
			if(matrix[0][0]==0)continue;
			res[++cnt]=calc();
		}
	random_shuffle(res+1,res+cnt+1);
	get_MinCir();
	fout<<circle.x<<" "<<circle.z<<" "<<radius;
	fout<<flush;
	fout.close();
	return 0;
}
