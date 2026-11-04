// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?setUnitNeedsNewAttackPos@HordeMeleeAmoeba@@UAEXPAXH@Z, retail 0x00587548 52B.
// Slot 12 offset 0x30 of vtable 0x0086FF38 (class of ??0HordeMeleeAmoeba 0x00587D9C).
// Bounds-checked vec60 store: if idx<0 or idx>=size return; vec[idx].needsPosition=1,
// vec[idx].index=0. Stride 0x3c proves 60-byte elements (the canonical BfmePod60
// with byte at +0xC and dword at +0x10, same shape as BfmePod60Ctor 0x00587500).
// First void* arg unused, second int is idx (ret 8). Same recipe as rowed
// HordeMeleeFormation slots 10/11 (Rva00586D8EVSlots.cpp) with 60B stride.
#include "../../../../GameEngine/Include/GameLogic/HordeMeleeAmoeba.h"

void HordeMeleeAmoeba::setUnitNeedsNewAttackPos(void *arg, int idx)
{
	(void)arg;
	if (idx < 0)
		return;
	if ((unsigned)idx >= slots.size())
		return;
	slots[idx].needsPosition = 1;
	slots[idx].index = 0;
}
