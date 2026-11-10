// cl: /DNDEBUG /MD
// BFME2 Apt value constructor at RVA 0x006DCD20 (40 bytes).
// Semantic reference: BFME1 Rva00899560AptValueCtor.cpp; BFME2 stores
// the AptVFT type in the high seven flag bits via the out-of-line initializer.
// Its assertions name AptValue/AptValue.inl and require 0 < type < 47.
// The exact original class name and meaning of the unused second argument
// are unknown. This body is not the DrawableModule constructor.
#include <new.h>
class BfmeAptValue006DCD20
{
    // The same one-slot vftable view Rva006DE2C0Ctors.cpp emits (declared virtual dtor),
    // so the select-any ??_7BfmeAptValue006DCD20 copies agree.
public:
    virtual ~BfmeAptValue006DCD20();
private:
    unsigned int m_flags;
    void setTypeAt006DBBC0(int type);
public:
    BfmeAptValue006DCD20(int type, unsigned int unused);
    BfmeAptValue006DCD20(int type);
};
class AptValue;
#include "../AptValueVector.h"
extern AptValueVector *g_releaseVectorAtE17710; // 0x00E17710
// g_releaseVectorAtE17710: matched references place it at VA 0xe17710 (zero-filled .bss).
AptValueVector * g_releaseVectorAtE17710;
BfmeAptValue006DCD20::BfmeAptValue006DCD20(int type, unsigned int)
{
    setTypeAt006DBBC0(type);
    m_flags = (m_flags & 0xFE000011u) | 0x10u;
}
// ??0BfmeAptValue006DCD20@@QAE@H@Z @0x006DCCC0 87B. Single-int ctor that marks
// defined bits and conditionally registers in the release vector.
// Evidence: stores vtable 0x008EAED0; calls rowed setTypeAt006DBBC0 and rowed
// AptValueVector::rva006E6C00 via global at 0x00E17710; callers pass type
// constants (e.g. 9 at 0x006D6519); types 0x1c/0x2b/0x2c clear releaseAtEnd.
// ?rva006DCCC0 naming would hide the proven class; this keeps the ctor family.
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline BfmeAptValue006DCD20::BfmeAptValue006DCD20(int type)
{
    setTypeAt006DBBC0(type);
    m_flags = (m_flags & 0xFE000035u) | 0x30u;
    if (type == 0x1c || type == 0x2b || type == 0x2c)
        m_flags &= ~4u;
    else {
        m_flags |= 4u;
        g_releaseVectorAtE17710->rva006E6C00(reinterpret_cast<AptValue *>(this));
    }
}

// ?bfmeAnchorBfmeAptValue006DCD20 absent-from-retail
void *bfmeAnchorBfmeAptValue006DCD20(void *where, int type)
{
	return new (where) BfmeAptValue006DCD20(type);
}


// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
