// cl: /O1 /Op /MD /EHsc /arch:SSE /ICode/Libraries/Include
//
// ?rva0053EDF4@Rva0053ED1A@@UAE?AUICoord2D@@XZ retail 0x0053EDF4 286B RET4.
// Target evidence: slot 4 of the +0xC vftable 0x00C6944C that
// ??0Rva0053ED1A (0x0053ED1A) installs, so ECX is the secondary subobject
// and [ecx+0x48] is the object's +0x54 int (zeroed by the ctor), passed to
// GameLogic::findObjectByID 0x00049DC5 as an ObjectID. It projects the
// object's screen point: skip when the template's KindOf bit 14 (+0x108)
// is set; start from the drawable's position (Object 0x005508E2 /
// Drawable 0x002763E6) or the object's +0x38 position; on a successful
// "Menu" best-contact query (0x002904DC) add the contact's offset from the
// object position, else lift Z by half of GeometryInfo (+0xA8)
// getMaxHeightAbovePosition 0x006BD7C0; project through TheTacticalView's
// virtual slot 88 (+0x160); -999,-999 when off screen or unavailable.
// WorldBuilder twin 0x01116650 (same strings and call graph) shows the
// MathCoord3D.h operator-=/operator+= calls and a user-constructed Coord3D
// (default and (0,0,0) ctors), carried here through Lib/Coord3DCtorView.h:
// the POD triple schedules the offset arm differently. The slot name
// follows Zero Hour's View::worldToScreenTriReturn (donor fact); the method
// and owner names are generated.
#define COORD3D_VIEW_INLINE
#include "Lib/Coord3DCtorView.h"
#include "Lib/ICoord2D.h"
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

#include "../../Include/GameClient/Drawable.h"

#include "../../Include/Common/Geometry.h"

struct ScreenPositionTemplateView
{
	char m_pad[0x108];
	unsigned int m_kindOf[1];
	int isKindOf14() const { return m_kindOf[0] & (1u << 14); }
};

class Object
{
public:
	Drawable *getDrawable() const;
	bool getWorldspaceBestContactPoint(Coord3D *, const Coord3D *, const char *, int, int, bool) const;
	const ScreenPositionTemplateView *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	const GeometryInfo &getGeometryInfo() const { return m_geometry; }

private:
	char m_pad00[4];
	ScreenPositionTemplateView *m_template;
	char m_pad08[0x38 - 0x08];
	Coord3D m_position;
	char m_pad44[0xA8 - 0x44];
	GeometryInfo m_geometry;
};

#define SCREEN_VIEW_SLOT(n) virtual void slot##n();
#define SCREEN_VIEW_SLOTS8(a) SCREEN_VIEW_SLOT(a##0) SCREEN_VIEW_SLOT(a##1) SCREEN_VIEW_SLOT(a##2) SCREEN_VIEW_SLOT(a##3) \
	SCREEN_VIEW_SLOT(a##4) SCREEN_VIEW_SLOT(a##5) SCREEN_VIEW_SLOT(a##6) SCREEN_VIEW_SLOT(a##7)

class View;
extern View *TheTacticalView;

// TheTacticalView's slots 0..87 are opaque here; slot 88 is the projection.
class ScreenPositionTacticalView
{
public:
	SCREEN_VIEW_SLOTS8(s0) SCREEN_VIEW_SLOTS8(s1) SCREEN_VIEW_SLOTS8(s2) SCREEN_VIEW_SLOTS8(s3)
	SCREEN_VIEW_SLOTS8(s4) SCREEN_VIEW_SLOTS8(s5) SCREEN_VIEW_SLOTS8(s6) SCREEN_VIEW_SLOTS8(s7)
	SCREEN_VIEW_SLOTS8(s8) SCREEN_VIEW_SLOTS8(s9) SCREEN_VIEW_SLOTS8(sA)
	virtual int worldToScreenTriReturn(const Coord3D *world, ICoord2D *screen);
};

#include "../../Include/Common/GameEngineDeletingBase.h"

class Rva005C6D4D
{
public:
	virtual ~Rva005C6D4D();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual ICoord2D rva0053EDF4();
private:
	char m_pad04[0x38];
};

class Rva0053ED1A : public GameEngineDeletingBase, public Rva005C6D4D
{
public:
	virtual ICoord2D rva0053EDF4();
private:
	char m_vector48[0x0C];
	ObjectID m_objectID;
	int m_58;
};

ICoord2D Rva0053ED1A::rva0053EDF4()
{
	ICoord2D screen;
	Object *obj = TheGameLogic->findObjectByID(m_objectID);
	if (obj && !obj->getTemplate()->isKindOf14())
	{
		Coord3D world;
		Drawable *draw = obj->getDrawable();
		if (draw)
			world = *draw->getPosition();
		else
			world = *obj->getPosition();
		Coord3D contact(0, 0, 0);
		if (obj->getWorldspaceBestContactPoint(&contact, &contact, "Menu", 0, 0, false))
		{
			contact -= *obj->getPosition();
			world += contact;
		}
		else
		{
			world.z += obj->getGeometryInfo().getMaxHeightAbovePosition() * 0.5f;
		}
		if (((ScreenPositionTacticalView *)TheTacticalView)->worldToScreenTriReturn(&world, &screen) != 0)
		{
			screen.x = -999;
			screen.y = -999;
		}
	}
	else
	{
		screen.x = -999;
		screen.y = -999;
	}
	return screen;
}
