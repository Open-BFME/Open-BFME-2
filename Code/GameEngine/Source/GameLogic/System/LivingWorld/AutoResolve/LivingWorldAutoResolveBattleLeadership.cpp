// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva004F9F39@LivingWorldAutoResolveBattle@@QAEXXZ retail 0x004F9F39..0x004FA10F
// (470 bytes; the method keeps its address name). Receiver: the battle's two
// unit vectors at +0x0C/+0x18 (12-byte stride), as in the matched sibling
// 0x004F971E (LivingWorldAutoResolveBattleChooseTargets.cpp).
// WorldBuilder twin 0x12EC720 (2209 bytes, unoptimised) shows the shape: per
// side, units whose leadership template (thing +0x2C, +0x494) yields a bonus
// for their level (getBonusForLevel 0x00417FBA) are filed as records into a
// local vector, which is sorted (0x004F9EF3); then each record hands its bonus
// to up to <count> units of the masked types (thing +0x5C4), front to back or
// back to front, skipping the leader itself, dead units and units that already
// carry a bonus (+0x1C). The twin reads units through the reference pointer's
// get() (templates_referenceptr.h:253) and the elements through STLport's
// vector::operator[] (*(begin() + n)); retail's lea operand order needs the
// back element through operator[] and the front one through the raw start.
// Type and member names below are views; only the method address name is
// claimed. No BFME1/ZH donor exists (LivingWorld is BFME 2 only).
#include <vector>
namespace _STL { template <class It, class Cmp> void sort(It, It, Cmp); }

#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"

// Retail inlines this release in the leadership loop; keep its body visible
// while sharing the canonical handle and referent declarations.
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}

struct MedianKey004F60EC
{
	int _00[2];
	int m_key;
};
struct Rva004F6352
{
	MedianKey004F60EC *m_ptr;
	int m_04;
	TreeHintRef00217D4C m_08;
};
namespace _STL {
template <> void vector<Rva004F6352>::reserve(unsigned int);
template <> Rva004F6352 *vector<Rva004F6352>::erase(Rva004F6352 *, Rva004F6352 *);
template <> void vector<Rva004F6352>::push_back(const Rva004F6352 &);
}
struct Rva004F6352Cmp
{
	bool operator()(const Rva004F6352 &a, const Rva004F6352 &b) const;
};
struct Rva004F691E
{
	int m_00;
	int m_04;
	TargetRef00217D4C *m_08;
	Rva004F691E(int a, int b, const TreeHintRef00217D4C &ref) throw();
	operator const Rva004F6352 &() const { return *(const Rva004F6352 *)this; }
	~Rva004F691E()
	{
		if (m_08)
			ReleaseTreeHintRef00217D4C(m_08);
	}
};

// The local record vector (dtor rowed 0x004F887C; its base ctor is the folded
// _Vector_base<int> 0x00211E58).
struct Rva004F887C : public _STL::_Vector_base<int, _STL::allocator<int> >
{
	Rva004F887C() : _STL::_Vector_base<int, _STL::allocator<int> >(_STL::allocator<int>()) {}
	~Rva004F887C();
	_STL::vector<Rva004F6352> *records() { return (_STL::vector<Rva004F6352> *)this; }
	Rva004F6352 *begin() const { return (Rva004F6352 *)_M_start; }
	Rva004F6352 *end() const { return (Rva004F6352 *)_M_finish; }
};

class Rva00417FBA
{
public:
	int *rva00417FBA(int key);
};
struct Rva004F9F39Key
{
	unsigned char m_pad00[0x0C];
	int m_key; // +0x0C
};
struct Rva004F9F39Template
{
	unsigned char m_pad000[0x494];
	Rva00417FBA *m_autoResolveLeadership; // +0x494
	unsigned char m_pad498[0x5C4 - 0x498];
	unsigned int m_autoResolveUnitType; // +0x5C4
};
struct Rva004F9F39Unit : public TargetRef00217D4C
{
	Rva004F9F39Key *m_08; // +0x08
	float m_health; // +0x0C
	unsigned char m_pad10[0x1C - 0x10];
	MedianKey004F60EC *m_leadershipBonus; // +0x1C
	unsigned char m_pad20[0x2C - 0x20];
	Rva004F9F39Template *m_template; // +0x2C
	MedianKey004F60EC *getBonus() const { return m_leadershipBonus; }
};
struct Rva004F9F39Mask
{
	unsigned int m_bits[4];
};
struct Rva004F9F39Info
{
	unsigned char m_pad00[0x04];
	Rva004F9F39Mask m_mask; // +0x04
	bool m_frontToBack; // +0x14
};
struct Rva004F9F39Vec
{
	TreeHintRef00217D4C *m_start;
	TreeHintRef00217D4C *m_finish;
	TreeHintRef00217D4C *m_end;
	unsigned int size() const { return m_finish - m_start; }
	TreeHintRef00217D4C *begin() const { return m_start; }
	TreeHintRef00217D4C &operator[](unsigned int i) { return *(begin() + i); }
};
static __forceinline const unsigned int &maxRef(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}

class LivingWorldAutoResolveBattle
{
public:
	void rva004F9F39();
private:
	unsigned char m_pad00[0x0C];
	Rva004F9F39Vec m_vecs[2]; // +0x0C, +0x18
};

void LivingWorldAutoResolveBattle::rva004F9F39()
{
	Rva004F887C records;
	records.records()->reserve(maxRef(m_vecs[1].size(), m_vecs[0].size()));
	for (int i = 0; i < 2; ++i)
	{
		Rva004F9F39Vec &vec = m_vecs[i];
		records.records()->erase(records.begin(), records.end());
		TreeHintRef00217D4C *end = vec.m_finish;
		for (TreeHintRef00217D4C *it = vec.m_start; it != end; ++it)
		{
			Rva004F9F39Unit *unit = (Rva004F9F39Unit *)it->m_ptr;
			Rva00417FBA *table = unit->m_template->m_autoResolveLeadership;
			if (!table)
				continue;
			int *entry = table->rva00417FBA(unit->m_08->m_key);
			if (!entry)
				continue;
			records.records()->push_back(Rva004F691E((int)entry, (int)table, TreeHintRef00217D4C(*it)));
		}
		_STL::sort(records.begin(), records.end(), Rva004F6352Cmp());
		Rva004F6352 *rend = records.end();
		for (Rva004F6352 *record = records.begin(); record != rend; ++record)
		{
			int count = record->m_ptr->_00[1];
			Rva004F9F39Info *info = (Rva004F9F39Info *)record->m_04;
			bool frontToBack = info->m_frontToBack;
			int numUnits = vec.size();
			for (int k = 0; count > 0 && k < numUnits; ++k)
			{
				const TreeHintRef00217D4C &ref = frontToBack ? vec.m_start[k] : vec[numUnits - k - 1];
				Rva004F9F39Unit *unit = (Rva004F9F39Unit *)ref.m_ptr;
				if (unit->getBonus() == 0)
				{
					unsigned int bit = unit->m_template->m_autoResolveUnitType;
					if ((info->m_mask.m_bits[bit >> 5] & (1u << (bit & 31))) && unit != (Rva004F9F39Unit *)record->m_08.m_ptr && !(unit->m_health <= 0.0f))
					{
						unit->m_leadershipBonus = record->m_ptr;
						--count;
					}
				}
			}
		}
	}
}
