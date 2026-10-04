// ?Rva00422377Get@@YAXPAURva00422377Out@@PAURva00422377In@@@Z
// partial score=0.88 date=2026-10-04
// ?Rva00422377Get@@YAXPAURva00422377Out@@PAURva00422377In@@@Z
// partial score=0.9 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva00422377Get@@YAXPAURva00422377Out@@PAURva00422377In@@@Z retail 0x00422377 232 bytes.
// Free function: if in==0 outputs 0,0 else scales boundingCircle (info+0x10 at in+0xB8)
// by g_Va00BC28F4 plus g_Va00BBB8D8; when flag byte at [in+4]+0x11F has bit 4 set,
// builds a default GeometryShape temp, fills it via rowed GeometryInfo::rva006BD9C0
// at in+0xA8, then scales its major/minor by g_Va00BC28F4 plus g_00BC2918.
// Evidence: callees 0x006BD9C0 rowed 0x00036410 rowed, floats g_Va00BC28F4 g_Va00BBB8D8
// g_00BC2918, caller 0x00424930 in 0x0042481E, neighbours deque TUs same flags.
#include "ascii_string.h"

extern float g_Va00BC28F4;
extern float g_Va00BBB8D8;
extern float g_00BC2918;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	Coord3D m_offset;
	AsciiString m_name;
	bool m_enabled;
	char m_21[3];
	int m_2C;
};

class GeometryInfo
{
public:
	void rva006BD9C0(GeometryShape &out) const;
private:
	char _00[0x10];
public:
	float m_10;
private:
	char _14[0x24];
};

struct Rva00422377Flag
{
	char _00[0x11F];
	unsigned char m_11F;
};

struct Rva00422377In
{
	char _00[4];
	Rva00422377Flag *m_04;
	char _08[0xA0];
	GeometryInfo m_a8;
};

struct Rva00422377Out
{
	int m_00;
	int m_04;
};

// ?Rva00422377Get@@YAXPAURva00422377Out@@PAURva00422377In@@@Z present-unmatched
void Rva00422377Get(Rva00422377Out *out, Rva00422377In *in)
{
	if (!in)
	{
		out->m_00 = 0;
		out->m_04 = 0;
		return;
	}
	float scaled = in->m_a8.m_10 * g_Va00BC28F4;
	Rva00422377Flag *flag = in->m_04;
	float f = scaled + g_Va00BBB8D8;
	int y = (int)f;
	int x = y;
	if ((flag->m_11F & 4) != 0)
	{
		GeometryShape shape;
		shape.m_type = 0;
		shape.m_height = g_Va00BBB8D8;
		shape.m_majorRadius = g_Va00BBB8D8;
		shape.m_minorRadius = g_Va00BBB8D8;
		shape.m_offset.x = 0.0f;
		shape.m_offset.y = 0.0f;
		shape.m_offset.z = 0.0f;
		shape.m_enabled = true;
		shape.m_21[0] = 1;
		in->m_a8.rva006BD9C0(shape);
		shape.m_2C = -1;
		shape.m_name.~AsciiString();
		float majorScaled = shape.m_majorRadius * g_Va00BC28F4 + g_00BC2918;
		y = (int)majorScaled;
		float minorScaled = shape.m_minorRadius * g_Va00BC28F4 + g_00BC2918;
		x = (int)minorScaled;
	}
	out->m_00 = x;
	out->m_04 = y;
}
