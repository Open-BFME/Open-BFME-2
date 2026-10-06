// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?getCDECount@BfmeOwnerCDE@@QAEHPAX@Z @0x0073D090 939B.
// BFME1 donor reference/open-bfme-1/game/GameEngine/Source/Common/BfmeOwnerCDECount.cpp
// getCDECount via rowed GeometryInfo::rva006BD9C0 0x006BD9C0 plus rowed bfmeStepsEU 0x0073B750.
// BFME2 deltas: theDebug stream with 3 args plus float 1.0 via g_Va00BBB8D8 and AsciiString temps.
// Caller at 0x0073D4B2 in rva008fa850. Prev stlport_deque / next BfmeOwnerCDECreate. LINK BONUS name.
#include "ascii_string.h"

class Debug;

class Debug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual Debug &slot20(float value);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(int report);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug &slot6c(int first, int second, int third);
};

extern Debug *theDebug;
extern float g_Va00BBB8D8;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

typedef bool Bool;
typedef float Real;

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct GeometryShape
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
	GeometryShape() : m_type(0), m_height(1), m_majorRadius(1), m_minorRadius(1), m_offsetX(0), m_offsetY(0), m_offsetZ(0), m_enabled(true), m_21(true) {}
};

class GeometryInfo
{
public:
	void rva006BD9C0(GeometryShape &out) const;
	void *m_vtbl;
	Bool m_isSmall;
	char m_pad05[3];
	int m_08;
	int m_0c;
	Real m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
};

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

#define NAMED_DEBUG (theDebug->slot6c(0, 0, 0).slot38("Geometry for ") << (const StringBase<char> &)object->name())
#define REPORT(msg) (bfmeRva000387C0() && (_bfme_debugRecordCallsite(1), theDebug->slot60(), (NAMED_DEBUG msg).slot4c(2), true))

int BfmeOwnerCDE::getCDECount(void *what)
{
	CountProvider008FA4B0 *object = (CountProvider008FA4B0 *)what;
	const GeometryInfo &geometry = object->geometry();
	GeometryShape shape;
	geometry.rva006BD9C0(shape);
	if (geometry.m_isSmall) {
		unsigned int count = ((BfmeHostEU *)this)->bfmeStepsEU((const BfmeShapeEU *)&shape);
		if (count >= 10000) {
			REPORT(.slot38(" is too large - INI error?\n"));
		} else if (count > 4) {
			switch (shape.m_type) {
				case 0:
				case 1:
					REPORT(.slot38(" is too large for a small object.\nReduce major radius to a value less than ").slot20(g_Va00BBB8D8 / (m_scale + m_scale)).slot38(" or make the geometry non-small.\n"));
					break;
				case 2:
					REPORT(.slot38(" is too large for a small object.\nReduce the length of the diagonal of the box to a value less than ").slot20(g_Va00BBB8D8 / (m_scale + m_scale)).slot38(" or make the geometry non-small.\nThe diagonal is calculated as SquareRoot( MajorRad*MajorRad + MinorRad*MinorRad ).\n"));
					break;
			}
		}
		return 4;
	} else {
		unsigned int count = ((BfmeHostEU *)this)->bfmeStepsEU((const BfmeShapeEU *)&shape);
		if (count >= 10000) {
			REPORT(.slot38(" is too large - INI error?\n"));
		}
		return count;
	}
}
