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
 FloatPair(float a,float b):x(a),y(b){}
 FloatPair(const FloatPair &p):x(p.x),y(p.y){}
	float x;
	float y;
};

class DisplayString
{
public:
	virtual void v00();
	virtual void setText(UnicodeString text);	// slot 1
	virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07();
	virtual void setWordWrap(Int wordWrap);	// slot 8
	virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void draw(Int x,Int y); virtual void v14();
	virtual void getSize(Int *width, Int *height);	// slot 15
};

struct IntPair
{
	int pad[9];
	int v24;
	int v28;
};
struct ScalePair
{
	float x;
	float y;
};
class Rva00222A8BTarget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual ScalePair *v15();
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;


// The header's inline length test, read as a 16-bit compare.
struct UnicodeStringHeaderView
{
	int ref_count;
	unsigned short length;
};
static __forceinline bool hasText(const UnicodeString &s)
{
	const UnicodeStringHeaderView *header = *(const UnicodeStringHeaderView *const *)&s;
	return header != 0 && header->length != 0;
}

class InGameCommandButtonHelp
{
public:
	class Impl;
};

class InGameCommandButtonHelp::Impl
{
public:
	void ComputeIconSizes(FloatPair *a, FloatPair *b, FloatPair *out);
 void Render(const FloatPair &position,const FloatPair &size);

private:
	void *m_owner;                     // +0x00
	UnicodeString m_name;              // +0x04
	UnicodeString m_title;             // +0x08
	UnicodeString m_description;       // +0x0C
	UnicodeString m_cost;              // +0x10
	unsigned short m_shortcutKey;      // +0x14
	Int m_width;                       // +0x18
	DisplayString *m_nameString;       // +0x1C
	DisplayString *m_titleString;      // +0x20
	DisplayString *m_descriptionString; // +0x24
	DisplayString *m_shortcutString;   // +0x28
	DisplayString *m_costString;       // +0x2C
	IntPair *m_icon30;                 // +0x30
	IntPair *m_icon34;                 // +0x34
};


class Image;
class Display;
extern Display *TheDisplay;
class W3DDisplay {public:void rva0004D6B3(Image*,float,float,float,float,Int,Int);};
// WB144C000 DrawIcon, native56C716: static helper's last references are
// internally passed in ECX(maximum)/EAX(icon); image and by-value pair are stack.
static void DrawIcon(Image *image,FloatPair position,const FloatPair &maximum,const FloatPair &icon) {
 position.x+=(maximum.x-icon.x)*0.5f;
 position.y+=(maximum.y-icon.y)*0.5f;
 ((W3DDisplay*)TheDisplay)->rva0004D6B3(image,position.x,position.y,position.x+icon.x,position.y+icon.y,-1,2);
}
void InGameCommandButtonHelp::Impl::ComputeIconSizes(FloatPair *a, FloatPair *b, FloatPair *out)
{
	ScalePair *scale = TheRva00222A8BTarget->v15();
	if (m_icon30 != 0) {
		a->x = (float)m_icon30->v24 * scale->x;
		a->y = (float)m_icon30->v28 * scale->y;
	} else {
		a->x = 0.0f;
		a->y = 0.0f;
	}
	if (m_icon34 != 0) {
		b->x = (float)m_icon34->v24 * scale->x;
		b->y = (float)m_icon34->v28 * scale->y;
	} else {
		b->x = 0.0f;
		b->y = 0.0f;
	}
	float *px;
	if (b->x > a->x)
		px = &b->x;
	else
		px = &a->x;
	out->x = *px;
	float *py;
	if (b->y > a->y)
		py = &b->y;
	else
		py = &a->y;
	out->y = *py;
}

static __forceinline Int rounded(float value){return WWMath::Float_To_Long((float)floor(value+0.5f));}
void InGameCommandButtonHelp::Impl::Render(const FloatPair &position,const FloatPair &size) {
 FloatPair firstIcon,secondIcon,maximum;
 ComputeIconSizes(&firstIcon,&secondIcon,&maximum);
 UnicodeString title=m_title;
 Image *titleIcon=(Image*)m_icon30;
 FloatPair titleSize=firstIcon;
 UnicodeString description=m_description;
 Image *descriptionIcon=(Image*)m_icon34;
 FloatPair descriptionSize=secondIcon;
 if(!hasText(title) && hasText(description)) {
  title.swap(description);titleIcon=descriptionIcon;titleSize=descriptionSize;
 }
 float y=position.y;
 Int w,h;
 m_nameString->getSize(&w,&h);
 float x=position.x+(size.x-(float)w)*0.5f;
 m_nameString->draw(rounded(x),rounded(y));
 y+=(float)h;
 float lineHeight=0.0f;
 Bool centered=false;
 if(m_shortcutKey) {
  if(hasText(title)) {
   m_titleString->getSize(&w,&h);
   float titleH=(float)h;
   m_shortcutString->getSize(&w,&h);
   float shortcutW=(float)w,shortcutH=(float)h;
   lineHeight=titleH>shortcutH?titleH:shortcutH;
   if(maximum.y>lineHeight)lineHeight=maximum.y;
   DrawIcon(titleIcon,FloatPair(position.x,y+(lineHeight-maximum.y)*0.5f),maximum,titleSize);
   Int drawX=WWMath::Float_To_Long((float)floor(position.x+maximum.x+0.5f)); Int drawY=WWMath::Float_To_Long((float)floor(y+(lineHeight-titleH+1.0f)*0.5f)); m_titleString->draw(drawX,drawY);
   Int shortX=rounded(position.x+size.x-shortcutW); Int shortY=WWMath::Float_To_Long((float)floor(y+(lineHeight-shortcutH+1.0f)*0.5f)); m_shortcutString->draw(shortX,shortY);
  } else {
   m_shortcutString->getSize(&w,&h);lineHeight=(float)h;
   x=position.x+(size.x-(float)w)*0.5f;
   m_shortcutString->draw(rounded(x),rounded(y));
  }
 } else {
  centered=true;
  if(hasText(title)) {
   m_titleString->getSize(&w,&h);float titleW=(float)w; float titleH=(float)h;
   lineHeight=maximum.y>titleH?maximum.y:titleH;
   titleW+=maximum.x; x=position.x+(size.x-titleW)*0.5f;
   DrawIcon(titleIcon,FloatPair(x,y+(lineHeight-maximum.y)*0.5f),maximum,titleSize);
   Int drawX=WWMath::Float_To_Long((float)floor(x+maximum.x+0.5f)); Int drawY=WWMath::Float_To_Long((float)floor(y+(lineHeight-titleH+1.0f)*0.5f)); m_titleString->draw(drawX,drawY);
  }
 }
 y+=lineHeight;
 if(hasText(description)) {
  m_descriptionString->getSize(&w,&h);FloatPair descriptionExtent((float)w,(float)h);float descriptionH=descriptionExtent.y;
  lineHeight=maximum.y>descriptionH?maximum.y:descriptionH;
  x=position.x;
  if(centered)x+=(size.x-(descriptionExtent.x+maximum.x))*0.5f;
  DrawIcon(descriptionIcon,FloatPair(x,y+(lineHeight-maximum.y)*0.5f),maximum,descriptionSize);
  Int drawX=WWMath::Float_To_Long((float)floor(x+maximum.x+0.5f)); Int drawY=WWMath::Float_To_Long((float)floor(y+(lineHeight-descriptionH+1.0f)*0.5f)); m_descriptionString->draw(drawX,drawY);
  y+=lineHeight;
 }
 m_costString->getSize(&w,&h);
 x=position.x+(size.x-(float)w)*0.5f;
 m_costString->draw(rounded(x),rounded(y));
}
