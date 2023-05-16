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

static bool isTiming=FALSE;
static bool Shine=FALSE;
static bool Display=FALSE;
static int textlen=0;
static int now=-1;
static char text[50];

void MyTextBox()
{
	InitGraphics();
	InitConsole();
	registerKeyboardEvent(KeyboardProcess);
	registerCharEvent(CharEventProcess);
	registerTimerEvent(TimerEventProcess);
	
	if(isTiming) startTimer(1,100);
	isTiming=!isTiming;
	
	if(isTiming) startTimer(1,100);
	else cancelTimer(1);
}

void KeyboardEvent(int key,int event)
{
	static char str[2]={'\0','\0'};
	if(event==KEY_DOWN)
	{
		if(key==VK_DELETE||key==VK_BACK)
		{
			if(now<0) return;
			SetEraseMode(TRUE);
			
			if(Shine&&Display)
			{
				MovePen(GetCurrentX(),GetCurrentY());
				DrawTextString("_");
				MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
			}
			
			str[0]=text[now];
			MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
			DrawTextString(str);
			
			if(now==textlen)
			{
				MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
			}
			else
			{
				string str1,str2;
				str1=SubString(text,now+1,textlen);
				str2=SubString(text,now,textlen);
				SetEraseMode(TRUE);
				DrawTextString(str1);
				SetEraseMode(FALSE);
				MovePen(GetCurrentX()-TextStringWidth(str2),GetCurrentY());
				DrawTextString(str1);
				MovePen(GetCurrentX()-TextStringWidth(str1),GetCurrentY());
			}
			int i;
			for(i=now;i<textlen;i++)
			{
				text[i]=text[i+1];
			}
			text[--textlen]='\0';
			now=now-1;
			SetEraseMode(FALSE);
		}
		else if(key==VK_LEFT)
		{
			if(now<0) return;
			if(Shine&&Display)
			{
				SetEraseMode(TRUE);
				MovePen(GetCurrentX(),GetCurrentY());
				DrawTextString("_");
				SetEraseMode(FALSE);
				MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
			}
			str[0]=text[now--];
			MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
		}
		else if(key==VK_RIGHT)
		{
			if(now>=textlen) return;
			if(Shine&&Dispaly)
			{
			    SetEraseMode(TRUE);
				MovePen(GetCurrentX(),GetCurrentY());
				DrawTextString("_");
				SetEraseMode(FALSE);
				MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
			}
			str[0]=text[++now];
			MovePen(GetCurrentX()+TextStringWidth(str),GetCurrentY());
		}
	}
}

void CharEventProcess(char key)
{
	if(key==VK_BACK||key==VK_DELETE) return;
	if(key=='\r')
	{
		SetEraseMode(TRUE);
		if(Shine&&Display)
		{
			DrawTextString("_");
			MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
		}
		InitConsole();
		printf("%s",text);
		system("pause");
		FreeConsole();
		MovePen(GetCurrentX()-TextStringWidth(text),GetCurrentY());
		DrawTextString(text);
		SetEraseMode(FALSE);
		MovePen(GetCurrentX()-TextStringWidth(text),GetCurrentY());
		textlen=0;
		now=-1;
		text[0]='\0';
	}
	else
	{
		char str[2]={'\0','\0'};
		str[0]=key;
		if(now==textlen-1)
		{
		   text[textlen]=key;
		   textlen++;
		   text[textlen]='\0';
		   DrawTextString(str);
           now++;
		}
		else{
		string Str;
		Str=SubString(text,now+1,textlen);
		SetEraseMode(TRUE);
		DrawTextString(Str);
		SetEraseMode(FALSE);
		MovePen(GetCurrentX()-TextStringWidth(Str),GetCurrentY());
		DrawTextString(str);
		DrawTextString(Str);
		MovePen(GetCurrentX()-TextStringWidth(Str),GetCurrentY());
		textlen++;
		now++;
		int i;
		for(i=textlen;i>=now;i--)
		{
			text[i]=text[i-1];
		}
		text[now]=key;
	}
	if(Shine&&Display)
	{
		SetEraseMode(TRUE);
		MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
		DrawTextString("_");
		MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
		SetEraseMode(FALSE);
		DrawTextString(str);
	}
	else
	{
		MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
		DrawTextString(str);
	}
  }
}

void TimerEventProcess(int timer)
{
	bool mode;
	double px,py;
	if(timer==1)
	{
		if(!Display) return;
		mode=GetEraseMode();
		SetEraseMode(Display);
		DrawTextString("_");
		MovePen(px=GetCurrentX(),py=GetCurrentY());
		if(textlen!=now+1)
		{
			char str[2]={'\0','\0'};
			str[0]=text[now+1];
			SetEraseMode(FALSE);
			DrawTextString(str);
			MovePen(px,py);
		}
		SetEraseMode(mode);
		Display=!Display;
	}
}
