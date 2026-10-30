// Target Ghidra5967B3+341; same 54-byte owner as constructor/dtor5966DD/59675A.
// BF1 9cbfb551fe20 FadeInTextRender.cpp initialize is the primary source lead:
// font scaling plus TextElvenClouds allocation. Target uses one animation and three phases.
// Target facts: Display slot40 unsigned width; FontLibrary getFont; Anim2D allocation34,
// template/collection call providers; oldScale20/font4; width4C and animation-derived height50.
// 0.75 and .00125 are compiler constants verified against retail data, not global escape hatches.
// Phase stores straddle two reads of canonical BfmeClientFramesPerSecond; preserve that alias-sensitive order.
// Existing address-derived constructor argument views retain provider identity uncertainty.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class Display;extern Display *TheDisplay;
class FadeDisplayCalls {public:
 virtual void p00();virtual void p04();virtual void p08();virtual void p0c();virtual void p10();virtual void p14();virtual void p18();virtual void p1c();virtual void p20();virtual void p24();virtual void p28();virtual void p2c();virtual void p30();virtual void p34();virtual void p38();virtual void p3c();virtual unsigned width();};
class GameFont;class FontLibrary {public:GameFont*getFont(const AsciiString*,float,bool);};extern FontLibrary*TheFontLibrary;
class Anim2DTemplate;class Anim2DCollection;extern Anim2DCollection*TheAnim2DCollection;
// The collection's template lookup is rowed under its address class.
struct Rva002D752DNode;class Rva002D752D {public:Rva002D752DNode*rva002D752D(const StringBase<char>&);};
static inline const StringBase<char>&fadeTextBase(const AsciiString&asciiString){return *(const StringBase<char>*)&asciiString;}
class Anim2D
{
public:
	Anim2D(Anim2DTemplate*,Anim2DCollection*);
	unsigned getCurrentFrameHeight() const;
	void setCurrentFrame(unsigned short);
	void draw(int,int,int,int);
	char m_pad00[0x34];
};
extern int BfmeClientFramesPerSecond;
// Slot 1 of FadeInTextRender's vftable 0x00C70A70 (slot 0 is its deleting
// destructor), as WB's LoadAssets is slot 1 of its table: virtual.
class __declspec(novtable) Rva0059675ABase
{
public:
    virtual ~Rva0059675ABase();
};
struct FadeInTextRender : Rva0059675ABase
{
    FadeInTextRender();
    virtual ~FadeInTextRender();
    virtual void LoadAssets();
    void bfmeExtend(int left, int top, int right, int bottom);

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
void FadeInTextRender::LoadAssets() {
 float naturalWidth=(float)((FadeDisplayCalls*)TheDisplay)->width();
 float scale=naturalWidth*0.00125f;scale*=0.75f;
 if(scale!=this->scale){font=0;this->scale=scale;}
 if(!font)font=TheFontLibrary->getFont(&fontName,(float)fontSize*scale,false);
 if(!anim){
  anim=new Anim2D((Anim2DTemplate*)((Rva002D752D*)TheAnim2DCollection)->rva002D752D(fadeTextBase(AsciiString("TextElvenClouds"))),TheAnim2DCollection);
  starts[1]=0;int end=BfmeClientFramesPerSecond;ends[2]=~0u;
  ends[1]=end;starts[2]=end+1;
  starts[0]=starts[2]+BfmeClientFramesPerSecond/2;ends[0]=~0u;
 }
 width=(int)naturalWidth;
 height=(int)((float)anim->getCurrentFrameHeight()*scale);
}
