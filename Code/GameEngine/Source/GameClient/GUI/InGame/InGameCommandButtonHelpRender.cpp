// cl: /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// Native 0056CCE2..0056D2BD (1499B; RET8; two wide-string EH states),
// WorldBuilder 0144B470 InGameCommandButtonHelp::Impl::Render. The native
// entry is reached by the help's +8 Impl forwarder at 0056D2C5. Its display
// strings and icons agree with the independently rowed SetWidthAndComputeHeight
// and ComputeIconSizes; the target's vtable calls measure each line then draw
// slot 13 at centered or icon-indented coordinates, followed by the cost line.
//
// Native 0056C716..0056C790 (122B; RET0), WB0144C000 DrawIcon. Its caller
// context establishes a static helper taking an Image*, a by-value point and
// two const point references. MSVC privately passes maximum in ECX and icon
// in EAX; the remaining twelve bytes are caller-cleaned. Field-wise point
// construction models both the stack argument and the measured temporary
// copies. No guessed calling convention or extra argument is introduced.
//
// ComputeIconSizes (170B) is rehomed from Rva0056C7F1Max.cpp unchanged apart
// from the proven Impl member names. Keeping that definition visible permits
// MSVC to reuse its dead output buffers after the string copies. An in-place
// addition to the title width reproduces the SSE lifetime across the max-height
// branch. WWMath::Float_To_Long is the reference's x87 conversion helper;
// vertical expressions already contain their half-pixel rounding adjustment.
#include <new>
#include "unicode_string.h"
#define _OPERATOR_NEW_DEFINED_
#include "wwmath.h"

typedef int Int;
typedef bool Bool;

struct FloatPair
{
 FloatPair(){}
 FloatPair(float xCoord,float yCoord):x(xCoord),y(yCoord){}
 FloatPair(const FloatPair &floatPair):x(floatPair.x),y(floatPair.y){}
	float x;
	float y;
};

#include "../../../../Include/GameClient/DisplayString.h"

struct IntPair
{
	int pad[9];
	int v24;
	int m_height;
};
struct ScalePair
{
	float x;
	float y;
};
#include "../../../../Include/Common/Rva00222A8BTarget.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;


// The header's inline length test, read as a 16-bit compare.
#include "../../../../Include/GameClient/UnicodeStringHeaderView.h"
static __forceinline bool hasText(const UnicodeString &unicodeString)
{
	const UnicodeStringHeaderView *header = *(const UnicodeStringHeaderView *const *)&unicodeString;
	return header != 0 && header->length != 0;
}

#include "../../../../Include/GameClient/InGameCommandButtonHelp.h"


class Image;
class Display;
extern Display *TheDisplay;
#include "../../../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayClass.h"
// WB144C000 DrawIcon, native56C716: static helper's last references are
// internally passed in ECX(maximum)/EAX(icon); image and by-value pair are stack.
static void DrawIcon(Image *image,FloatPair position,const FloatPair &maximum,const FloatPair &icon) {
 position.x+=(maximum.x-icon.x)*0.5f;
 position.y+=(maximum.y-icon.y)*0.5f;
 ((W3DDisplay*)TheDisplay)->rva0004D6B3(image,position.x,position.y,position.x+icon.x,position.y+icon.y,-1,2);
}
void InGameCommandButtonHelp::Impl::ComputeIconSizes(FloatPair *floatPair, FloatPair *descriptionIconSize, FloatPair *out)
{
	ScalePair *scale = reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->v15();
	if (m_30 != 0) {
		floatPair->x = (float)reinterpret_cast<const IntPair *>(m_30)->v24 * scale->x;
		floatPair->y = (float)reinterpret_cast<const IntPair *>(m_30)->m_height * scale->y;
	} else {
		floatPair->x = 0.0f;
		floatPair->y = 0.0f;
	}
	if (m_34 != 0) {
		descriptionIconSize->x = (float)reinterpret_cast<const IntPair *>(m_34)->v24 * scale->x;
		descriptionIconSize->y = (float)reinterpret_cast<const IntPair *>(m_34)->m_height * scale->y;
	} else {
		descriptionIconSize->x = 0.0f;
		descriptionIconSize->y = 0.0f;
	}
	float *px;
	if (descriptionIconSize->x > floatPair->x)
		px = &descriptionIconSize->x;
	else
		px = &floatPair->x;
	out->x = *px;
	float *py;
	if (descriptionIconSize->y > floatPair->y)
		py = &descriptionIconSize->y;
	else
		py = &floatPair->y;
	out->y = *py;
}

static __forceinline Int rounded(float value){return WWMath::Float_To_Long((float)floor(value+0.5f));}
void InGameCommandButtonHelp::Impl::Render(const FloatPair &position,const FloatPair &size) {
 FloatPair firstIcon,secondIcon,maximum;
 ComputeIconSizes(&firstIcon,&secondIcon,&maximum);
 UnicodeString title=m_08;
 Image *titleIcon=(Image*)m_30;
 FloatPair titleSize=firstIcon;
 UnicodeString description=m_0C;
 Image *descriptionIcon=(Image*)m_34;
 FloatPair descriptionSize=secondIcon;
 if(!hasText(title) && hasText(description)) {
  title.swap(description);titleIcon=descriptionIcon;titleSize=descriptionSize;
 }
 float y=position.y;
 Int w,h;
 m_1C->getSize(&w,&h);
 float x=position.x+(size.x-(float)w)*0.5f;
 m_1C->draw(rounded(x),rounded(y));
 y+=(float)h;
 float lineHeight=0.0f;
 Bool centered=false;
 if(m_14) {
  if(hasText(title)) {
   m_20->getSize(&w,&h);
   float titleH=(float)h;
   m_28->getSize(&w,&h);
   float shortcutW=(float)w,shortcutH=(float)h;
   lineHeight=titleH>shortcutH?titleH:shortcutH;
   if(maximum.y>lineHeight)lineHeight=maximum.y;
   DrawIcon(titleIcon,FloatPair(position.x,y+(lineHeight-maximum.y)*0.5f),maximum,titleSize);
   Int drawX=WWMath::Float_To_Long((float)floor(position.x+maximum.x+0.5f)); Int drawY=WWMath::Float_To_Long((float)floor(y+(lineHeight-titleH+1.0f)*0.5f)); m_20->draw(drawX,drawY);
   Int shortX=rounded(position.x+size.x-shortcutW); Int shortY=WWMath::Float_To_Long((float)floor(y+(lineHeight-shortcutH+1.0f)*0.5f)); m_28->draw(shortX,shortY);
  } else {
   m_28->getSize(&w,&h);lineHeight=(float)h;
   x=position.x+(size.x-(float)w)*0.5f;
   m_28->draw(rounded(x),rounded(y));
  }
 } else {
  centered=true;
  if(hasText(title)) {
   m_20->getSize(&w,&h);float titleW=(float)w; float titleH=(float)h;
   lineHeight=maximum.y>titleH?maximum.y:titleH;
   titleW+=maximum.x; x=position.x+(size.x-titleW)*0.5f;
   DrawIcon(titleIcon,FloatPair(x,y+(lineHeight-maximum.y)*0.5f),maximum,titleSize);
   Int drawX=WWMath::Float_To_Long((float)floor(x+maximum.x+0.5f)); Int drawY=WWMath::Float_To_Long((float)floor(y+(lineHeight-titleH+1.0f)*0.5f)); m_20->draw(drawX,drawY);
  }
 }
 y+=lineHeight;
 if(hasText(description)) {
  m_24->getSize(&w,&h);FloatPair descriptionExtent((float)w,(float)h);float descriptionH=descriptionExtent.y;
  lineHeight=maximum.y>descriptionH?maximum.y:descriptionH;
  x=position.x;
  if(centered)x+=(size.x-(descriptionExtent.x+maximum.x))*0.5f;
  DrawIcon(descriptionIcon,FloatPair(x,y+(lineHeight-maximum.y)*0.5f),maximum,descriptionSize);
  Int drawX=WWMath::Float_To_Long((float)floor(x+maximum.x+0.5f)); Int drawY=WWMath::Float_To_Long((float)floor(y+(lineHeight-descriptionH+1.0f)*0.5f)); m_24->draw(drawX,drawY);
  y+=lineHeight;
 }
 m_2C->getSize(&w,&h);
 x=position.x+(size.x-(float)w)*0.5f;
 m_2C->draw(rounded(x),rounded(y));
}
