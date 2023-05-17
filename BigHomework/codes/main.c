#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "imgui.h" 

void DrawLogInUI(double cx,double cy);//主界面ui 
void MouseEventProcess(int x, int y, int button, int event);//鼠标事件 
void Main()
{
	InitGraphics();//初始化界面 
	void InitGUI();//初始化ui工作（不知道有什么用） 
	double cx,cy;
	cx = GetWindowWidth()/2;
	cy = GetWindowHeight()/2;//取界面中点 
	DrawLogInUI(cx,cy);//画主界面ui 
	registerMouseEvent(MouseEventProcess);
}

void DrawLogInUI(double cx,double cy)
{
	DisplayClear();
	MovePen(cx,cy+2);
	DrawTextString("登录界面");
	MovePen(cx-2,cy+0.5);
	DrawTextString("账号");
	MovePen(cx-2,cy-0.5);
	DrawTextString("密码");
	textbox(2,cx-1,cy+0.3,3,0.5,"insert account",20);
	textbox(2,cx-1,cy-0.8,3,0.5,"insert password",20);//以上代码正常运行 
	if(button(1,cx,cy-2,1,0.5,"确定"))
	{
		//DisplayClear();
		//MovePen(cx+1,cy);
		//DrawArc(1,0,360);本来在按下确定后应该实现的代码 
		
	}
}
void MouseEventProcess(int x, int y, int button, int event)//好像没写对的鼠标事件代码 
{
	uiGetMouse(x,y,button,event);
	double cx = GetWindowWidth()/2, cy = GetWindowHeight()/2;/*中点坐标*/
	double mx,my;
	int isLogIn=0;//判断是否点击确定 
	switch(event)
	{
		case BUTTON_DOWN:
			mx=GetMouseX();my=GetMouseY(); 
			if(button==LEFT_BUTTON&&mx<cx+1&&mx>cx&&my<cy-1.5&&my>cy-2)//判断点击是否在button范围 
			{
				isLogIn=1;
			}
		case BUTTON_UP:
			if(button==LEFT_BUTTON&&isLogIn==1) DisplayClear();//抬起左键：清屏 
		/*default:
			DrawLogInUI(cx,cy);*/
	}
	/*if(isLogIn==1)
	{
	DisplayClear();
	MovePen(cx,cy);
	DrawTextString("啥比");
	}*/
	DrawLogInUI(cx,cy);
} 
