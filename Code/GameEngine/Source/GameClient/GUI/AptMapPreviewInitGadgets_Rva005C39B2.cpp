// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
//
// ??0FunctorBindingSingle@@QAE@P8FunctorTargetSingle@@AEXXZPAV1@@Z
// retail 0x005C39B2, 18 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/GUI/AptMapPreviewInitGadgets.cpp
// (reference/open-bfme-1 @ 6d943426). Recompiled /Os it is byte-identical to
// retail once relocations are masked (unique hit on unclaimed .text). Only the
// placed body is defined here; the donor's other definition is omitted.
//
//   005C39B2  8b c1              mov eax, ecx          ; return this
//   005C39B4  8b 4c 24 08        mov ecx, [esp+8]      ; target
//   005C39B8  89 08              mov [eax], ecx        ; m_target = target
//   005C39BA  8b 4c 24 04        mov ecx, [esp+4]      ; method
//   005C39BE  89 48 04           mov [eax+4], ecx      ; m_method = method
//   005C39C1  c2 08 00           ret 8
//
// with 0x005C39B1 (`ret`) immediately before it, so the boundary is proven.
// The single pointer-sized load per field is a 4-byte `void (T::*)()`, so the
// method pointer carries no vtable-offset adjustment: the null single-inheritance
// base class the donor uses costs the field nothing.

class __single_inheritance FunctorTargetSingle
{
};

typedef void (FunctorTargetSingle::*FunctorMethodSingle)(void);

struct FunctorBindingSingle
{
	FunctorBindingSingle(FunctorMethodSingle method, FunctorTargetSingle *target);

	FunctorTargetSingle *m_target;
	FunctorMethodSingle m_method;
};

// Defined out of line on purpose: an in-class definition is implicitly inline,
// and MSVC 7.1 does not emit an inline member this TU never calls, so the body
// would be missing from the object and the byte gate would have nothing to
// compare. The emitted code is the same either way.
FunctorBindingSingle::FunctorBindingSingle(FunctorMethodSingle method, FunctorTargetSingle *target)
	: m_target(target), m_method(method)
{
}