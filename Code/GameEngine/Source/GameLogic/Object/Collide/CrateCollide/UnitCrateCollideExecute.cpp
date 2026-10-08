// ?executeCrateBehavior@UnitCrateCollide@@MAE_NPAVObject@@@Z
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
// 0x004BCCBD 373B slot 12 of vtable 0x0085A914 (class of ??0UnitCrateCollide at 0x004BCC13).
// Protected virtual bool(Object*) like Heal/Salvage siblings (MAE_N).
// Donor ZH UnitCrateCollide::executeCrateBehavior (unitCount/unitType via ModuleData,
// findTemplate, newObject loop with findPositionAround, crateFreeUnit audio).
// Retail deltas: ModuleData at this+4 with count+0x5c type+0x60, Team at Player+0x2EC,
// newObject 4-arg with zeroed CreateMask, FindPositionOptions floats from globals,
// orientation/position/ID inlined at Object+0x38/+0x44/+0x74, audio via 0x2D97D6/0x2D9531/0x2D9A43.
#include "Common/BfmeAudioEventPrefix136.h"

class Object;
class Player;
class Team;
class ThingTemplate;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct FindPositionOptions
{
	unsigned int flags;
	float minRadius;
	float maxRadius;
	float startAngle;
	float maxZDelta;
	const void *ignoreObject;
	const void *sourceToPathToDest;
	const void *relationshipObject;
};

struct CreateMask
{
	char m_pad[0x10];
};

class Thing
{
public:
	void setOrientation(float angle);	// 0x0030AB9D
	void setPosition(const Coord3D *pos);	// 0x0030AA80
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	float getOrientation() const { return m_orientation; }
	int getID() const { return m_id; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	float m_orientation;	// +0x44
	char m_pad048[0x74 - 0x48];
	int m_id;			// +0x74
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	char m_pad[0x2EC];
	Team *m_defaultTeam;	// +0x2EC
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);	// 0x002D06CA
};
extern class ThingFactory *TheThingFactory;

void __cdecl ji_006291ae();

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);	// 0x002D0A23 pin
};

class PartitionManager
{
public:
	static bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);	// 0x00285202 pin
};

extern const float g_00C5A910;

class AudioManager;
extern AudioManager *TheAudio;

struct UnitCrateMiscView
{
	char _pad[0x5C];
	OpaqueRefElement4 crateFreeUnit;	// +0x5C
};

class UnitCrateAudioView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *evt);
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual const UnitCrateMiscView *getMiscAudio();
};

class Rva002D9531
{
public:
	void rva002D9531(int v);	// 0x002D9531
};

class CrateCollideModuleData
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData();
private:
	unsigned char m_pad[0x5C - 4];
};

class UnitCrateCollideModuleData : public CrateCollideModuleData
{
public:
	unsigned int m_unitCount;	// +0x5C
	AsciiString m_unitType;	// +0x60
};

class CrateCollide
{
public:
	virtual ~CrateCollide();
protected:
	virtual bool executeCrateBehavior(Object *other);
	virtual bool isValidToExecute(const Object *other) const;
};

class UnitCrateCollide : public CrateCollide
{
	const UnitCrateCollideModuleData *m_moduleData;	// +4
protected:
	virtual bool executeCrateBehavior(Object *other);
};

bool UnitCrateCollide::executeCrateBehavior(Object *other)
{
	unsigned int remaining = m_moduleData->m_unitCount;
	void *tmpl = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&m_moduleData->m_unitType);
	if (tmpl == 0)
		return false;
	for (; remaining > 0; --remaining)
	{
		Team *creationTeam = other->getControllingPlayer()->getDefaultTeam();
		CreateMask mask;
		((void (__cdecl *)(void *, int, unsigned int))&ji_006291ae)(&mask, 0, 0x10);
		Object *newObj = ((ThingFactory *)TheThingFactory)->newObject((const ThingTemplate *)tmpl, creationTeam, &mask, false);
		if (newObj != 0)
		{
			Coord3D creationPoint;
			creationPoint.x = other->m_pos.x;
			creationPoint.y = other->m_pos.y;
			creationPoint.z = other->m_pos.z;
			FindPositionOptions fpOptions;
			fpOptions.startAngle = g_00C5A910;
			fpOptions.maxZDelta = 10000000000.0f;
			fpOptions.minRadius = 0.0f;
			fpOptions.flags = 0;
			fpOptions.ignoreObject = 0;
			fpOptions.sourceToPathToDest = 0;
			fpOptions.relationshipObject = 0;
			fpOptions.maxRadius = 20.0f;
			PartitionManager::findPositionAround(&creationPoint, &fpOptions, &creationPoint);
			newObj->setOrientation(other->getOrientation());
			newObj->setPosition(&creationPoint);
		}
	}
	BfmeAudioEventPrefix136 soundToPlay(reinterpret_cast<UnitCrateAudioView *>(TheAudio)->getMiscAudio()->crateFreeUnit, 0);
	((Rva002D9531 *)&soundToPlay)->rva002D9531(other->getID());
	reinterpret_cast<UnitCrateAudioView *>(TheAudio)->addAudioEvent(&soundToPlay);
	return true;
}
