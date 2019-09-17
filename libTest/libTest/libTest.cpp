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




int _tmain(int argc, _TCHAR* argv[])
{
	CMyTxt txtCtl;

	CTxtBody* pHorBody1 = txtCtl.CreateHorTextBody(36, 7, 2, L"QSSS11");
	CTxtBody* pHorBody2 = txtCtl.CreateHorTextBody(36, 19, 2, L"水平文本测试2");

	CTxtBody* pVerBody1 = txtCtl.CreateVerTextBody(36, 9, 1, L"垂直文本测试1");
	CTxtBody* pVerBody2 = txtCtl.CreateVerTextBody(48, 9, 1, L"垂直文本测试2");

	CTxtBody* pVerBody3 = txtCtl.CreateVerTextBody(48, 21, 3, L"床前明月光\n疑是地上霜\n举头望明月\n低头思故乡");
	//txtCtl.SetTxt(pVerBody3, L"床前明月光\n疑是地上霜\n举头望明月\n低头思故乡aa");
	//txtCtl.HorVerChange(pVerBody3);
	//pVerBody3->ToHor();
	//pVerBody3->ToVer();


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);//设置蓝色

	txtCtl.PrintTxtBody(pHorBody1);
	txtCtl.PrintTxtBody(pHorBody2);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//设置绿色
	txtCtl.PrintTxtBody(pVerBody1);
	txtCtl.PrintTxtBody(pVerBody2);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	//txtCtl.SetTxt(pVerBody1, L"abc\n666\n111666\n0000急急急\n呵呵呵呵呵\n日日日");
	txtCtl.PrintTxtBody(pVerBody3);

	//txtCtl.HorVerChange(pHorBody2);
	//txtCtl.PrintTxtBody(pHorBody2);

	getchar();
	return 0;

}

