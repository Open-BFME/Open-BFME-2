// FadeInTextRender rendering, native 0x00596908..0x00596AE9.
// BFME 1 cee35b7d8 FadeInTextRenderDraw004721F0 is the semantic guide;
// target-specific bounds, frame phases and cloud animation are described below.
// LoadAssets belongs to FadeInTextRender.cpp; this unit only needs
// its virtual declaration, not a second definition of the asset loader.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "unicode_string.h"
#include "Lib/ICoord2D.h"

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

struct Template004721F0 { char field00[16]; unsigned short field10;
 unsigned short getNumFrames() const { return field10; } };
class Anim2DCallView { public:
 void draw(int,int,int,int);
 char field00[12]; Template004721F0* m_template; char field10[12]; float m_alpha;
 const Template004721F0* getAnimTemplate() const { return m_template; }
 void setAlpha(float a) { m_alpha = a; }
};

class Anim2DTemplate;class Anim2DCollection;
class Anim2D
{
public:
	Anim2D(Anim2DTemplate*,Anim2DCollection*);
	unsigned getCurrentFrameHeight() const;
	void setCurrentFrame(unsigned short);
	void draw(int,int,int,int);
	char m_pad00[0x34];
};

class Rva0059675ABase
{
public:
    virtual ~Rva0059675ABase();
};

class GameFont;

// Slot 2 of FadeInTextRender's vftable 0x00C70A70 (slot 0 is its deleting
// destructor, slot 1 LoadAssets, as WB's LoadAssets is slot 1 of its table).
struct FadeInTextRender : Rva0059675ABase
{
    FadeInTextRender();
    virtual ~FadeInTextRender();
    virtual void LoadAssets();
    virtual void rva00596908(Text004721F0 *text, const ICoord2D *pos, unsigned frame);
    void bfmeExtend(int left, int top, int right, int bottom); // grow the +8..+0x14 bounds (0x0059668D)

    GameFont* font;
    int m_bfmeLeft;
    int m_bfmeTop;
    int m_bfmeRight;
    int m_bfmeBottom;
    unsigned effectColor;
    Anim2D* anim;
    float scale;
    AsciiString fontName;
    unsigned color;
    int delay;
    unsigned fontSize;
    unsigned starts[3], ends[3];
    int width, height;
};
// LoadAssets is supplied by FadeInTextRender.cpp at 0x005967B3.
// Keep its virtual declaration; this draw unit must not emit a second owner.

// Native596908..596AE9 is FadeInTextRender tableC70A70 slot2. BF1 cee35b7d8
// FadeInTextRenderDraw004721F0 is the semantic guide; target bounds worker
// 59668D and the single cloud animation are target-specific. Original method
// spelling is retained as unknown; the class follows the named LoadAssets slot.
void FadeInTextRender::rva00596908(Text004721F0* text, const ICoord2D* pos, unsigned frame) {
 int textWidth, h;
 text->size(&textWidth, &h);
 UnicodeString s = text->getText();
 const ICoord2D &point = *pos;
 int y=point.y-(height-h)/2;
 int x = point.x;
 int width = 0;
 text->size(&width, 0);
 int bottom = y + height;

 bfmeExtend(x,y,(x + width),bottom);
 int i;
 i=0;
 for(;i<3;++i) {
  unsigned start=starts[i], end=ends[i];
  if(*(volatile unsigned*)&frame>=start && frame<=end) {
   float progress=float(frame-start)/float(end-start);
   switch(i) {
   case 0: {
    unsigned frames=((Anim2DCallView*)anim)->getAnimTemplate()->getNumFrames();
    if(frames) {
     anim->setCurrentFrame(((frame-start)/4)%frames);
     unsigned color=effectColor;
     ((Anim2DCallView*)anim)->setAlpha(float(color>>24)/255.0f);
     anim->draw(x-width/2,y,width*2,height);
     anim->draw(x-width/2,y,width*2,height);
    }
    break;
   }
   case 1: {
    unsigned alpha=(unsigned)(int)((1.0f<progress ? 1.0f:progress)*255.0f)<<24;
    unsigned textColor=(color&0xffffff)|alpha;
    text->colors(textColor,alpha);
    text->draw(point.x,point.y,1,1);
    break;
   }
   case 2:
    text->colors(color|effectColor,effectColor);
    text->draw(point.x,point.y,1,1);
    break;
   }
  }
 }
}
