// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0046CF21@HordeContain@@QAEXXZ -- retail 0x0046CF21..0x0046D158 (567 bytes).
// Banner carrier spawn of the horde contain. Identity: the WorldBuilder twin
// HordeContain::spawnBannerCarrier (HordeContain.cpp; "Banner Carrier template
// not found!" and "Banner Carrier Update Module Not Found!" assertions) has the
// same call graph in the same order. Retail evidence: state +0x26C gate / module
// data +0x218 name list looked up through TheThingFactory 0x002D06CA / zeroed
// 0x10-byte create mask / controlling player +0x3BC enable byte +0x110 saved
// and restored around the spawn (0x0039B780) / status 0x3E selects the original
// team (0x0046AA11 name and TeamFactory 0x003A40F5) / newObject 0x002D0A23 /
// weapon set flags 0x18 0x19 0x1A copied (0x0028D891 then 0x00290963) / shroud
// hiding of the new drawable / replacement state 0x002928B5 / GameLogic
// 0x0023D0C2 with +0x45C / exit through the producer (+0x78) exit interface
// slots 1 and 2 when status 2 is set or else the source transform and layer /
// slot 0x74 of the +0x11C interface / 0x00469B73 / the BannerCarrierUpdate
// lookup 0x00468E26 (thiscall pin of HordeContain) whose module data +0x14
// reloads the countdown at +0x27C. Sole caller 0x0046E740 (same class).
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"

#include <string.h>

enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum WeaponSetType { WEAPONSET_NONE = 0 };
enum CellShroudStatus { CELLSHROUD_CLEAR = 0 };
enum PathfindLayerEnum { LAYER_INVALID = 0 };

class ThingTemplate;
class Team;
class Matrix3D;

struct CreateMask
{
	char m_data[0x10];
};

#include "../../../../Include/GameClient/Drawable.h"

#include "../../../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DBridge.h"

class Player
{
public:
	char pad000[0x54];
	int m_playerIndex;	// +0x54
	char pad058[0x3BC - 0x58];
	W3DBridge m_3bc;	// +0x3BC
};

#include "../../../../Include/Common/PlayerList.h"

#include "../../../../Include/GameLogic/Module/ExitInterface.h"

#include "../../../../Include/Common/Rva0028D891Owner.h"

class Rva0046AA11AsciiField
{
public:
	AsciiString get() const;
};

#include "../../../Common/Thing/thing.h"

static inline const ThingTemplate *containThingTemplate(const Thing *thing) { return thing->m_template; }


class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes status) const;
	void setWeaponSetFlag(WeaponSetType wst);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	void bfmeTransferReplacementState(Object *other);
	ExitInterface *getObjectExitInterface() const;
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);

	char pad060[0x78 - 0x60];
	ObjectID m_producerID;	// +0x78
	char pad07C[0x304 - 0x7C];
	Team *m_team;	// +0x304
	char pad308[0x45C - 0x308];
	int m_45c;	// +0x45C
};


enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID deferInit);
};

#include "../../../../Include/Common/TeamFactory.h"

struct AsciiStringVector
{
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_cap;
	bool empty() const { return m_begin == m_end; }
	AsciiString &operator[](int i) { return m_begin[i]; }
};

struct HordeContainModuleData
{
	char pad000[0x218];
	AsciiStringVector m_bannerCarrierNames;	// +0x218
};

struct BannerCarrierUpdateModuleData
{
	char pad00[0x14];
	unsigned int m_countdown;	// +0x14
};

struct HordeBannerCarrierUpdate
{
	void *m_vtbl;
	BannerCarrierUpdateModuleData *m_moduleData;	// +0x04
};

class Rva0046E740Iface11C
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
	virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
	virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
	virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
	virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
	virtual void vf70();
	virtual void vf74(Object *newObj, Object *source, bool flag);	// +0x74
};

class HordeContain
{
public:
	void rva0046CF21();

	void *m_vtbl;	// +0x00
	HordeContainModuleData *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
	char pad00C[0x11C - 0x0C];
	Rva0046E740Iface11C m_iface11C;	// +0x11C
	char pad120[0x26C - 0x120];
	int m_state;	// +0x26C
	char pad270[0x27C - 0x270];
	unsigned int m_countdown;	// +0x27C
};
class Module;
Module *__stdcall Rva00468E26Get(Object *);
// The native BannerCarrierUpdate getter ignores ambientECX and returns the
// Module* from Object::findModule. Retain the witnessed caller receiver.
union NativeBannerUpdateCall {
 Module *(__stdcall *target)(Object *);
 Module *(HordeContain::*member)(Object *);
};
typedef char BannerUpdatePointerWidth[sizeof(NativeBannerUpdateCall)==4 ? 1 : -1];

class Rva00469B73
{
public:
	void rva00469B73(void *obj);
};

extern ThingFactory *TheThingFactory;
extern TeamFactory *TheTeamFactory;
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;


void HordeContain::rva0046CF21()
{
	if (m_state != 0)
		return;

	AsciiStringVector &names = m_moduleData->m_bannerCarrierNames;
	if (names.empty())
		return;

	const ThingTemplate *unitTemplate =
		TheThingFactory->findTemplate(names[0]);
	if (!unitTemplate)
		return;

	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Object *obj = m_object;
	Object *newObj;

	Player *player = obj->getControllingPlayer();
	W3DBridge *bridge = &player->m_3bc;
	bool wasEnabled = bridge->m_enabled;
	bridge->setEnabled(false);

	if (!obj->testStatus((ObjectStatusTypes)0x3E))
	{
		Team *team = obj->m_team;
		newObj = TheThingFactory->newObject(unitTemplate, team, &mask, (ObjectID)0);
	}
	else
	{
		Team *team = TheTeamFactory->findTeam(((const Rva0046AA11AsciiField *)obj)->get());
		if (!team)
		{
			bridge->setEnabled(wasEnabled);
			return;
		}
		newObj = TheThingFactory->newObject(unitTemplate, team, &mask, (ObjectID)0);
	}
	bridge->setEnabled(wasEnabled);

	if (((const Rva0028D891Owner *)obj)->testBit(0x18))
		newObj->setWeaponSetFlag((WeaponSetType)0x18);
	if (((const Rva0028D891Owner *)obj)->testBit(0x19))
		newObj->setWeaponSetFlag((WeaponSetType)0x19);
	if (((const Rva0028D891Owner *)obj)->testBit(0x1A))
		newObj->setWeaponSetFlag((WeaponSetType)0x1A);

	if (newObj->getDrawable())
	{
		if (obj->getShroudStatusForPlayer(ThePlayerList->m_local->m_playerIndex) >= 3)
			newObj->getDrawable()->setFullyObscuredByShroud(true);
	}

	if (obj->testStatus((ObjectStatusTypes)0x3E))
		obj->bfmeTransferReplacementState(newObj);

	TheGameLogic->rva0023D0C2(newObj, obj->m_45c);

	bool exited = false;
	Object *producer = TheGameLogic->findObjectByID(obj->m_producerID);
	if (producer && obj->testStatus((ObjectStatusTypes)2))
	{
		ExitInterface *exitInterface = producer->getObjectExitInterface();
		if (exitInterface)
		{
			ExitDoorType door = exitInterface->reserveDoorForExit(containThingTemplate(newObj), newObj);
			if (door != -1)
			{
				exitInterface->exitObjectViaDoor(newObj, door);
				exited = true;
			}
		}
	}
	if (!exited)
	{
		newObj->setTransformMatrix(&obj->m_transform);
		newObj->setLayer((PathfindLayerEnum)obj->rva0028B511());
	}

	m_iface11C.vf74(newObj, obj, true);
	((Rva00469B73 *)this)->rva00469B73(newObj);
	NativeBannerUpdateCall getter={&Rva00468E26Get};
	HordeBannerCarrierUpdate *update = (HordeBannerCarrierUpdate *)(this->*getter.member)(newObj);
	if (update)
		m_countdown = update->m_moduleData->m_countdown;
}
