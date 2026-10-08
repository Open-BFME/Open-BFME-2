// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?Rva00113BA0@@YAHPAVGenSlot08@@@Z 0x00306A4E, 16 bytes
//   (the donor's own @-comment cites 0x00113BA0, which is its BFME 1 RVA)
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S2NullCheckedTailDispatch.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. The body is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not. Only this one placed
// body was defined by the initial transfer; the donor's Rva000833E0, Rva00703EF0 and two
// BFME_NULL_CHECKED_TAIL members stay out, so the unmatched-definition gate
// passes.
//
// Shape of the donor family, which is why the body is written as it is:
//
//     mov ecx,<pointer> / test ecx,ecx / je zero
//     mov eax,[ecx] / jmp dword ptr [eax+<SLOT>]
//     zero: xor eax,eax / ret
//
// Control leaves through `jmp`, so the callee's `ret` returns to OUR caller
// and its stack pop is ours; with a bare `ret` on this side both sides are
// __thiscall taking no stack arguments. The zero arm is `xor eax,eax`, the
// full-register form, so the return value is dword-wide.
// IDENTITY IS NOT RECOVERED.  Names are address-derived; the vtable slots ahead
// of the called one exist only to place it and say nothing about the real class.

class GenSlot08
{
public:
	virtual int slot00();
	virtual int slot04();
	virtual int slot08();
};

// @?Rva00113BA0@@YAHPAVGenSlot08@@@Z 0x00306A4E
int Rva00113BA0( GenSlot08 *held )
{
	if( held )
		return held->slot08();
	return 0;
}

// BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 clean donor
// game/GameEngine/Source/Common/S2NullCheckedTailDispatch.cpp supplied the
// nullable first-slot dispatch expression, compiled /O1 /arch:SSE /G7.
// Retail independently proves receiver[0], zero on a null held pointer,
// otherwise a tail jump through its first vtable slot. The whole leaf is
// 0x000E44B1..0x000E44BE; the preceding function's final backward jump ends
// at the start and the following EH-framed function begins at the end.
// Both original classes and the slot's purpose remain unknown. Unsigned
// expresses the returned raw32 bits without asserting source signedness.
class Rva000E44B1Slot0
{
public:
    virtual unsigned dispatch();
};

class Rva000E44B1
{
public:
    unsigned dispatch() const;
    Rva000E44B1Slot0 *m_held;
};

unsigned Rva000E44B1::dispatch() const
{
    Rva000E44B1Slot0 *held = m_held;
    if (held)
        return held->dispatch();
    return 0;
}
