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

void DrawLogInUI(double cx,double cy);//������ui 
void MouseEventProcess(int x, int y, int button, int event);//����¼� 
void Main()
{
	InitGraphics();//��ʼ������ 
	void InitGUI();//��ʼ��ui��������֪����ʲô�ã� 
	double cx,cy;
	cx = GetWindowWidth()/2;
	cy = GetWindowHeight()/2;//ȡ�����е� 
	DrawLogInUI(cx,cy);//��������ui 
	registerMouseEvent(MouseEventProcess);
}

void DrawLogInUI(double cx,double cy)
{
	DisplayClear();
	MovePen(cx,cy+2);
	DrawTextString("��¼����");
	MovePen(cx-2,cy+0.5);
	DrawTextString("�˺�");
	MovePen(cx-2,cy-0.5);
	DrawTextString("����");
	textbox(2,cx-1,cy+0.3,3,0.5,"insert account",20);
	textbox(2,cx-1,cy-0.8,3,0.5,"insert password",20);//���ϴ����������� 
	if(button(1,cx,cy-2,1,0.5,"ȷ��"))
	{
		//DisplayClear();
		//MovePen(cx+1,cy);
		//DrawArc(1,0,360);�����ڰ���ȷ����Ӧ��ʵ�ֵĴ��� 
		
	}
}
void MouseEventProcess(int x, int y, int button, int event)//����ûд�Ե�����¼����� 
{
	uiGetMouse(x,y,button,event);
	double cx = GetWindowWidth()/2, cy = GetWindowHeight()/2;/*�е�����*/
	double mx,my;
	int isLogIn=0;//�ж��Ƿ���ȷ�� 
	switch(event)
	{
		case BUTTON_DOWN:
			mx=GetMouseX();my=GetMouseY(); 
			if(button==LEFT_BUTTON&&mx<cx+1&&mx>cx&&my<cy-1.5&&my>cy-2)//�жϵ���Ƿ���button��Χ 
			{
				isLogIn=1;
			}
		case BUTTON_UP:
			if(button==LEFT_BUTTON&&isLogIn==1) DisplayClear();//̧����������� 
		/*default:
			DrawLogInUI(cx,cy);*/
	}
	/*if(isLogIn==1)
	{
	DisplayClear();
	MovePen(cx,cy);
	DrawTextString("ɶ��");
	}*/
	DrawLogInUI(cx,cy);
} 
