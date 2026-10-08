// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?rva000B61AB@W3DScriptedModelDraw@@UAEMXZ, retail 0x000B61AB..0x000B6253
// (168 bytes): a float virtual inherited unchanged by the W3D draw vtables
// that also carry the rowed W3DScriptedModelDraw::getButtonImage (slot 50 of
// the draw-module tables, slot 51 of W3DTruckDraw's DrawInterface8C table);
// WorldBuilder's twin (0x00949E50) is unnamed, so the method keeps an
// address-derived name. A drawable whose object's template carries the 0x40
// flag (+0x108) answers four times its geometry's maximum height (rowed
// geometry getter 0x00270FEE, rowed GeometryInfo::getMaxHeightAbovePosition).
// Otherwise, when the drawable's template flags (+0x5E2) hold 0x386 -- or
// 0xC000 while TheWritableGlobalData's +0x60 flag is set -- and this module's
// +0x4A flag is set, it answers twice the drawable's height above the ground
// (TheTerrainLogic's slot 6, pinned getPosition 0x00276470) plus that maximum
// height; else zero.

#include "Coord3D.h"

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class TerrainLogic
{
public:
	virtual void t0();
	virtual void t1();
	virtual void t2();
	virtual void t3();
	virtual void t4();
	virtual void t5();
	virtual float getGroundHeight(float x, float y, Coord3D *normal);
};

extern TerrainLogic *TheTerrainLogic;

class GlobalData
{
public:
	unsigned char m_pad00[0x60];
	bool m_60;
};

extern GlobalData *TheWritableGlobalData;

struct Rva000B61ABObjectTemplate
{
	unsigned char m_pad000[0x108];
	unsigned char m_flags108;
};

struct Rva000B61ABObject
{
	unsigned char m_pad00[0x04];
	Rva000B61ABObjectTemplate *m_template04;
};

struct Rva000B61ABDrawTemplate
{
	unsigned char m_pad000[0x5E2];
	unsigned short m_flags5E2;
};

// The rowed geometry getter of the drawable (0x00270FEE).
class Rva00270FEE
{
public:
	char *rva00270FEE();
};

class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
	const GeometryInfo *getGeometry() { return (const GeometryInfo *)reinterpret_cast<Rva00270FEE *>(this)->rva00270FEE(); }

	unsigned char m_pad000[0x04];
	Rva000B61ABDrawTemplate *m_template04;	// +0x04
	unsigned char m_pad008[0xFC - 0x08];
	Rva000B61ABObject *m_objectFC;			// +0xFC
};

class W3DScriptedModelDraw
{
public:
	virtual float rva000B61AB();
private:
	unsigned char m_pad04[0x08 - 0x04];
	Rva00276470Drawable *m_drawable;		// +0x08
	unsigned char m_pad0C[0x4A - 0x0C];
	bool m_4a;								// +0x4A
};

float W3DScriptedModelDraw::rva000B61AB()
{
	Rva00276470Drawable *draw = m_drawable;
	Rva000B61ABObject *obj = draw->m_objectFC;
	Rva000B61ABDrawTemplate *tmpl = draw->m_template04;
	if (obj && (obj->m_template04->m_flags108 & 0x40))
		return draw->getGeometry()->getMaxHeightAbovePosition() * 4.0f;
	unsigned short flags = tmpl->m_flags5E2;
	if (!((flags & 0x386) || ((flags & 0xC000) && TheWritableGlobalData->m_60)) || !m_4a)
		return 0.0f;
	const Coord3D *p = draw->rva00276470();
	Coord3D pos;
	pos.x = p->x;
	pos.y = p->y;
	pos.z = p->z;
	float above = pos.z - TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
	return (m_drawable->getGeometry()->getMaxHeightAbovePosition() + above) * 2.0f;
}
