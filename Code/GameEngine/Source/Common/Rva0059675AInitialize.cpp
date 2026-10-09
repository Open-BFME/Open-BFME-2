// Target Ghidra5967B3+341; same 54-byte owner as constructor/dtor5966DD/59675A.
// BF1 9cbfb551fe20 FadeInTextRender.cpp initialize is the primary source lead:
// font scaling plus TextElvenClouds allocation. Target uses one animation and three phases.
// Target facts: Display slot40 unsigned width; FontLibrary getFont; Anim2D allocation34,
// template/collection call providers; oldScale20/font4; width4C and animation-derived height50.
// 0.75 and .00125 are compiler constants verified against retail data, not global escape hatches.
// Phase stores straddle two reads of canonical g_009BA4E8; preserve that alias-sensitive order.
// Existing address-derived constructor argument views retain provider identity uncertainty.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class Display;extern Display *TheDisplay;
class FadeDisplayCalls {public:
 virtual void p00();virtual void p04();virtual void p08();virtual void p0c();virtual void p10();virtual void p14();virtual void p18();virtual void p1c();virtual void p20();virtual void p24();virtual void p28();virtual void p2c();virtual void p30();virtual void p34();virtual void p38();virtual void p3c();virtual unsigned width();};
class GameFont;class FontLibrary {public:GameFont*getFont(const AsciiString*,float,bool);};extern FontLibrary*TheFontLibrary;
class Anim2DTemplate;class Anim2DCollection {public:Anim2DTemplate*findTemplate(const AsciiString&);};extern Anim2DCollection*TheAnim2DCollection;
struct Rva002D752DNode;class Rva002D752D;
class Anim2D {public:Anim2D(Rva002D752DNode*,Rva002D752D*);unsigned getCurrentFrameHeight() const;char pad[0x34];};
extern int g_009BA4E8;
class FadeInTextRender {public:
 void LoadAssets();
 void*head;GameFont*font;char pad08[0x14];Anim2D*anim;float oldScale;AsciiString fontName;unsigned color;int delay;unsigned fontSize;unsigned starts[3],ends[3];int width,height;
};
void FadeInTextRender::LoadAssets() {
 float naturalWidth=(float)((FadeDisplayCalls*)TheDisplay)->width();
 float scale=naturalWidth*0.00125f;scale*=0.75f;
 if(scale!=oldScale){font=0;oldScale=scale;}
 if(!font)font=TheFontLibrary->getFont(&fontName,(float)fontSize*scale,false);
 if(!anim){
  anim=new Anim2D((Rva002D752DNode*)TheAnim2DCollection->findTemplate(AsciiString("TextElvenClouds")),(Rva002D752D*)TheAnim2DCollection);
  starts[1]=0;int end=g_009BA4E8;ends[2]=~0u;
  ends[1]=end;starts[2]=end+1;
  starts[0]=starts[2]+g_009BA4E8/2;ends[0]=~0u;
 }
 width=(int)naturalWidth;
 height=(int)((float)anim->getCurrentFrameHeight()*scale);
}
