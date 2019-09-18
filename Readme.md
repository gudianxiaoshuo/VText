![](https://github.com/gudianxiaoshuo/VText/blob/master/demo.png)


将自己之前折腾的一些软件中用到的核心东西：文字显示 ，提取下，提炼出基本的文字显示功能。

整体上， 文字以 文本体--段落--行--文字 结构组织

实现上， 以列表进行数据结构操作

功能上， 精确控制每个字的位置， 提供 横排显示、竖排显示、 横竖转换、 重置文字 等功能

以静态库的方式提供，VTextLib

<hr>
以控制台为例（不限于控制台）：

1) 头文件
```cpp 
#include "VHText.h"
using namespace VText;
```
<hr>
2）写一个子类 继承CTxt
```cpp
	class CTxt :public CBasicTxt
	{
	public:
		void PrintTxtBody(Chunk* pBody);
		virtual	void DispWord(word *pWord) = 0;
	};
```
     实现，显示某个字的功能

```cpp
     class CMyTxt :public CTxt
{
public:
 
	void DispWord(word *pWord)
	{
 
 
		Chunk* pChunk = pWord->Parent;
		Chunk* pBody = GetChunkBody(pChunk);
 
		int numPre = GetPreBrotherNum(pChunk->Parent);
		int x = 0;
		int y = 0;
 
		if (pBody->bVertical)
		{
			x = pWord->Left;// pBody->Left - numPre * 2 - 1; 
			y = pWord->Top;
		}
		else{
 
			int nNumPreWords = GetPreBrotherNum(pWord);
			x = pWord->Left; //pChunk->Left + nNumPreWords * 2; 
			y = pWord->Top;
		}
 
 
 
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
 
		COORD pos = { x, y };
		SetConsoleCursorPosition(hOut, pos);
		setlocale(LC_ALL, "chs");
		wprintf(L"%s", pWord->Str);
	}
 
 
 
};
```
<hr>
3）创建文本
```cpp
CMyTxt txtCtl;
 
void HorText()
{
	
 
	CTxtBody* pHorBody1 = txtCtl.CreateHorTextBody(36, 7, 2, L"水平文本测试1");
	CTxtBody* pHorBody2 = txtCtl.CreateHorTextBody(36, 10, 2, L"水平文本测试2");
 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);//设置蓝色
 
	txtCtl.PrintTxtBody(pHorBody1);
	txtCtl.PrintTxtBody(pHorBody2);
 
}
```

```cpp
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
```

```cpp
void HorVerChange()
{
	CTxtBody* pVerBody = txtCtl.CreateVerTextBody(48, 21, 3, L"床前明月光\n疑是地上霜\n举头望明月\n低头思故乡");
	
	txtCtl.HorVerChange(pVerBody);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	txtCtl.PrintTxtBody(pVerBody);
}
```

 ```cpp
void ReSetText()
{
	CTxtBody* pVerBody = txtCtl.CreateVerTextBody(48, 21, 3, L"床前明月光\n疑是地上霜\n举头望明月\n低头思故乡");
 
	txtCtl.SetTxt(pVerBody, L"大江东去浪淘尽\n千古英雄");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	txtCtl.PrintTxtBody(pVerBody);
}
```
```cpp
int _tmain(int argc, _TCHAR* argv[])
{
	HorText();
	VerText();
 
	
	//ReSetText();
 
	getchar();
	
 
	return 0;
 
}
```