// cl: /MD /EHsc /DNDEBUG
// stlport
//
// ?rva00507558@Rva00507823@@QAEEPBX@Z retail 0x00507558 126B
// Upgrade-mask prerequisite test on the Rva00507823 pair at +0x04/+0x84.
// Builds the combined Object+Player mask (Object at +0x284 via rowed copy
// 0x0004548B plus Player at +0x13c via rowed _M_do_or 0x0028C557) then tests
// it against required at +0x04 and exempt at +0x84 via rowed 0x0033A453.
// Null holder returns 0; missing Object returns !is_any of required mask
// (rowed 0x000454A6) via neg/sbb/inc uchar shape. Evidence: same 0x80 mask
// blocks as ctor 0x0050775B at +0x04/+0x84 plus same-cluster callers
// 0x005075D6 and 0x0050774A plus vtable 0x00864010 class of 0x00507823.
// UChar return proven by sbb al al inc al; final test/setne from !=0.
#include "../../Include/Common/BfmeFixedStorage128.h"

namespace _STL
{
template <unsigned N> struct _Base_bitset;
template <> struct _Base_bitset<32>
{
	bool _M_is_any() const;
	void _M_do_or(const _Base_bitset<32> &other);
	unsigned long _M_w[32];
};
}

class Rva0033A453
{
public:
	bool rva0033A453(const void *required, const void *exempt) const;
};

#include "GameLogicObjectLookupView.h"

class Player
{
public:
	char m_pad00[0x13c];
	BfmeFixedStorage128 m_mask13c;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad00[0x284];
	BfmeFixedStorage128 m_mask284;
};


extern GameLogic *TheGameLogic;

struct Rva00507558Arg
{
	char m_pad00[8];
	ObjectID m_id08;
};

#include "../../Include/GameLogic/Module/Rva00507823.h"

unsigned char Rva00507823::rva00507558(const void *arg)
{
	const Rva00507558Arg *holder = (const Rva00507558Arg *)arg;
	if (!holder)
		return false;
	Object *obj = TheGameLogic->findObjectByID(holder->m_id08);
	if (!obj)
		return !reinterpret_cast<const _STL::_Base_bitset<32> &>(m_mask04)._M_is_any();
	BfmeFixedStorage128 tmp(obj->m_mask284);
	Player *player = obj->getControllingPlayer();
	((_STL::_Base_bitset<32> &)tmp)._M_do_or((const _STL::_Base_bitset<32> &)player->m_mask13c);
	return ((const Rva0033A453 &)tmp).rva0033A453(&m_mask04, &m_mask84) != 0;
}

unsigned char Rva00507823::rva0050774A(const void *arg, int unused)
{
	return rva00507558(arg) != 0;
}
