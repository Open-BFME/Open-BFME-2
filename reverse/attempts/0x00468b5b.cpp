// ?rva00468B5B@HordeContain@@UAEMM@Z
// partial score=0.95 date=2026-10-08
// Banked near miss for ?rva00468B5B@HordeContain@@UAEMM@Z @0x00468B5B (129 B),
// HordeContain +0x11C iface slot 145, in
// Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp.
// Needs HordeContain's float m_2EC (+0x2EC, iface +0x1D0), Object's float
// m_B8 and the override declaration `virtual float rva00468B5B(float value);`.
// Constants: 0xBCF628 = 0.01f, 0xBBB8D8 = 1.0f, 0xBC8270 = 0.9f, 0xBC8E28 = 6.0f.
//
// Only diff: the first six instructions use mirrored xmm registers (ours
// loads b8 into xmm1 and d into xmm0; retail b8 into xmm0 and d into xmm1).
// The two returns are required for retail's `comiss 0,d; ja` then
// `comiss 0,d; jae` (NaN runs the body); a single `d > 0` gives jbe. b8 must be
// a local used twice or cl folds m_B8 as a memory operand of subss. Tried:
// d local, 0.0f < d, clamp-to-zero, -b8 + c, d -= b8, accessor by value and
// by reference, 0 > c - b8 order, a const Object* local, c2 local, || forms.
float HordeContain::rva00468B5B(float value)
{
	float b8 = m_object->m_B8;
	if (0.0f > m_2EC - b8)
		return value;
	if (0.0f >= m_2EC - b8)
		return value;
	value = (1.0f - m_2EC * 0.01f) * value;
	m_2EC = m_2EC * 0.9f;
	if (value > 6.0f)
		value = 6.0f;
	return value;
}

#if 0
// Variant 2026-10-10 w5-g3 (score .95, same mirror residue): volatile loads
// force the reg-form sub (plain b8 local folds m_B8 into subss mem-operand);
// f-local reproduces the m-store-before-value-store order; two ordered
// early-outs give the ja/jae pair. Tried and failed to flip the mirror:
// plain/named-local/volatile-anchor-first/volatile-both orderings (cl always
// puts the minuend in xmm0 regardless of source order).
float HordeContain::rva00468B5B_g3(float value)
{
	float m = *(volatile float *)&m_2EC;
	float anchor = *(volatile float *)&m_object->m_B8;
	float diff = m - anchor;
	if (0.0f > diff)
		return value;
	if (0.0f >= diff)
		return value;
	float f = (1.0f - m_2EC * 0.01f) * value;
	m_2EC = m_2EC * 0.9f;
	value = f;
	if (value > 6.0f)
		value = 6.0f;
	return value;
}
#endif
