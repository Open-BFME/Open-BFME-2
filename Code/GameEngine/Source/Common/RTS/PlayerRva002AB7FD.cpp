// cl: /DNDEBUG /MD /EHsc
// ?rva002AB7FD@Player@@QBE_NABV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z @0x002AB7FD (48B): Player::rva002AB7FD const any-of over ScienceVec.
// Evidence: calls Player::hasScience @0x002AB7D5 rowed in PlayerHasScience.cpp with same this; takes ScienceVec const& proven by 0x0029FCB4 vector<ScienceType> copy ctor at 0x0054878E constructing the arg; loops begin at [eax] to end at [eax+4] and returns true on first hasScience hit; callers at 0x002A7111 and 0x0031D985 pass ScienceVec from 0x0029FCB4.
enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL {
	template <class _Tp> class allocator;
	template <class _Tp, class _Alloc> class vector;
	typedef vector<ScienceType, allocator<ScienceType> > ScienceVec;
}

class Player
{
	char m_pad[0x2F0];
	ScienceType *m_begin;
	ScienceType *m_end;
	ScienceType *m_capacity;
public:
	bool hasScience(ScienceType t) const;
	bool rva002AB7FD(const _STL::ScienceVec &range) const;
};

// ?rva002AB7FD@Player@@QBE_NABV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z
bool Player::rva002AB7FD(const _STL::ScienceVec &range) const
{
	ScienceType *begin = *(ScienceType * const *)&range;
	ScienceType *end = *((ScienceType * const *)&range + 1);
	for (ScienceType *it = begin; it != end; ++it) {
		if (hasScience(*it))
			return true;
	}
	return false;
}
