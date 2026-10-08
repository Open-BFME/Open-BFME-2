// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ??0Rva002E1F42@@QAE@XZ @0x002E1F21 33B ctor via baseConstruct plus vtable plus vector base.
// Evidence: thiscall ctor storing vtable 0x00804A84 at +0 then vector_base
// 0x00211E58 at +0xC with allocator temp at [esp+7] after baseConstruct
// 0x001B4E63; dtor 0x002E1F42 frees +0xC then base; prev/next share /O1.
#include <vector>
struct BfmeE16 { float x, y, z, w; };

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase();
private:
	char m_flag;
	int m_value;
};

class Rva002E1F42 : public BFME2NativeNetworkBase
{
public:
	Rva002E1F42();
private:
	_STL::vector<BfmeE16> m_0c;
};

Rva002E1F42::Rva002E1F42()
{
}
