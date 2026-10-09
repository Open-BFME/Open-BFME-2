// ?groupDoSpecialPowerAtObject@AIGroup@@QAEXIPAVObject@@IW4CommandSourceType@@@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmelist /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?groupDoSpecialPowerAtObject@AIGroup@@QAEXIPAVObject@@IW4CommandSourceType@@@Z
// retail 0x0036E658..0x0036E8EA (658 bytes, EH, RET 0x10).
//
// Donor and identity:
// - The donor is BFME 1's AIGroup::groupDoSpecialPowerAtObject
//   (reference/open-bfme-1 game/GameEngine/Source/GameLogic/AI/
//   AIGroup_groupDoSpecialPowerAtObject.cpp).
// - The member list at +0x04 is the same as the rowed AIGroup bodies
//   (groupChangeStance 0x0036E269 and others).
// - The calls are rowed or pinned: findSpecialPowerTemplateByID,
//   ActionManager::canDoSpecialPowerAtObject, Object::rva0028E01F and
//   rva0028AC34, ExperienceTracker::rva0039AC0C, IsValid and GetLevelRank.
// - WorldBuilder 0x00EE9F50 is the same function before the retail-only
//   changes noted below.
//
// What BFME 2 adds over the donor:
// - Unless option bit 0x100000 is set, members whose template has KindOf bit
//   0x5A compete on experience level rank. The tie goes to the lower +0x74 ID.
//   When such a member wins, only it fires.
// - Otherwise the members are sorted by GetLengthEstimate2D distance to the
//   target, as in the donor.
// - For a player command, an AI whose +0x3C5 byte is set is skipped.
// - The check-source-requirements flag is commandSource == CMD_FROM_PLAYER.
//
// Matching notes:
// - /EHs, not /EHsc, keeps retail's state -1 store before the list dtor.
// - The declaration order (list, iterator, best, rank) and the if / else-if
//   rank test are what give retail's frame slots and reload order.
// - AIGroupDistanceEntry is the 8-byte {Object *, Real} element. Its list
//   ctor (0x0035C9A6) and insert (0x0036E30E) are ICF-folded STLport bodies
//   that need pins under this element name. Its _List_base dtor resolves to
//   0x004EC395 by its own body.
#include <list>

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's out-of-line GetLengthEstimate2D (rowed 0x000037D1) that the distance sort calls; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Real GetLengthEstimate2D() const;
};

class ExperienceLevelList;
class ExperienceLevelIterator
{
public:
	ExperienceLevelIterator() {}
	ExperienceLevelIterator(const ExperienceLevelIterator &other) : m_node(other.m_node) {}
private:
	void *m_node;
};
struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &other) : m_list(other.m_list), m_iter(other.m_iter) {}
	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};
class ExperienceLevelStore
{
public:
	Bool IsValid(ExperienceLevelHandle handle) const;
	Int GetLevelRank(ExperienceLevelHandle handle) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class ExperienceTracker
{
public:
	ExperienceLevelHandle rva0039AC0C() const;
};

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplateByID(UnsignedInt id);
};
extern SpecialPowerStore *TheSpecialPowerStore;

class Object;
class ActionManager
{
public:
	Bool canDoSpecialPowerAtObject(const Object *obj, const Object *target, CommandSourceType commandSource,
		const SpecialPowerTemplate *spTemplate, UnsignedInt commandOptions, Bool checkSourceRequirements);
};
extern ActionManager *TheActionManager;

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(Int kind) const { return (m_kindOf[kind >> 3] & (1 << (kind & 7))) != 0; }
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20];						// +0x108
};

class AIUpdateInterface
{
public:
	unsigned char m_pad000[0x48];
	CommandSourceType m_lastCommandSource;			// +0x48
	unsigned char m_pad04C[0x3C5 - 0x4C];
	Bool m_3C5;										// +0x3C5
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() const { return m_ai; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
	Int getID() const { return m_id; }
	void rva0028E01F(const SpecialPowerTemplate *spTemplate, Object *target, Int commandOptions, Int forced);
	void rva0028AC34(Bool value);

	unsigned char m_pad000[4];
	const ThingTemplate *m_template;					// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos;										// +0x38
	unsigned char m_pad044[0x74 - 0x44];
	Int m_id;											// +0x74
	unsigned char m_pad078[0x258 - 0x78];
	AIUpdateInterface *m_ai;							// +0x258
	unsigned char m_pad25C[0x264 - 0x25C];
	ExperienceTracker *m_experienceTracker;			// +0x264
};

struct AIGroupDistanceEntry
{
	Object *m_object;
	Real m_distance;
};

class AIGroup
{
public:
	void groupDoSpecialPowerAtObject(UnsignedInt specialPowerID, Object *target, UnsignedInt commandOptions, CommandSourceType commandSource);
private:
	unsigned char m_pad000[4];
	_STL::list<Object *> m_memberList;				// +0x04
};

void AIGroup::groupDoSpecialPowerAtObject(UnsignedInt specialPowerID, Object *target, UnsignedInt commandOptions, CommandSourceType commandSource)
{
	_STL::list<AIGroupDistanceEntry> sorted;
	_STL::list<Object *>::iterator i;
	Object *best = 0;
	Int bestRank = 0;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (!(commandOptions & 0x100000) && obj->getTemplate()->isKindOf(0x5A))
		{
			ExperienceLevelHandle level = obj->getExperienceTracker()->rva0039AC0C();
			if (!reinterpret_cast<const ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(level))
				continue;
			Int rank = reinterpret_cast<const ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(level);
			if (best == 0 || rank > bestRank)
			{
				best = obj;
				bestRank = rank;
			}
			else if (rank == bestRank && obj->getID() < best->getID())
			{
				best = obj;
				bestRank = rank;
			}
		}
		if (best)
			continue;

		Real distance = 0.0f;
		if (target)
		{
			Coord3D delta = *target->getPosition();
			delta.x -= obj->getPosition()->x;
			delta.y -= obj->getPosition()->y;
			delta.z -= obj->getPosition()->z;
			distance = delta.GetLengthEstimate2D();
		}
		AIGroupDistanceEntry entry;
		entry.m_object = obj;
		entry.m_distance = distance;
		Bool inserted = false;
		for (_STL::list<AIGroupDistanceEntry>::iterator at = sorted.begin(); at != sorted.end(); ++at)
		{
			if (at->m_distance > entry.m_distance)
			{
				sorted.insert(at, entry);
				inserted = true;
				break;
			}
		}
		if (!inserted)
			sorted.push_back(entry);
	}

	Bool checkSourceRequirements = commandSource == CMD_FROM_PLAYER;
	if (best == 0)
	{
		for (_STL::list<AIGroupDistanceEntry>::iterator j = sorted.begin(); j != sorted.end(); ++j)
		{
			Object *obj = j->m_object;
			AIUpdateInterface *ai = obj->getAI();
			if (ai)
			{
				if (commandSource == CMD_FROM_PLAYER && ai->m_3C5)
					continue;
				ai->m_lastCommandSource = commandSource;
			}
			const SpecialPowerTemplate *spTemplate = TheSpecialPowerStore->findSpecialPowerTemplateByID(specialPowerID);
			if (!spTemplate)
				continue;
			if (TheActionManager->canDoSpecialPowerAtObject(obj, target, CMD_FROM_PLAYER, spTemplate, commandOptions, checkSourceRequirements))
			{
				obj->rva0028E01F(spTemplate, target, commandOptions, 0);
				obj->rva0028AC34(false);
			}
		}
	}
	else
	{
		AIUpdateInterface *ai = best->getAI();
		if (ai)
		{
			if (commandSource == CMD_FROM_PLAYER && ai->m_3C5)
				return;
			ai->m_lastCommandSource = commandSource;
		}
		const SpecialPowerTemplate *spTemplate = TheSpecialPowerStore->findSpecialPowerTemplateByID(specialPowerID);
		if (spTemplate && TheActionManager->canDoSpecialPowerAtObject(best, target, CMD_FROM_PLAYER, spTemplate, commandOptions, checkSourceRequirements))
		{
			best->rva0028E01F(spTemplate, target, commandOptions, 0);
			best->rva0028AC34(false);
		}
	}
}
