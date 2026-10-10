// cl: /DNDEBUG /MD /EHsc
// ??1Rva001095B2@@UAE@XZ @0x001095B2 94B
// Sibling of the rowed Rva00109610Dtor.cpp over the same base (base vtable
// 0x007CEFA0, modelled there as W3DProjectedShadow with an inline virtual
// dtor). Derived vtable 0x007CF9F4 { rowed ??_G 0x0010B9C9, ... }. The body
// destroys the two owned polymorphic objects at +0x58 and +0x5C (slot-0 call
// with 0 then the rowed operator delete 0x0002FD60, the deleteInstance
// spelling used by the rowed SidesList_sidesInfo.cpp) and resets to the base
// vtable; EH state 0 covers the base subobject. Caller ??_G 0x0010B9C9.

class Rva001095B2Owned
{
public:
	virtual void *deleteInstance(int pool);
};

// Base vtable 0x007CEFA0 is BfmeShadowBufferOwnerBase's (slot 0 is the rowed
// ??_GBfmeShadowBufferOwnerBase 0x000EFAD2); this class, with vtable 0x007CF9F4,
// is the W3DProjectedShadow that W3DProjectedShadowManager 0x0010C2D5 creates.
#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/Shadow/BfmeShadowPrefix.h"

class Rva001095B2 : public BfmeShadowBufferOwnerBase
{
public:
	virtual ~Rva001095B2();

private:
	// BfmeShadowBufferOwnerBase fills +0x00..+0x57
	Rva001095B2Owned *m_58; // +0x58
	Rva001095B2Owned *m_5C; // +0x5C
};

Rva001095B2::~Rva001095B2()
{
	::operator delete(m_58 ? m_58->deleteInstance(0) : 0);
	::operator delete(m_5C ? m_5C->deleteInstance(0) : 0);
}
