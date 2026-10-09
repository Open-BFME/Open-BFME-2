// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Native56C790..56C7F1 is a97B private helper consumed by250B
// SetupDisplayStrings56D2E9..56D3E3. WB name lead/callgraph establishes
// InGameCommandButtonHelp::Impl::SetupDisplayStrings; its five observed
// fields1C..2C consume the four independently rowed16B font getters.
// BF1 f989 and ZH DisplayString/FontLibrary sources guide the font lifetime
// and font-lookup semantics; no clean donor specialized helper was found.
// Target helper consumes ESI string / EDI font. Defining it earlier in
// this TU permits MSVC's measured private convention without an asm shim.
// Scale is min(AptPlayer slot15 x/y); descriptor fields0/4/8/C are target
// facts from rowed getter/copy providers. Slots9/10 retain neutral names
// since ZH's corresponding declarations differ from the target call arity.
#include "ascii_string.h"
#include "unicode_string.h"
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
virtual void setText(UnicodeString);
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void setFont(GameFont *);
 virtual void v7(); virtual void setWordWrap(int); virtual void slot9(bool); virtual void slot10(int,int);
 virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void getSize(int*,int*);
};
class Rva0043FC20 {public:
 Rva0043FC20(const Rva0043FC20 &);
 AsciiString m_00; int m_04; bool m_08; char pad[3]; int m_0C;
};
class Rva0029F8B8 {public:
 Rva0043FC20 rva0029F8B8(); Rva0043FC20 rva0029D844(); Rva0043FC20 rva0029D8C6(); Rva0043FC20 rva0029D948();
};
class InGameUI; extern InGameUI *TheInGameUI;
__declspec(noinline) static void Rva0056C790(DisplayString *str,const Rva0043FC20 *font) {
 ScalePair *scale=TheAptPlayer->v15();
 float factor;
 if(scale->y>scale->x) factor=scale->x; else factor=scale->y;
 GameFont *f=TheFontLibrary->getFont(&font->m_00,(float)font->m_04*factor,font->m_08);
 str->slot10(font->m_0C,0);str->slot9(true);str->setFont(f);
}
class Rva0056D3FD;
class Image{public:char pad[0x24];int width,height;};
class ImageCollection{public:const Image*findImageByName(const AsciiString&);};
extern ImageCollection *TheMappedImageCollection;
struct AsciiStringPlusString {const AsciiString *first,*second;operator AsciiString();};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b){AsciiStringPlusString p={&a,&b};return p;}
class InGameCommandButtonHelp {public: class Impl;};
class InGameCommandButtonHelp::Impl {public:
 Rva0056D3FD *owner;UnicodeString name,title,description,cost;unsigned short key;char pad16[2];int width;DisplayString *s1,*s2,*s3,*s4,*s5;const Image *icon30,*icon34;
 void SetupDisplayStrings();
 Impl(Rva0056D3FD*,const UnicodeString&,const UnicodeString&,const UnicodeString&,const UnicodeString&,const AsciiString&);
};
void InGameCommandButtonHelp::Impl::SetupDisplayStrings() {
 Rva0056C790(s1,&((Rva0029F8B8*)TheInGameUI)->rva0029F8B8());
 Rva0056C790(s2,&((Rva0029F8B8*)TheInGameUI)->rva0029D844());
 Rva0056C790(s3,&((Rva0029F8B8*)TheInGameUI)->rva0029D844());
 Rva0056C790(s4,&((Rva0029F8B8*)TheInGameUI)->rva0029D8C6());
 Rva0056C790(s5,&((Rva0029F8B8*)TheInGameUI)->rva0029D948());
}

// Native539619..5396E6 is a205B cdecl hidden-result string helper.
// It preserves a string with no '&'; otherwise it copies the prefix before
// the first '&' then appends remaining non-'&' characters. The target
// rowed string providers prove char reads and substring/copy lifetimes.
// getLength() before the cached header yields native indexESI/headerEDI;
// an explicit found predicate avoids the redundant post-loop index test.
// Native5397F7..5398B3 is188B RET12. WB1435680 and the already rowed
// outer constructor establish InGameSimpleHelp::Impl. Its20B layout is
// owner0/title4/text8/displayC,10; the earlier file-static font helper
// reproduces both observed ESI/EDI calls. BF1/ZH string/font source is
// the reference guide; this specialized help code has no clean donor.
__declspec(noinline) UnicodeString Rva00539619(const UnicodeString &str){
 struct Header {int count;unsigned short length,capacity;unsigned short data[1];};
 int length=str.getLength();
 const Header *header=*(const Header *const*)&str;
 int i=0;
 bool found=false;
 for(;i!=length;++i)if(str.getCharAt(i)=='&'){found=true;break;}
 if(!found){return str;}else{
 UnicodeString out(UnicodeString(header?header->data:(const unsigned short*)L""),0,i);
 for(;i<length;++i){unsigned short c=str.getCharAt(i);if(c!='&')out+=c;}
 return out;
 }
}
class DisplayStringManager {public:
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
virtual DisplayString *newDisplayString();};
extern DisplayStringManager *TheDisplayStringManager;
class __declspec(novtable) Rva005398CDRefCounted {public:
 Rva005398CDRefCounted():m_refCount(0){} virtual ~Rva005398CDRefCounted();int m_refCount;
};
class InGameSimpleHelp:public Rva005398CDRefCounted {public:class Impl;
 InGameSimpleHelp(const UnicodeString&,const UnicodeString&);virtual ~InGameSimpleHelp();
 private:Impl *m_impl;
};
class InGameSimpleHelp::Impl {public:
 InGameSimpleHelp *owner;UnicodeString title,text;DisplayString *titleString,*textString;
 Impl(InGameSimpleHelp*,const UnicodeString&,const UnicodeString&);
 int rva0053973F(int);
};
InGameSimpleHelp::Impl::Impl(InGameSimpleHelp *o,const UnicodeString&t,const UnicodeString&txt):owner(o),title(Rva00539619(t)),text(txt){
 titleString=TheDisplayStringManager->newDisplayString();textString=TheDisplayStringManager->newDisplayString();
 Rva0056C790(titleString,&((Rva0029F8B8*)TheInGameUI)->rva0029F8B8());
 Rva0056C790(textString,&((Rva0029F8B8*)TheInGameUI)->rva0029D948());
}

// Native53973F..5397D3 RET4 returns combined height after word wrapping
// and measuring both nonempty strings. Scope each measured height after
// its by-value setText argument dies: MSVC reuses the incoming width slot
// and reproduces148B rather than149B. No original method name is asserted.
int InGameSimpleHelp::Impl::rva0053973F(int width){
 titleString->setWordWrap(width);textString->setWordWrap(width);
 int total=0;int textWidth;
 if(!title.isEmpty()) {titleString->setText(title);int textHeight;titleString->getSize(&textWidth,&textHeight);total=textHeight;}
 if(!text.isEmpty()) {textString->setText(text);int textHeight;textString->getSize(&textWidth,&textHeight);total+=textHeight;}
 return total;
}

// Native56C89B..56C996: target strip-and-select-shortcut helper has EBX
// string input and AX key result. It removes ampersand markers while selecting
// the first following alphanumeric key through measured iswalnum/towupper.
// Native56D438..56D5BD RET24 is the56B help implementation constructor,
// connected to the rowed outer98B factory and owner56C996 destructor.
// Four37050 calls prove wide-string inputs; the fifth is narrow image suffix.
// Original constructor spelling is inferred from these owner/call facts.
// The implicit AsciiStringPlusString conversion preserves the native single
// returned temporary and prefix lifetime; explicit casts introduce a copy.
extern "C" __declspec(dllimport) int __cdecl iswalnum(unsigned short);
extern "C" __declspec(dllimport) unsigned short __cdecl towupper(unsigned short);
__declspec(noinline) static unsigned short Rva0056C89B(UnicodeString &str){
 int length=str.getLength();
 struct Header {int count;unsigned short length,capacity;unsigned short data[1];};
 const Header *header=*(const Header *const*)&str;
 int i=0;bool found=false;
 for(;i!=length;++i)if(str.getCharAt(i)=='&'){found=true;break;}
 if(!found)return 0;
 unsigned short key=0;
 UnicodeString out(UnicodeString(header?header->data:(const unsigned short*)L""),0,i);
 for(;i<length;++i){
  unsigned short c=str.getCharAt(i);
  if(c=='&'){
   if(++i>=length)break;
   c=str.getCharAt(i);
   if(!key&&iswalnum(c))key=towupper(c);
  }
  out.concat(&c,1);
 }
 str.swap(out);
 return key;
}
InGameCommandButtonHelp::Impl::Impl(Rva0056D3FD *o,const UnicodeString&n,const UnicodeString&t,const UnicodeString&d,const UnicodeString&c,const AsciiString&r):owner(o),name(n),title(t),description(d),cost(c),key(0),width(0){
 s1=TheDisplayStringManager->newDisplayString();s2=TheDisplayStringManager->newDisplayString();s3=TheDisplayStringManager->newDisplayString();s4=TheDisplayStringManager->newDisplayString();s5=TheDisplayStringManager->newDisplayString();
 icon30=TheMappedImageCollection->findImageByName(AsciiString("Resource_Icon"));
 icon34=0;
 key=Rva0056C89B(name);
 if(icon30&&(icon30->width<=0||icon30->height<=0))icon30=0;
 if(!r.isEmpty()){
  icon34=TheMappedImageCollection->findImageByName(AsciiString("ResourceBar_")+r);
  if(icon34&&(icon34->width<=0||icon34->height<=0))icon34=0;
 }
 SetupDisplayStrings();
}
