// cl: /DNDEBUG /MD
// ?Rva000A98BACleanup@@YAXXZ @0x000A98BA 34B
// Free singleton destroy: if W3DAptAux::s_renderer non-null call virtual dtor at 0x0011018B then operator delete at 0x0002FD60 and clear with and [m],0.
// Evidence: frameless mov ecx test je; push esi mov esi ecx call the 0x0011018B destructor (rowed ??1Rva00785FD0Renderer@@QAE@XZ); push esi call ??3 mem_ops; and global 0 pop ecx pop esi ret; callers at 0x0006290B 0x000668FC.
class BfmeHub982;
class W3DAptAux
{
	friend void Rva000A98BACleanup();
	static BfmeHub982 *s_renderer;
};
// Storage is owned by W3DAptAuxPreDrawRva000A8F98.cpp at VA 0x00DE6170.
#include <new>

// The destructor at 0x0011018B is rowed as the non-virtual
// ??1Rva00785FD0Renderer@@QAE@XZ (WW3D2/Rva0011018BDestructor.cpp).
#include "../../Include/Common/Rva00785FD0Renderer.h"

void __cdecl Rva000A98BACleanup(void)
{
	if (W3DAptAux::s_renderer == 0)
		return;
	BfmeHub982 *p = W3DAptAux::s_renderer;
	((Rva00785FD0Renderer *)W3DAptAux::s_renderer)->~Rva00785FD0Renderer();
	::operator delete(p);
	W3DAptAux::s_renderer = 0;
}
