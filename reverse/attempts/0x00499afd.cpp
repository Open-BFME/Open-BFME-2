// ?rva00499AFD@OneRingPenaltyUpdate@@AAEXXZ
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva00499AFD@OneRingPenaltyUpdate@@AAEXXZ, retail 0x00499AFD, 284 bytes.
// Private helper on the primary this: spawns the module-data special object
// (ThingTemplate via g_009FF000 from +0x08 name) on the neutral player's
// default team (ThePlayerList +0x18, else Object +0x304 team), zeroes a
// 16-byte CreateMask via the rowed memset thunk 0x006291AE, news it via
// rowed ThingFactory::newObject 0x002D0A23, stores its ObjectID +0x74 at
// +0x24, picks a random direction via rowed GetGameLogicRandomValueReal
// 0x00234092 (g_00BC7470/g_00BC7468, file OneRingPenaltyUpdate.cpp:0xDA),
// offsets the holder's +0x38 position by Cos/Sin 0x0002FBC0/0x0002FBB0 scaled
// by data +0x18, takes ground height via TheTerrainLogic slot 6, sets the new
// position via rowed Thing::setPosition 0x0030AA80, and stamps the angle at
// +0x2C. Evidence: LINK BONUS caller update 0x00499E98, disassembly, SlavedUpdate
// moveToNewRepairSpot precedent for the Cos/Sin/ground pattern, layout from
// rowed ctor 0x00499A70 and ModuleData ctor/dtor.
#include "ascii_string.h"

typedef float Real;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

class ThingTemplate;
class Team;
class Object;

struct CreateMask
{
	unsigned int words[4];
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern Rva002D06CA *g_009FF000;

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
public:
	Coord3D m_position; // +0x38
private:
	unsigned char m_pad44[0x74 - 0x44];
public:
	unsigned int m_id74; // +0x74
private:
	unsigned char m_pad78[0x304 - 0x78];
public:
	Team *m_team304; // +0x304
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	char m_pad[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class PlayerList
{
public:
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
private:
	unsigned char m_pad00[0x10];
	Player *m_localPlayer; // +0x10
	unsigned char m_pad14[0x18 - 0x10 - 4];
	Player *m_neutralPlayer; // +0x18
};
extern PlayerList *ThePlayerList;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;
};
extern TerrainLogic *TheTerrainLogic;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
};

extern float g_00BC7468;
extern float g_00BC7470;
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
float Cos(float value);
float Sin(float value);

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class ModuleData
{
public:
	virtual ~ModuleData();
};
class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void slotUpdate();
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class OneRingPenaltyUpdateModuleData
{
public:
	const void *m_vtable; // +0x00
	int m_unused04; // +0x04
	AsciiString m_specialObjectName; // +0x08
	unsigned int m_0C; // +0x0C
	unsigned int m_10; // +0x10
	unsigned int m_14; // +0x14
	float m_startingDistanceFromMe; // +0x18
};

class OneRingPenaltyUpdate : public UpdateModule
{
public:
	void updateAnchor();
private:
	void rva00499AFD();
	const void *m_20; // +0x20
	unsigned int m_24; // +0x24
	unsigned int m_28; // +0x28
	float m_2C; // +0x2C
	unsigned int m_30; // +0x30
};

// ?rva00499AFD@OneRingPenaltyUpdate@@AAEXXZ present-unmatched
void OneRingPenaltyUpdate::rva00499AFD()
{
	const OneRingPenaltyUpdateModuleData *data = (const OneRingPenaltyUpdateModuleData *)m_moduleData;
	Object *obj = m_object;
	const ThingTemplate *tmpl = (const ThingTemplate *)g_009FF000->rva002D06CA(&data->m_specialObjectName);
	if (!tmpl)
		return;
	Team *team;
	Player *neutral = ThePlayerList->getNeutralPlayer();
	if (neutral)
		team = neutral->getDefaultTeam();
	else
		team = obj->m_team304;
	union MaskPos
	{
		CreateMask mask;
		struct
		{
			unsigned int pad0;
			Coord3D pos;
		} overlay;
	};
	MaskPos u;
	ji_006291ae(&u.mask, 0, sizeof(u.mask));
	Object *newObj = ((ThingFactory *)g_009FF000)->newObject(tmpl, team, &u.mask, false);
	if (!newObj)
		return;
	m_24 = newObj->m_id74;
	u.overlay.pos.set(obj->getPosition());
	Real angle = GetGameLogicRandomValueReal(g_00BC7470, g_00BC7468, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\OneRingPenaltyUpdate.cpp", 0xDA);
	u.overlay.pos.x += Cos(angle) * data->m_startingDistanceFromMe;
	u.overlay.pos.y += Sin(angle) * data->m_startingDistanceFromMe;
	u.overlay.pos.z = TheTerrainLogic->getGroundHeight(u.overlay.pos.x, u.overlay.pos.y, 0);
	newObj->setPosition(&u.overlay.pos);
	m_2C = angle;
}
