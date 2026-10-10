// cl: /MD /EHsc /DNDEBUG /O1 /G7 /Oy- /arch:SSE
#include <math.h>
#include "GameLogicObjectLookupView.h"

enum Relationship { ENEMIES, NEUTRAL, ALLIES };
class ThingTemplate { public: bool isEquivalentTo(const ThingTemplate *) const; };
class Player;
struct Rva2225E0Filter { bool accepts(Object *, Player *); };
class ObjectFilter { public: bool isValid() const; };
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
struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128 &other);
	unsigned char bytes[128];
};

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
	Relationship getRelationship(const Object *) const;
	bool isSignificantlyAboveTerrain() const;
	char m_pad00[4];
	const ThingTemplate *m_template;
	char m_pad08[0x40-8];
	float m_z;
	char m_pad44[0x74-0x44];
	unsigned int m_id;
	unsigned int m_ownerId;
	char m_pad7C[0x284-0x7C];
	BfmeFixedStorage128 m_mask284;
};



extern GameLogic *TheGameLogic;

struct Rva00507558Arg
{
	char m_pad00[4];
	const ThingTemplate *m_template;
	ObjectID m_id08;
};

class Rva00507823
{
public:
	unsigned char rva00507558(const void *arg);
	unsigned char rva0050774A(const void *arg, int unused);
	unsigned char rva005075D6(const void *arg, Object *target);
private:
	char m_pad00[4];
	_STL::_Base_bitset<32> m_need04;
	_STL::_Base_bitset<32> m_ban84;
};

// ZH ControlBar.cpp isValidObjectTarget supplies the relationship-mask guide.
// Target 5075D6..50774A proves the larger BF2 filter, receiver+120,
// source-template flags110, target-kind bytes and z-distance threshold10.
// The original descriptor owner is unknown; retained address-derived view.
// The native x87 comparison reads a four-byte 10.0f constant at BC2428.
// Retain that operand width; promoting a literal to double selects FLD64.
static const float targetHeightTolerance=10.0f;
unsigned char Rva00507823::rva005075D6(const void *arg, Object *target)
{
    if (!target) return false;
    const Rva00507558Arg *holder=(const Rva00507558Arg *)arg;
    if (!rva00507558(holder)) return false;
    Object *source=TheGameLogic->findObjectByID(holder->m_id08);
    if (!source) return rva00507558(holder);
    unsigned int options=*(const unsigned int *)((const char *)holder->m_template+0x110);
    if (!(options&1)) {
        if (source==target) return false;
        if (source->m_ownerId==target->m_id && !(*(const unsigned char *)((const char *)target->m_template+0x10F)&0x80)) return false;
    }
    if ((options&0x20) && (source?source->m_template:source->m_template)->isEquivalentTo((target?target->m_template:target->m_template)) && source->getRelationship(target)==ALLIES) return false;
    if ((*(const unsigned char *)((const char *)target->m_template+0x10B)&2) && !(options&0x80)) return false;
    if ((options&0x40) && target->isSignificantlyAboveTerrain()) return false;
    if ((options&0x100) && fabs((double)(target->m_z-source->m_z))>*(const volatile float *)&targetHeightTolerance) return false;
    if (!((*(const unsigned char *)((const char *)target->m_template+0x10E)&0x80) && (*(const unsigned char *)((const char *)target->m_template+0x108)&4)) && !(*(const unsigned char *)((const char *)target+0x437)&0x10)) {
        Relationship r=source->getRelationship(target);
        if (!(r==NEUTRAL && (*(const unsigned char *)((const char *)target->m_template+0x10E)&4))) {
            unsigned int mask;
            if (r==ALLIES) mask=2;
            else mask=r!=ENEMIES?8:4;
            if (!(options&mask)) return false;
        }
    }
    ObjectFilter *filter=(ObjectFilter *)((char *)this+0x120);
    if (filter->isValid() && !((Rva2225E0Filter *)filter)->accepts(target,source->getControllingPlayer())) return false;
    return true;
}
