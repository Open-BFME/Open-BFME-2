// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??1Rva004E9B46@@UAE@XZ @0x004E9BC6 77B. Identity: dtor storing vtable 0x00862874 then member cleanup via 0x004E9B70 and free of +0x0C then base vtable via 0x00506B28.
// Evidence: vtable store at [this]; callees rowed 0x004E9B70 0x00506B28 free 0x00030830; unblocks 0x004E9F52.
// Written against AIWallBuilder.cpp's view: the +0x0C member is the
// vector<BfmeE16> the constructor 0x004E9B46 builds, whose inlined teardown
// is the native null test and direct free; its unwind funclets call the
// folded vector destructor 0x0007FAB3.
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
#pragma comment(linker, "/alternatename:?v1@Rva004E9B46@@UAEXXZ=?update@AIWallBuilder@@QAEXXZ")
#pragma comment(linker, "/alternatename:?v2@Rva004E9B46@@UAEXXZ=?rva004E9B70@Rva004E9B70@@QAEXXZ")
#include "../../Include/GameLogic/Rva00506B1B.h"

class Rva004E9B46 : public Rva00506B1B
{
public:
    int m_08;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
    Rva004E9B46(int x);
    virtual ~Rva004E9B46();
    virtual void v1();
    virtual void v2();
};

class Rva004E9B70
{
public:
	void rva004E9B70();
};

Rva004E9B46::~Rva004E9B46()
{
	((Rva004E9B70 *)this)->rva004E9B70();
}
