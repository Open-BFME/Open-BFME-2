// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// Object overrides of its +0x64 and +0x70 interface subobjects. Identity: the
// vtables 0x00BFC2D8 (+0x64) and 0x00BFC290 (+0x70) are stored by 0x00298EA9,
// the constructor the object factory at 0x0023CAE7 calls right after new(0x4D8),
// and by its destructor 0x00299CE4; the bodies read Object fields through the
// subobject this (template +0x04, position +0x38, GeometryInfo +0xA8) and sit
// in the retail Object.cpp range. Slot names are not established, hence
// address names.
// Retail 0x00290EE0 (30 bytes), +0x64 slot 0: returns the template AsciiString
// at +0x64 by value.
// Retail 0x0028C037 / 0x0028C08D (86 bytes each), +0x70 slots 0 and 1: the
// bounding box min / max corner, position minus / plus the GeometryInfo +0x10
// radius in x and y and the matched getMaxHeightBelowPosition /
// getMaxHeightAbovePosition in z. Retail copies the position member by member
// (Coord3D with a memberwise copy ctor) and builds the returned value in place
// (named result constructed with z, then x and y adjusted).

#include "ascii_string.h"
typedef float Real;
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	Coord3D(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
	float x;
	float y;
	float z;
};
class GeometryInfo
{
	friend class Object;
public:
	float getMaxHeightBelowPosition() const;
	float getMaxHeightAbovePosition() const;
private:
	unsigned char m_pad00[0x10];
	float m_10; // +0x10
	unsigned char m_pad14[0x5C - 0x14];
};
class ThingTemplate
{
public:
	const AsciiString &rva00290EE0Name() const { return m_64; }
private:
	unsigned char m_pad[0x64];
	AsciiString m_64; // +0x64
};
class ObjectBase
{
public:
	virtual ~ObjectBase();
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
private:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x64 - 0x44];
};
class Rva00290EE0Iface64
{
public:
	virtual AsciiString rva00290EE0() = 0;
private:
	unsigned char m_pad[0x70 - 0x68];
};
class Rva0028C037Iface70
{
public:
	virtual Coord3D rva0028C037() = 0;
	virtual Coord3D rva0028C08D() = 0;
private:
	unsigned char m_pad[0xA8 - 0x74];
};
class Object : public ObjectBase, public Rva00290EE0Iface64, public Rva0028C037Iface70
{
public:
	virtual AsciiString rva00290EE0();
	virtual Coord3D rva0028C037();
	virtual Coord3D rva0028C08D();
private:
	GeometryInfo m_geometryInfo; // +0xA8
};
Coord3D Object::rva0028C037()
{
	const GeometryInfo *geom = &m_geometryInfo;
	Coord3D pos = *getPosition();
	Coord3D result(pos.x, pos.y, pos.z - geom->getMaxHeightBelowPosition());
	result.x -= geom->m_10;
	result.y -= geom->m_10;
	return result;
}
Coord3D Object::rva0028C08D()
{
	const GeometryInfo *geom = &m_geometryInfo;
	Coord3D pos = *getPosition();
	Coord3D result(pos.x, pos.y, pos.z + geom->getMaxHeightAbovePosition());
	result.x += geom->m_10;
	result.y += geom->m_10;
	return result;
}
AsciiString Object::rva00290EE0()
{
	return getTemplate()->rva00290EE0Name();
}
