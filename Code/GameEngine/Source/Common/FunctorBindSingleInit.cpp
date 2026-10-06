// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// The byte-identical 18-byte __cdecl initialisers of BFME's functor-bind family
// whose bound pointer-to-member is a SINGLE-inheritance PMF.
//
// Retail:
//
//     mov eax,[esp+4] / mov ecx,[esp+0xC] / mov edx,[esp+8]
//     mov [eax],ecx / mov [eax+4],edx / ret
//
// A bare `ret` with three dword slots consumed is __cdecl -- __stdcall would be
// `ret 0xC`.  The first slot is the object: eax is loaded from it and both
// stores are based on eax.  The remaining two land at +0x00 and +0x04, in the
// argument order 3rd, 2nd.
//
// WHY IT IS THE SINGLE-INHERITANCE SIBLING OF THE OTHER FAMILY.  Beside the
// __cdecl initialiser at 0x0050DF30:
//
//     0x0050DF30   self=[esp+4] a=[esp+8] b=[esp+0xC] c=[esp+0x10]
//                  [self+0]=c  [self+8]=a  [self+0xC]=b   ret
//     0x00510280   self=[esp+4] a=[esp+8]               c=[esp+0xC]
//                  [self+0]=c  [self+4]=a                 ret
//
// The same member-to-argument mapping with the pointer-to-member collapsed from
// two stack slots to one, and the skipped +0x04 member gone with it: a 4-byte
// single-inheritance PMF instead of the 8-byte {code, delta} pair.  The family's
// own invoker at 0x005102D0 (FunctorBindSingleInvokers.cpp) settles it --
// `mov eax,ecx / mov ecx,[eax+8] / jmp [eax+0xC]` -- i.e. the bound object is
// loaded into ecx and the code address is the very next dword with NO delta
// added, which is what a single-inheritance PMF invoked on a bound object looks
// like.  Relative to the sub-object at +0x08 those fields are +0x00 (object) and
// +0x04 (code) -- the two slots this initialiser writes.
//
// WHY IT IS NOT SPELLED AS A CONSTRUCTOR AND WHY THE NAME IS ADDRESS-DERIVED:
// MSVC 7.1 forces __thiscall on constructors and silently discards an explicit
// `__cdecl` on one; and the image witnesses this framework only through the
// RTTI descriptor `.?AVFunctorNotSet@@`, so no class name has been recovered and
// this row claims the bytes without asserting one.

// ?Rva00510280FunctorBindInit@@YAXPAURva00510280FunctorBind@@P8FunctorTargetSingle@@AEXXZPAV2@@Z
// retail 0x0050F19E, 18 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/FunctorBindSingleInit.cpp
// (reference/open-bfme-1 @ 6d943426). Byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other 23 initialisers are omitted.

class __single_inheritance FunctorTargetSingle;

typedef void (FunctorTargetSingle::*SingleInheritancePmf)(void);

struct Rva00510280FunctorBind
{
	FunctorTargetSingle *m_target;
	SingleInheritancePmf m_method;
};

void __cdecl Rva00510280FunctorBindInit( Rva00510280FunctorBind *binding,
	SingleInheritancePmf method, FunctorTargetSingle *target )
{
	binding->m_target = target;
	binding->m_method = method;
}