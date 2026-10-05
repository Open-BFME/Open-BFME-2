// cl: /O1 /DNDEBUG /MD /GX /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ??1Rva000C9A12@@QAE@XZ @0x000C9A12 63B: vector<RefCountPtr<TextureClass>>
// destructor in the RvaVectorDtorFamily 63B shell shape (unwind-only EH, no
// try/catch per re_attempts 8763/9472): range-Destroy call plus free plus
// epilog. Binds the rowed provider Rva000C99F9Destroy at 0x000C99F9 (25B,
// RefCountPtrTextureDestroyRange.cpp; stride 4 via rowed 0x17098D) instead
// of emitting a duplicate. Retail bytes at 0xC9A12 match the family shell
// verbatim (EH prolog 0x629188, Destroy call, free 0x30830). Prior Gen_
// attempt hit the EH wall with the template-vector try-catch shape; the
// Rva-style unwind-only shell closed C7720 first try and is reused here.
// W3D lane: callee of W3DLaserDraw 0xC9B1D per symbols pin 4318; element
// identity is the rowed RefCountPtr<TextureClass> (4B stride), never opaque.

#include "../../../../reference/shims/bfmestreak/ref_ptr.h"

class TextureClass;

extern "C" void __cdecl free(void *block);

template <class E> struct RvaVectorFamilyBase
{
	E *m_start;
	E *m_finish;
	E *m_endOfStorage;
	~RvaVectorFamilyBase()
	{
		if (m_start)
			free(m_start);
	}
};

void __cdecl Rva000C99F9Destroy(RefCountPtr<TextureClass> *first,
                               RefCountPtr<TextureClass> *last);

// ??1Rva000C9A12@@QAE@XZ @0x000C9A12 63B -> ?Rva000C99F9Destroy@@YAXPAV?$RefCountPtr@VTextureClass@@@@0@Z
struct Rva000C9A12 : RvaVectorFamilyBase<RefCountPtr<TextureClass> >
{
	~Rva000C9A12();
};

Rva000C9A12::~Rva000C9A12()
{
	Rva000C99F9Destroy(m_start, m_finish);
}
