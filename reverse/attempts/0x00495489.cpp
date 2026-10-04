// ?scanClosestTarget@CommandButtonHuntUpdate@@IAEPAVObject@@XZ
// partial score=0.97 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?scanClosestTarget@CommandButtonHuntUpdate@@AAEPAVObject@@XZ, retail
// 0x00495489, 721 bytes. Zero Hour's CommandButtonHuntUpdate::scanClosestTarget
// (reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdate.cpp)
// as BFME2 compiles it: no enter/hijack branch (a missing special power
// template returns at once), the capture-building and place-explosive
// special power types read as 0x1D and 0x17 / 0x19 off the template's final
// override (+0x1C), BFME2's partition filter chain (alive, then not-this,
// then the enemy relationship filter unless capturing), and float
// priorities: the attack-priority info's getPriority (0x00357CDE) takes the
// hunter, the target and 1 and returns a Real. Layout: m_commandButton at
// +0x24 as the matched ctor 0x004952CF sets it; the command button's
// special power template at +0x44; the template's view-object range at
// +0x50; the module data's scan range at +0x0C.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" double sqrt(double);

class Thing;
class ModuleData;
class Player;
class Object;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	Int getSpecialPowerType() const { return getFinal()->m_type; }
	Real getViewObjectRange() const { return getFinal()->m_viewObjectRange; }
private:
	const SpecialPowerTemplate *getFinal() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}
	unsigned char m_pad00[0x1C];
	Int m_type;				// +0x1C
	unsigned char m_pad20[0x50 - 0x20];
	Real m_viewObjectRange;			// +0x50
};

class CommandButton
{
public:
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
private:
	unsigned char m_pad00[0x44];
	const SpecialPowerTemplate *m_specialPower;	// +0x44
};

class SpecialPowerModuleInterface;

class AttackPriorityInfo
{
public:
	Real getPriority(const Object *source, const Object *target, Bool flag) const;	// 0x00357CDE
};

class AIUpdateInterface
{
public:
	const AttackPriorityInfo *getAttackInfo() const { return m_attackInfo; }
private:
	unsigned char m_pad00[0x70];
	const AttackPriorityInfo *m_attackInfo;	// +0x70
};

class Object
{
public:
	Player *getControllingPlayer() const;							// 0x0028AFA9
	Relationship getRelationship(const Object *that) const;					// 0x0028D156
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *t) const;	// 0x0028BB9E
	Real rva00263763(const void *other) const;						// 0x00263763
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos;				// +0x38
	unsigned char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai;		// +0x258
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF: not the given object.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit) throw();	// 0x00045411
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00BC2908, allow 0x002610DE: every kind of the first mask and
// none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class ActionManager
{
public:
	Bool canDoSpecialPowerAtObject(const Object *obj, const Object *target,
		CommandSourceType commandSource, const SpecialPowerTemplate *spTemplate,
		UnsignedInt commandOptions, Bool checkSourceRequirements);	// 0x0041CFCC
};
extern ActionManager *TheActionManager;

struct TAiData
{
	unsigned char m_pad00[0x54];
	Real m_attackPriorityDistanceModifier;	// +0x54
};

class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
private:
	unsigned char m_pad00[0x18];
	TAiData *m_aiData;			// +0x18
};
extern AI *TheAI;

struct CommandButtonHuntUpdateModuleData
{
	unsigned char m_pad00[0x0C];
	Real m_scanRange;			// +0x0C
};

class CommandButtonHuntUpdate
{
protected:
	Object *scanClosestTarget();
private:
	const CommandButtonHuntUpdateModuleData *getCommandButtonHuntUpdateModuleData() const
	{
		return m_moduleData;
	}
	Object *getObject() const { return m_object; }
	virtual void anchor();
	const CommandButtonHuntUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;					// +0x08
	unsigned char m_pad0C[0x24 - 0x0C];			// interfaces, update state, name
	const CommandButton *m_commandButton;			// +0x24
};

enum
{
	SPECIAL_INFANTRY_CAPTURE_BUILDING = 0x1D,
	SPECIAL_TIMED_CHARGES = 0x17,
	SPECIAL_TANKHUNTER_TNT_ATTACK = 0x19,
	KINDOF_MINE = 0x37
};

Object *CommandButtonHuntUpdate::scanClosestTarget()
{
	const CommandButtonHuntUpdateModuleData *data = getCommandButtonHuntUpdateModuleData();
	Object *me = getObject();

	const SpecialPowerTemplate *spTemplate = m_commandButton->getSpecialPowerTemplate();
	if (!spTemplate)
		return 0;

	Bool isCaptureBuilding = spTemplate->getSpecialPowerType() == SPECIAL_INFANTRY_CAPTURE_BUILDING;
	Bool isPlaceExplosive = false;
	if (spTemplate->getSpecialPowerType() == SPECIAL_TIMED_CHARGES)
		isPlaceExplosive = true;
	if (spTemplate->getSpecialPowerType() == SPECIAL_TANKHUNTER_TNT_ATTACK)
		isPlaceExplosive = true;

	Rva0026119DFilter aliveFilter;
	Rva00260EB1Filter filterTeam(me, 1, false);
	Rva002611BFFilter filterNotMe(me);
	aliveFilter.link(&filterNotMe);
	if (!isCaptureBuilding)
		aliveFilter.link(&filterTeam);

	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(me->getPosition(), data->m_scanRange,
		0, &aliveFilter, 1);

	Object *bestTarget = 0;
	Real effectivePriority = 0;
	Real actualPriority = 0;
	const AttackPriorityInfo *info = 0;
	if (me->getAI())
		info = me->getAI()->getAttackInfo();

	SpecialPowerModuleInterface *mod = me->getSpecialPowerModule(spTemplate);
	if (mod) {
		Object *other;
		while ((other = iter.next()) != 0) {
			if (isCaptureBuilding) {
				if (me->getControllingPlayer() == other->getControllingPlayer())
					continue;
				if (me->getRelationship(other) == ALLIES)
					continue;
			}
			if (TheActionManager->canDoSpecialPowerAtObject(me, other, CMD_FROM_AI, spTemplate, 0, true)) {
				if (isPlaceExplosive) {
					Real range = spTemplate->getViewObjectRange();
					Rva00260E2AFilter filterPlayer(me->getControllingPlayer());
					Object *mine = ThePartitionManager->getClosestObject(other->getPosition(), range, 1,
						Rva0004584D(BfmeFixedStorage0004543D(0, KINDOF_MINE),
							*(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(&filterPlayer));
					if (mine)
						continue;
				}
				Real distSqr = me->rva00263763(other);
				Real dist = (Real)sqrt(distSqr);
				Real curPriority = info ? info->getPriority(me, other, true) : data->m_scanRange - dist;
				if (curPriority == 0.0f)
					continue;
				Real modifier = dist / TheAI->getAiData()->m_attackPriorityDistanceModifier;
				Real modPriority = curPriority - modifier;
				if (modPriority < 1.0f)
					modPriority = 1.0f;
				if (modPriority > effectivePriority) {
					effectivePriority = modPriority;
					actualPriority = curPriority;
					bestTarget = other;
				}
				if (modPriority == effectivePriority && curPriority > actualPriority) {
					effectivePriority = modPriority;
					actualPriority = curPriority;
					bestTarget = other;
				}
			}
		}
	}

	return bestTarget;
}
