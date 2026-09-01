// ?getIdNoCase@PooledString@@QBEIXZ
// partial score=0.9 date=2026-09-01
// ?getIdNoCase@PooledString@@QBEIXZ
// partial score=0.9 date=2026-08-31
// ?getIdNoCase@PooledString@@QBEIXZ
// partial score=0.9 date=2026-08-31
// cl: /O1
// Retail 0x0060B820 is 11 bytes and selects the case-folded alias with a
// conditional move:
//     mov eax,[ecx] ; mov ecx,[eax+4] ; test ecx,ecx ; cmovne eax,ecx ; ret
// MSVC 7.1 emits the 9-byte test/je/mov instead, and it does so for every shape
// tried: the plain pointer ternary, a pointer ternary through a named local, a
// reference bound to the ternary (the form that DOES produce a cmov in
// RealRange::combine), an unsigned ternary, and a reference to an unsigned
// ternary - the last of which drags in a frame. /O2 does reach for cmov here
// but breaks all seven other bodies in PooledString.cpp, so the unit is /O1 and
// this is a codegen shape, not identity.
//
// 2026-09-01: the split-into-its-own-unit fix that landed RGBColor(int) does
// NOT work here. In an isolated TU containing only these two bodies, none of
// /O2, /Ox, /O2 /GX-, /O2 /Ot, /O2 /GR-, /O2 /Gy, /O1 /G6, /O2 /G6, /O2 /G7,
// /O2 /arch:SSE2 or /Og /Oi /Ot /Oy /Ob2 reaches the cmov, and neither do an
// if-statement over a pointer local, the same over unsigned locals, or a
// reference bound to the ternary. So the earlier note's "/O2 does reach for
// cmov here" was an effect of the rest of PooledString.cpp, not of the flag.
// Whatever produces it needs surrounding code, not a shape or a switch.
//
// ?isEqualNoCase@PooledString@@QBE_NABV1@@Z at 0x0060B82B is blocked behind the
// same thing: it is this body inlined twice and compared, and both copies carry
// the cmov.
unsigned int PooledString::getIdNoCase() const
{
    return (unsigned int)(m_entry->m_noCase ? m_entry->m_noCase : m_entry);
}

bool PooledString::isEqualNoCase(const PooledString &that) const
{
    return getIdNoCase() == that.getIdNoCase();
}
