// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /Oy /G7 /arch:SSE
//
// ?createPotentialClaimDecal@Impl@PlaceTerrainResourceClaimantFeedback@@QAEXXZ @0x004E65CF 191B
// Leaf method on the 0x004E669A class (same this, +4/+8/+0xC/+0x1C): builds an
// Shadow::ShadowTypeInfo temp from the +4 param-block string, scales the +0xC
// float by 2.0f into its two sizes, adds it through g_00DEC2D4 slot 8 into +0x1C,
// then on success zeroes decal+0x20, applies texture 0xFFFF8000, copies rope
// position into decal+8 and sets +0x64/opacity. Evidence: rowed Shadow::ShadowTypeInfo
// ctor 0x00079514 plus StringBase set 0x000366F0 plus dtor 0x000793FA, manager
// at 0x009EC2D4 slot 8, float 2.0f at 0x007C28F4, pins for SetTexture 0x330995
// plus BFMERopeDrawable::getPosition 0x2763E6, rowed Shadow::setOpacity
// 0x3308F6, caller 0x004E6739, neighbours in same Bfme dir.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();
		AsciiString m_first;
		AsciiString m_second;
		int m_type;
		float m_floatC;
		float m_float10;
		float m_float14;
		float m_float18;
		float m_float1C;
		float m_float20;
		unsigned char m_byte24;
		unsigned char m_byte25;
		unsigned char m_byte26;
	};

	void setOpacity(int value);
};

struct Rva004E65CFParams
{
	AsciiString m_sound;
	AsciiString m_font;
	int m_size;
	unsigned char m_bold;
	char m_pad0D[3];
	int m_color;
};

struct Rva004E65CFFloatSrc
{
	char m_pad00[8];
	float m_f08;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};


class Rva00330995
{
public:
	void SetTexture(void *p);
	char m_pad00[8];
	Coord3D m_pos08;
	char m_pad14[12];
	float m_f20;
	char m_pad24[64];
	unsigned char m_b64;
};

class Rva004E65CFMgr
{
public:
	virtual ~Rva004E65CFMgr() {}
	virtual void s04() = 0;
	virtual Rva00330995 *play(Shadow::ShadowTypeInfo *ev) = 0;
};

extern Rva004E65CFMgr *g_00DEC2D4;
extern float g_Va00BC28F4;
// g_Va00BC28F4: matched references place it at VA 0xbc28f4 (retail .rdata value 2.0f).
float g_Va00BC28F4 = 2.0f;

struct ICoord2D { int x,y; };
class FeedbackDisplayString {
public:
 virtual void s00(); virtual void setText(UnicodeString text);
 virtual void s08(); virtual void s0C(); virtual void s10(); virtual void s14();
 virtual void s18(); virtual void s1C(); virtual void s20(); virtual void s24();
 virtual void setColor(unsigned int color,unsigned int shadow);
 virtual void s2C(); virtual void s30(); virtual void s34(); virtual void s38();
 virtual void getSize(int *width,int *height);
};

class PlaceTerrainResourceClaimantFeedback
{
public:
	class Impl;
};

class PlaceTerrainResourceClaimantFeedback::Impl
{
	void *m_00;
	Rva004E65CFParams *m_04;
	BFMERopeDrawable *m_08;
	Rva004E65CFFloatSrc *m_0C;
	FeedbackDisplayString *m_10;
	ICoord2D m_position;
	Rva00330995 *m_1C;
public:
	void createPotentialClaimDecal();
 void updateStringPos(ICoord2D *position);
};

void PlaceTerrainResourceClaimantFeedback::Impl::createPotentialClaimDecal()
{
	Shadow::ShadowTypeInfo ev;
	ev.m_first = m_04->m_sound;
	Rva004E65CFFloatSrc *p = m_0C;
	Rva004E65CFMgr *mgr = g_00DEC2D4;
	ev.m_byte25 = 0;
	ev.m_byte26 = 1;
	ev.m_type = 0x2000;
	float f = p->m_f08 * g_Va00BC28F4;
	ev.m_float10 = f;
	ev.m_floatC = f;
	m_1C = mgr->play(&ev);
	if (m_1C)
	{
		m_1C->m_f20 = 0.0f;
		m_1C->SetTexture((void *)0xFFFF8000);
		const Coord3D *pos = m_08->getPosition();
		Rva00330995 *decalForDest = m_1C;
		Coord3D *dest = &decalForDest->m_pos08;
		*dest = *pos;
		m_1C->m_b64 = 1;
		((Shadow *)m_1C)->setOpacity(0x80);
	}
}
// ?g_00DEC2D4@@3PAVRva004E65CFMgr@@A: the global at VA 0xdec2d4 is ?g_00DEC2D4@@3PAVAudioManager0029E159@@A.
#pragma comment(linker, "/alternatename:?g_00DEC2D4@@3PAVRva004E65CFMgr@@A=?g_00DEC2D4@@3PAVAudioManager0029E159@@A")

class Mouse;
class TacticalView;
extern Mouse *TheMouse;
extern TacticalView *TheTacticalView;
struct FeedbackMouseView { char pad[0x4F0C]; ICoord2D position; };
class FeedbackTacticalView {
public:
 virtual void s00();
 virtual void s04();
 virtual void s08();
 virtual void s0C();
 virtual void s10();
 virtual void s14();
 virtual void s18();
 virtual void s1C();
 virtual void s20();
 virtual void s24();
 virtual void s28();
 virtual void s2C();
 virtual void s30();
 virtual void s34();
 virtual void s38();
 virtual int width(); virtual void s40(); virtual int height();
};
// WB13249A0 independently names updateStringPos. Whole native4E6328..4E63DB
// RET4: input/mouse position, display-string size, centering and screen clamp.
// Three scalar clamp locals grouped in this order reproduce retail stack slots;
// the pointer-select min/max operations retain the native signed comparisons.
void PlaceTerrainResourceClaimantFeedback::Impl::updateStringPos(ICoord2D *p)
{
 if(p) m_position=*p;
 else m_position=((FeedbackMouseView*)TheMouse)->position;
 struct ClampBounds { int zero; int maxX; int height; } bounds;
 m_10->getSize((int*)&p,&bounds.height);
 bounds.zero=0;
 m_position.x+=(*(int*)&p)/-2;
 m_position.y+=-20-bounds.height;
 bounds.maxX=((FeedbackTacticalView*)TheTacticalView)->width()-(*(int*)&p);
 int *pp1=(bounds.maxX<m_position.x)?&bounds.maxX:&m_position.x;
 if(*pp1<0) pp1=&bounds.zero;
 int v1=*pp1;
 bounds.zero=0;
 m_position.x=v1;
 int t2=((FeedbackTacticalView*)TheTacticalView)->height()-bounds.height;
 int *pp2=(t2<m_position.y)?&t2:&m_position.y;
 if(*pp2<0) pp2=&bounds.zero;
 m_position.y=*pp2;
}
