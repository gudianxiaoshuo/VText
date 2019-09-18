
#pragma  once
#include<string>
#include <tchar.h>
#include <vector>
#include <stdbool.h>
//
// V1.0


using UINT = unsigned int;



//


namespace VText{


	typedef struct word
	{
		int Left;
		int Top;
		int Right;
		int Bottom;

		short FontSize;

		wchar_t Str[3];

		struct word* PreBrother;
		struct word* NextBrother;
		class chunk* Parent;

		void Init(int Top, int Left, int FontSize, wchar_t* Str, struct word* PreBrother, struct word* NextBrother, struct chunk* Parent);


	}Word;


	enum ChunkLevel {


		Body = 1,
		Paragraph,
		Line
	};


	typedef class chunk
	{
	public:

		ChunkLevel Level; //层次 1、2、3     1:body体   2：段落  3:文本行

		short FontSize;

		long Left;
		long Top;
		long Right;
		long Bottom;


		long Width;
		long Height;


		wchar_t* pFontName;    // 字体名  如 楷体  宋体 等


		bool  bVertical;//Body是横排还是竖排
		short nAngle;


		struct chunk* LeftBrother;
		struct chunk* RightBrother;
		struct chunk* UpBrother;
		struct chunk* DownBrother;
		struct chunk* Parent;
		void* Son;


		short nArrange;// 0 Left  1 Center 2 Right     -------文字对齐方式
		short nLineDis;//行距
		short nPramDis;//段距
		short nIndent;//首行缩进几个





		chunk()
		{


			bVertical = true;

			nAngle = 0;


			nArrange = 0;

			nIndent = 0;
			nLineDis = 0;
			nPramDis = 0;

			pFontName = NULL;



			this->LeftBrother = NULL;
			this->RightBrother = NULL;
			this->UpBrother = NULL;
			this->DownBrother = NULL;
			this->Parent = NULL;
			this->Son = NULL;
		}

		void Init(short Type, ChunkLevel Level, short FontSize, int Top, int Left/*Right*/, int Width, int Height, struct chunk* LeftBrother,
		struct chunk* RightBrother, struct chunk* UpBrother, struct chunk* DownBrother, struct chunk* Parent, void* Son)
		{


			bVertical = true;

			//this->Type = Type;
			this->Level = Level;
			this->FontSize = FontSize;
			this->Top = Top;

			this->Width = Width;
			this->Height = Height;


			this->Left = Left;
			this->Right = Left + Width;

			this->Bottom = Top + Height;



			this->pFontName = NULL;


			this->LeftBrother = LeftBrother;
			this->RightBrother = RightBrother;
			this->UpBrother = UpBrother;
			this->DownBrother = DownBrother;
			this->Parent = Parent;
			this->Son = Son;

		}


		virtual ~chunk()  //基类声明为虚析构函数   这样当基类指针指向的是子类时  delete 时候 也能正确析构掉子类
		{




		}



	public:


		int CountOfColumns();
		int CountOfSon();

		//bIncludeLine  是否包含换行符
		int  CountOfAllWords(bool bIncludeLine = false);
		void CountOfWords(chunk* pChunk, int & nAllWorldCount, bool bIncludeLine = false);






		chunk*  GetChunkBody(chunk *pChunk);

		void* GetFirstElem();

		chunk* GetFirstWordChunk();


		int WidthOfVerticalChunk(chunk* pChunk);
		int WidthOfChunk(chunk* pChunk);

		int HeightOfChunk(chunk* pChunk);
		int HeightOfVerticalChunk(chunk* pChunk);


		void UpdateWordVertical(Word* pWord);

		void UpdateWordsVertical(chunk* pChunk);


		void UpdateChunkVertical(chunk* pChunk);

		void UpdateWord(Word* pWord, bool bParentSize);

		void UpdateWords(chunk* pChunk, bool bParentSize = false);

		void ReleaseChunk(chunk* pChunk);
		//删除一个链表中的某个字串
		chunk* DeleteChunk(chunk* pChunk);


		void SetChunkFont(chunk *pChunk, TCHAR *pFontName);

		//------------------------------插入块--------------------------------
		chunk* InsertChunk(short Type, ChunkLevel Level, short FontSize, int Top, int Right, int Width, int Height, chunk* LeftBrother,
			chunk* RightBrother, chunk* UpBrother, chunk* DownBrother, chunk* Parent, void* Son);


		void UpdateChunk(chunk* pChunk, bool bUpdateParent);


		Word* InsertWord(wchar_t* Str, Word* PreBrother, Word* NextBrother);





		bool bWordChunk();
		//将Chunk下所有的字删除掉 但是Chunk保留 CHUNK为T_WORD类型
		void  DeleteAllWordsOfChunk();



		void ReleaseBodySon();
		Word * ReAddOneChar(wchar_t* Str, chunk* pCurChunk, Word* pCurElem);


		chunk* GetColumnChunk(chunk* pChunk);
		chunk* GetLastChunk(chunk* pParentChunk);


		//
		void ToVer();//转成竖排
		void ToHor();//转成横排



	} Chunk, ParaChunk, CTxtBody;



	//文本控制类
	class CBasicTxt{
	public:

		Chunk* pCurrentChunk; //当前块的BODY 不一定是主BODY
		Chunk* pCurBody;
		void* pCurrentElem;
		std::vector<Chunk*> bodyVec;


		Chunk* InsertOrtherBody(int nTop, int nLeft, int nWidth, int nHeight, int nSize, std::wstring fisrtChunkStr = L"", bool bAddSonChunk = true);


		Chunk*  InsertColumn(Chunk* pCurColumn); //插入纯粹的布局块
		Chunk*  InsertColumn(); //插入纯粹的布局块

		Chunk* InsertChunk(short Type, ChunkLevel Level, Chunk* PreChunk, Chunk *pNextChunk);//插入一个串 其他值根据前一个确定

		//Type 类型T_LAYOUT T_WORD   ；Level 层； FontSize大小，           LeftBrother ：下一个     RightBrother:上一个      
		Chunk* InsertChunk(short Type, ChunkLevel Level, UINT FontSize, int Top, int Right, int Width, int Height, struct chunk* LeftBrother, struct chunk* RightBrother, struct chunk* UpBrother, struct chunk* DownBrother, struct chunk* Parent, void* Son);


		Chunk* InsetSubChunk(Chunk* Chunk_Column, Chunk* pChunk, std::wstring str = _T("")); //在布局块中插入字块

		Chunk * InsertSingleWordChunk(std::wstring str, int nTop, int nLeft, int nWidth, int nHeight);//插入单一字串

		Chunk* ReadPramChunk(Chunk* Chunk_Parent, Chunk* Chunk_Brother, std::wstring  parmStr);

		int  GetPreBrotherNum(Chunk* pChunk);
		int  GetPreBrotherNum(word* pWord);
		Chunk* DeleteChunk(Chunk* pChunk);
		void ReleaseChunk(Chunk* pChunk);


		//Str  PRE Next Parent  插入一个字
		Word* InsertWord(wchar_t* Str, Word* PreBrother, Word* NextBrother, Chunk* Parent);

		//添加多个字  Parent为空串   PreBrother    NextBrother默认为NULL  所以   若之前插入L“\r”则会有内存泄露 因为这个字没有连接到Parent 上
		Word* AppendWord(std::wstring nStr, std::wstring nStyle, Chunk* Parent, Word* PreBrother);

		ParaChunk*  CreateOneChunk(Chunk* pre, Chunk* next);


		//添加字串 及格式化
		Word* AppendStrToNullChunk(std::wstring nStr, Chunk* Parent, bool bAdd13 = true);//往空串中加入字符串
		//添加足量字串   线程中删除字符时会出问题，因此，添加足量字符串，只改变字符 而不删除字符  末尾字符默认为\0
		//画标题时用到，因为标题在生成动图过程中不断改变

		void UpdateWords(Chunk* pChunk, bool bParentSize = false);
		void UpdateWord(Word* pWord, bool bParentSize = false);
		void UpdateWordsVertical(Chunk* pChunk);
		void UpdateWordVertical(Word* pWord);
		void UpdateWordsAccordingAngle(Chunk* pChunk);
		void UpdateWordAccordingAngle(Word* pWord, int angle);
		void UpdateSingleChunkWords(Chunk* pChunk);


		void UpdateChunk(Chunk* pChunk, bool bUpdateParent = false);
		void UpdateParentChunk(Chunk* pChunk, bool bUpdateParent = false);

		void UpdateChunkVertical(Chunk* pChunk); //竖排
		void FlashChunkVertical(Chunk* pChunk);
		void FlashChunk(Chunk* pChunk, bool bUpdateParent = false);

		int HeightOfVerticalChunk(Chunk* pChunk);
		int WidthOfVerticalChunk(Chunk* pChunk);
		int HeightOfChunk(Chunk* pChunk);
		int WidthOfChunk(Chunk* pChunk);

		void HorVerChange(Chunk* pChunkBody);


		Chunk* GetChunkBody(Chunk *pChunk);
		void ChangeBodyPosition(int nTop, int nLeft, Chunk * pCurBody);
		void SetTxt(Chunk* pBody, std::wstring str);
		void EmptyText(Chunk* pBody);
		void ReadStrToBody(Chunk* pBody, std::wstring str);



	public:
		//

		Chunk* CreateHorTextBody(int x, int y, int nFontSize = 20, std::wstring str = L"横文测试");
		Chunk* CreateVerTextBody(int x, int y, int nFontSize = 20, std::wstring str = L"竖文测试");






		///////


	};

	class CTxt :public CBasicTxt
	{
	public:
		void PrintTxtBody(Chunk* pBody);
		virtual	void DispWord(word *pWord) = 0;
	};
}