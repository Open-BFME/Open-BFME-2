// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /Oy /G7 /arch:SSE /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep
//
// ?createPotentialClaimDecal@Impl@PlaceTerrainResourceClaimantFeedback@@QAEXXZ @0x004E65CF 191B
// Leaf method on the 0x004E669A class (same this, +4/+8/+0xC/+0x1C): builds an
// Shadow::ShadowTypeInfo temp from the +4 param-block string, scales the +0xC
// float by 2.0f into its two sizes, adds it through TheProjectedShadowManager slot 8 into +0x1C,
// then on success zeroes decal+0x20, applies texture 0xFFFF8000, copies rope
// position into decal+8 and sets +0x64/opacity. Evidence: rowed Shadow::ShadowTypeInfo
// ctor 0x00079514 plus StringBase set 0x000366F0 plus dtor 0x000793FA, manager
// at 0x009EC2D4 slot 8, float 2.0f at 0x007C28F4, pins for SetTexture 0x330995
// plus Drawable::getPosition 0x2763E6, rowed Shadow::setOpacity
// 0x3308F6, caller 0x004E6739, neighbours in same Bfme dir.
// All floor operations inline here; keep the unused wrapper local.
extern "C" { static float __cdecl floorf(float); }
#include "ascii_string.h"
#include "unicode_string.h"
#include "wwmath.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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
	float m_radius;
 char m_pad0C[8];
 bool m_flag14;
};

#include "../../../Include/GameClient/Drawable.h"


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

class AudioManager0029E159;
class ProjectedShadowManager;
extern ProjectedShadowManager *TheProjectedShadowManager;
extern float g_Va00BC28F4;
// g_Va00BC28F4: matched references place it at VA 0xbc28f4 (retail .rdata value 2.0f).
float g_Va00BC28F4 = 2.0f;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
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
	void rva004E6693(ICoord2D *position);
private:
	Impl *m_impl;	// +0
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
	Shadow::ShadowTypeInfo shadowInfo;
	shadowInfo.m_first = m_04->m_sound;
	Rva004E65CFFloatSrc *p = m_0C;
	Rva004E65CFMgr *shadowManager = (Rva004E65CFMgr *)TheProjectedShadowManager;
	shadowInfo.m_byte25 = 0;
	shadowInfo.m_byte26 = 1;
	shadowInfo.m_type = 0x2000;
	float decalSize = p->m_radius * g_Va00BC28F4;
	shadowInfo.m_float10 = decalSize;
	shadowInfo.m_floatC = decalSize;
	m_1C = shadowManager->play(&shadowInfo);
	if (m_1C)
	{
		m_1C->m_f20 = 0.0f;
		m_1C->SetTexture((void *)0xFFFF8000);
		const Coord3D *claimPosition = m_08->getPosition();
		Rva00330995 *decalForDest = m_1C;
		Coord3D *decalPosition = &decalForDest->m_pos08;
		*decalPosition = *claimPosition;
		m_1C->m_b64 = 1;
		((Shadow *)m_1C)->setOpacity(0x80);
	}
}

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
 int *clampedXSource=(bounds.maxX<m_position.x)?&bounds.maxX:&m_position.x;
 if(*clampedXSource<0) clampedXSource=&bounds.zero;
 int clampedX=*clampedXSource;
 bounds.zero=0;
 m_position.x=clampedX;
 int maxY=((FeedbackTacticalView*)TheTacticalView)->height()-bounds.height;
 int *clampedYSource=(maxY<m_position.y)?&maxY:&m_position.y;
 if(*clampedYSource<0) clampedYSource=&bounds.zero;
 m_position.y=*clampedYSource;
}

class GameLogic;
class PlayerList;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
struct FeedbackPlayerIndexView { char pad[0x54]; int index; };
#include "../../../Include/GameClient/TerrainResourceManager.h"
// WB1324880 and retail4E6295..4E630C: local player INDEX is an int,
// not the pointer view in the prior bank. The final claim-fraction helper
// at359A0C consumes five arguments and ends RET20; original name unknown.
float PlaceTerrainResourceClaimantFeedback::Impl::rva004E6295()
{
 GameLogic *gameLogic=TheGameLogic;
 if(gameLogic) {
  TerrainResourceManager *terrainResources=*(TerrainResourceManager **)((char*)gameLogic+0x170);
  if(terrainResources) {
   FeedbackPlayerIndexView *localPlayer=*(FeedbackPlayerIndexView **)((char*)ThePlayerList+0x10);
   int index=localPlayer ? localPlayer->index : 0;
   Rva004E65CFFloatSrc *data=m_0C;
   const Coord3D *position=m_08->getPosition();
   return terrainResources->rva00359A0C(position->x,m_08->getPosition()->y,data->m_radius,data->m_flag14,index);
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
 unsigned char red,g,b;
 if(m_10) {
  UnicodeString format=((FeedbackTextInterface*)TheGameText)->fetch("GUI:TerrainResourcePercentageClaimable",0);
  UnicodeString percentageText;
  int claimablePercent=WWMath::Float_To_Long((float)floor(rva004E6295()*100.0f+0.5f));
  percentageText.format(format.str(),claimablePercent);
  m_10->setText(percentageText);
  updateStringPos(position);
  float claimableFraction=rva004E6295();
  if(claimableFraction>0.75f) { red=0;g=255;b=0; }
  else if(claimableFraction>=0.5f) {red=255;g=255;b=0;}
  else if(claimableFraction>=0.25f) {red=255;g=0;b=0;}
  else {red=0;g=0;b=0;}
  m_10->setColor((255u<<24)|((unsigned)red<<16)|((unsigned)g<<8)|b,255u<<24);
 }
 if(m_1C) {
  m_1C->SetTexture((void*)((255u<<24)|((unsigned)red<<16)|((unsigned)g<<8)|b));
  const Coord3D *claimPosition=m_08->getPosition();
  m_1C->m_pos08=*claimPosition;
 }
}


// ?rva004E6693@PlaceTerrainResourceClaimantFeedback@@QAEXPAUICoord2D@@@Z
// @0x004E6693 7B: the outer class forwards to its Impl (mov ecx, [ecx]; tail
// jump to Impl::update above, argument unchanged). Called at 0x002A301E.
// Address-named: a pimpl outer usually shares the Impl method's name
// (update), which is not proven here.
void PlaceTerrainResourceClaimantFeedback::rva004E6693(ICoord2D *position)
{
	m_impl->update(position);
}
