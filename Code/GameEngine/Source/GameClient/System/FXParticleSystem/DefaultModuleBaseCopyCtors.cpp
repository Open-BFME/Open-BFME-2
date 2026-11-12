// cl: /O2 /Os /DNDEBUG /MD /EHs-c-
// Default module base copy constructors (retail 0x003AEEB3 cluster).
// The shared three-vtable base: smart-pointer head (vptr 0x00C1B590,
// 12-byte member copied through the rowed 0x0004CC19 body, int at +0x10)
// plus two vtable-only bases sharing 0x00C1C780. The 73-byte body is the
// 59-byte info-base shape (see ParticleModuleInfoCopyCtors.cpp) with one
// more vtable-only base: compare 0x003AF50D.
// Identity: eight per-module template copies (0x003AEA4C, 0x003AEB14,
// 0x003AEBD3, 0x003AEC95, 0x003AED75, 0x003AEE2D, 0x003AEFA5, 0x003AF08D)
// call this address at the same +0x10 displacement; all vftable dwords
// are DIR32 sites the gate takes from the target.
// ??0Rva003AEEB3@@QAE@ABVRvaSmartPtr12@@H@Z retail 0x0055BEE9 56B: same class
// own vtable 0x00C1D5FC plus second/third 0x00C1C780 via rowed Head 0x003A57C5;
// callers at 0x003A5861 0x0055B5CA 0x0055BF2C 0x0055F995 0x005641C6.

// The class is the canonical Rva003AEEB3 (DefaultModuleHeadBase plus the two one-slot
// secondary bases at +0x14 and +0x18, both table 0x00C1C780: one __purecall, no destructor).
#include "../../../../Include/GameClient/Rva003AEEB3.h"

Rva003AEEB3::Rva003AEEB3(const Rva003AEEB3 &other)
	: DefaultModuleHeadBase(other)
{
}

Rva003AEEB3::Rva003AEEB3(const RvaSmartPtr12 &smart, int i)
	: DefaultModuleHeadBase(smart, i)
{
}
