// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0036DA02@AIGroup@@QAE_NIPBUCoord3D@@PBVObject@@IH@Z @ 0x0036DA02 440B
// AIGroup veteran special-power dispatch: pick highest-rank member whose
// template carries 0x04000000 (byte 0x113 bit2) via ExperienceTracker handle
// rank with lower ObjectID74 tie-break, else walk all members; for the chosen
// object(s) store arg5 to AI+0x48 (gated by AI+0x3C5 when arg5 is 0), call
// rva00293105 when arg5 is 0, then canDo/doSpecialPowerAtLocation plus
// rva0028AC34(false), returning whether any power fired.
// Evidence: flanked by AIGroup rows 0x0036D837/0x0036DBBA, list at this+0x04
// with payload at node+0x08, callees findSpecialPowerTemplateByID pin
// 0x003B0FD0 plus ExperienceTracker 0x0039AC0C plus IsValid pin 0x0028891F
// plus GetLevelRank 0x0028879C plus Object 0x00293105/0x0028AC34 plus
// ActionManager canDo pin 0x0041D60B plus Object::doSpecialPowerAtLocation
// 0x0028E0F9, callers 0x0037812A/0x0037815C/0x00378239 build AIGroup via
// createGroup/add with (id, Coord3D, Object, options, 0), ControlBar
// rva0053DD53 precedent for rank/ID74 selection.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class SpecialPowerTemplate;
class ExperienceLevelList;
class ExperienceLevelIterator
{
public:
	ExperienceLevelIterator() {}
	ExperienceLevelIterator(const ExperienceLevelIterator &that) : m_node(that.m_node) {}
	void *m_node;
};

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}
	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};

class ExperienceTracker
{
public:
	ExperienceLevelHandle rva0039AC0C() const;
};

class ExperienceLevelStore
{
public:
	bool IsValid(ExperienceLevelHandle handle) const;
	Int GetLevelRank(ExperienceLevelHandle handle) const;
};

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplateByID(UnsignedInt id);
};
extern SpecialPowerStore *TheSpecialPowerStore;

class ThingTemplate
{
public:
	char m_pad[0x113];
	unsigned char m_113;
};

class AIUpdate
{
public:
	char m_pad00[0x48];
	Int m_48;
	char m_pad4C[0x3C5 - 0x4C];
	unsigned char m_3C5;
};

class Object
{
public:
	void rva00293105();
	void rva0028AC34(bool on);
	void doSpecialPowerAtLocation(const SpecialPowerTemplate *specialPowerTemplate, const Coord3D *loc, UnsignedInt commandOptions, bool forceUsable);

	char m_pad00[0x04];
	ThingTemplate *m_template;
	char m_pad08[0x74 - 0x08];
	Int m_id;
	char m_pad78[0x258 - 0x78];
	AIUpdate *m_ai;
	char m_pad25C[0x264 - 0x25C];
	ExperienceTracker *m_tracker;
};

class ActionManager
{
public:
	bool canDoSpecialPowerAtLocation(const Object *obj, const Coord3D *loc, CommandSourceType commandSource,
		const SpecialPowerTemplate *spTemplate, const Object *objectInWay, UnsignedInt commandOptions, bool checkSourceRequirements);
};
extern ActionManager *TheActionManager;

class AIGroup
{
public:
	bool rva0036DA02(UnsignedInt id, const Coord3D *loc, const Object *objectInWay, UnsignedInt commandOptions, Int unk);

private:
	unsigned char m_pad00[4];
	_STL::list<Object *> m_memberList;
};

bool AIGroup::rva0036DA02(UnsignedInt id, const Coord3D *loc, const Object *objectInWay, UnsignedInt commandOptions, Int unk)
{
	const SpecialPowerTemplate *spTemplate = TheSpecialPowerStore->findSpecialPowerTemplateByID(id);
	Object *best = 0;
	bool done = false;
	Int bestRank = 0;
	for (_STL::list<Object *>::iterator it = m_memberList.begin(); it != m_memberList.end(); ++it) {
		Object *object = *it;
		ThingTemplate *tmpl = object->m_template;
		if ((tmpl->m_113 & 4) == 0)
			continue;
		ExperienceLevelHandle handle = object->m_tracker->rva0039AC0C();
		if (!((ExperienceLevelStore *)TheExperienceLevelSystem)->IsValid(handle))
			continue;
		Int rank = ((ExperienceLevelStore *)TheExperienceLevelSystem)->GetLevelRank(handle);
		if (!best || rank > bestRank) {
			best = object;
			bestRank = rank;
		} else if (best && rank == bestRank) {
			if (object->m_id < best->m_id) {
				best = object;
				bestRank = rank;
			}
		}
	}
	if (best == 0) {
	for (_STL::list<Object *>::iterator it = m_memberList.begin(); it != m_memberList.end(); ++it) {
		Object *object = *it;
		AIUpdate *ai = object->m_ai;
		if (ai != 0) {
			if (unk == 0) {
				if (ai->m_3C5 != 0)
					continue;
			}
			ai->m_48 = unk;
		}
		if (unk == 0)
			object->rva00293105();
		if (spTemplate == 0)
			continue;
		if (!TheActionManager->canDoSpecialPowerAtLocation(object, loc, CMD_FROM_PLAYER, spTemplate, objectInWay, commandOptions, true))
			continue;
		object->doSpecialPowerAtLocation(spTemplate, loc, commandOptions, false);
		object->rva0028AC34(false);
		done = true;
	}
	} else {
		AIUpdate *ai = best->m_ai;
		if (ai != 0) {
			if (unk == 0) {
				if (ai->m_3C5 != 0)
					return false;
			}
			ai->m_48 = unk;
		}
		if (unk == 0)
			best->rva00293105();
		if (spTemplate != 0) {
			if (TheActionManager->canDoSpecialPowerAtLocation(best, loc, CMD_FROM_PLAYER, spTemplate, objectInWay, commandOptions, true)) {
				best->doSpecialPowerAtLocation(spTemplate, loc, commandOptions, false);
				best->rva0028AC34(false);
				done = true;
			}
		}
	}
	return done;
}
