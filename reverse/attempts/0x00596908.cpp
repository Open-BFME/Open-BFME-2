// ?draw@Rva0059675A@@QAEXPAVText004721F0@@PBUPoint004721F0@@I@Z
// partial score=0.854658 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "unicode_string.h"


struct Point004721F0 { int x, y; };
class Text004721F0 {
public:
 virtual void slot00();
 virtual void slot04();
 virtual UnicodeString getText();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void colors(unsigned, unsigned);
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void draw(int,int,int,int);
 virtual void size(int*,int*);
};
class Anim2D { public: void setCurrentFrame(unsigned short); void draw(int,int,int,int); };
struct Template004721F0 { char field00[16]; unsigned short field10;
 unsigned short getNumFrames() const { return field10; } };
class Anim2DCallView { public:
 void draw(int,int,int,int);
 char field00[12]; Template004721F0* field0c; char field10[12]; float field1c;
 const Template004721F0* getAnimTemplate() const { return field0c; }
 void setAlpha(float a) { field1c = a; }
};
class Gen_00470870 {public:void bfmeExtend(int,int,int,int);};
class Rva0059675A { public:
 void draw(Text004721F0*, const Point004721F0*, unsigned);
 char field00[8]; int field08, field0c, field10, field14;
 unsigned field18; Anim2DCallView* field1c;
 char field20[8]; unsigned field28; char field2c[8];
 unsigned field34[3], field40[3]; int field4c, field50;
};
// RVA 004721F0: three timed text/animation phases (EA evidence: FadeInTextRender::Render).
// Both colour locals keep the dword alpha load and unsigned x87 conversion retail shows.
void Rva0059675A::draw(Text004721F0* text, const Point004721F0* pos, unsigned frame) {
 int w, h;
 text->size(&w, &h);
 UnicodeString s = text->getText();
 int halfHeight=(field50-h)/2;
 int y=pos->y-halfHeight;
 int x = pos->x;
 int width = 0;
 text->size(&width, 0);
 int bottom = y + field50;
 int right = x + width;
 ((Gen_00470870*)this)->bfmeExtend(x,y,right,bottom);
 for(int i=0;i<3;++i) {
  unsigned start=field34[i], end=field40[i];
  if(frame>=start && frame<=end) {
   float progress=float(frame-start)/float(end-start);
   switch(i) {
   case 0: {
    unsigned frames=field1c->getAnimTemplate()->getNumFrames();
    if(frames) {
     ((Anim2D*)field1c)->setCurrentFrame(((frame-start)/4)%frames);
     unsigned color=field18;
     field1c->setAlpha(float(color>>24)/255.0f);
     ((Anim2D*)field1c)->draw(x-width/2,y,width*2,field50);
     ((Anim2D*)field1c)->draw(x-width/2,y,width*2,field50);
    }
    break;
   }
   case 1: {
    unsigned alpha=(unsigned)(int)((1.0f<progress ? 1.0f:progress)*255.0f)<<24;
    unsigned color=(field28&0xffffff)|alpha;
    text->colors(color,alpha);
    text->draw(pos->x,pos->y,1,1);
    break;
   }
   case 2:
    text->colors(field28|field18,field18);
    text->draw(pos->x,pos->y,1,1);
    break;
   }
  }
 }
}
