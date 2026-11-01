// cl: /O2 /DNDEBUG /MD /GX- /Ob2
// BFME2 adaptation: PC C0EBF0 Geometry -> ABFEE0; full105B.
// Existing BFME1 donor reproduced below. PC scanIndexList is a member;
// retail default construction also sets shape flag +21 to true.
// Open-BFME: GeometryInfo::parseGeometryType, retail 0x00880480.
//
// ThingTemplate registers this callback for both Geometry fields.  The body
// parses through the canonical GeometryNames table, grows GeometryInfo's
// 0x24-byte shape vector at +0x2C, writes the selected type into its first
// element, and tail-calls calcBoundingStuff.
//
// Modeling the real nested Coord3D and string members is material here.  Their
// inline default construction preserves retail's constant/load schedule; a
// flat collection of volatile scalar fields emits the same stores in a
// different order around the saved scan result.

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
class Xfer;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

// Native9DBFE0..9DBFF0: three enum names followed by the null sentinel.
// The parser's scanIndexList consumes the table; unrelated scalar defaults
// begin at9DBFF0, establishing the complete16B extent.
extern const char *const GeometryNames[] = { "SPHERE", "CYLINDER", "BOX", 0 };

#include "../../../Include/Common/INI/INI.h"

struct BfmeCoord3D
{
	__forceinline BfmeCoord3D() throw() : x(0.0f), y(0.0f), z(0.0f) {}

	float x;
	float y;
	float z;
};

class BfmeAsciiString
{
public:
	__forceinline BfmeAsciiString() throw() : m_data(0) {}

private:
	char *m_data;
};

struct BfmeElem60
{
	__forceinline BfmeElem60() throw()
		: m_type(0), m_height(1.0f), m_majorRadius(1.0f),
		  m_minorRadius(1.0f), m_center(), m_name(), m_enabled(true), m_flag21(true)
	{
	}

	__forceinline BfmeElem60(const BfmeElem60 &other) throw()
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_minorRadius = other.m_minorRadius;
		m_center = other.m_center;
		m_name = other.m_name;
		m_enabled = other.m_enabled;
        m_flag21 = other.m_flag21;
	}

	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	BfmeCoord3D m_center;
	BfmeAsciiString m_name;
	unsigned char m_enabled;
	unsigned char m_flag21;
    unsigned char m_padding[2];
};

class BfmeVec60
{
public:
	void resize(unsigned int count, BfmeElem60 value) throw();
	void resize(unsigned int count) throw();
	int size() const { return m_end - m_begin; }

	BfmeElem60 *m_begin;
	BfmeElem60 *m_end;
	BfmeElem60 *m_capacity;
};

struct GeometryXferVersion
{
	GeometryXferVersion(unsigned char minimum, unsigned char current) : m_minimum(minimum), m_current(current) {}
	unsigned char m_minimum;
	unsigned char m_current;
};

// Retail string 0x00CE7AA8 "GeometryType" (defined in ConstIntGettersAddr.cpp).
extern const char s_geometryTypeString[];

#include "XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

class GeometryInfo : public Snapshot
{
public:
	static void parseGeometryType(INI *, void *, void *, const void *);
	virtual void DoXfer(Xfer &xfer);

private:
	unsigned char m_isSmall; // +0x04
	char m_pad05[3];
	int m_08;
	int m_0c;
	float m_boundingCircleRadius; // +0x10
	float m_boundingSphereRadius; // +0x14
	BfmeCoord3D m_center18; // +0x18
	float m_24;
	float m_28;
	BfmeVec60 m_shapes; // +0x2C
	char m_38[12];
	BfmeCoord3D m_44;
	BfmeCoord3D m_50;

public:
private:
	void calcBoundingStuff() throw();
	friend class BfmeAsciiString;
	friend class BfmeCoord3D;
	friend class BfmeElem60;
	friend class BfmeVec60;
	friend class INI;
};

void GeometryInfo::parseGeometryType(INI *ini, void *, void *store, const void *)
{
	int type = ini->scanIndexList(ini->getNextToken(0), GeometryNames);
	GeometryInfo *geometry = (GeometryInfo *)store;
	geometry->m_shapes.resize(1, BfmeElem60());
	geometry->m_shapes.m_begin->m_type = type;
	geometry->calcBoundingStuff();
}

// ?resize@BfmeVec60@@QAEXI@Z @0x006BFE60 63B: the one-argument resize, which
// builds a default BfmeElem60 straight into the by-value argument slot and
// calls the rowed two-argument resize 0x006BFCB0.
void BfmeVec60::resize(unsigned int count) throw()
{
	resize(count, BfmeElem60());
}

// ?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z retail 0x006C0030..0x006C01B0
// (384 bytes, ret 4): slot 3 of the GeometryInfo snapshot table 0x00BC4E94.
// Target facts: skipped under the light CRC (Xfer slot 4); xfers a
// two-byte version {1, 2} (slot 10), the +0x04 isSmall flag (slot 36), the
// shape count (slot 31) of the 0x24-byte shape vector at +0x2C, resizes it
// through the inline one-argument resize (a default shape built straight
// into the by-value argument of the rowed two-argument resize 0x006BFCB0,
// matching the out-of-line copy 0x006BFE60), then per shape xfers the type
// through slot 37 with the "GeometryType" string 0x00CE7AA8 and size 4,
// height/major/minor radii (slot 28), the offset Coord3D (slot 24) and,
// for version > 1, the enabled byte at +0x20; finally +0x10/+0x14/+0x24/+0x28
// (slot 28) and the Coord3Ds +0x18/+0x44/+0x50 (slot 24).
// Donor carry: Zero Hour Geometry.cpp GeometryInfo::xfer field order
// (type, height, major, minor; then bounding radii); BFME 2's shape vector,
// version byte pair and Coord3D members are target facts from retail. The
// member names past the shape vector are structural, not donor-proven.
void GeometryInfo::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;

	GeometryXferVersion version(1, 2);
	xfer == reinterpret_cast<Xfer::Version &>(version);
	xfer == reinterpret_cast<bool &>(m_isSmall);

	int count = m_shapes.size();
	xfer == count;
	m_shapes.resize(count);
	for (int i = 0; i < count; ++i)
	{
		BfmeElem60 *shape = &m_shapes.m_begin[i];
		xfer.XferEnum(s_geometryTypeString, &shape->m_type, sizeof(shape->m_type));
		xfer == shape->m_height;
		xfer == shape->m_majorRadius;
		xfer == shape->m_minorRadius;
		xfer == reinterpret_cast<Coord3DBase &>(shape->m_center);
		if (version.m_current > 1)
			xfer == reinterpret_cast<bool &>(shape->m_enabled);
	}

	xfer == m_boundingCircleRadius;
	xfer == m_boundingSphereRadius;
	xfer == m_24;
	xfer == m_28;
	xfer == reinterpret_cast<Coord3DBase &>(m_center18);
	xfer == reinterpret_cast<Coord3DBase &>(m_44);
	xfer == reinterpret_cast<Coord3DBase &>(m_50);
}
