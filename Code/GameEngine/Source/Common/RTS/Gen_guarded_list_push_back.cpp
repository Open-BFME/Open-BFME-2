// cl: -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/RTS
// stlport
// ?m@Gen_00581350@@QAEXPAX@Z
// retail 0x002007A7, 23 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/RTS/Gen_guarded_list_push_back.cpp
// (reference/open-bfme-1 @ 6d943426). Compiled /Os the donor body is
// byte-identical to retail once relocations are masked (unique hit on unclaimed
// .text). Only the placed body is defined here; the donor's other five
// definitions are omitted.
//
// The guarded push_back, over a _STL::list of 4-byte elements:
//
//     if (x == NULL) return;  m_list.push_back(x);
//
// The list sits at this+0x08, which the class's two pad words establish: retail
// reaches it with `add ecx, 8` immediately before the insert call. The lever
// that makes this shape reproducible is _STLP_NO_EXCEPTIONS; see
// ResourceGatheringManager_addSupply.cpp in this directory for the mechanism.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

// Native 2007B6 calls 5548F, not the other list<void*> body at 526103.
// This external ABI view names only the observed 4-byte element append.
// The complete 26-byte provider is already rowed as list<int>::push_back;
// its native insert target differs from the other pointer-list instance.
class Rva0005548FNativeList { public: void append(void *const &value); };
#pragma comment(linker, "/alternatename:?append@Rva0005548FNativeList@@QAEXABQAX@Z=?push_back@?$list@HV?$allocator@H@_STL@@@_STL@@QAEXABH@Z")

// ?m@Gen_00581350@@QAEXPAX@Z  -- list at this+0x08
struct Gen_00581350
{
	void m(void *x);
	void *m_slice_vtbl;
	void *m_slice_word1;
	_STL::list<void *> m_list;
};

void Gen_00581350::m(void *x)
{
	if (x == NULL)
		return;

	reinterpret_cast<Rva0005548FNativeList *>(&m_list)->append(x);
}
