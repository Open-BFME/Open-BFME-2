// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?getCDECount@BfmeOwnerCDE@@QAEHPAX@Z @0x0073D090 939B.
// BFME1 donor reference/open-bfme-1/game/GameEngine/Source/Common/BfmeOwnerCDECount.cpp
// getCDECount via rowed GeometryInfo::rva006BD9C0 0x006BD9C0 plus rowed bfmeStepsEU 0x0073B750.
// BFME2 deltas: theDebug stream with 3 args plus float 1.0 via g_Va00BBB8D8 and AsciiString temps.
// Caller at 0x0073D4B2 in RegisterObject. Prev stlport_deque / next BfmeOwnerCDECreate. LINK BONUS name.
#include "ascii_string.h"

#include "debug.h"
extern float g_Va00BBB8D8;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

typedef bool Bool;
typedef float Real;

#include "../../../Libraries/Include/Lib/Coord3D.h"

// This function consumes the same 36-byte shape through a local layout view.
// Its inlined initializer has a different compiler body from the other
// GeometryShape units; retain their name for the external writer API.
struct GeometryShape;
struct BfmeCDEGeometryView
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Real m_offsetX;
	Real m_offsetY;
	Real m_offsetZ;
	AsciiString m_name;
	bool m_enabled;
	bool m_21;
	BfmeCDEGeometryView() : m_type(0), m_height(1), m_majorRadius(1), m_minorRadius(1), m_offsetX(0), m_offsetY(0), m_offsetZ(0), m_enabled(true), m_21(true) {}
};

#include "../../Include/Common/Geometry.h"

class CountVirtualBase008FA4B0
{
public:
	virtual const GeometryInfo &geometry();
};

class CountLeading008FA4B0
{
public:
	virtual AsciiString name();
};

class CountProvider008FA4B0 : public CountLeading008FA4B0, public virtual CountVirtualBase008FA4B0
{
};

class BfmeShapeEU
{
public:
	int m_kind;
	unsigned char m_pad[4];
	float m_a;
	float m_b;
};

class BfmeHostEU
{
public:
	int bfmeStepsEU(const BfmeShapeEU *s);
	unsigned char m_head[0x20];
	float m_scale;
};

class BfmeOwnerCDE : public BfmeHostEU
{
public:
	int getCDECount(void *what);
};

#define NAMED_DEBUG ((theDebug->CrashBegin(0, 0, 0) << "Geometry for ") << (const StringBase<char> &)object->name())
#define REPORT(msg) (bfmeRva000387C0() && (_bfme_debugRecordCallsite(1), theDebug->SkipNext(), (NAMED_DEBUG msg).CrashDone(2), true))

int BfmeOwnerCDE::getCDECount(void *what)
{
	CountProvider008FA4B0 *object = (CountProvider008FA4B0 *)what;
	const GeometryInfo &geometry = object->geometry();
	BfmeCDEGeometryView shape;
	geometry.rva006BD9C0(reinterpret_cast<GeometryShape &>(shape));
	if (geometry.m_isSmall) {
		unsigned int count = ((BfmeHostEU *)this)->bfmeStepsEU((const BfmeShapeEU *)&shape);
		if (count >= 10000) {
			REPORT(<< " is too large - INI error?\n");
		} else if (count > 4) {
			switch (shape.m_type) {
				case 0:
				case 1:
					REPORT(<< " is too large for a small object.\nReduce major radius to a value less than " << g_Va00BBB8D8 / (m_scale + m_scale) << " or make the geometry non-small.\n");
					break;
				case 2:
					REPORT(<< " is too large for a small object.\nReduce the length of the diagonal of the box to a value less than " << g_Va00BBB8D8 / (m_scale + m_scale) << " or make the geometry non-small.\nThe diagonal is calculated as SquareRoot( MajorRad*MajorRad + MinorRad*MinorRad ).\n");
					break;
			}
		}
		return 4;
	} else {
		unsigned int count = ((BfmeHostEU *)this)->bfmeStepsEU((const BfmeShapeEU *)&shape);
		if (count >= 10000) {
			REPORT(<< " is too large - INI error?\n");
		}
		return count;
	}
}
