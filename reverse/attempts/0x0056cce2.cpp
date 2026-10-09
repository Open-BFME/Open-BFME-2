// ?Render@Impl@InGameCommandButtonHelp@@QAEXABUFloatPair@@0@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" __declspec(dllimport) double __cdecl floor(double);
static __forceinline float floorf(float f){return (float)floor((double)f);}
static __forceinline int fast_real_to_int(float f){int i; __asm {fld f
 fistp i} return i;}
struct FloatPair {float x,y;FloatPair(){} FloatPair(float a,float b):x(a),y(b){} FloatPair(const FloatPair &o):x(o.x),y(o.y){}};
class Image;
class W3DDisplay {public: void rva0004D6B3(Image*,float,float,float,float,int,int);};
extern W3DDisplay *TheDisplay;
__declspec(noinline) static void DrawIcon(Image*image,FloatPair pos,const FloatPair *maxIcon,const FloatPair *icon){
 pos.x+=(maxIcon->x-icon->x)*0.5f; pos.y+=(maxIcon->y-icon->y)*0.5f;
 TheDisplay->rva0004D6B3(image,pos.x,pos.y,pos.x+icon->x,pos.y+icon->y,-1,2);
}
struct UnicodeHeader {int count;unsigned short length;};
static __forceinline bool hasText(const UnicodeString&s){const UnicodeHeader*h=*(const UnicodeHeader*const*)&s;return h && h->length; }
struct ScalePair {float x,y;};
class AptPlayer {public:
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
virtual ScalePair *v15();};
extern AptPlayer *TheAptPlayer;
class GameFont;
class FontLibrary {public: GameFont *getFont(const AsciiString *,float,bool);};
extern FontLibrary *TheFontLibrary;
class DisplayString {public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void setFont(GameFont *);
 virtual void v7(); virtual void v8(); virtual void slot9(bool); virtual void slot10(int,int);
 virtual void v11();virtual void v12();virtual void draw(int,int);virtual void v14();virtual void getSize(int*,int*);
};
class Rva0043FC20 {public:
 Rva0043FC20(const Rva0043FC20 &);
 AsciiString m_00; int m_04; bool m_08; char pad[3]; int m_0C;
};
class Rva0029F8B8 {public:
 Rva0043FC20 rva0029F8B8(); Rva0043FC20 rva0029D844(); Rva0043FC20 rva0029D8C6(); Rva0043FC20 rva0029D948();
};
class InGameUI; extern InGameUI *TheInGameUI;
class InGameCommandButtonHelp {public: class Impl;};
class InGameCommandButtonHelp::Impl {public:
 void *owner; UnicodeString name,title,description,cost;unsigned short key;char pad16[2];int width; DisplayString *s1,*s2,*s3,*s4,*s5;Image *icon1,*icon2;
 void SetupDisplayStrings();
 void ComputeIconSizes(FloatPair*,FloatPair*,FloatPair*);
 void Render(const FloatPair &pos,const FloatPair &size);
};
void InGameCommandButtonHelp::Impl::ComputeIconSizes(FloatPair *a,FloatPair*b,FloatPair*out){
 ScalePair *scale=TheAptPlayer->v15();
 if(icon1){a->x=(float)((int*)icon1)[9]*scale->x;a->y=(float)((int*)icon1)[10]*scale->y;}else{a->x=0;a->y=0;}
 if(icon2){b->x=(float)((int*)icon2)[9]*scale->x;b->y=(float)((int*)icon2)[10]*scale->y;}else{b->x=0;b->y=0;}
 float *px;if(b->x>a->x)px=&b->x;else px=&a->x;out->x=*px;
 float *py;if(b->y>a->y)py=&b->y;else py=&a->y;out->y=*py;
}
void InGameCommandButtonHelp::Impl::Render(const FloatPair &pos,const FloatPair &size){
 int textWidth;{int textHeight;
 FloatPair firstIcon,secondIcon,icons;
 ComputeIconSizes(&firstIcon,&secondIcon,&icons);
 UnicodeString firstTitle=title;Image *firstImage=icon1;FloatPair firstSize=firstIcon;
 UnicodeString secondTitle=description;Image *secondImage=icon2;FloatPair secondSize=secondIcon;
 if(!hasText(firstTitle)&&hasText(secondTitle)){ firstTitle.swap(secondTitle);firstImage=secondImage;firstSize=secondSize; }
 float y=pos.y;
 s1->getSize(&textWidth,&textHeight);
 float x=pos.x+(size.x-(float)textWidth)*.5f;
 s1->draw(fast_real_to_int(floorf(x+.5f)),fast_real_to_int(floorf(y+.5f)));
 y+=(float)textHeight;
 float rowHeight=0;bool centered=false;
 if(key){
  if(hasText(firstTitle)){
   s2->getSize(&textWidth,&textHeight);float titleHeight=(float)textHeight;
   s4->getSize(&textWidth,&textHeight);float shortcutWidth=(float)textWidth,shortcutHeight=(float)textHeight;
   rowHeight=titleHeight>shortcutHeight?titleHeight:shortcutHeight;
   if(icons.y>rowHeight)rowHeight=icons.y;
   DrawIcon(firstImage,FloatPair(pos.x,y+(rowHeight-icons.y)*.5f),&icons,&firstSize);
   int dx=fast_real_to_int(floorf(pos.x+icons.x+.5f));int dy=fast_real_to_int(floorf(y+(rowHeight-titleHeight+1.0f)*.5f));s2->draw(dx,dy);
   int shortcutDx=fast_real_to_int(floorf(pos.x+size.x-shortcutWidth+.5f));int shortcutDy=fast_real_to_int(floorf(y+(rowHeight-shortcutHeight+1.0f)*.5f));s4->draw(shortcutDx,shortcutDy);
  }else{
   s4->getSize(&textWidth,&textHeight);rowHeight=(float)textHeight;
   x=pos.x+(size.x-(float)textWidth)*.5f;
   s4->draw(fast_real_to_int(floorf(x+.5f)),fast_real_to_int(floorf(y+.5f)));
  }
 }else{
  centered=true;
  if(hasText(firstTitle)){
   s2->getSize(&textWidth,&textHeight);float titleWidth=(float)textWidth;float titleHeight=(float)textHeight;
   rowHeight=icons.y>titleHeight?icons.y:titleHeight;
   float combinedWidth=titleWidth+icons.x;
   x=pos.x+(size.x-combinedWidth)*.5f;
   DrawIcon(firstImage,FloatPair(x,y+(rowHeight-icons.y)*.5f),&icons,&firstSize);
   int dx=fast_real_to_int(floorf(x+icons.x+.5f));int dy=fast_real_to_int(floorf(y+(rowHeight-titleHeight+1.0f)*.5f));s2->draw(dx,dy);
  }
 }
 y+=rowHeight;
 if(hasText(secondTitle)){
  s3->getSize(&textWidth,&textHeight);float descriptionWidth=(float)textWidth;float descriptionHeight=(float)textHeight;
  rowHeight=icons.y>descriptionHeight?icons.y:descriptionHeight;
  x=pos.x;if(centered){float combinedWidth=descriptionWidth+icons.x;x+=(size.x-combinedWidth)*.5f;}
  DrawIcon(secondImage,FloatPair(x,y+(rowHeight-icons.y)*.5f),&icons,&secondSize);
  int dx=fast_real_to_int(floorf(x+icons.x+.5f));int dy=fast_real_to_int(floorf(y+(rowHeight-descriptionHeight+1.0f)*.5f));s3->draw(dx,dy);
  y+=rowHeight;
 }
 s5->getSize(&textWidth,&textHeight);
 x=pos.x+(size.x-(float)textWidth)*.5f;
 s5->draw(fast_real_to_int(floorf(x+.5f)),fast_real_to_int(floorf(y+.5f)));
}
}
