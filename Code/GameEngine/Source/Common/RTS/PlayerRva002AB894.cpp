// cl: /DNDEBUG /MD /EHsc
// ?rva002AB894@Player@@QBE_NABURva002AB894List@@@Z @0x002AB894 (60B): Player all-of test over a pointer list: true when every
// UpgradeTemplate in [m_begin, m_end) passes the rowed Player::rva002AB87D (0x002AB87D); the empty list is true. Address-derived names:
// the list's owner and the caller identity are not established (target evidence: retail bytes, rowed callee).
// Codegen (lab-found with a beam search over source edits, target evidence only): the counter declared BEFORE the count computation
// (retail's xor edi,edi sits between the sub and the sar), the pointer declared inside the `0 < count` guard, loop wrapped in the guard.
class UpgradeTemplate;

struct Rva002AB894List
{
	const UpgradeTemplate **m_begin;
	const UpgradeTemplate **m_end;
};

#include "../../../Include/Common/Player.h"

// ?rva002AB894@Player@@QBE_NABURva002AB894List@@@Z
bool Player::rva002AB894(const Rva002AB894List &list) const
{
	unsigned int i = 0;
	unsigned int count = list.m_end - list.m_begin;
	if (0 < count)
	{
		const UpgradeTemplate **it = list.m_begin;
		for (; i < count; ++i, ++it)
		{
			if (!rva002AB87D(*it))
				return false;
		}
	}
	return true;
}
