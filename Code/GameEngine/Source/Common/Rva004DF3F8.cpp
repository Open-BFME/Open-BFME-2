// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004DF3F8@Rva004DF3F8@@QAEXPAX@Z @0x004DF3F8 32B: list BfmePod12 remove by int at +0x74 via rowed remove; caller jmp at 0x0028BC21 unblocks 0x0028BC17; this list at +0x24
#include <list>

struct BfmePod12
{
	int a[3];
};

inline bool operator==(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] == y.a[0]; }

struct Rva004DF3F8Arg
{
	char m_pad00[0x74];
	int m_74;
};

class Rva004DF3F8
{
public:
	void rva004DF3F8(void *p);
private:
	char m_pad00[0x24];
	_STL::list<BfmePod12> m_24;
};

void Rva004DF3F8::rva004DF3F8(void *p)
{
	if (p == 0)
		return;
	int tmp = ((Rva004DF3F8Arg *)p)->m_74;
	m_24.remove(*(const BfmePod12 *)&tmp);
}
