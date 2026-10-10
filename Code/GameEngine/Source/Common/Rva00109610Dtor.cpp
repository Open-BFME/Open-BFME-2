// cl: /DNDEBUG /MD /EHsc
// ??1Rva00109610@@UAE@XZ @0x00109610 51B
// Derived dtor sets derived vtable 0x007CFA00 calls rowed base
// W3DProjectedShadow::rva00108951 on same this then restores base vtable
// 0x007CEFA0; caller is ??_G at 0x0010BA83; chain from 0x00108951.
// The base vtable 0x007CEFA0 is BfmeShadowBufferOwnerBase's (its slot 0 is the
// rowed ??_GBfmeShadowBufferOwnerBase 0x000EFAD2). W3DProjectedShadow is the
// sibling class with vtable 0x007CF9F4 (Rva001095B2Dtor.cpp); 0x00108951 is
// rowed under its name, so the call goes through a vtable-free view.
#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/Shadow/BfmeShadowPrefix.h"
class W3DProjectedShadow
{
public:
	void rva00108951();
};
class Rva00109610 : public BfmeShadowBufferOwnerBase
{
public:
	virtual ~Rva00109610();
};
Rva00109610::~Rva00109610()
{
	reinterpret_cast<W3DProjectedShadow *>(this)->rva00108951();
}
