
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

		ChunkLevel Level; //��� 1��2��3     1:body��   2������  3:�ı���

		short FontSize;

		long Left;
		long Top;
		long Right;
		long Bottom;


		long Width;
		long Height;


		wchar_t* pFontName;    // ������  �� ����  ���� ��


		bool  bVertical;//Body�Ǻ��Ż�������
		short nAngle;


		struct chunk* LeftBrother;
		struct chunk* RightBrother;
		struct chunk* UpBrother;
		struct chunk* DownBrother;
		struct chunk* Parent;
		void* Son;


		short nArrange;// 0 Left  1 Center 2 Right     -------���ֶ��뷽ʽ
		short nLineDis;//�о�
		short nPramDis;//�ξ�
		short nIndent;//������������





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


		virtual ~chunk()  //��������Ϊ����������   ����������ָ��ָ���������ʱ  delete ʱ�� Ҳ����ȷ����������
		{




		}



	public:


		int CountOfColumns();
		int CountOfSon();

		//bIncludeLine  �Ƿ�������з�
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
		//ɾ��һ�������е�ĳ���ִ�
		chunk* DeleteChunk(chunk* pChunk);


		void SetChunkFont(chunk *pChunk, TCHAR *pFontName);

		//------------------------------�����--------------------------------
		chunk* InsertChunk(short Type, ChunkLevel Level, short FontSize, int Top, int Right, int Width, int Height, chunk* LeftBrother,
			chunk* RightBrother, chunk* UpBrother, chunk* DownBrother, chunk* Parent, void* Son);


		void UpdateChunk(chunk* pChunk, bool bUpdateParent);


		Word* InsertWord(wchar_t* Str, Word* PreBrother, Word* NextBrother);





		bool bWordChunk();
		//��Chunk�����е���ɾ���� ����Chunk���� CHUNKΪT_WORD����
		void  DeleteAllWordsOfChunk();



		void ReleaseBodySon();
		Word * ReAddOneChar(wchar_t* Str, chunk* pCurChunk, Word* pCurElem);


		chunk* GetColumnChunk(chunk* pChunk);
		chunk* GetLastChunk(chunk* pParentChunk);


		//
		void ToVer();//ת������
		void ToHor();//ת�ɺ���



	} Chunk, ParaChunk, CTxtBody;



	//�ı�������
	class CBasicTxt{
	public:

		Chunk* pCurrentChunk; //��ǰ���BODY ��һ������BODY
		Chunk* pCurBody;
		void* pCurrentElem;
		std::vector<Chunk*> bodyVec;


		Chunk* InsertOrtherBody(int nTop, int nLeft, int nWidth, int nHeight, int nSize, std::wstring fisrtChunkStr = L"", bool bAddSonChunk = true);


		Chunk*  InsertColumn(Chunk* pCurColumn); //���봿��Ĳ��ֿ�
		Chunk*  InsertColumn(); //���봿��Ĳ��ֿ�

		Chunk* InsertChunk(short Type, ChunkLevel Level, Chunk* PreChunk, Chunk *pNextChunk);//����һ���� ����ֵ����ǰһ��ȷ��

		//Type ����T_LAYOUT T_WORD   ��Level �㣻 FontSize��С��           LeftBrother ����һ��     RightBrother:��һ��      
		Chunk* InsertChunk(short Type, ChunkLevel Level, UINT FontSize, int Top, int Right, int Width, int Height, struct chunk* LeftBrother, struct chunk* RightBrother, struct chunk* UpBrother, struct chunk* DownBrother, struct chunk* Parent, void* Son);


		Chunk* InsetSubChunk(Chunk* Chunk_Column, Chunk* pChunk, std::wstring str = _T("")); //�ڲ��ֿ��в����ֿ�

		Chunk * InsertSingleWordChunk(std::wstring str, int nTop, int nLeft, int nWidth, int nHeight);//���뵥һ�ִ�

		Chunk* ReadPramChunk(Chunk* Chunk_Parent, Chunk* Chunk_Brother, std::wstring  parmStr);

		int  GetPreBrotherNum(Chunk* pChunk);
		int  GetPreBrotherNum(word* pWord);
		Chunk* DeleteChunk(Chunk* pChunk);
		void ReleaseChunk(Chunk* pChunk);


		//Str  PRE Next Parent  ����һ����
		Word* InsertWord(wchar_t* Str, Word* PreBrother, Word* NextBrother, Chunk* Parent);

		//��Ӷ����  ParentΪ�մ�   PreBrother    NextBrotherĬ��ΪNULL  ����   ��֮ǰ����L��\r��������ڴ�й¶ ��Ϊ�����û�����ӵ�Parent ��
		Word* AppendWord(std::wstring nStr, std::wstring nStyle, Chunk* Parent, Word* PreBrother);

		ParaChunk*  CreateOneChunk(Chunk* pre, Chunk* next);


		//����ִ� ����ʽ��
		Word* AppendStrToNullChunk(std::wstring nStr, Chunk* Parent, bool bAdd13 = true);//���մ��м����ַ���
		//��������ִ�   �߳���ɾ���ַ�ʱ������⣬��ˣ���������ַ�����ֻ�ı��ַ� ����ɾ���ַ�  ĩβ�ַ�Ĭ��Ϊ\0
		//������ʱ�õ�����Ϊ���������ɶ�ͼ�����в��ϸı�

		void UpdateWords(Chunk* pChunk, bool bParentSize = false);
		void UpdateWord(Word* pWord, bool bParentSize = false);
		void UpdateWordsVertical(Chunk* pChunk);
		void UpdateWordVertical(Word* pWord);
		void UpdateWordsAccordingAngle(Chunk* pChunk);
		void UpdateWordAccordingAngle(Word* pWord, int angle);
		void UpdateSingleChunkWords(Chunk* pChunk);


		void UpdateChunk(Chunk* pChunk, bool bUpdateParent = false);
		void UpdateParentChunk(Chunk* pChunk, bool bUpdateParent = false);

		void UpdateChunkVertical(Chunk* pChunk); //����
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

		Chunk* CreateHorTextBody(int x, int y, int nFontSize = 20, std::wstring str = L"���Ĳ���");
		Chunk* CreateVerTextBody(int x, int y, int nFontSize = 20, std::wstring str = L"���Ĳ���");






		///////


	};

	class CTxt :public CBasicTxt
	{
	public:
		void PrintTxtBody(Chunk* pBody);
		virtual	void DispWord(word *pWord) = 0;
	};
}