// ?isAnyKindOf@Thing@@QBE_NABV?$BitFlags@$0EF@@@@Z @0x0030ADC7
// Shard TU: Rva001DCD30Kind.cpp hosts isNotAnyKindOf which calls this
// out-of-line; defining it there inlines and breaks it.

template <int N>
class BitFlags
{
public:
	bool test(const void *kindOf) const;
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;
	// N preserves the existing ABI spelling. Both retail query instantiations
	// (BitFlags69Test and BitFlags116TestSetAndClear) walk seven dwords.
	unsigned int m_bits[7];
};

// ZH KINDOFMASK_NONE starts clear. Native 41C865 passes DFEFA4 as the
// capture filter's second mask; the rowed 464B ActionManager check verifies
// this DIR32 placement at RVA 0x009FEFA4, whose 28 bytes are all zero.
BitFlags<116> KINDOFMASK_NONE = { { 0, 0, 0, 0, 0, 0, 0 } };

#include "../../Include/Common/ThingTemplate.h"

#include "Thing/thing.h"

// ?isAnyKindOf@Thing@@QBE_NABV?$BitFlags@$0EF@@@@Z
bool Thing::isAnyKindOf(const BitFlags<69> &mask) const
{
	const void *kindOf = &m_template->m_kindof[0];
	return mask.test(kindOf);
}

// ?isKindOfMulti@Thing@@QBE_NABV?$BitFlags@$0HE@@@0@Z
bool Thing::isKindOfMulti(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear) const
{
	const BitFlags<116> *kindOf = (const BitFlags<116> *)&m_template->m_kindof[0];
	return kindOf->testSetAndClear(mustBeSet, mustBeClear);
}
