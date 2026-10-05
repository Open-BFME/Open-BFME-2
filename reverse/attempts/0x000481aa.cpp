// ?rva000481AA@@YGXPAV?$StringBase@D@@PBV1@@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
#include <new>

template <typename T> class StringBase
{
	void releaseBuffer();
	void *m_data;

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void set(const StringBase<T> &src);
	void set(const T *str);
	void clear()
	{
		releaseBuffer();
	}
	void concat(const StringBase<T> &str);
	~StringBase();
};

template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct Rva000481AAString8
{
	char *m_text;
	StringBase<char> m_base;
	Rva000481AAString8() : m_text(0) {}
	~Rva000481AAString8() {}
};

struct Rva00DFE144Globals
{
	char m_pad[0x1774];
	int m_1774;
};
extern Rva00DFE144Globals *TheRva00DFE144;

struct BfmeR1025
{
	char *m_bfmeName;
};
char bfmeGo1025F(BfmeR1025 *p);

void __stdcall Rva000481AA(StringBase<char> *dst, const StringBase<char> *src)
{
	int flag = 0;
	Rva000481AAString8 a;
	StringBase<char> b;
	switch (TheRva00DFE144->m_1774)
	{
	case 0:
		a.m_base.set("L");
		break;
	case 1:
		a.m_base.set("M");
		break;
	case 2:
	case 3:
		a.m_base.clear();
		break;
	default:
		break;
	}
	b.set(*src);
	b.concat(a.m_base);
	if (bfmeGo1025F((BfmeR1025 *)&b))
		new (dst) StringBase<char>(b);
	else
		new (dst) StringBase<char>(*src);
	flag = 1;
}
