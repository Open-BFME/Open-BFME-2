// cl: /DNDEBUG /MD /EHsc
// ?hasScience@Player@@QBE_NW4ScienceType@@@Z @0x002AB7D5 (40B): Player::hasScience const find over ScienceVec at +0x2F0.
// Evidence: called first in Player::addScience @0x002AD661 with same this and arg which then does vector<ScienceType>::push_back at [esi+0x2F0] via rowed 0x002E01C6; called in Player::isCapableOfPurchasingScience @0x002ABE86 after SCIENCE_INVALID check; ZH Player.cpp hasScience shape with BFME2 vector at +0x2F0; 23 callers including 0x002AB7FD and 0x002AD661.
enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Player
{
	char m_pad[0x2F0];
	ScienceType *m_begin;
	ScienceType *m_end;
	ScienceType *m_capacity;
public:
	bool hasScience(ScienceType t) const;
};

namespace _STL {
	template <class _InputIter, class _Tp>
	_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

// ?hasScience@Player@@QBE_NW4ScienceType@@@Z
bool Player::hasScience(ScienceType t) const
{
	ScienceType *end = m_end;
	return _STL::find(m_begin, end, t) != end;
}
