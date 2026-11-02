// cl: /DNDEBUG /MD
//
// ModelConditionFlags::set(bit, value) at retail 0x000B3FA5 (43B, RET 8): the
// bit-twiddling "conditionally set or clear bits without branching" idiom on one
// word of the 19-word (0x4C-byte) mask, w ^= (-f ^ w) & m. Callers: the CrushDie
// onDie flag setters (0x0048645E, 0x00486478) under the ModelConditionFlags
// spelling, and the 0x0027930F / parseModelConditionFlags 0x000B62D4 sites under
// the WeaponTemplateSetHead spelling (an ICF twin: same address, same bytes).
//
// Codegen: retail copies `this` to ESI at entry because the shift mask is formed
// first (ECX is the shift count). Naming the mask first and then reducing `bit`
// in place (bit >>= 5) gives that order; the plain one-expression form lets cl
// consume `this` before the shift and picks ECX for it instead. 19 words come
// from the 0x4C-byte local the callers build; the class carries only the words.

#include "../../Include/GameClient/ModelConditionFlags.h"

void ModelConditionFlags::rva000B3FA5(int bit, int value)
{
	unsigned int m = 1u << (bit & 31);
	bit >>= 5;
	unsigned int old = m_bits[bit];
	m_bits[bit] = old ^ (((0 - (unsigned)value) ^ old) & m);
}

// WeaponTemplateSetHead ICF twin is owned alongside its caller in
// Audio/DynamicAudioEventInfoXferNoName.cpp; its verified43B body stays visible.
