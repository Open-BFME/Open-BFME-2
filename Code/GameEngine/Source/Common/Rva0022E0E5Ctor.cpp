// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0022E0E5@@QAE@XZ @0x0022E0E5 60B.
// Ctor: base BFME2NativeNetwork via inline ctor calling rowed baseConstruct
// 0x001B4E63, vtable 0x007D7678, list<BfmePod72> member at +0xC via rowed
// _List_base ctor 0x00229924. Layout base 0xC plus list at +0xC; pattern from
// Rva0039225ECtor (baseConstruct then list base). Evidence: rowed callees,
// caller at 0x0022E47A, EH prolog with state 0 around list construction.
#include <list>

struct BfmePod72 { int a[18]; };
inline bool operator==(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] < y.a[0]; }

class __declspec(novtable) BFME2NativeNetwork
{
public:
	BFME2NativeNetwork()
	{
		baseConstruct();
	}
	void baseConstruct();
	virtual ~BFME2NativeNetwork();
private:
	char m_flag04;
	char m_pad05[3];
	int m_value08;
};

class Rva0022E0E5 : public BFME2NativeNetwork
{
public:
	Rva0022E0E5();
	virtual ~Rva0022E0E5();
private:
	_STL::list<BfmePod72, _STL::allocator<BfmePod72> > m_list0C;
};

Rva0022E0E5::Rva0022E0E5()
{
}
