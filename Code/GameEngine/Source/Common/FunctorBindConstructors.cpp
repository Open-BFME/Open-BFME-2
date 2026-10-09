// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// The 82 byte-identical 25-byte constructors of BFME's functor-binding family.
//
// WHAT THE BODY IS. Retail:
//
//     mov eax,ecx / mov ecx,[esp+0xC] / mov edx,[esp+4]
//     mov [eax],ecx / mov ecx,[esp+8] / mov [eax+8],edx
//     mov [eax+0xC],ecx / ret 0xC
//
// `mov eax,ecx` with no other use of eax is a constructor returning `this`;
// three dword arguments; stores land at +0x00, +0x08, +0x0C in that order, so
// those are the members in DECLARATION order and +0x04 is a member this
// constructor leaves alone. `ret 0xC` with two stack arguments consumed is
// __thiscall, not __cdecl.
//
// WHY THE ARGUMENTS ARE A POINTER-TO-MEMBER PLUS AN OBJECT. The neighbours of
// the first cluster settle the layout. 0x0050DB20 is the call operator of the
// wrapper that embeds one of these at +0x08:
//
//     mov eax,ecx / mov ecx,[eax+0x14] / add ecx,[eax+8] / jmp [eax+0x10]
//
// -- `this` for the dispatched call is (object + delta) and the code address is
// a third field, which is MSVC's multiple-inheritance pointer-to-member-function
// representation {code, delta} bound to an object. Relative to the embedded
// sub-object at +0x08 those fields sit at +0x00 (object), +0x08 (code) and
// +0x0C (delta) -- exactly the three slots this constructor writes, and exactly
// what `(m_obj, <unused>, m_pmf)` produces when the second argument is an
// 8-byte pointer-to-member occupying stack slots 1 and 2 and the object is the
// third. 0x0050DAE0, the wrapper's copy constructor, corroborates it: vftable
// to +0x00, zero to +0x04, then sixteen bytes copied into +0x08.
//
// WHY THE NAME IS ADDRESS-DERIVED. The image witnesses the framework's
// existence but not this class's name: the only surviving RTTI descriptor for
// it is `.?AVFunctorNotSet@@`, the exception type, and no other "Functor"
// string or symbol appears anywhere in the image or the ledger. The 82 bodies
// are 82 separate template instantiations, kept apart rather than folded, and
// each is named for its own address so the row claims the bytes without
// asserting a class name nobody has recovered.

// ??0Rva0050DA20FunctorBind@@QAE@P8FunctorTarget@@AEXXZPAV1@@Z
// retail 0x004E823F, 25 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/FunctorBindConstructors.cpp
// (reference/open-bfme-1 @ 6d943426). Byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other 81 constructors are omitted.

class __multiple_inheritance FunctorTarget;

typedef void (FunctorTarget::*FunctorMethod)(void);

class Rva0050DA20FunctorBind
{
public:
	Rva0050DA20FunctorBind( FunctorMethod method, FunctorTarget *target );

private:
	FunctorTarget *m_target;
	unsigned int m_unmodelled_04;
	FunctorMethod m_method;
};
Rva0050DA20FunctorBind::Rva0050DA20FunctorBind( FunctorMethod method, FunctorTarget *target )
	: m_target( target ), m_method( method ) {}
// Reference guide: Open-BFME-1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// Common/Rva00192120FunctorInvoker.cpp expresses the member binding dispatch.
// Its void/no-argument prototype is not adopted: native registration ABB87
// supplies callback306EDC which forwards two pointer words through slot1 and
// returns AL. Table BC9584 slot1 targets the complete AD770..AD77B entry.
// Native AD73D stores object+0C and the {code+10 delta+14} member binding.
// This access prefix asserts only those fields and the observed byte return;
// original parser subclass/target names and the preceding12 bytes remain unknown.
class __multiple_inheritance Rva000AD770Target;
typedef unsigned char (Rva000AD770Target::*Rva000AD770Method)(void *, void *);

class Rva000AD770Binding
{
public:
    unsigned char invoke(void *first, void *second);
private:
    unsigned char m_unmodelled_00[0x0C];
    Rva000AD770Target *m_target;
    Rva000AD770Method m_method;
};

unsigned char Rva000AD770Binding::invoke(void *first, void *second)
{
    return (m_target->*m_method)(first, second);
}
