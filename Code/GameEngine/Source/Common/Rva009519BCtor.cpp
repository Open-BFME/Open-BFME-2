// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ??0Rva009519B@@QAE@XZ retail 0x00215160 268 bytes: the default constructor
// of the CloudEffect record class Rva009519B (vtable 0x00BC81A8), whose slot
// 14 0x00214F14 (Rva00214F14Init.cpp) copies the CloudEffect settings into
// it and whose dtor is 0x0009519B (SubsystemDerivedDtors.cpp). Base ctor
// SubsystemInterface 0x001B4E63, then the vptr, then the members in order;
// the member types follow the slot-14 copies from the settings field table
// (VA 0x00BE5390). The object is 0xBC bytes; 1.0f is .rdata 0x00BBB8D8.
//
// Its own unit, not Rva00214F14Init.cpp: the vtable it emits reaches the
// dtor, and the dtor copy the link keeps (OpaqueScalarDeletingDtors.cpp's
// inline empty one) is not retail's, which would stop that unit linking too.
#include "ascii_string.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
private:
	int m_04;
	AsciiString m_name;
};

// The two darkening colours are zeroed by an inline default constructor
// (stored in member order), the shadow colour only by a chained assignment
// in the body (stored last, +0x6C first), so they are two types here; the
// names are not known.
struct RGBColor
{
	float red;
	float green;
	float blue;
};

struct ZeroedRGBColor
{
	ZeroedRGBColor() : red(0.0f), green(0.0f), blue(0.0f) {}

	float red;
	float green;
	float blue;
};

class GameClientRandomVariable
{
public:
	GameClientRandomVariable() { m_type = 0; m_low = 0.0f; m_high = 0.0f; }

private:
	int m_type;
	float m_low;
	float m_high;
};

// A position pair (the settings parse it with parseCoord2D) whose inline
// default constructor zeroes it; retail's Coord2D() (0x0047A6A9) is empty, so
// this is not that type and keeps a descriptive name.
struct ZeroedCoord2D
{
	ZeroedCoord2D() : x(0.0f), y(0.0f) {}

	float x;
	float y;
};

class Rva009519B : public SubsystemInterface
{
public:
	Rva009519B();
	virtual ~Rva009519B();
private:
	AsciiString m_0C;
	AsciiString m_10;
	AsciiString m_14;
	float m_18;
	float m_1C;
	bool m_20;
	AsciiString m_24;
	float m_28;
	float m_2C;
	ZeroedRGBColor m_30;
	ZeroedRGBColor m_3C;
	int m_48;
	int m_4C;
	float m_50;
	float m_54;
	float m_58;
	unsigned char m_5C;
	float m_60;
	RGBColor m_64;
	float m_70;
	GameClientRandomVariable m_74;
	float m_80;
	GameClientRandomVariable m_84;
	unsigned char m_90;
	unsigned char m_91;
	ZeroedCoord2D m_94;
	ZeroedCoord2D m_9C;
	ZeroedCoord2D m_A4;
	AsciiString m_AC;
	ZeroedCoord2D m_B0;
	int m_B8;
};

Rva009519B::Rva009519B() :
	m_18(0.0f),
	m_1C(0.0f),
	m_20(false),
	m_28(0.0f),
	m_2C(0.0f),
	m_48(0),
	m_4C(0),
	m_50(0.0f),
	m_54(0.0f),
	m_58(1.0f),
	m_5C(0),
	m_60(0.0f),
	m_70(0.0f),
	m_80(0.0f),
	m_90(0),
	m_91(0),
	m_B8(0)
{
	m_64.red = m_64.green = m_64.blue = 0.0f;
}
