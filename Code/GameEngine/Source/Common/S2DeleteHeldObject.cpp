// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// ?Rva007889D0@@YAXPAVGen0002AB5D@@@Z
// retail 0x000AB450, 25 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S2DeleteHeldObject.cpp (reference/open-bfme-1 @
// 6d943426), which recompiled /Os emits this body byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other three bodies are omitted.
//
// The donor's evidence for this shape, carried over: the destructor is reached
// by a direct REL32 call, not through the object's vtable, so `delete` here is
// not deleting through a virtual destructor. The free form takes one pointer
// and is __cdecl because the caller pops nothing and the argument sits at
// [esp+4] on entry. The operator delete is 0x00881EB0, pinned as ??3@YAXPAX@Z.
//
// IDENTITY IS NOT RECOVERED. The name is address-derived.

// @?Rva007889D0@@YAXPAVGen0002AB5D@@@Z 0x007889D0
#define BFME_DELETE_ARGUMENT( NAME, CALLEE )                              \
	class CALLEE                                                          \
	{                                                                     \
	public:                                                               \
		~CALLEE();                                                        \
	};                                                                    \
	void NAME( CALLEE *held )                                             \
	{                                                                     \
		delete held;                                                      \
	}

BFME_DELETE_ARGUMENT( Rva007889D0, Gen0002AB5D )