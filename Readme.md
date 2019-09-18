![](https://github.com/gudianxiaoshuo/VText/blob/master/demo.png)


���Լ�֮ǰ���ڵ�һЩ������õ��ĺ��Ķ�����������ʾ ����ȡ�£�������������������ʾ���ܡ�

�����ϣ� ������ �ı���--����--��--���� �ṹ��֯

ʵ���ϣ� ���б�������ݽṹ����

�����ϣ� ��ȷ����ÿ���ֵ�λ�ã� �ṩ ������ʾ��������ʾ�� ����ת���� �������� �ȹ���

�Ծ�̬��ķ�ʽ�ṩ��VTextLib

<hr>
�Կ���̨Ϊ���������ڿ���̨����

1) ͷ�ļ�
```cpp 
#include "VHText.h"
using namespace VText;
```
<hr>
2��дһ������ �̳�CTxt
```cpp
	class CTxt :public CBasicTxt
	{
	public:
		void PrintTxtBody(Chunk* pBody);
		virtual	void DispWord(word *pWord) = 0;
	};
```
     ʵ�֣���ʾĳ���ֵĹ���

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
3�������ı�
```cpp
CMyTxt txtCtl;
 
void HorText()
{
	
 
	CTxtBody* pHorBody1 = txtCtl.CreateHorTextBody(36, 7, 2, L"ˮƽ�ı�����1");
	CTxtBody* pHorBody2 = txtCtl.CreateHorTextBody(36, 10, 2, L"ˮƽ�ı�����2");
 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);//������ɫ
 
	txtCtl.PrintTxtBody(pHorBody1);
	txtCtl.PrintTxtBody(pHorBody2);
 
}
```

```cpp
void VerText()
{
	CTxtBody* pVerBody1 = txtCtl.CreateVerTextBody(33, 9, 1, L"��ֱ�ı�����1");
	CTxtBody* pVerBody2 = txtCtl.CreateVerTextBody(52, 9, 1, L"��ֱ�ı�����2");
	CTxtBody* pVerBody3 = txtCtl.CreateVerTextBody(48, 21, 3, L"��ǰ���¹�\n���ǵ���˪\n��ͷ������\n��ͷ˼����");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//������ɫ
	txtCtl.PrintTxtBody(pVerBody1);
	txtCtl.PrintTxtBody(pVerBody2);
	txtCtl.PrintTxtBody(pVerBody3);
}
```

```cpp
void HorVerChange()
{
	CTxtBody* pVerBody = txtCtl.CreateVerTextBody(48, 21, 3, L"��ǰ���¹�\n���ǵ���˪\n��ͷ������\n��ͷ˼����");
	
	txtCtl.HorVerChange(pVerBody);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	txtCtl.PrintTxtBody(pVerBody);
}
```

 ```cpp
void ReSetText()
{
	CTxtBody* pVerBody = txtCtl.CreateVerTextBody(48, 21, 3, L"��ǰ���¹�\n���ǵ���˪\n��ͷ������\n��ͷ˼����");
 
	txtCtl.SetTxt(pVerBody, L"�󽭶�ȥ���Ծ�\nǧ��Ӣ��");
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