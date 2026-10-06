// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?append@Rva00420F0E@@QAEXHHH@Z @0x00420F0E 49B: conditional list append via rowed list<BfmePod12>::push_back 0x00420DF3. Evidence: cmp byte [ecx+0x14] guard plus 12B stack tmp {arg2->+0x74, arg1, arg3 byte} plus add ecx,0x10 plus REL32 to rowed 0x00420DF3; ret 0xC three args.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct BfmePod12
{
	char m_pad[12];
public:
	BfmePod12(const BfmePod12 &);
	~BfmePod12();
};

struct Rva00420F0EPod
{
	int m_a;
	int m_b;
	unsigned char m_c;
	char m_pad[3];
};

struct Rva00420F0EArg2
{
	char m_pad[0x74];
	int m_val74;
};

class Rva00420F0EHost
{
public:
	void append(int a, int b, int c);
private:
	char m_00[0x10];
	_STL::list<BfmePod12> m_list10;
	unsigned char m_14;
};

void Rva00420F0EHost::append(int a, int b, int c)
{
	if (m_14 != 0)
		return;
	Rva00420F0EPod tmp;
	tmp.m_a = ((Rva00420F0EArg2 *)b)->m_val74;
	tmp.m_b = a;
	tmp.m_c = (unsigned char)c;
	m_list10.push_back((const BfmePod12 &)tmp);
}
