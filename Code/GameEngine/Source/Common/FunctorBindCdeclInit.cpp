// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// The byte-identical 25-byte __cdecl siblings of the functor-bind constructor
// family in game/GameEngine/Source/Common/FunctorBindConstructors.cpp.
//
// WHAT THE BODY IS. Retail:
//
//     mov eax,[esp+4] / mov ecx,[esp+0x10] / mov edx,[esp+8] / mov [eax],ecx
//     mov ecx,[esp+0xC] / mov [eax+8],edx / mov [eax+0xC],ecx / ret
//
// A bare `ret` with four dword slots consumed is __cdecl -- __stdcall would be
// `ret 0x10` and __thiscall `ret 0xC`. The first slot is the object: eax is
// loaded from it and every store is based on eax. The remaining three land at
// +0x00, +0x08 and +0x0C, in the argument order 4th, 2nd, 3rd.
//
// WHY IT IS THE SAME FUNCTION AS THE __thiscall FAMILY. Put the two side by
// side with `this` counted as slot zero:
//
//     0x0050DA20 (__thiscall)  this=ecx  a=[esp+4]  b=[esp+8]  c=[esp+0xC]
//                              [this+0]=c  [this+8]=a  [this+0xC]=b  ret 0xC
//     0x0050DF30 (__cdecl)     this=[esp+4] a=[esp+8] b=[esp+0xC] c=[esp+0x10]
//                              [this+0]=c  [this+8]=a  [this+0xC]=b  ret
//
// Identical member-to-argument mapping, identical skipped slot at +0x04, one
// argument slot of shift. So the arguments are an 8-byte multiple-inheritance
// pointer-to-member-function occupying two slots and an object pointer, and
// the three stores are {object at +0x00, code at +0x08, delta at +0x0C}.
//
// WHY IT IS NOT SPELLED AS A CONSTRUCTOR. It cannot be one. MSVC 7.1 forces
// __thiscall on constructors and silently discards an explicit `__cdecl` on
// one: writing `__cdecl NAME( FunctorMethod, FunctorTarget * )` compiles to
// `??0NAME@@QAE@...` and emits the 0x0050DA20 bytes, not these. What does emit
// these -- on the first spelling, and equally from a `__cdecl` member function
// -- is a free __cdecl function taking the object as its first argument, which
// is what is written here because it is the plainest C++ that asserts only what
// the bytes show.
//
// WHY THE NAME IS ADDRESS-DERIVED: as in FunctorBindConstructors.cpp. These
// bodies sit in a dead-COMDAT zone with no surviving class name -- the only
// RTTI descriptor the framework leaves in the image is `.?AVFunctorNotSet@@` --
// and distinct addresses are distinct instantiations that merely compile to the
// same bytes. This row claims the bytes without asserting a class identity.

// ?Rva0050DF30FunctorBindInit@@YAXPAURva0050DF30FunctorBind@@P8FunctorTarget@@AEXXZPAV2@@Z
// retail 0x0050F1B0, 25 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/FunctorBindCdeclInit.cpp
// (reference/open-bfme-1 @ 6d943426). Byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other 41 initialisers are omitted.

class __multiple_inheritance FunctorTarget;

typedef void (FunctorTarget::*FunctorMethod)(void);

struct Rva0050DF30FunctorBind
{
	FunctorTarget *m_target;
	unsigned int m_unmodelled_04;
	FunctorMethod m_method;
};

void __cdecl Rva0050DF30FunctorBindInit( Rva0050DF30FunctorBind *self,
	FunctorMethod method, FunctorTarget *target )
{
	self->m_target = target;
	self->m_method = method;
}