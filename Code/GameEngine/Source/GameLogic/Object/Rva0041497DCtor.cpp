// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0Rva0041497D@@QAE@XZ, retail 0x0041497D, 47 bytes. Default ctor with two
// bases: BFME2NativeNetwork via rowed baseConstruct 0x001B4E63 (+0..+B),
// Snapshot at +0xC via shared header (base vtable g_00BBB554 then derived
// g_00C3A0AC), own vtable g_00C3A0BC at +0, vector<BfmeE16> at +0x10 via
// rowed Vector_base 0x00211E58 with stack allocator temp. Evidence: leaf
// packet calls rowed bodies; layout mirrors Rva001F092ACtor (same base plus
// vector) and sibling Rva00414932Dtor; caller at 0x0022FC4C.
#include <vector>

#include "Common/Snapshot.h"

struct BfmeE16 { float x; float y; float z; float w; };

class __declspec(novtable) BFME2NativeNetwork
{
public:
	BFME2NativeNetwork();
	virtual ~BFME2NativeNetwork();
	void baseConstruct() throw();
private:
	virtual void unused() = 0;
	char m_flag;
	int m_value;
};

// ??0BFME2NativeNetwork@@QAE@XZ present-unmatched
__forceinline BFME2NativeNetwork::BFME2NativeNetwork()
{
	baseConstruct();
}

class Rva0041497D : public BFME2NativeNetwork, public Snapshot
{
public:
	Rva0041497D();
private:
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec10;
};

Rva0041497D::Rva0041497D()
{
}
