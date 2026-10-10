// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?drawIconUI@Drawable@@QAEXXZ
// retail 0x00278DFE..0x0027900B (525 bytes) thiscall RET 0.
//
// Zero Hour's Drawable::drawIconUI gate and computeHealthRegion as BFME 2
// builds them (WorldBuilder twin 0x00CAAAF0 is unnamed with the same
// statements; Open-BFME-1 Drawable_drawIconUI_BFME.cpp is BFME 1's body).
// It does nothing unless TheGameLogic draws icon UI (+0x9A) and
// TheScriptEngine has no fade (+0x1A138), or without an object (+0xFC).
// The health box position (0x002775C9) and the object's health box
// dimensions (pinned 0x0028D900) are projected through TheTacticalView
// (slot 88); off screen the object must have status 2 and the position is
// lowered by a third toward the drawable position (0x00276470) and projected
// again. The width is scaled by the inverse zoom (slot 73) and the region at
// +0x460 gets the box (0.45 of the width left of centre and four pixels
// high). Then TheGameClient queues icon layer 0 and, unless the object is
// effectively dead (+0x438 bit 0) or its template has KindOf bit 0x2F
// (template +0x108), layers 1 and 2, layer 5 with shift held for templates
// whose +0x0C is not -1, and layer 3 for the locally controlled object's
// squad number 0..9 when the drawable's +0x43C flag is set. Callees:
// testStatus 0x0004E536 isLocallyControlled 0x0028B07A
// getControllingPlayer 0x0028AFA9 the squad lookup 0x002AA191
// addIconLayer 0x00239FCC and Keyboard::isShift 0x00232683.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

typedef int Int;
typedef float Real;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_2 = 2
};

class Player;
class Drawable;

class ThingTemplate
{
public:
	Bool isKindOf2F() const { return (m_kindOf[0x2F >> 3] & (1 << (0x2F & 7))) != 0; }

	unsigned char m_pad00[0x0C];
	Int m_0C;					// +0x0C
	unsigned char m_pad10[0x108 - 0x10];
	unsigned char m_kindOf[0x10];			// +0x108
};

class Object
{
public:
	Bool rva0028D900(Real *height, Real *width);	// 0x0028D900
	Bool testStatus(ObjectStatusTypes status) const;	// 0x0004E536
	Bool isLocallyControlled() const;		// 0x0028B07A
	Player *getControllingPlayer() const;		// 0x0028AFA9
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x438 - 0x08];
	unsigned char m_privateStatus;			// +0x438
};

class Rva002AA191
{
public:
	Int rva002AA191(const Object *obj);		// 0x002AA191, squad number
};

class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;		// 0x00276470, the position
};

class View
{
public:
#define V(n) virtual void slot##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72)
	virtual Real getZoom();				// slot 73 (+0x124)
	V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
#undef V
	virtual Int worldToScreen(const Coord3D *world, ICoord2D *screen);	// slot 88 (+0x160)
};
extern View *TheTacticalView;

class ScriptEngine
{
public:
	Int getFade() const { return m_fade; }
private:
	unsigned char m_pad00[0x1A138];
	Int m_fade;					// +0x1A138
};
extern ScriptEngine *TheScriptEngine;

class GameClient
{
public:
	void addIconLayer(Int layer, Drawable *draw);	// 0x00239FCC
};
extern GameClient *TheGameClient;

class Keyboard
{
public:
	Bool isShift();					// 0x00232683
};
extern Keyboard *TheKeyboard;

class Drawable
{
public:
	void drawIconUI();
	void rva002775C9(Coord3D *pos);			// 0x002775C9, the health box position

	const Coord3D *getPosition() const { return ((const Rva00276470Drawable *)this)->rva00276470(); }
	Object *getObject() { return m_object; }

private:
	unsigned char m_pad00[0xFC];
	Object *m_object;				// +0xFC
	unsigned char m_pad100[0x43C - 0x100];
	Bool m_43C;					// +0x43C
	unsigned char m_pad43D[0x460 - 0x43D];
	IRegion2D m_healthBarRegion;			// +0x460
};

void Drawable::drawIconUI()
{
	if (TheGameLogic->getDrawIconUI() && TheScriptEngine->getFade() == 0)
	{
		Object *obj = getObject();
		if (!obj)
			return;

		Coord3D p;
		rva002775C9(&p);
		Real healthBoxWidth, healthBoxHeight;
		if (!obj->rva0028D900(&healthBoxHeight, &healthBoxWidth))
			return;

		ICoord2D screenCenter;
		if (TheTacticalView->worldToScreen(&p, &screenCenter))
		{
			if (!obj->testStatus(OBJECT_STATUS_2))
				return;
			Coord3D lowered;
			rva002775C9(&lowered);
			Real posZ = getPosition()->z;
			lowered.z -= (lowered.z - posZ) * 0.333f;
			ICoord2D loweredScreen;
			if (TheTacticalView->worldToScreen(&lowered, &loweredScreen))
				return;
		}

		Real zoom = TheTacticalView->getZoom();
		Real widthScale = 1.0f / zoom;
		Real heightScale = 1.0f;
		healthBoxWidth *= widthScale;
		healthBoxHeight *= heightScale;
		healthBoxHeight = 4.0f;

		m_healthBarRegion.lo.x = screenCenter.x - healthBoxWidth * 0.45f;
		m_healthBarRegion.lo.y = screenCenter.y - healthBoxHeight * 0.5f;
		m_healthBarRegion.hi.x = m_healthBarRegion.lo.x + healthBoxWidth;
		m_healthBarRegion.hi.y = m_healthBarRegion.lo.y + healthBoxHeight;

		TheGameClient->addIconLayer(0, this);
		if (obj->isEffectivelyDead() || obj->getTemplate()->isKindOf2F())
			return;
		TheGameClient->addIconLayer(1, this);
		TheGameClient->addIconLayer(2, this);
		if (TheKeyboard->isShift() && obj->getTemplate()->m_0C != -1)
			TheGameClient->addIconLayer(5, this);
		if (!m_43C)
			return;
		if (!obj->isLocallyControlled())
			return;
		Player *player = obj->getControllingPlayer();
		Int squad = ((Rva002AA191 *)player)->rva002AA191(obj);
		if (squad > -1 && squad < 10)
			TheGameClient->addIconLayer(3, this);
	}
}
