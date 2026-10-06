// cl: /DNDEBUG /MD /EHsc
// ?rva002AB82D@Player@@QBE_NPAVCreateAHeroData@@@Z @0x002AB82D (40B): Player const find over CreateAHeroData* vec at +0x2FC.
// Evidence: same 40B shape as rowed Player::hasScience @0x002AB7D5 which finds over ScienceVec at +0x2F0 via rowed _STL::find @0x0020E873; this body calls the same rowed find for CreateAHeroData* with begin at [ecx+0x2FC] and end at [ecx+0x300] immediately after that ScienceVec; neighbours 0x002AB7FD and 0x002AB87D are Player const methods with same flags.
class CreateAHeroData;

class Player
{
	char m_pad[0x2FC];
	CreateAHeroData **m_begin;
	CreateAHeroData **m_end;
	CreateAHeroData **m_capacity;
public:
	bool rva002AB82D(CreateAHeroData *hero) const;
};

namespace _STL {
	template <class _InputIter, class _Tp>
	_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

bool Player::rva002AB82D(CreateAHeroData *hero) const
{
	CreateAHeroData **end = m_end;
	return _STL::find(m_begin, end, hero) != end;
}
