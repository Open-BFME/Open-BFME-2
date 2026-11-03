// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva004F69C3@@QAE@PBHABVRva004F6093Holder@@@Z, retail 0x004F6318,
// 29 bytes. Entry ctor for sorted vector: int key at +0 via pointer deref,
// Holder value at +4 via rowed copy ctor 0x004F6093. Same 8-byte entry layout
// as Rva0040CB11Entry at 0x0040CB11 (27B direct int) but key comes through a
// pointer here. Evidence: single caller at 0x004F6A2B in FUN_008f6a1a.

#include "../../Include/Common/Rva004F6093Holder.h"

struct Rva004F69C3
{
public:
	Rva004F69C3(const int *keyPtr, const Rva004F6093Holder &val);
private:
	int m_first;
	Rva004F6093Holder m_second;
};

// Select-any like the LivingWorldAutoResolveBattle.cpp copy (this retail body
// comes first in link order, so it is the copy the link keeps); the anchor
// keeps the body emitted.
inline Rva004F69C3::Rva004F69C3(const int *keyPtr, const Rva004F6093Holder &val) : m_first(*keyPtr), m_second(val)
{
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva004F69C3Entry@@YAXPAVRva004F69C3@@PBHABVRva004F6093Holder@@@Z absent-from-retail
void bfmeEmitRva004F69C3Entry(Rva004F69C3 *p, const int *keyPtr, const Rva004F6093Holder &val)
{
	p->Rva004F69C3::Rva004F69C3(keyPtr, val);
}

// The entry constructor/factory and the existing 4F69C3 destructor own
// one eight-byte pair. Native 4F9C8E EH cleanup proves the same lifetime.
