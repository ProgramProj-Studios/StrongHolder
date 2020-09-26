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
} loc[MAXN],res[MAXN*(MAXN-1)/2],circle;

double f[MAXN],radius=0;
int n,cnt;
const double pai=3.141592653589793238462643383279502884197169399375105820974944;

coordinate calc(int i,int j)
{
	coordinate result;
	result.x=(loc[i].x*cos(f[i])*sin(f[j])-loc[j].x*sin(f[i])*cos(f[j])+(loc[i].z-loc[j].z)*sin(f[i])*sin(f[j]))/sin(f[j]-f[i]);
	result.z=(loc[j].z*cos(f[i])*sin(f[j])-loc[i].z*sin(f[i])*cos(f[j])-(loc[i].x-loc[j].x)*cos(f[i])*cos(f[j]))/sin(f[j]-f[i]);
	return result;
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
	for(int i = 1;i <= cnt;i ++)
		if(!In_Cir(res[i]))
		{
			circle.x=res[i].x,circle.z=res[i].z,radius=0;
			for(int j = 1;j < i;j ++)
				if(!In_Cir(res[j]))
				{
					circle.x=(res[i].x+res[j].x)/2.0,circle.z=(res[i].z+res[j].z)/2,radius=get_distance(res[i],circle);
					for(int k = 1;k < j;k ++)
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
	fout.open(".\\api-mc l Je StrongHolder.ans");
	fin.open(".\\api-mc l Je StrongHolder.in");
	finput:
	if(!fin.is_open())
	{
		system("echo.>\"api-mc l Je StrongHolder.in\"");
		fin.open(".\\api-mc l Je StrongHolder.in");
		goto finput;
	}
	fin>>n;
	if(n<1)
	{
		#ifdef WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		#endif
		fout<<"[IOS/ERR]Invalid input operation: number out of expect!\n";
		#ifdef WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		#endif
		exit(-2);
	}
	if(n>100)
	{
		#ifdef WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		#endif
		fout<<"[IOS/ERR]Invalid input operation: number out of expect!\n";
		#ifdef WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		#endif
		exit(-2);
	}
	for(int i = 1;i <= n;i ++)
	{
		fin>>loc[i].x>>loc[i].z>>f[i];
		f[i]*=pai/180.0;
	}
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j < i;j ++)
		{
			if(f[i] == f[j])
			{
				continue;
			}
			res[++cnt] = calc(i,j);
		}
	random_shuffle(res+1,res+cnt+1);
	get_MinCir();
	fout<<"x="<<circle.x<<" z="<<circle.z<<" r="<<radius;
	fout<<flush;
	fout.close();
	return 0;
}
