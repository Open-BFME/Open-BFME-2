// cl: /Ob0 /EHsc /MD
// stlport
// ?rva00506A52@Rva00506A52@@QAEXXZ @ 0x00506A52 168B (placeholder, real signature TBD)
// Chain from 0x005AD6C3: iterates hash_map buckets via rowed bucket_count,
// fetches Object* per index via rowed rva0025BFF8, filters via rowed
// rva00506A0C plus +0x520==12, news 0x10 AINavyUnitBattleShip from Object and
// push_backs into vector at this+4. Evidence: calls at 0x00506A6B/75/8B/99/
// AC4/DB, new 0x10 at 0x00506AAE, vector at [edi+4], Player at [edi].
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <hash_map>
// bfme link decl-only begin
namespace _STL { template <> unsigned int hash_map<int, int, hash<int>, equal_to<int>, allocator<pair<int const, int> > >::bucket_count() const; }
namespace _STL { template <> unsigned int hashtable<pair<int const, int>, int, hash<int>, _Select1st<pair<int const, int> >, equal_to<int>, allocator<pair<int const, int> > >::bucket_count() const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAPBVModuleData@@PBV1@V?$allocator@PBVModuleData@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> const ModuleData **_STLP_alloc_proxy<const ModuleData **, const ModuleData *, allocator<const ModuleData *> >::allocate(size_t); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@PBVModuleData@@@_STL@@QBEPAPBVModuleData@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> const ModuleData **allocator<const ModuleData *>::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PBVModuleData@@@_STL@@QBEXPAPBVModuleData@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void allocator<const ModuleData *>::deallocate(const ModuleData **, size_t) const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_clear(); }

namespace _STL {
template <> inline void _Construct<const ModuleData *, const ModuleData *>(
    const ModuleData **p, const ModuleData *const &value)
{ if (p) *p = value; }
}

class Player;
class Object;
class ModuleData;

struct Rva00506A0COther
{
	char m_pad[0x74];
	int m_74;
};

struct Rva005DCC4BSource
{
	char m_bytes00[0x74];
	int m_field74;
};

#include "../../Include/GameLogic/Rva002A8F24.h"

#include "../../Include/Common/Rva0025BFF8.h"

class Rva00506A0C
{
public:
	bool rva00506A0C(const Rva00506A0COther *other);
};

class Rva005DCC4B
{
public:
	Rva005DCC4B(const Rva005DCC4BSource *source);
	virtual ~Rva005DCC4B();

	int m_field04;
};

class AINavyUnitBattleShip : public Rva005DCC4B
{
public:
	AINavyUnitBattleShip(const Rva005DCC4BSource *source);
	virtual ~AINavyUnitBattleShip();

	int m_field08;
	int m_field0C;
};

class Object
{
public:
	void *m_04;
	char m_pad08[0x74 - 0x08];
	int m_74;
};

extern Rva002A8F24 *TheSkirmishAIManager;

class Rva00506A52
{
public:
	void rva00506A52();
private:
	Player *m_00;
	_STL::vector<const ModuleData *> m_04;
};

void Rva00506A52::rva00506A52()
{
	void *ret = TheSkirmishAIManager->rva002A8F24(m_00);
	Rva0025BFF8 *maps = *(Rva0025BFF8 **)((char *)ret + 4);
	unsigned int count = (( _STL::hash_map<int, int> *)maps)->bucket_count();
	for (unsigned int i = 0; i < count; ++i) {
		Object *obj = maps->rva0025BFF8((int)i);
		if (obj == 0)
			continue;
		if (((Rva00506A0C *)this)->rva00506A0C((const Rva00506A0COther *)obj))
			continue;
		void *inner = *(void **)((char *)obj + 4);
		if (*(int *)((char *)inner + 0x520) != 12)
			continue;
		AINavyUnitBattleShip *nw = new AINavyUnitBattleShip((const Rva005DCC4BSource *)obj);
		const ModuleData *moduleData = (const ModuleData *)nw;
		m_04.push_back(moduleData);
	}
}
