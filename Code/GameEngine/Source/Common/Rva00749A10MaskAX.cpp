// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Include
// Native ADF90..AE13E, RET12: circumscribed bounds and a strict circle test.
// Same-this call ADA1A proves the already-rowed bit setter's receiver view.
// The target border is +10; width/height8/C agree with the setter's accesses.
// Related BFME1 575ba2b04 WorldHeightMap conversion code is a math/rounding
// guide, not proof of the unknown original method or point type. Only the
// observed two float components are modeled. Existing basetype rounding
// supports native x87 conversion alongside SSE (/QIfist is incompatible).
// Reuse the owned TheTerrainRenderObject global atDE1EAC; only its observed
// vtable slot136 and three stack arguments are described by the notifier.
#include "basetype.h"

struct MaskCirclePoint {
    float x, y;
    __forceinline MaskCirclePoint(const MaskCirclePoint &point)
    {
        x = point.x;
        y = point.y;
    }
};
struct MaskCircleBounds { int xMin,yMin,xMax,yMax; };
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;


// Near-twin of BfmeMaskAX::bfmeMarkAX (twin 0x00749830, BfmeMaskAX.cpp):
// identical two-dimensional bounds-checked bit setter, only the padding
// before the begin/end byte-range pointers differs (0x3C bytes here instead
// of 0x0C), moving m_bits from +0x44/+0x48 to +0x74/+0x78. Concrete class
// identity is not present in the available BFME source or symbols, so the
// address-derived class name is intentional.

struct Rva00749A10Bytes
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char &operator[](int index) { return m_begin[index]; }
};

class Rva00749A10MaskAX
{
public:
	void bfmeMarkAX(int x, int y, unsigned char value);

private:
	char m_pad00[8];
	int m_width;
	int m_height;
	char m_pad10[0x24];
	int m_pitch;
	char m_pad38[0x3C];
	Rva00749A10Bytes m_bits;
};

// address-derived: ?bfmeMarkAX@Rva00749A10MaskAX@@QAEXHHE@Z
void Rva00749A10MaskAX::bfmeMarkAX(int x, int y, unsigned char value)
{
	Rva00749A10MaskAX *self = this;

	if (x < 0)
		return;
	if (y < 0)
		return;
	if (y >= self->m_height)
		return;
	if (x >= self->m_width)
		return;

	int index = self->m_pitch * y + (x >> 3);
	if ((unsigned int)index >= self->m_bits.size())
		return;

	unsigned char *slot = self->m_bits.m_begin + index;
	if (value)
		*slot |= (unsigned char)(1 << (x & 7));
	else
		*slot &= (unsigned char)~(1 << (x & 7));
}

// Whole clean donor Rva007498E0MaskMark.cpp at BFME1 revision
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 supplies this sibling's
// control-flow lead. Independent complete Ghidra entry ADA1A/83 and
// native RET12 prove signed x/y bounds against +8/+C, stride +34,
// begin/end +50/+54, and a byte set/clear selected by the third argument.
// The existing ADADC/83 sibling above has the same verified transfer
// pattern with its separate buffer at +74/+78. This declares only a
// distinct observed prefix; original owners, names, unused fields and
// any relationship between these owners remain unknown.
struct Rva000ADA1AMaskBytes
{
    unsigned char *begin;
    unsigned char *end;

    // ?Rva000ADA1AMaskBytes::size present-unmatched
    unsigned size() const { return (unsigned)(end - begin); }
};

class Rva000ADA1AMask
{
public:
    void markBit(int x, int y, unsigned char value);
    void rva000ADF90(const MaskCirclePoint*,float,unsigned char);
private:
    unsigned char reserved00[8];
    int width;
    int height;
    int border; // native circle body observes +0x10
    unsigned char reserved14[0x20];
    int pitch;
    unsigned char reserved38[0x18];
    Rva000ADA1AMaskBytes bits;
};

void Rva000ADA1AMask::markBit(int x, int y, unsigned char value)
{
    Rva000ADA1AMask *self = this;
    if (x < 0)
        return;
    if (y < 0)
        return;
    if (y >= self->height)
        return;
    if (x >= self->width)
        return;

    int index = self->pitch * y + (x >> 3);
    if ((unsigned int)index >= self->bits.size())
        return;

    unsigned char *slot = self->bits.begin + index;
    if (value)
        *slot |= (unsigned char)(1 << (x & 7));
    else
        *slot &= (unsigned char)~(1 << (x & 7));
}

class MaskCircleTerrainNotify { public:
 virtual void unused0();
 virtual void unused1();
 virtual void unused2();
 virtual void unused3();
 virtual void unused4();
 virtual void unused5();
 virtual void unused6();
 virtual void unused7();
 virtual void unused8();
 virtual void unused9();
 virtual void unused10();
 virtual void unused11();
 virtual void unused12();
 virtual void unused13();
 virtual void unused14();
 virtual void unused15();
 virtual void unused16();
 virtual void unused17();
 virtual void unused18();
 virtual void unused19();
 virtual void unused20();
 virtual void unused21();
 virtual void unused22();
 virtual void unused23();
 virtual void unused24();
 virtual void unused25();
 virtual void unused26();
 virtual void unused27();
 virtual void unused28();
 virtual void unused29();
 virtual void unused30();
 virtual void unused31();
 virtual void unused32();
 virtual void unused33();
 virtual void unused34();
 virtual void unused35();
 virtual void unused36();
 virtual void unused37();
 virtual void unused38();
 virtual void unused39();
 virtual void unused40();
 virtual void unused41();
 virtual void unused42();
 virtual void unused43();
 virtual void unused44();
 virtual void unused45();
 virtual void unused46();
 virtual void unused47();
 virtual void unused48();
 virtual void unused49();
 virtual void unused50();
 virtual void unused51();
 virtual void unused52();
 virtual void unused53();
 virtual void unused54();
 virtual void unused55();
 virtual void unused56();
 virtual void unused57();
 virtual void unused58();
 virtual void unused59();
 virtual void unused60();
 virtual void unused61();
 virtual void unused62();
 virtual void unused63();
 virtual void unused64();
 virtual void unused65();
 virtual void unused66();
 virtual void unused67();
 virtual void unused68();
 virtual void unused69();
 virtual void unused70();
 virtual void unused71();
 virtual void unused72();
 virtual void unused73();
 virtual void unused74();
 virtual void unused75();
 virtual void unused76();
 virtual void unused77();
 virtual void unused78();
 virtual void unused79();
 virtual void unused80();
 virtual void unused81();
 virtual void unused82();
 virtual void unused83();
 virtual void unused84();
 virtual void unused85();
 virtual void unused86();
 virtual void unused87();
 virtual void unused88();
 virtual void unused89();
 virtual void unused90();
 virtual void unused91();
 virtual void unused92();
 virtual void unused93();
 virtual void unused94();
 virtual void unused95();
 virtual void unused96();
 virtual void unused97();
 virtual void unused98();
 virtual void unused99();
 virtual void unused100();
 virtual void unused101();
 virtual void unused102();
 virtual void unused103();
 virtual void unused104();
 virtual void unused105();
 virtual void unused106();
 virtual void unused107();
 virtual void unused108();
 virtual void unused109();
 virtual void unused110();
 virtual void unused111();
 virtual void unused112();
 virtual void unused113();
 virtual void unused114();
 virtual void unused115();
 virtual void unused116();
 virtual void unused117();
 virtual void unused118();
 virtual void unused119();
 virtual void unused120();
 virtual void unused121();
 virtual void unused122();
 virtual void unused123();
 virtual void unused124();
 virtual void unused125();
 virtual void unused126();
 virtual void unused127();
 virtual void unused128();
 virtual void unused129();
 virtual void unused130();
 virtual void unused131();
 virtual void unused132();
 virtual void unused133();
 virtual void unused134();
 virtual void unused135();
 virtual void updateCircle(const MaskCircleBounds*,Rva000ADA1AMask*,int);
};

void Rva000ADA1AMask::rva000ADF90(const MaskCirclePoint *center,float radius,unsigned char value) {
 int xMin=fast_float2long_round((float)floor((center->x-radius)*0.1f))+border;
 int yMin=fast_float2long_round((float)floor((center->y-radius)*0.1f))+border;
 if(xMin<0)xMin=0;
 if(yMin<0)yMin=0;
 int xMax=fast_float2long_round((float)ceil((center->x+radius)*0.1f))+border;
 int yMax=fast_float2long_round((float)ceil((center->y+radius)*0.1f))+border;
 if(xMax>width)xMax=width;
 if(yMax>height)yMax=height;
 float radius2=radius*radius;MaskCirclePoint p(*center);p.x+=border*10.0f;p.y+=border*10.0f;float centerX=p.x,centerY=p.y;
 for(int x=xMin;x<xMax;++x) {
  for(int y=yMin;y<yMax;++y) {
   float dx=((float)x+0.5f)*10.0f-centerX;
   float dy=((float)y+0.5f)*10.0f-centerY;
   if(dx*dx+dy*dy<radius2)markBit(x,y,value);
  }
 }
 MaskCircleBounds bounds;bounds.xMin=xMin;bounds.yMin=yMin;bounds.xMax=xMax;bounds.yMax=yMax;
 MaskCircleTerrainNotify *terrain=(MaskCircleTerrainNotify*)TheTerrainRenderObject;
 if(terrain)terrain->updateCircle(&bounds,this,0);
}
