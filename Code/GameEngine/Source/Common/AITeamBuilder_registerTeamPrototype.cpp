// cl: /Ireference/shims/bfme2_ascii /GX- /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// ?registerTeamPrototype@AITeamBuilder@@QAEXPAUArg@@@Z @0x0059A71C (90B)
// Thiscall takes one pointer arg with AsciiString at +0x14. Loads chain
// [this+0x14]->+0x2ec->+0x30 for other string or TheEmptyString then
// arg+0x14 compare via rowed StringBase compare. If equal return. Else
// _STL find CreateAHeroData range [this+8 this+0xc) for arg and if found
// return else vector ModuleData push_back at this+8. Ret 4. Caller
// 0x0059A85C unblocks 0x0059A85C. Evidence unlock lane plus compare find
// push_back rows plus TheEmptyString extern plus ret N thiscall.
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
#include <algorithm>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_insert_overflow(const ModuleData **, const ModuleData *const &, const __true_type &, size_t, bool); }
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
// push_back is called out of line: bind it to the rowed retail copy instead of
// emitting this unit's own (0x004DFCB0, stlport_moduledatavector_push.cpp).
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &); }
class CreateAHeroData;
class ModuleData;
struct Leaf
{
	char m_pad[0x14];
	StringBase<char> m_name;
};
struct Mid2
{
	char m_pad[0x30];
	Leaf *m_leaf;
};
struct Mid1
{
	char m_pad[0x2ec];
	Mid2 *m_mid;
};
struct Arg
{
	char m_pad[0x14];
	StringBase<char> m_name;
};
struct Arg;
#include <set>
class Team;
class TeamPrototype;
class Object;
class Player;
struct Coord3D;
struct AITeamRequirementView;
struct AITargetView;
class AITeamBuilder {
public:
 void recruitPreDefined(Team*,int*,TeamPrototype*);
 bool defineUnitsNormal_old(TeamPrototype*);
 void recruitUnDefined(Team*,int*);
 void distanceSortUnits(void*,const void*,const Coord3D*);
 void registerTeamPrototype(Arg *);
 int getCurNumUnits(Team *);
 int doesTeamMeetThreat(Team *);
 bool rva0059A01C(Object*,const AITeamRequirementView*,const AITargetView*);
 void checkIdleTeams();
 void update();
 void rva0059ABC9(void *);
 void rva0059AC4D(void *);
 Team *rva00599F74(TeamPrototype *);
 void rva0059A153(TeamPrototype *);
 char prefix[8]; _STL::vector<TeamPrototype *> prototypes;
 Player* owner14; _STL::set<int> busy;
};
void AITeamBuilder::registerTeamPrototype(Arg *arg)
{
	Mid2 *mid = ((Mid1 *)owner14)->m_mid;
	Leaf *leaf = mid->m_leaf;
	StringBase<char> *other;
	if (leaf == 0)
		other = (StringBase<char> *)&AsciiString::TheEmptyString;
	else
		other = &leaf->m_name;
	if (arg->m_name.compare(*other) == 0)
		return;
	CreateAHeroData **beg = (CreateAHeroData **)((_STL::vector<const ModuleData *> *)&prototypes)->begin();
	CreateAHeroData **end = (CreateAHeroData **)((_STL::vector<const ModuleData *> *)&prototypes)->end();
	CreateAHeroData **found = _STL::find(beg, end, (CreateAHeroData * const &)arg);
	if (found != end)
		return;
	((_STL::vector<const ModuleData *> *)&prototypes)->push_back((const ModuleData * const &)arg);
}
