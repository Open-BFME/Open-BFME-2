// cl: /Ireference/shims/bfme2_ascii /MD /GX
//
// VeterancyCrateCollide (vftable 0x00C5A954: slot 0 the deleting dtor
// 0x004BCEC0, slot 12 executeCrateBehavior, slot 13 isValidToExecute). Its
// module data (ctor 0x00255B09) keeps the effect range at +0x5C (unsigned),
// AddsOwnerVeterancy at +0x60, IsPilot at +0x61 and AffectsUpToLevel at
// +0x64. Zero Hour's and BFME1's VeterancyCrateCollide are the donors; BFME2
// drops the pilot's goal-object check, gives every promoted unit the
// GUI:GainRank text, and walks the range with the partition filter chain.
//
//   0x004BCEDC  getLevelsToGain: 0 with AddsOwnerVeterancy, else 1 (defined
//               here: the callers keep edx live across its call, which cl
//               does only for a body it has already compiled in the unit)
//   0x004BCEF0  isValidToExecute
//   0x004BCFF0  executeCrateBehavior

#include "ascii_string.h"
#include "unicode_string.h"

class Object;
class Player;

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

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
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
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;

class ScriptEngine
{
public:
	void rva00357960(const AsciiString &name, Object *obj);	// 0x00357960
};
extern ScriptEngine *TheScriptEngine;

class ExperienceTracker
{
public:
	bool isTrainable() const;	// 0x0039ADAF
	bool rva0039ABFF() const;	// 0x0039ABFF
	bool rva0039B4EC(int levels, bool flag1, bool flag2);	// 0x0039B4EC
	char m_pad00[0x24];
	int m_level;	// +0x24
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool isSignificantlyAboveTerrain() const;	// 0x0030ADDC
	bool isUsingAirborneLocomotor() const;	// 0x0028B81E
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x88 - 0x44];
	AsciiString m_name;		// +0x88
	char m_pad08C[0x264 - 0x8C];
	ExperienceTracker *m_experienceTracker;	// +0x264
	char m_pad268[0x438 - 0x268];
	unsigned char m_438;		// +0x438 (bit 0: effectively dead)
};

struct VeterancyCrateCollideModuleData
{
	char m_pad00[0x5C];
	unsigned m_rangeOfEffect;	// +0x5C
	bool m_addsOwnerVeterancy;	// +0x60
	bool m_isPilot;			// +0x61
	int m_affectsUpToLevel;		// +0x64
};

class CrateCollide
{
public:
	virtual ~CrateCollide();
protected:
	virtual bool executeCrateBehavior(Object *other);
	virtual bool isValidToExecute(const Object *other) const;	// 0x004BC6C2
	void rva004BCF92(const Object *other, const UnicodeString *text);	// 0x004BCF92
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class VeterancyCrateCollide : public CrateCollide
{
protected:
	virtual bool executeCrateBehavior(Object *other);
	virtual bool isValidToExecute(const Object *other) const;
private:
	const VeterancyCrateCollideModuleData *getVeterancyCrateCollideModuleData() const
	{
		return (const VeterancyCrateCollideModuleData *)m_moduleData;
	}
	int getLevelsToGain() const;
};

int VeterancyCrateCollide::getLevelsToGain() const
{
	const VeterancyCrateCollideModuleData *data = getVeterancyCrateCollideModuleData();
	if (data && data->m_addsOwnerVeterancy)
		return 0;
	return 1;
}

bool VeterancyCrateCollide::isValidToExecute(const Object *other) const
{
	const VeterancyCrateCollideModuleData *data = getVeterancyCrateCollideModuleData();
	if (!data)
		return false;
	if (!CrateCollide::isValidToExecute(other))
		return false;
	if (other->isEffectivelyDead())
		return false;
	if (other->isSignificantlyAboveTerrain())
		return false;
	int levelsToGain = getLevelsToGain();
	if (levelsToGain <= 0)
		return false;
	const ExperienceTracker *tracker = other->getExperienceTracker();
	if (!tracker || !tracker->isTrainable())
		return false;
	if (!tracker || !tracker->rva0039ABFF())
		return false;
	if (tracker->m_level > data->m_affectsUpToLevel)
		return false;
	if (data->m_isPilot) {
		const Object *object = m_object;
		if (other->getControllingPlayer() != object->getControllingPlayer())
			return false;
		if (other->isUsingAirborneLocomotor())
			return false;
	}
	return true;
}

bool VeterancyCrateCollide::executeCrateBehavior(Object *other)
{
	const VeterancyCrateCollideModuleData *data = getVeterancyCrateCollideModuleData();
	float range = (float)data->m_rangeOfEffect;
	if (range == 0) {
		if (other && other->getExperienceTracker()) {
			other->getExperienceTracker()->rva0039B4EC(getLevelsToGain(), !data->m_isPilot, false);
			UnicodeString rankString;
			rankString.format(TheGameText->slot44("GUI:GainRank", 0), getLevelsToGain());
			rva004BCF92(other, &rankString);
		}
	} else {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(other->getPosition(), range, 0,
			Rva00260E2AFilter(other->getControllingPlayer()).link(&Rva002611BFFilter(other)), 0);
		Object *obj;
		while ((obj = hits.next()) != 0) {
			if (obj && obj->getExperienceTracker()) {
				obj->getExperienceTracker()->rva0039B4EC(getLevelsToGain(), !data->m_isPilot, false);
				UnicodeString rankString;
				rankString.format(TheGameText->slot44("GUI:GainRank", 0), getLevelsToGain());
				rva004BCF92(obj, &rankString);
			}
		}
	}
	if (data->m_isPilot)
		TheScriptEngine->rva00357960(m_object->m_name, other);
	return true;
}
