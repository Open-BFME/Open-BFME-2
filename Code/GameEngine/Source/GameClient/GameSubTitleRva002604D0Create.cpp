// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// ?Rva002604D0Create@@YAPAVGameSubTitle@@PBVAsciiString@@HABVUnicodeString@@IHHHHH@Z @0x002604D0 135B
// Native [2604D0,260557), cdecl factory; independently rowed233B GameSubTitle
// constructor establishes the eight forwarded arguments. Display slot40
// supplies unsigned width, scaling font points by width/1024. Allocation38
// is target evidence; the unused object layout is deliberately opaque here.
#include "ascii_string.h"
#include "unicode_string.h"
class GameFont;
class FontLibrary { public:GameFont *getFont(const AsciiString *,float,bool); };
extern FontLibrary *TheFontLibrary;
class Display;extern Display *TheDisplay;
class Rva002604D0DisplayView {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
#undef V
 virtual unsigned getWidth();
};
class GameSubTitle {
public:GameSubTitle(GameFont *,const UnicodeString &,unsigned,int,int,int,int,int);
private:unsigned char opaque[0x38];
};
GameSubTitle *Rva002604D0Create(const AsciiString *fontName,int fontSize,
 const UnicodeString &text,unsigned color,int style,int align,int line,
 int startFrame,int endFrame)
{
 // One expression: a separate scale local makes cl defer the fimul past the float argument slot
 // allocation (push ecx; mov ecx; fimul) where retail multiplies first.
 float points=fontSize*(static_cast<float>(reinterpret_cast<Rva002604D0DisplayView *>(TheDisplay)->getWidth())*(1.0f/1024.0f));
 GameFont *font=TheFontLibrary->getFont(fontName,points,false);
 return new GameSubTitle(font,text,color,style,align,line,startFrame,endFrame);
}
