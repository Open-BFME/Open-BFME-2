// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroHero::ConstructHeroBlingList, retail 0x00409A76..0x00409C3D
// (455 B, RET 0). WorldBuilder 0x01082260 names it (CreateAHeroHero.cpp,
// the ASSERT(subClass) at line 1622) and gives the statement shapes: clear
// the bling-dirty bit, rebuild the +0x74 group-key -> bling-id map from the
// hero's sub class, then add the bling of every earned award whose upgrade
// names a bling group the hero has and whose id that group lacks.
// The sub-class group key is const, which is why retail keeps it in EBX
// while the map lookup takes its address.
// Split from CreateAHeroHero.cpp, whose CreateAHeroHero view types +0x74 as a
// bare map-header pointer; this unit needs the real map<Int, vector> there.
#include "ascii_string.h"
#include <vector>
#include <map>
#include <algorithm>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
namespace _STL { template <> vector<unsigned int, allocator<unsigned int> >::vector(allocator<unsigned int> const &); }
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_create_node(pair<int const, vector<unsigned int, allocator<unsigned int> > > const &); }
namespace _STL { template <> void vector<unsigned int, allocator<unsigned int> >::_M_set(unsigned int *, unsigned int *, unsigned int *); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Nonconst_traits<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >, bool> _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::insert_unique(pair<int const, vector<unsigned int, allocator<unsigned int> > > const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@IV?$allocator@I@_STL@@@_STL@@IAEXPAIABIABU__true_type@2@I_N@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<unsigned int, allocator<unsigned int> >::_M_insert_overflow(unsigned int *, const unsigned int &, const __true_type &, size_t, bool); }
// Its push_back then compiles to 58 bytes, not retail's 0x004DFCB0, and this
// unit is the first in link order to emit one: ConstructHeroBlingList calls
// the kept retail copy instead.
namespace _STL { template <> void vector<unsigned int, allocator<unsigned int> >::push_back(const unsigned int &); }

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/GameLogic/CreateAHeroManager.h"

class CreateAHeroManager::CreateAHeroSubClass
{
public:
	void *GetBlingGroupNameKey(UnsignedInt index);			// 0x0021AD5D
	UnsignedInt GetBlingIndex(Int groupKey, UnsignedInt index);	// 0x0021BCEA
	Int rva0021BC2C(Int groupKey) const;				// 0x0021BC2C
	char m_pad00[0x28];
	UnsignedInt m_blingGroupCount;					// +0x28
};

class CreateAHeroHero;
// The rowed award test (0x0040AA27): every requirement holds for the hero.
class CreateAHeroAward
{
public:
	bool rva0040AA27(const CreateAHeroHero *hero) const;
};
// The award record's upgrade-key list (+0x04) and its keyed getter.
class Rva0040A7F1
{
public:
	Int rva0040A7F1(Int index) const;			// 0x0040A7F1
	char m_pad00[4];
	_STL::vector<Int> m_upgradeKeys;			// +0x04
};
struct BfmePod40;
class Rva0040AAD5 { public: BfmePod40 *rva0040AAD5(Int awardId); };
extern Rva0040AAD5 *TheAwardSystemManager;
#include "../../../Include/Common/Rva00406E7D.h"
class Rva00406E8F { public: Int rva00406E8F(UnsignedInt index); };

// 0x004079D5 (31 B, rowed in Rva004079D5.cpp): the hero's +0x74 map
// lookup. Its body is visible here so cl proves the out-node's address does
// not escape; with it retail shares that node slot with the first loop's
// push_back temporary.
class Rva004079D5Sub74
{
public:
	int rva00388E63(int *out);
	int m_0;
};

class Rva004079D5
{
public:
	__declspec(noinline) char rva004079D5(int tmp, int *out)
	{
		int v = m_74.rva00388E63(&tmp);
		*out = v;
		return v != m_74.m_0;
	}
private:
	char m_pad00[0x74];
	Rva004079D5Sub74 m_74;
};

struct CreateAHeroBlingNode
{
	unsigned char m_pad00[0x14];
	_STL::vector<UnsignedInt> m_blingIds;		// +0x14
};

class CreateAHeroHero
{
public:
	void ConstructHeroBlingList();
private:

	unsigned char m_pad00[0x0C];
	UnsignedInt m_classIndex;			// +0x0C
	UnsignedInt m_subClassIndex;			// +0x10
	unsigned char m_pad14[0x38 - 0x14];
	UnsignedInt m_flags38 : 7;			// +0x38
	UnsignedInt m_blingListValid : 1;		// +0x38 bit 7
	unsigned char m_pad3C[0x74 - 0x3C];
	_STL::map<Int, _STL::vector<UnsignedInt> > m_bling;	// +0x74
};

void CreateAHeroHero::ConstructHeroBlingList()
{
	CreateAHeroManager::CreateAHeroSubClass *subClass = const_cast<CreateAHeroManager::CreateAHeroSubClass *>(
		TheCreateAHeroManager->rva0021A1B6(m_classIndex, m_subClassIndex));
	m_blingListValid = 0;
	if (!subClass)
		return;

	m_bling.clear();
	Int blingGroupKey;
	for (UnsignedInt i = 0; i < subClass->m_blingGroupCount; ++i)
	{
		blingGroupKey = (Int)subClass->GetBlingGroupNameKey(i);
		for (UnsignedInt j = 0; j < (UnsignedInt)subClass->rva0021BC2C(blingGroupKey); ++j)
			m_bling[blingGroupKey].push_back(subClass->GetBlingIndex(blingGroupKey, j));
	}

	for (UnsignedInt awardIndex = 0; awardIndex < (UnsignedInt)((Rva00406E7D *)this)->rva00406E7D(); ++awardIndex)
	{
		BfmePod40 *award = TheAwardSystemManager->rva0040AAD5(((Rva00406E8F *)this)->rva00406E8F(awardIndex));
		if (!award || !((const CreateAHeroAward *)award)->rva0040AA27(this))
			continue;
		const Rva0040A7F1 *upgrades = (const Rva0040A7F1 *)award;
		for (UnsignedInt k = 0; k < upgrades->m_upgradeKeys.size(); ++k)
		{
			AsciiString upgradeName = TheNameKeyGenerator->keyToName((NameKeyType)upgrades->rva0040A7F1(k));
			UnsignedInt blingId = 0;
			Int groupKey = 0;
			CreateAHeroBlingNode *node = 0;
			if (TheCreateAHeroManager->FindBlingByUpgradeName(upgradeName, (Int *)&blingId, &groupKey)
				&& ((Rva004079D5 *)this)->rva004079D5(groupKey, (int *)&node))
			{
				_STL::vector<UnsignedInt> &ids = node->m_blingIds;
				if (_STL::find(ids.begin(), ids.end(), blingId) == ids.end())
					m_bling[groupKey].push_back(blingId);
			}
		}
	}
}
