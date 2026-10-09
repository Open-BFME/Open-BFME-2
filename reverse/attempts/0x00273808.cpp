// ?drawAmmo@Drawable@@QAEXXZ
// partial score=0.75 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?drawAmmo@Drawable@@QAEXXZ @0x00273808 457B: legacy no-argument ammo-pip
// renderer. Target evidence: selected/moused-over local-player gate, the
// rowed Object::rva0028AEF5 weapon-slot/ammo pair, full/empty ammo images
// initialized by Rva00274E7DInit, a world-to-screen projection, and a pip
// loop. BFME1 Drawable::drawAmmo supplies the purpose and shared data use;
// target bytes show this older version stores its left edge at Drawable+460
// and treats worldToScreen nonzero as off-screen.
typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord2D { Real x, y; };
struct Coord3D { Real x, y, z; };
struct ICoord2D { Int x, y; };

class Player;
class Image
{
public:
	Int getImageWidth() const
	{
		return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x24);
	}
	Int getImageHeight() const
	{
		return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x28);
	}
};

class GlobalData
{
public:
	char m_pad000[0xDC];
	Coord3D m_ammoPipWorldOffset;
	char m_padE8[0x0C];
	Coord2D m_ammoPipScreenOffset;
	char m_padFC[0x9BD - 0xFC];
	Bool m_showObjectHealth;
};
extern GlobalData *TheGlobalData;

class PlayerList
{
	char m_pad000[0x10];
	Player *m_localPlayer;
public:
	Player *getLocalPlayer() const { return m_localPlayer; }
};
extern PlayerList *ThePlayerList;

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89();
	virtual void slot90(); virtual void slot91(); virtual void slot92();
	virtual Int getMousedOverDrawableID() const;
};
extern InGameUI *TheInGameUI;
class View
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual Int worldToScreen(const Coord3D *, ICoord2D *);
};
extern View *TheTacticalView;
class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61();
	virtual void drawImage(const Image *, Real, Real, Real, Real, Int color = -1, Int layer = 2);
};
extern Display *TheDisplay;

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	Real getBoundingSphereRadius() const
	{
		return *reinterpret_cast<const Real *>(reinterpret_cast<const char *>(this) + 0x14);
	}
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool rva0028AEF5(void **outCapacity, unsigned *outAmmo) const;
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}
	const GeometryInfo &getGeometryInfo() const
	{
		return *reinterpret_cast<const GeometryInfo *>(reinterpret_cast<const char *>(this) + 0xA8);
	}
};

class Drawable
{
public:
	void drawAmmo();

private:
	void *m_vtable;
	char m_pad004[0xF8];
	Object *m_object;                 // +0xFC
	Int m_id;                         // +0x100
	char m_pad104[0x338];
	Bool m_selected;                  // +0x43C
	char m_pad43D[0x23];
	Int m_iconLeft;                   // +0x460

	static const Image *s_fullAmmo;
	static const Image *s_emptyAmmo;
};

void Drawable::drawAmmo()
{
	register Drawable *drawable = this;
	register Object *obj = drawable->m_object;
	if (!TheGlobalData->m_showObjectHealth)
		return;
	if (!drawable->m_selected)
	{
		InGameUI *ui = TheInGameUI;
		if (!ui)
			return;
		Int drawableID = drawable->m_id;
		if (ui->getMousedOverDrawableID() != drawableID)
			return;
	}
	Player *localPlayer = ThePlayerList->getLocalPlayer();
	if (obj->getControllingPlayer() != localPlayer)
		return;

	Int numTotal;
	Int numFull;
	if (!obj->rva0028AEF5(reinterpret_cast<void **>(&numTotal), reinterpret_cast<unsigned *>(&numFull)))
		return;
	if (!s_fullAmmo || !s_emptyAmmo)
		return;

	Int boxWidth = (Int)(Real)s_emptyAmmo->getImageWidth();
	Int boxHeight = (Int)(Real)s_emptyAmmo->getImageHeight();
	const Int SPACING = 1;

	Coord3D pos = *obj->getPosition();
	pos.x += TheGlobalData->m_ammoPipWorldOffset.x;
	pos.y += TheGlobalData->m_ammoPipWorldOffset.y;
	pos.z += TheGlobalData->m_ammoPipWorldOffset.z + obj->getGeometryInfo().getMaxHeightAbovePosition();
	ICoord2D screenCenter;
	if (TheTacticalView->worldToScreen(&pos, &screenCenter) != 0)
		return;

	Real bounding = obj->getGeometryInfo().getBoundingSphereRadius();
	Int posx = drawable->m_iconLeft;
	Int posy = screenCenter.y + (Int)(TheGlobalData->m_ammoPipScreenOffset.y * bounding);
	for (Int i = 0; i < numTotal; ++i)
	{
		TheDisplay->drawImage(i < numFull ? s_fullAmmo : s_emptyAmmo, posx, posy + 1,
			posx + boxWidth, posy + 1 + boxHeight, -1, 2);
		posx += boxWidth + SPACING;
	}
}
