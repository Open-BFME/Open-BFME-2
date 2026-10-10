// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /Oy /G7 /arch:SSE /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep
//
// ?createPotentialClaimDecal@Impl@PlaceTerrainResourceClaimantFeedback@@QAEXXZ @0x004E65CF 191B
// Leaf method on the 0x004E669A class (same this, +4/+8/+0xC/+0x1C): builds an
// Shadow::ShadowTypeInfo temp from the +4 param-block string, scales the +0xC
// float by 2.0f into its two sizes, adds it through g_00DEC2D4 slot 8 into +0x1C,
// then on success zeroes decal+0x20, applies texture 0xFFFF8000, copies rope
// position into decal+8 and sets +0x64/opacity. Evidence: rowed Shadow::ShadowTypeInfo
// ctor 0x00079514 plus StringBase set 0x000366F0 plus dtor 0x000793FA, manager
// at 0x009EC2D4 slot 8, float 2.0f at 0x007C28F4, pins for SetTexture 0x330995
// plus Drawable::getPosition 0x2763E6, rowed Shadow::setOpacity
// 0x3308F6, caller 0x004E6739, neighbours in same Bfme dir.
#include "ascii_string.h"
#include "unicode_string.h"
#include "wwmath.h"

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
 char m_pad0C[8];
 bool m_flag14;
};

class Drawable
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

class FeedbackTextInterface {
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
 virtual UnicodeString fetch(const char *label,bool *exists);
};
class GameTextInterface;
extern GameTextInterface *TheGameText;
class PlaceTerrainResourceClaimantFeedback
{
public:
	class Impl;
};

class PlaceTerrainResourceClaimantFeedback::Impl
{
	void *m_00;
	Rva004E65CFParams *m_04;
	Drawable *m_08;
	Rva004E65CFFloatSrc *m_0C;
	FeedbackDisplayString *m_10;
	ICoord2D m_position;
	Rva00330995 *m_1C;
public:
	void createPotentialClaimDecal();
 float rva004E6295();
 void updateStringPos(ICoord2D *position);
 void update(ICoord2D *position);
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
class View;
extern Mouse *TheMouse;
extern View *TheTacticalView;
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

class GameLogic;
class PlayerList;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
struct FeedbackPlayerIndexView { char pad[0x54]; int index; };
class TerrainResourceManager { public: float rva00359A0C(float x, float y, float radius, bool flag, int playerIndex); };
// WB1324880 and retail4E6295..4E630C: local player INDEX is an int,
// not the pointer view in the prior bank. The final claim-fraction helper
// at359A0C consumes five arguments and ends RET20; original name unknown.
float PlaceTerrainResourceClaimantFeedback::Impl::rva004E6295()
{
 GameLogic *logic=TheGameLogic;
 if(logic) {
  TerrainResourceManager *view=*(TerrainResourceManager **)((char*)logic+0x170);
  if(view) {
   FeedbackPlayerIndexView *player=*(FeedbackPlayerIndexView **)((char*)ThePlayerList+0x10);
   int index=player ? player->index : 0;
   Rva004E65CFFloatSrc *data=m_0C;
   const Coord3D *position=m_08->getPosition();
   return view->rva00359A0C(position->x,m_08->getPosition()->y,data->m_f08,data->m_flag14,index);
  }
 }
 return 0.0f;
}

// WB1324400 names update at line142. RGB bytes preserve the native
// conditional initialization: the decal tail uses the same bytes.
// ZH WWMath::Float_To_Long(float), committed donor874, is the existing
// x87 conversion primitive: ordinary casts emit __ftol2 and /QIfist
// cannot be combined with retail SSE. The remainder is clean C++.
// Native4E6455..4E65CF RET4; both local helpers are separately exact.
void PlaceTerrainResourceClaimantFeedback::Impl::update(ICoord2D *position)
{
 unsigned char r,g,b;
 if(m_10) {
  UnicodeString format=((FeedbackTextInterface*)TheGameText)->fetch("GUI:TerrainResourcePercentageClaimable",0);
  UnicodeString text;
  int percent=WWMath::Float_To_Long((float)floor(rva004E6295()*100.0f+0.5f));
  text.format(format.str(),percent);
  m_10->setText(text);
  updateStringPos(position);
  float fraction=rva004E6295();
  if(fraction>0.75f) { r=0;g=255;b=0; }
  else if(fraction>=0.5f) {r=255;g=255;b=0;}
  else if(fraction>=0.25f) {r=255;g=0;b=0;}
  else {r=0;g=0;b=0;}
  m_10->setColor((255u<<24)|((unsigned)r<<16)|((unsigned)g<<8)|b,255u<<24);
 }
 if(m_1C) {
  m_1C->SetTexture((void*)((255u<<24)|((unsigned)r<<16)|((unsigned)g<<8)|b));
  const Coord3D *pos=m_08->getPosition();
  m_1C->m_pos08=*pos;
 }
}

