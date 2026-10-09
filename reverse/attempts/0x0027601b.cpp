// ?rva0027601B@Rva0027601BHost@@QAEXXZ
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// NEAR draft for ?rva0027601B@Rva0027601BHost@@QAEXXZ 0x0027601B (472 bytes): Drawable health bar
// gate (WB 0x00CAD980). 472B with every instruction matching except one scheduling
// residue: retail loads the body vptr (mov eax,[esi]) before the two zero stores of the
// stack offset pair [ebp-0x14] ahead of the getHealth call; cl keeps the stores first.
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

class GlobalData
{
public:
	char m_pad000[0x9BD];
	Bool m_9BD; // +0x9BD
	Bool m_9BE; // +0x9BE
};

extern GlobalData *TheWritableGlobalData;

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(Int t) const { return m_kindOf[t >> 5] & (1 << (t & 31)); }

private:
	char m_pad000[0x108];
	UnsignedInt m_kindOf[8]; // +0x108
};

class Team
{
public:
	Relationship getRelationship(const Team *that) const;
};

class Player
{
public:
	Bool isPlayerActive() const;
	Team *getDefaultTeam() const { return m_defaultTeam; }

private:
	char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }

private:
	char m_pad000[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92();
	virtual DrawableID getMousedOverDrawableID() const; // +0x174
};

extern InGameUI *TheInGameUI;

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual Real getHealth() const; // +0x10
	virtual void slot05();
	virtual Real getMaxHealth() const; // +0x18
};

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

class Module
{
public:
	virtual void slot00();

private:
	char m_pad004[0x24 - 4];
};

class UpgradeMux
{
public:
	virtual Bool isUpgradeActive() const; // +0x24 subobject slot 0
};

class WallUpgradeUpdate : public Module, public UpgradeMux
{
public:
	static Module *rva004AB1F5(Object *obj);
};

class Drawable
{
public:
	DrawableID getID() const { return m_id; }
	Object *getObject() const { return m_object; }
	Bool isSelected() const { return m_selected != 0; }
	void rva0027411F(void *out, float healthRatio);

	char m_pad000[0xFC];
	Object *m_object; // +0xFC
	DrawableID m_id; // +0x100
	char m_pad104[0x43C - 0x104];
	Bool m_selected; // +0x43C
};

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
	if (!TheWritableGlobalData->m_9BD)
		return;
	Bool selected = self->isSelected();
	if (!selected)
	{
		Object *obj = self->getObject();
		if (obj != 0)
		{
			Object *container = obj->getContainedBy();
			if (container != 0 && container->getTemplate()->isKindOf(0x6D))
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
		if (TheInGameUI->getMousedOverDrawableID() != self->getID())
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
	const ThingTemplate *tmpl = obj->getTemplate();
	if (!tmpl->isKindOf(0x5A) && !tmpl->isKindOf(0x0B) && !tmpl->isKindOf(0x0A)
		&& !tmpl->isKindOf(0x37) && !tmpl->isKindOf(0x07) && !tmpl->isKindOf(0xAA))
	{
		if (!TheWritableGlobalData->m_9BE)
			return;
		if (!tmpl->isKindOf(0x08) && !tmpl->isKindOf(0x09))
			return;
	}
	if (obj->getTemplate()->isKindOf(0x96))
	{
		WallUpgradeUpdate *wall = static_cast<WallUpgradeUpdate *>(WallUpgradeUpdate::rva004AB1F5(obj));
		if (wall != 0 && !wall->isUpgradeActive())
			return;
	}
	if (obj->getTemplate()->isKindOf(0x3D) && !obj->getTemplate()->isKindOf(0xAA))
		return;
	if (obj->getTemplate()->isKindOf(0x36) || obj->getTemplate()->isKindOf(0x88)
		|| obj->getTemplate()->isKindOf(0x6D))
		return;
	BodyModuleInterface *body = obj->getBodyModule();
	Real maxHealth = body->getMaxHealth();
	if (maxHealth == 0.0f)
		return;
	Rva0027601BOffset offset;
	offset.x = 0;
	offset.y = 0;
	Real health = body->getHealth();
	if (health == 0.0f)
		return;
	self->rva0027411F(&offset, health / maxHealth);
}
