// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// ?release@Rva009706B0@@QAEXXZ
// retail 0x0017FED0, 32 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S3DeleteOwnedMemberAndClear.cpp
// (reference/open-bfme-1 @ 6d943426), which recompiled /Os emits this body
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's other
// five are omitted.
//
// The donor's evidence for this shape, carried over: the destructor is reached
// by a direct call, not through a vtable slot and not through a `??_G` scalar
// deleting destructor, so the pointee's destructor is non-virtual -- `delete p`
// on a polymorphic type would have gone indirect. operator delete takes the raw
// pointer with a cdecl `add esp,4`, the ordinary global one, not a pool
// overload. Two registers are preserved across the pair of calls because both
// `this` and the loaded pointer outlive them.
//
// This row is the UNGUARDED spelling: the `je` lands on the zero-store, so the
// store is unconditional and the source reads `delete m_owned; m_owned = 0;`.
// (Rva00695D60 in the donor jumps PAST the store, which is the guarded form.)
//
// IDENTITY IS NOT RECOVERED. The name is address-derived, carried from the
// donor.

// CriticalSectionClass::LockClass is a real header type (mutex.h); the local
// stand-in classes below are only for the un-identified destructors.
#include "../../../Libraries/Source/WWVegas/WWLib/mutex.h"

#define S3_OWNED_CALLEE_NAMED( NAME )                                     \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
	};

#define S3_DELETE_AND_CLEAR( NAME, CALLEE, OFFSET )                       \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void release();                                                   \
		char m_lead[ OFFSET ];                                            \
		CALLEE *m_owned;                                                  \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		delete m_owned;                                                   \
		m_owned = 0;                                                      \
	}

S3_OWNED_CALLEE_NAMED( HLodDefClass )

// @?release@Rva009706B0@@QAEXXZ 0x0017FED0
S3_DELETE_AND_CLEAR( Rva009706B0, HLodDefClass, 20 )