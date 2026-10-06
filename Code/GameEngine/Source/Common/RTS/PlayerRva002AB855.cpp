// cl: /DNDEBUG /MD /EHsc
// ?rva002AB855@Player@@QBE_NPAVCreateAHeroData@@@Z @0x002AB855 (40B): Player const find over CreateAHeroData* vec at +0x308.
// Evidence: identical 40B shape to just-landed Player::rva002AB82D @0x002AB82D over vec at +0x2FC via same rowed _STL::find @0x0020E873; neighbours are Player const methods with same flags.
class CreateAHeroData;

class Player
{
	char m_pad[0x308];
	CreateAHeroData **m_begin;
	CreateAHeroData **m_end;
	CreateAHeroData **m_capacity;
public:
	bool rva002AB855(CreateAHeroData *hero) const;
};

namespace _STL {
	template <class _InputIter, class _Tp>
	_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

bool Player::rva002AB855(CreateAHeroData *hero) const
{
	CreateAHeroData **end = m_end;
	return _STL::find(m_begin, end, hero) != end;
}
