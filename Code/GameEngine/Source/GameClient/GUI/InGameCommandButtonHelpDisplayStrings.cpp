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
class InGameCommandButtonHelp {public: class Impl;};
class InGameCommandButtonHelp::Impl {public:
 char pad[0x1C]; DisplayString *s1,*s2,*s3,*s4,*s5;
 void SetupDisplayStrings();
};
void InGameCommandButtonHelp::Impl::SetupDisplayStrings() {
 Rva0056C790(s1,&((Rva0029F8B8*)TheInGameUI)->rva0029F8B8());
 Rva0056C790(s2,&((Rva0029F8B8*)TheInGameUI)->rva0029D844());
 Rva0056C790(s3,&((Rva0029F8B8*)TheInGameUI)->rva0029D844());
 Rva0056C790(s4,&((Rva0029F8B8*)TheInGameUI)->rva0029D8C6());
 Rva0056C790(s5,&((Rva0029F8B8*)TheInGameUI)->rva0029D948());
}
