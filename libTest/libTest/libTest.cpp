// libTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VHText.h"
#include"windows.h"

using namespace VText;

class CMyTxt :public CTxt
{
public:

	void DispWord(word *pWord)
	{
		//setlocale(LC_ALL, "chs");
		//wprintf(L"%s  Left:%d   Top:%d \n", pWord->Str, pWord->Left, pWord->Top);


		Chunk* pChunk = pWord->Parent;
		Chunk* pBody = GetChunkBody(pChunk);

		int numPre = GetPreBrotherNum(pChunk->Parent);
		int x = 0;
		int y = 0;

		if (pBody->bVertical)
		{
			x = pWord->Left;// pBody->Left - numPre * 2 - 1; //pWord->Left
			y = pWord->Top;
		}
		else{

			int nNumPreWords = GetPreBrotherNum(pWord);
			x = pWord->Left; //pChunk->Left + nNumPreWords * 2;  // // pWord->Left;//
			y = pWord->Top;
		}



		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD pos = { x, y };
		SetConsoleCursorPosition(hOut, pos);
		setlocale(LC_ALL, "chs");
		wprintf(L"%s", pWord->Str);
	}



};
CMyTxt txtCtl;

void HorText()
{
	

	CTxtBody* pHorBody1 = txtCtl.CreateHorTextBody(36, 7, 2, L"水平文本测试1");
	CTxtBody* pHorBody2 = txtCtl.CreateHorTextBody(36, 10, 2, L"水平文本测试2");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);//设置蓝色

	txtCtl.PrintTxtBody(pHorBody1);
	txtCtl.PrintTxtBody(pHorBody2);

}

void VerText()
{
	CTxtBody* pVerBody1 = txtCtl.CreateVerTextBody(33, 9, 1, L"垂直文本测试1");
	CTxtBody* pVerBody2 = txtCtl.CreateVerTextBody(52, 9, 1, L"垂直文本测试2");
	CTxtBody* pVerBody3 = txtCtl.CreateVerTextBody(48, 21, 3, L"床前明月光\n疑是地上霜\n举头望明月\n低头思故乡");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//设置绿色
	txtCtl.PrintTxtBody(pVerBody1);
	txtCtl.PrintTxtBody(pVerBody2);
	txtCtl.PrintTxtBody(pVerBody3);
}

void HorVerChange()
{
	CTxtBody* pVerBody = txtCtl.CreateVerTextBody(48, 21, 3, L"床前明月光\n疑是地上霜\n举头望明月\n低头思故乡");
	
	txtCtl.HorVerChange(pVerBody);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	txtCtl.PrintTxtBody(pVerBody);
}

void ReSetText()
{
	CTxtBody* pVerBody = txtCtl.CreateVerTextBody(48, 21, 3, L"床前明月光\n疑是地上霜\n举头望明月\n低头思故乡");

	txtCtl.SetTxt(pVerBody, L"大江东去浪淘尽\n千古英雄");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	txtCtl.PrintTxtBody(pVerBody);
}

int _tmain(int argc, _TCHAR* argv[])
{
	HorText();
	VerText();

	
	//ReSetText();

	getchar();
	

	return 0;

}

