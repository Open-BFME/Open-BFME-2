// ?rva0046EA94@HordeContain@@UAE_NPAVObject@@@Z
// partial score=0.82 date=2026-10-08
// Bank for HordeContain iface slot 28, ?rva0046EA94@HordeContain@@UAE_NPAVObject@@@Z
// @0x0046EA94 (488 B), unit Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp.
// Score 0.82 (instruction similarity). Control flow and block layout match;
// register allocation does not. Retail keeps the Object from rva002931F5 in edi,
// ours (self, m_object) only in memory [ebp-0x10], self's player as a spilled
// temp [ebp-0x18] reloaded into ecx for the compare, and enregisters constant 0
// in ebx (xor ebx,ebx right after the player compare) for the rest: obj is
// reloaded from [ebp+8] in the no-rider branch, the name local is [ebp-0x14]
// and the esp save reuses [ebp+8]. This body gets self in memory and the rider
// in edi, but self in ebx in the rider branch, no zero register and name at
// [ebp+8]. Without the Player local (expression compare) self goes to edi and
// the rider spills (0.75). Tried without effect: other/self declaration order,
// == 0 spellings, record local, operand order, block scope for name, a
// __forceinline busy(2,3) helper, an else block, Player locals for both sides;
// a __forceinline member helper for the no-rider branch gives the 3-slot frame
// but copies this to edi (0.76). The rider-branch early returns ARE needed:
// they give retail's xor bl,bl block straight after the lookup test.
#if 0
// View additions this body needs (all in HordeContainIface11CSlots.cpp):
//  ThingTemplate: unsigned char m_109 at +0x109 (bit 3 tested)
//  ExperienceTracker: int m_24 at +0x24 (compared with 1)
//  enum KindOfType { KINDOF_INVALID = -1 };
//  template <int N> class BitFlags { public: bool any() const; unsigned int m_words[(N + 31) / 32]; };
//    (rowed BitFlags<11>::any 0x0023C58B reads Object +0x1C8)
//  Object: BitFlags<11> m_disabledMask at +0x1C8;
//    bool isDisabled() const { return m_disabledMask.any(); }
//    bool isKindOf(KindOfType kind) const; // 0x0006F039
//  HordeContainModuleDataFields: Rva00469851Names m_1F4 (+0x1F4), m_218 (+0x218),
//    bool m_238 (+0x238), AsciiString m_23C (+0x23C)
//  iface slot 28: virtual bool rva0046EA94(Object *obj) = 0; (was gap28)
//  HordeContain: virtual bool rva0046EA94(Object *obj);
#endif
bool HordeContain::rva0046EA94(Object *obj)
{
	if (!obj || obj->isEffectivelyDead())
		return false;
	if (obj->testStatus((ObjectStatusTypes)0x3B) || obj->testStatus((ObjectStatusTypes)0x3E))
		return false;
	Object *self = m_object;
	if (self->testStatus((ObjectStatusTypes)0x3E))
		return false;
	if (obj->isDisabled() || obj->isKindOf((KindOfType)0xDA))
		return false;
	Object *other = obj->rva002931F5(false);
	Player *player = self->getControllingPlayer();
	if (player != obj->getControllingPlayer())
		return false;
	if (!other)
	{
		const HordeContainModuleDataFields *data = fields();
		if (rva0046970D(obj, (int)m_264, &data->m_1F4, false))
			return true;
		if (rva0046970D(obj, m_26C, &data->m_218, false) && m_object->m_264->m_24 <= 1)
			return true;
		if (!data->m_238 || !(obj->m_template->m_109 & 8) || data->m_23C.compare(obj->m_template->m_64) != 0)
			return false;
		return true;
	}
	if (!self || other == self)
		return false;
	AsciiString name;
	name = other->m_template->m_64;
	if (!rva0046D158(name))
		return false;
	if (other->testStatus((ObjectStatusTypes)2) || other->testStatus((ObjectStatusTypes)3))
		return false;
	if (self->testStatus((ObjectStatusTypes)2) || self->testStatus((ObjectStatusTypes)3))
		return false;
	return true;
}
