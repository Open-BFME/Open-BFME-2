// ?rva006D5160@@YA?AVEAStringC@@PBDABV1@@Z
// partial score=0.9605569764 date=2026-10-09
// ?rva006D5160@@YA?AVEAStringC@@PBDABV1@@Z
// partial score=0.9605569764 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);
#pragma intrinsic(memcpy)
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)

class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	static void FreeData(StringDataC *data);

	StringDataC *m_pData;

	EAStringC(const EAStringC &other);
	EAStringC(unsigned int nSize);
 EAStringC(const char* text) {m_pData=0; Assign(text);}
 void Assign(const char* text);
	~EAStringC()
	{
		FreeData(m_pData);
	}
	void SetSize(int size);
	
};

EAStringC rva006D5160(const char *left, const EAStringC &right)
{
 unsigned int size=right.m_pData->m_uSize;
 if(!size)return EAStringC(left);
 unsigned int otherSize=strlen(left);
 if(!otherSize)return right;
 unsigned int total=otherSize+size;
 EAStringC result(total);
 char *text=(char*)result.m_pData+8;
 memcpy(text,left,otherSize);
 memcpy(text+otherSize,(char*)right.m_pData+8,size);
 text[otherSize+size]=0;
 result.SetSize(total);
 result.m_pData->m_uHash=0;
 return result;
}
