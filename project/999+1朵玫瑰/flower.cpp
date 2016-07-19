#include <windows.h>
#include<graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define WS_EX_LAYERED 0x00080000
#pragma comment( lib, "MSIMG32.LIB")// 引用该库才能使用 TransparentBlt 函数
#pragma comment(lib,"Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )//不显示控制台

#define PI 3.141592653


bool SetWindowTransparent(HWND hwnd,COLORREF crkcolor,BYTE bAlpha,DWORD dwFlags);
void Frametransparent(HWND hwnd,bool frame);
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
void playmusic();
void drawaixin(HDC dstDC,HDC srcDC);
void aixin(HDC dstDC,HDC srcDC);
void shuzi();
void puman(HDC dstDC,HDC srcDC);
void shuaxin();
void meiguihua();
void huaban();
void puman2();

int chang=GetSystemMetrics(SM_CXSCREEN);//1366
int gao=GetSystemMetrics(SM_CYSCREEN);//768
int	rosesize = 500;
int	h = -250;

// 定义结构体
struct DOT
{
double x;
double y;
double z;
double r;	// 红色

double g;	// 绿**(蓝色) 通过 r 计算
};
// 计算点
bool calc(double a, double b, double c, DOT &d)
{
double j, n, o, w, z;

if(c > 60)	 // 花柄
{
d.x = sin(a * 7) * (13 + 5 / (0.2 + pow(b * 4, 4))) - sin(b) * 50;
d.y = b * rosesize + 50;
d.z = 625 + cos(a * 7) * (13 + 5 / (0.2 + pow(b * 4, 4))) + b * 400;
d.r = a * 1 - b / 2;
d.g = a;
return true;
} 

double A = a * 2 - 1;
double B = b * 2 - 1;
if(A * A + B * B < 1)
{
if(c > 37)	 // 叶
{
j = (int(c) & 1);
n = j ? 6 : 4;
o = 0.5 / (a + 0.01) + cos(b * 125) * 3 - a * 300;
w = b * h; 

d.x = o * cos(n) + w * sin(n) + j * 610 - 390;
d.y = o * sin(n) - w * cos(n) + 550 - j * 350;
d.z = 1180 + cos(B + A) * 99 - j * 300;
d.r = 0.4 - a * 0.1 + pow(1 - B * B, -h * 6) * 0.15 - a * b * 0.4 + cos(a + b) / 5 + pow(cos((o * (a + 1) + (B > 0 ? w : -w)) / 25), 30) * 0.1 * (1 - B * B);
d.g = o / 1000 + 0.7 - o * w * 0.000003;
return true;
}
if(c > 32)	 // 花萼
{
c = c * 1.16 - 0.15;
o = a * 45 - 20;
w = b * b * h;
z = o * sin(c) + w * cos(c) + 620;

d.x = o * cos(c) - w * sin(c);
d.y = 28 + cos(B * 0.5) * 99 - b * b * b * 60 - z / 2 - h;
d.z = z;
d.r = (b * b * 0.3 + pow((1 - (A * A)), 7) * 0.15 + 0.3) * b;
d.g = b * 0.7;
return true;
} 

// 花
o = A * (2 - b) * (80 - c * 2);
w = 99 - cos(A) * 120 - cos(b) * (-h - c * 4.9) + cos(pow(1 - b, 7)) * 50 + c * 2;
z = o * sin(c) + w * cos(c) + 700;

d.x = o * cos(c) - w * sin(c);
d.y = B * 99 - cos(pow(b, 7)) * 50 - c / 3 - z / 1.35 + 450;
d.z = z;
d.r = (1 - b / 1.2) * 0.9 + a * 0.1;
d.g = pow((1 - b), 20) / 4 + 0.05;
return true;
}
return false;
} 
void main()
{
	initgraph(chang,gao);
	playmusic();
	setorigin(chang/2,gao/2);//683,384
	setbkcolor(WHITE);
	cleardevice();
	HWND hwnd = GetHWnd();
	Frametransparent(hwnd,0);
	SetWindowTransparent(hwnd,WHITE,100,0x1);
	SetWindowPos(hwnd,HWND_DESKTOP,0,0,0,0,SWP_NOSIZE);
	//加载玫瑰花
	//第一个界面改
	short	*zBuffer;
   int	 x, y, z, zBufferIndex;
   DOT	 dot;

// 初始化	 // 创建绘图窗口
   setbkcolor(WHITE);	 // 设置背景色为白色
   cleardevice();	 // 清屏
// 初始化 z-buffer
   zBuffer = new short[rosesize * rosesize];
   memset(zBuffer, 0, sizeof(short) * rosesize * rosesize);
 
  for(int j = 0; j < 2000 && !_kbhit(); j++)	// 按任意键退出
  {
  for(int i = 0; i < 10000; i++)	 // 减少是否有按键的判断
  if(calc(double(rand()) / RAND_MAX, double(rand()) / RAND_MAX, rand() % 46 / 0.74, dot))
  {
  z = int(dot.z + 0.5);
  x = int(dot.x * rosesize / z - h + 0.5);
  y = int(dot.y * rosesize / z - h + 0.5);
  if (y >= rosesize) continue;

  zBufferIndex = y * rosesize + x;

  if(!zBuffer[zBufferIndex] || zBuffer[zBufferIndex] > z)
{
zBuffer[zBufferIndex] = z;
// 画点
int r = ~int((dot.r * h));	 if (r < 0) r = 0;	if (r > 255) r = 255;
int g = ~int((dot.g * h));	 if (g < 0) g = 0;	if (g > 255) g = 255;
int b = ~int((dot.r * dot.r * -80));	if (b < 0) b = 0;	if (b > 255) b = 255;
putpixel(x + 50, y - 20, RGB(r, g, b));
}
}

Sleep(1);
}
setcolor(0x0000A8);
setfont(35,0,"楷体");
outtextxy(-600,-300,"亲爱的洁莹，我爱你");
Sleep(1000);
outtextxy(-600,-250,"不知道我为什么在等待，直到你的出现");
Sleep(1000);
outtextxy(-600,-200,"我才真正发现，原来我所有的等待，只是为了你的出现");
Sleep(1000);
outtextxy(-600,-150,"你是我的整个世界，我要亲口对你说，我等你好久了");
Sleep(1000);
outtextxy(-600,-100,"我想牵着你的手，直到满头白发的那一天");
Sleep(1000);
outtextxy(-600,-50,"我愿意守护你的生命里的精彩，并陪你一直精彩下去");
Sleep(1000);
outtextxy(-600,0,"我期待带你去所有想去的地方，陪你闹着笑着，历经你生命里的点滴，我期待一生能牵着你走下去．");
Sleep(1000);
Sleep(10000);
cleardevice();
	IMAGE img1;
	loadimage(&img1,"IMAGE",_T("img1"));
	HDC dstDC = GetImageHDC();
    HDC srcDC = GetImageHDC(&img1);
		
	drawaixin(dstDC,srcDC);
	aixin(dstDC,srcDC);
	shuzi();
	puman(dstDC,srcDC);
	shuaxin();
	
	Sleep(1000);
	
	huaban();
	meiguihua();
	setfont(110,0,"楷体");
	outtextxy(-600,-300, _T("给你一个正式的表白，不管"));
	outtextxy(-600,-180, _T("结果怎样，我只要你好"));
	Sleep(10000);

	
}
 
void puman2()
{
	IMAGE img[4];

	loadimage(&img[0],_T("IMAGE"),_T("zise"));
	loadimage(&img[1],_T("IMAGE"),_T("img1"));
	loadimage(&img[2],_T("IMAGE"),_T("juhua"));
	loadimage(&img[3],_T("IMAGE"),_T("fenhong"));
	HDC dstDC=GetImageHDC();
	HDC srcDC;

	int i;
	int x,y;

	srcDC=GetImageHDC(&img[1]);
	TransparentBlt(dstDC,x,y,100,100,srcDC,0,0,100,100,0x000000);
	

	for(i=0;i<100;i++)
	{	
		srand((unsigned int)time(NULL));
		int count=fabs(rand()%4);
		x=rand()%chang-chang/2;
		y=rand()%gao-gao/2;
		switch (count)
		{
			case 0:	
			{
				srcDC=GetImageHDC(&(img[0]));
				TransparentBlt(dstDC,x,y,500,500,srcDC,0,0,500,500,0x000000);
				FlushBatchDraw();
				break;
			}
			case 1:
			{
				srcDC=GetImageHDC(&img[1]);
				TransparentBlt(dstDC,x,y,100,100,srcDC,0,0,100,100,0x000000);
				FlushBatchDraw();
				break;
			}
			case 2:
			{
				srcDC=GetImageHDC(&img[2]);
				TransparentBlt(dstDC,x,y,200,200,srcDC,0,0,200,200,0x000000);
				FlushBatchDraw();
				break;
			}
			case 3:
			{
				srcDC=GetImageHDC(&img[3]);
				TransparentBlt(dstDC,x,y,200,200,srcDC,0,0,200,200,0x000000);
				FlushBatchDraw();
				break;
			}
		}
		Sleep(100);
	}
}


void huaban()
{
	IMAGE img[7];
	IMAGE img0;
	IMAGE image;
	getimage(&img0,-chang/2,-gao/2,chang,gao);
	loadimage(&img[0],_T("IMAGE"),_T("hua00"));
	loadimage(&img[1],_T("IMAGE"),_T("hua02"));
	loadimage(&img[2],_T("IMAGE"),_T("hua03"));
	loadimage(&img[3],_T("IMAGE"),_T("hua04"));
	loadimage(&img[4],_T("IMAGE"),_T("hua05"));
	loadimage(&img[5],_T("IMAGE"),_T("hua06"));
	loadimage(&img[6],_T("IMAGE"),_T("hua06"));
	HDC h1=GetImageHDC();
	HDC h2;
	int i,j,k;
	srand((unsigned int )time(NULL));
	j=-gao/2;
	while(j<=(gao/2-100))
	{
		putimage(-chang/2,-gao/2,&img0);
		for(i=-chang/2;i<=chang/2;i+=200)
		{
			
			int m=rand()%7;
			m=fabs(m);
			h2=GetImageHDC(&(img[m]));
			TransparentBlt(h1,i,j,200,200,h2,0,0,200,200,0x000000);
			FlushBatchDraw();
		}
		j+=20;
		Sleep(100);
			
	}
	getimage(&image,-chang/2,gao/2-400,chang,400);
	putimage(-chang/2,gao/2-400,&image);
	Sleep(2000);
	
	j=-gao/2;
	while(j<=(gao/2-100))
	{
		putimage(-chang/2,-gao/2,&img0);
		putimage(-chang/2,gao/2-400,&image);
		for(i=-chang/2+50;i<=chang/2;i+=200)
		{
			
			int m=rand()%7;
			m=fabs(m);
			h2=GetImageHDC(&(img[m]));
			TransparentBlt(h1,i,j,200,200,h2,0,0,200,200,0x000000);
			FlushBatchDraw();
		}
		j+=20;
		Sleep(100);		
	}
	getimage(&image,-chang/2,gao/2-400,chang,400);
	putimage(-chang/2,gao/2-400,&image);
	Sleep(2000);

	j=-gao/2;
	while(j<=(gao/2-100))
	{
		putimage(-chang/2,-gao/2,&img0);
		putimage(-chang/2,gao/2-400,&image);
		for(i=-chang/2+100;i<=chang/2;i+=200)
		{
			
			int m=rand()%7;
			m=fabs(m);
			h2=GetImageHDC(&(img[m]));
			TransparentBlt(h1,i,j,200,200,h2,0,0,200,200,0x000000);
			FlushBatchDraw();
		}
		j+=20;
		Sleep(100);		
	}
	
	getimage(&image,-chang/2,gao/2-400,chang,400);
	putimage(-chang/2,gao/2-400,&image);
	Sleep(2000);

	j=-gao/2;
	while(j<=(gao/2-100))
	{
		putimage(-chang/2,-gao/2,&img0);
		putimage(-chang/2,gao/2-400,&image);
		for(i=-chang/2+100;i<=chang/2;i+=200)
		{
			
			int m=rand()%7;
			m=fabs(m);
			h2=GetImageHDC(&(img[m]));
			TransparentBlt(h1,i,j,200,200,h2,0,0,200,200,0x000000);
			FlushBatchDraw();
		}
		j+=20;
		Sleep(80);		
	}
	
	getimage(&image,-chang/2,gao/2-400,chang,400);
	putimage(-chang/2,gao/2-400,&image);
	Sleep(2000);
}
void meiguihua()
{
	IMAGE img,img1;
	IMAGE image;
	loadimage(&img, _T("IMAGE"),_T("meigui1"));	

	HDC dstDC=GetImageHDC();
	HDC srcDC=GetImageHDC(&img);
	
	int i=-chang/2,j;
	while(i<=chang/2)
	{
		for(j=-gao/2;j<=0;j+=10)
		{	
			getimage(&img1,i,j,300,400);
			putimage(-chang,gao/2-400,&img1);

			TransparentBlt(dstDC,i,j,300,400,srcDC,0,0,300,400,0x000000);
			FlushBatchDraw();
			Sleep(100);
			putimage(i,j,&img1);
		}
		TransparentBlt(dstDC,i,j,300,400,srcDC,0,0,300,400,0x000000);
		FlushBatchDraw();
		getimage(&image,-chang,gao/2-400,chang,400);
		i+=200;
	}

	Sleep(7000);
}

void shuaxin()
{
	IMAGE img;
	loadimage(&img,_T("IMAGE"),_T("kongbai"));
	for(int i=-chang/2;i<700;i+=10)
	{
		putimage(i,-gao/2,&img);
		Sleep(70);
	}
	Sleep(3000);
}

void shuzi()
{
	setfont(150,0,"楷体");
	outtextxy(-160,-140, _T("洁莹"));
	Sleep(2000);

}
void drawaixin(HDC dstDC,HDC srcDC)
{
	double i;
	int x;
	int y;
	int R1=340;
	for(i=30;i<=150;i+=5)
	{
		x=-70+340-R1*cos(i*PI/180);
		y=-80+16-R1*sin(i*PI/180);
		TransparentBlt(dstDC, x, y, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
		FlushBatchDraw();
		Sleep(100);	
	}
	TransparentBlt(dstDC,570,-210, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	double j;
	int R2=600;
	for(j=-10;j>=-60;j-=3)
	{
		x=-10+R2*cos(j*PI/180);
		y=-300-R2*sin(j*PI/180);
		TransparentBlt(dstDC, x,y, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
		FlushBatchDraw();
		Sleep(100);
	}
	TransparentBlt(dstDC,290,210, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,260,225, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,230,240, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,200,255, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,170,270, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,140,283, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,110,296, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,80,306, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,50,314, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,20,320, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-10,326, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-40,320, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-70,314, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-100,306, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-130,296, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	TransparentBlt(dstDC,-160,283, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-190,270, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-220,255, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-250,240, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,225, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-310,210, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	for(j=-120;j>=-140;j-=3)
	{
		x=-15+R2*cos(j*PI/180);
		y=-310-R2*sin(j*PI/180);
		TransparentBlt(dstDC, x,y, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
		FlushBatchDraw();
		Sleep(100);
	}
	TransparentBlt(dstDC,-480,70, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-506,50, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-530,30, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-550,10, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-565,-10, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-583,-35, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-598,-60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-608,-85, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-618,-110, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-626,-130, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-634,-150, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-640,-170, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-646,-190, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-644,-210, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	
	for(i=30;i<=150;i+=5)
	{
		x=-340-R1*cos(i*PI/180);
		y=-80+16-R1*sin(i*PI/180);
		TransparentBlt(dstDC, x, y, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
		FlushBatchDraw();
		Sleep(100);	
	}

}
void aixin(HDC dstDC,HDC srcDC)
{
	TransparentBlt(dstDC,-330,-200, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-305,-200, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,-200, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-255,-200, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-230,-200, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,-160, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,-130, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,-100, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,-70, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,-40, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,-10, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280, 20, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-330,60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-305,60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-280,60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-255,60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,-230,60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(500);
	
	TransparentBlt(dstDC,150,-200, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,150,-170, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	
	TransparentBlt(dstDC,150,-140, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,150,-110, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,150,-80, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	
	TransparentBlt(dstDC,150,-50, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,150,-20, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,160,0, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,180,20, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,200,40, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,220,53, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	
	TransparentBlt(dstDC,240,60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,260,60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,280,60, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);

	TransparentBlt(dstDC,300,53, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,320,40, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,340,20, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,360,0, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,370,-20, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,370,-50, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,370,-80, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,370,-110, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,370,-140, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,370,-170, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(100);
	TransparentBlt(dstDC,370,-200, 100,100, srcDC, 0, 0, 100, 100, 0x000000);
	FlushBatchDraw();
	Sleep(500);

	IMAGE img5;
	getimage(&img5,-290,-180,585,328);


	setbkmode(TRANSPARENT);
	IMAGE img3;
	loadimage(&img3,_T("IMAGE"),_T("aixin"));
	putimage(-290,-180,&img3,SRCAND);
	Sleep(2000);
	
	IMAGE img0;
	int i,j;
	for(i=-290,j=-180;i>=-883&&j<=534;i-=10,j+=4)
	{	
		getimage(&img0,i,j,585,328);
		BeginBatchDraw();
		
		putimage(i,j,&img3,SRCAND);
		FlushBatchDraw();
		Sleep(80);
		putimage(i,j,&img0);
	}
	EndBatchDraw();
	putimage(i,j,&img3,SRCAND);
	

	for(i=-290,j=-180;i>=-903&&j>=-534;i-=10,j-=6)
	{
		getimage(&img0,i,j,585,328);
		BeginBatchDraw();
		putimage(i,j,&img3,SRCAND);
		FlushBatchDraw();
		Sleep(80);
		putimage(i,j,&img0);
	}
	EndBatchDraw();
	putimage(i,j,&img3,SRCAND);


	for(i=-290,j=-180;i<=283&&j<=184;i+=10,j+=4)
	{
		getimage(&img0,i,j,585,328);
		BeginBatchDraw();
		putimage(i,j,&img3,SRCAND);
		FlushBatchDraw();
		Sleep(80);
		putimage(i,j,&img0);
	}
	EndBatchDraw();
	putimage(i,j,&img3,SRCAND);
	
	
	for(i=-290,j=-180;i<=273&&j>=-584;i+=11,j-=7)
	{
		getimage(&img0,i,j,585,328);
		BeginBatchDraw();
		putimage(i,j,&img3,SRCAND);
		FlushBatchDraw();
		Sleep(80);
		putimage(i,j,&img0);
	}
	EndBatchDraw();
	putimage(i,j,&img3,SRCAND);
	Sleep(2000);
	putimage(-290,-180,&img5);

	Sleep(2000);
}


void puman(HDC dstDC,HDC srcDC)
{
	int x,y;
	srand((unsigned int) time (NULL));
	for(int i=0;i<1200;i++)
	{
		x=rand()%chang-chang/2-50;
		y=rand()%gao-gao/2-50;
		TransparentBlt(dstDC,x,y,100,100,srcDC ,0,0,100,100,0x000000);
		FlushBatchDraw();
		Sleep(30);
	}
	
	Sleep(1000);
	setbkmode(TRANSPARENT);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight=100;
	f.lfWidth=40;
	settextstyle(&f);
	outtextxy(-150,-200,_T("我爱你"));
	Sleep(1200);
	outtextxy(-200,-60,_T("  MJY"));
	Sleep(1200);
	outtextxy(-240,80,_T("让我来照顾你"));
	Sleep(3000);
}

bool SetWindowTransparent(HWND hwnd,COLORREF crkcolor,BYTE bAlpha,DWORD dwFlags)
{
	HINSTANCE hm=GetModuleHandle(_T("USER32.DLL"));
	if(hm)
	{
		FARPROC fun=GetProcAddress(hm,"SetLayeredWindowAttributes");
		bool (WINAPI *SetLayeredWindowAttributes)(HWND,COLORREF,BYTE,DWORD)=(bool (WINAPI*) (HWND,COLORREF,BYTE,DWORD))fun;

		if(SetLayeredWindowAttributes)
		{
			LONG ret=GetWindowLong(hwnd,GWL_EXSTYLE);
			ret|=WS_EX_LAYERED;
			SetWindowLong(hwnd,GWL_EXSTYLE,ret);
			SetLayeredWindowAttributes(hwnd,crkcolor,bAlpha,dwFlags);
		}
		FreeLibrary(hm);
		return true;
	}
	else
	{
		return false;
	}
}

void Frametransparent(HWND hwnd,bool frame)//去掉边框，只需调用EFrame(0);
{
	long style =GetWindowLong(hwnd,GWL_STYLE);
	if(frame)
	{
		style |= WS_CAPTION;//加上边框
	}
	else
	{
		style &= ~ WS_CAPTION;//去掉边框
	}	
	SetWindowLong(hwnd,GWL_STYLE,style);//设置完成 
}



bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC	hRes	= ::FindResource(NULL, strResName, strResType);
	HGLOBAL	hMem	= ::LoadResource(NULL, hRes);
	DWORD	dwSize	= ::SizeofResource(NULL, hRes);
	
	// 写入文件
	DWORD dwWrite = 0;  	// 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}

void playmusic()
{
	char s[300];
	char tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	strcat(tmpmp3, "playmp3_mu.mp3");
	ExtractResource(tmpmp3, _T("misic"), _T("mu.mp3"));
	sprintf(s, "open \"%s\" alias mymusic", tmpmp3);
	mciSendString(s, NULL, 0, NULL);
	mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);
	//mciSendString("play mymusic repeat",NULL,0,NULL);//
}  