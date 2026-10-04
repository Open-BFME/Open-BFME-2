// cl: -DNDEBUG /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
//
// ?invoke@LoadGameFadeWrapper@@UAEIM_N@Z
// retail 0x00211216, 20 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/GUI/Rva00612160Post.cpp
// (reference/open-bfme-1 @ 6d943426). Recompiled /Os it is byte-identical to
// retail once relocations are masked (unique hit on unclaimed .text). Only the
// placed body is defined here; the donor's other definition is omitted.
//
//   00211216  ff 74 24 08        push dword ptr [esp+8]   ; b, as float
//   0021121A  d9 44 24 08        fld dword ptr [esp+8]    ; after the push
//   0021121E  51                 push ecx                 ; this
//   0021121F  d9 1c 24           fstp dword ptr [esp]     ; a, in place of b
//   00211222  ff 51 08           call dword ptr [ecx+8]   ; the callback
//   00211225  59                 pop ecx                  ; drop the pushed this
//   00211226  59                 pop ecx                  ; drop the pushed b
//   00211227  c2 08 00           ret 8
//
// with 0x00211215 (`00`) immediately before it, so the boundary is proven.
//
// The push/load/store dance is the cdecl float-argument ABI as MSVC 7.1 emits
// it: the caller's two already-stacked arguments are addressed at [esp+8]
// because `this` and one float have been pushed first, and the callee's `this`
// slot at [esp] is reused for the first float. The callee returns the same
// single-slot x87 result the wrapper passes through, so it is an unsigned int
// here and the floats are dropped on return. `call [ecx+8]` is the wrapper's
// own virtual slot 2 -- the m_fn-calling `invoke` the donor declares inline --
// so no static callee is named and nothing needs pinning.

typedef unsigned (__cdecl *FadeCallback)(float, bool);

struct LoadGameFadeSlot
{
	LoadGameFadeSlot(FadeCallback fn) : m_fn(fn) {}
	FadeCallback m_fn;
};

class LoadGameFadeWrapperHead
{
public:
	LoadGameFadeWrapperHead() throw() : m_refCount(0) {}
	virtual ~LoadGameFadeWrapperHead() {}
	int m_refCount;
};

class LoadGameFadeWrapper : public LoadGameFadeWrapperHead
{
public:
	LoadGameFadeWrapper(const LoadGameFadeSlot &slot) throw() : m_slot(slot) {}
	virtual ~LoadGameFadeWrapper() {}
	virtual unsigned invoke(float a, bool b);
	LoadGameFadeSlot m_slot;
};

// Defined out of line on purpose: an in-class definition is implicitly inline,
// and MSVC 7.1 does not emit an inline member this TU never calls, so the body
// would be missing from the object and the byte gate would have nothing to
// compare. The emitted code is the same either way.
unsigned LoadGameFadeWrapper::invoke(float a, bool b)
{
	return m_slot.m_fn(a, b);
}