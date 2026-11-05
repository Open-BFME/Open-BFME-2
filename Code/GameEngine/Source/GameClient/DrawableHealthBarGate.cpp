// ?rva0027601B@Rva0027601BHost@@QAEXXZ
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native27601B..2761F3 RET0 and WB CAD980 establish the Drawable UI
// health-bar gate, global flags9BD/9BE, object/body and kind filters.
// Primary semantic and codegen guide: BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// game/GameEngine/Source/GameClient/DrawableHealthBar.cpp (511B donor).
// Target-specific relationships, offsets and kind numbers are witnessed in
// retail independently; the original BFME2 method spelling remains unproved.
// BF1's explicit vtable-view lever separates the health-address load from
// the zero stores. Each target query has only ECX receiver and ST0 float
// result, so a one-register function-pointer view preserves that ABI.
typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

#include "../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

#include "../../Include/Common/ThingTemplate.h"

#include "../../Include/Common/TeamBFME2.h"

#include "../../Include/Common/Player.h"

#include "../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

#include "../../Include/GameLogic/Module/BodyModule.h"

struct HealthBodyVtable {void *slots[4]; Real (__fastcall *getHealth)(BodyModuleInterface *);void *slot5;Real (__fastcall *getMaxHealth)(BodyModuleInterface *);};
class Drawable;

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Drawable *getDrawable() const;
	Bool rva0028F518();
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Object *getContainedBy() const { return m_containedBy; }
	Team *getTeam() const { return m_team; }

private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	char m_pad008[0x254 - 8];
	BodyModuleInterface *m_body; // +0x254
	char m_pad258[0x274 - 0x258];
	Object *m_containedBy; // +0x274
	char m_pad278[0x304 - 0x278];
	Team *m_team; // +0x304
};

#include "../../Include/GameLogic/Module/WallUpgradeUpdate.h"

#include "../../Include/GameClient/Drawable.h"

struct Rva0027601BOffset
{
	Int x;
	Int y;
};

class Rva0027601BHost
{
public:
	void rva0027601B();
};

void Rva0027601BHost::rva0027601B()
{
	Drawable *self = reinterpret_cast<Drawable *>(this);
	if (!TheWritableGlobalData->m_showObjectHealth)
		return;
	Bool selected = self->isSelected();
	if (!selected)
	{
		Object *obj = self->getObject();
		if (obj != 0)
		{
			Object *container = obj->getContainedBy();
			if (container != 0 && (container->getTemplate()->m_kindof[3] & (1 << (0x6D & 31))))
			{
				Drawable *draw = container->getDrawable();
				selected = draw != 0 && draw->isSelected();
			}
		}
	}
	if (!selected)
	{
		if (TheInGameUI == 0)
			return;
		DrawableID drawableID = self->m_id;
		if (TheInGameUI->getMousedOverDrawableID() != drawableID)
			return;
	}
	Object *obj = self->getObject();
	if (obj == 0)
		return;
	if (obj->rva0028F518())
	{
		Player *localPlayer = ThePlayerList->getLocalPlayer();
		Team *team = obj->getTeam();
		if (localPlayer != 0 && team != 0 && localPlayer->isPlayerActive()
			&& team->getRelationship(localPlayer->getDefaultTeam()) != ALLIES)
			return;
	}
	const ThingTemplate *thingTemplate = obj->getTemplate();
	if (!(thingTemplate->m_kindof[2] & (1 << (0x5A & 31))) && !(thingTemplate->m_kindof[0] & (1 << (0x0B & 31))) && !(thingTemplate->m_kindof[0] & (1 << (0x0A & 31)))
		&& !(thingTemplate->m_kindof[1] & (1 << (0x37 & 31))) && !(thingTemplate->m_kindof[0] & (1 << (0x07 & 31))) && !(thingTemplate->m_kindof[5] & (1 << (0xAA & 31))))
	{
		if (!TheWritableGlobalData->field09BE)
			return;
		if (!(thingTemplate->m_kindof[0] & (1 << (0x08 & 31))) && !(thingTemplate->m_kindof[0] & (1 << (0x09 & 31))))
			return;
	}
	if ((obj->getTemplate()->m_kindof[4] & (1 << (0x96 & 31))))
	{
		WallUpgradeUpdate *wall = static_cast<WallUpgradeUpdate *>(WallUpgradeUpdate::rva004AB1F5(obj));
		if (wall != 0 && !wall->rva004AB3AE())
			return;
	}
	if ((obj->getTemplate()->m_kindof[1] & (1 << (0x3D & 31))) && !(obj->getTemplate()->m_kindof[5] & (1 << (0xAA & 31))))
		return;
	if ((obj->getTemplate()->m_kindof[1] & (1 << (0x36 & 31))) || (obj->getTemplate()->m_kindof[4] & (1 << (0x88 & 31)))
		|| (obj->getTemplate()->m_kindof[3] & (1 << (0x6D & 31))))
		return;
	BodyModuleInterface *body = obj->getBodyModule();
	Real maxHealth = body->getMaxHealth();
	if (maxHealth == 0.0f)
		return;
	HealthBodyVtable *vtable = *reinterpret_cast<HealthBodyVtable **>(body);
 Rva0027601BOffset offset;
	offset.x = 0;
	offset.y = 0;
	Real health = vtable->getHealth(body);
	if (health == 0.0f)
		return;
	self->rva0027411F(&offset, health / maxHealth);
}
