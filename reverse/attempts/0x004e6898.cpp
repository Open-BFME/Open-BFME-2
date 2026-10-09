// ?RenderMessage@InGameNotificationBoxMovieClip@@QAEXPBVCoord2D@@0PAX1@Z
// partial score=0.973015873015873 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /Oy /G7 /arch:SSE /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep /ICode/Libraries/Include/Lib
#include "ascii_string.h"
#include "unicode_string.h"
#include "Coord2D.h"
#include "wwmath.h"
#include <stdlib.h>
// Notification-box ownership transfer: native004E6BF6..004E6C34 RET4;
// WorldBuilder013238A0 returns a consuming holder through a hidden result.
// Rva004E6A1D clear and Rva004E6A37 destructor/assignment establish the
// existing owner spellings. Copy empties its source before publishing the
// pointer; the returned holder has the independently rowed destructor.
// The original method name is unproven; preserve a neutral address name.
class Rva004E6935;
class Rva004E6A37 {
public:
 Rva004E6935 *m_ptr;
 Rva004E6A37(Rva004E6935 *p=0):m_ptr(p) {}
 Rva004E6A37(Rva004E6A37 &v) { Rva004E6935 *p=v.m_ptr; v.m_ptr=0; m_ptr=p; }
 ~Rva004E6A37();
 Rva004E6A37 &operator=(Rva004E6A37);
};
class Rva004E6A1D {
public:
 Rva004E6935 *m_ptr;
 Rva004E6A1D():m_ptr(0){}
 ~Rva004E6A1D(){clear();}
 void clear();
 Rva004E6A37 rva004E6BF6();
};
Rva004E6A37 Rva004E6A1D::rva004E6BF6() {
 Rva004E6A37 transfer(m_ptr);
 m_ptr=0;
 return Rva004E6A37(transfer);
}

namespace _STL {
 template<class T> class allocator {public:allocator(){}};
 template<class T,class A> class _Vector_base {public:_Vector_base(const A&);protected:T*first,*last,*limit;};
}
class Rva0052413E {public:Rva0052413E();~Rva0052413E();char data[12];};
class Rva005241B0 {public:Rva005241B0();~Rva005241B0();char data[12];};
class Rva005242D7 {public:Rva005242D7();~Rva005242D7();char data[12];};
class Rva00524265 {public:Rva00524265();~Rva00524265();private:_STL::_Vector_base<AsciiString,_STL::allocator<AsciiString> > names;};
Rva00524265::Rva00524265():names(_STL::allocator<AsciiString>()){}
struct AsciiStringRef{const AsciiString*string;};
struct Rva000B3F84Pair{const char*string;int length;};
struct AsciiStringPlusText:AsciiStringRef{Rva000B3F84Pair text;operator AsciiString();};
AsciiStringPlusText operator+(const AsciiString&,const char*);
class __single_inheritance InGameNotificationBoxMovieClip;
typedef void(InGameNotificationBoxMovieClip::*NoticeCommand)(unsigned);
struct DelegateDesc{DelegateDesc(InGameNotificationBoxMovieClip*p,NoticeCommand m):object(p),method(m){} InGameNotificationBoxMovieClip*object;NoticeCommand method;};
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47&);~Rva00579E47();void*ptr;};
template<class T> class AptRef:public Rva00579E47{public:AptRef(DelegateDesc d):Rva00579E47(d){}};
class AptCommandMap;class AptExternHandler;class AptCustomRender;
class AptCommandMapAdder {public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);};
class AptExternHandlerAdder {public:void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>);};
class AptCustomRenderAdder {public:void AddCustomRender(const AsciiString&,AptRef<AptCustomRender>);};
class DisplayString;
class NoticeStringView{public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();
 virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual void s2C();
 virtual void s30();virtual void draw(int,int);virtual void s38();virtual void getSize(int*,int*);
};
class DisplayStringManager;extern DisplayStringManager*TheDisplayStringManager;
class NoticeStringManagerView {public:
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
virtual DisplayString*newString();
};
class BfmeAptWindowManager;extern BfmeAptWindowManager*g_bfmeAptWindowManager;
class NoticeAptManagerView {public:
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
virtual void s3C();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4C();
virtual int load(AsciiString,AsciiString,int,int);
};
class Rva002224FE {public:bool rva002224FE(int);};
class Rva004E67B3 {public:void rva004E67B3(unsigned);};
class Rva002217EA;
class Rva004E6A9BBase {public:virtual unsigned char rva00578522()const;virtual void rva004E6B7D(bool);virtual void DoOpen(const UnicodeString&,const Rva002217EA&,int);virtual void DoClose();~Rva004E6A9BBase(){}};
class InGameNotificationBoxMovieClip:public Rva004E6A9BBase {public:
 InGameNotificationBoxMovieClip();
 virtual unsigned char rva00578522()const;virtual void rva004E6B7D(bool);
 virtual void DoOpen(const UnicodeString&,const Rva002217EA&,int);virtual void DoClose();
 void CloseImmediately();void OnInitialized(unsigned);void OnClosed(unsigned);void rva004E67D0(int);
 void MessageWidth(int,const char*,bool);void RenderMessage(const Coord2D*,const Coord2D*,void*,void*);
 int level,state;Rva0052413E commands;Rva005241B0 externs;Rva00524265 renders;Rva005242D7 images;
 float width;Rva004E6A1D pending,active;unsigned timestamp;DisplayString*string;unsigned char flag50,iconVisible;
};
InGameNotificationBoxMovieClip::InGameNotificationBoxMovieClip():level(-1),state(0),width(0.0f),timestamp(0),string(((NoticeStringManagerView*)TheDisplayStringManager)->newString()),flag50(0),iconVisible(1) {
 level=((NoticeAptManagerView*)g_bfmeAptWindowManager)->load(AsciiString("Apt\\"),AsciiString("InGameNotificationBox.apt"),0,0);
 AsciiString prefix;prefix.format("_level%u",level);
 ((AptCommandMapAdder*)&commands)->AddCommandMap(prefix+"_OnInitialized",AptRef<AptCommandMap>(DelegateDesc(this,&InGameNotificationBoxMovieClip::OnInitialized)));
 ((AptCommandMapAdder*)&commands)->AddCommandMap(prefix+"_OnOpen",AptRef<AptCommandMap>(DelegateDesc(this,reinterpret_cast<NoticeCommand>(&Rva004E67B3::rva004E67B3))));
 ((AptCommandMapAdder*)&commands)->AddCommandMap(prefix+"_OnClosed",AptRef<AptCommandMap>(DelegateDesc(this,&InGameNotificationBoxMovieClip::OnClosed)));
 ((AptCommandMapAdder*)&commands)->AddCommandMap(prefix+"_OnCloseButtonClicked",AptRef<AptCommandMap>(DelegateDesc(this,reinterpret_cast<NoticeCommand>(&InGameNotificationBoxMovieClip::rva004E67D0))));
 ((AptExternHandlerAdder*)&externs)->AddExternHandler(prefix+"_MessageWidth",0,AptRef<AptExternHandler>(DelegateDesc(this,reinterpret_cast<NoticeCommand>(&InGameNotificationBoxMovieClip::MessageWidth))));
 ((AptCustomRenderAdder*)&renders)->AddCustomRender(prefix+"_Message",AptRef<AptCustomRender>(DelegateDesc(this,reinterpret_cast<NoticeCommand>(&InGameNotificationBoxMovieClip::RenderMessage))));
 ((Rva002224FE*)g_bfmeAptWindowManager)->rva002224FE(level);
}
void InGameNotificationBoxMovieClip::OnInitialized(unsigned){if(state==0)state=1;}
void InGameNotificationBoxMovieClip::MessageWidth(int,const char*text,bool){width=(float)atof(text);}
unsigned char InGameNotificationBoxMovieClip::rva00578522()const{return flag50;}
void InGameNotificationBoxMovieClip::rva004E6B7D(bool value){if(value!=flag50){if(!value)CloseImmediately();flag50=value;}}
void InGameNotificationBoxMovieClip::RenderMessage(const Coord2D*position,const Coord2D*size,void*,void*) {
 if(active.m_ptr){int w,h;((NoticeStringView*)string)->getSize(&w,&h);
 int x=WWMath::Float_To_Long((float)floor(position->x+(size->x-w+1.0f)*0.5f));
 int y=WWMath::Float_To_Long((float)floor(position->y+(size->y-h+1.0f)*0.5f));
 ((NoticeStringView*)string)->draw(x,y);}
}
