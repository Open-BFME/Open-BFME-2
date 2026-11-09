// cl: -MD -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/GUI
// stlport
// Constructor body at 0x00787710. Matched factory 0x00788290 allocates 0x30
// bytes and calls this body through ILT 0x0003097C. The established factory
// spelling bfmeConstruct00788290 is retained by the ledger object-symbol note.
// Vtable 0x01126AD0 and destructor 0x007859D0 independently establish the owner,
// base, m_name (+4), and m_displayString (+8). Tail fields are address-qualified.
// Rect/size aggregate initialization preserves the native store order. The
// two volatile rectangle stores retain retail's y-before-right write ordering.
// Existing display-string shims put getSize at +0x30; this body calls +0x3C
// and +0x48, so its observed virtual interface is kept local. This split
// unit emits only setSize and uses the shared BFME2 text and string declarations.

#include <string>
#include <string.h>
#include <new>
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../../../reference/shims/bfme2_ascii/unicode_string.h"
std::wstring MultiByteToWideCharSingleLine(const char*);
class GameFont;
#include "../../../../../GameEngine/Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;
#include "../../../../../GameEngine/Include/GameClient/DisplayString.h"
#include "../../../../../GameEngine/Include/GameClient/DisplayStringManager.h"
extern DisplayStringManager *TheDisplayStringManager;
#include "../../../../../GameEngine/Include/GameClient/GameText.h"
class AptTextListener;
class WindowManager { public: void bfme_bindAptText(const AsciiString&,const UnicodeString&,AptTextListener*); };
extern WindowManager *g_rva012F19E8WindowManager;
extern bool Rva012BB864ScaleEnabled;
extern float Rva012BB86CScaleX,Rva012BB870ScaleY;
class Rva00788290Base { public: virtual ~Rva00788290Base() {} };
class Rva00788290Object {
public:
 const char *m_at00;
 float m_at04,m_at08,m_at0c,m_at10;
 int m_at14,m_at18;
 int m_state1c;
 float m_value20;
 int m_at24,m_at28,m_at2c;
 char m_pad30[0x10];
 float m_value40,m_value44;
 float m_at48;
 int m_at4c,m_at50;
 const char *m_at54;
 unsigned m_flags58;
 void *m_source5c;
};
struct Rect00787710 { float a,b,c,d; Rect00787710() : a(0),b(0),c(0),d(0) {} };
struct Size00787710 { float a,b; Size00787710(float x,float y) : a(x),b(y) {} };
class Rva00788290Allocation : public Rva00788290Base {
public:
 Rva00788290Allocation(Rva00788290Object *source);
 void setSize(float width,float h);
 void setRect00787710(float x,float y,float r,float b);
 virtual ~Rva00788290Allocation();
 AsciiString m_name;
 DisplayString *m_displayString;
 Rect00787710 m_rect00787710;
 Size00787710 m_size;
 unsigned m_at24,m_at28;
 bool m_at2c,m_dropShadow,m_at2e;
};
// Only the target body is emitted here; the donor's 0x00787710 constructor is
// omitted. setSize00787710 is declared in-class and defined out-of-line so it
// is emitted without the caller.
void Rva00788290Allocation::setSize(float width,float h) { m_size.a=width; m_size.b=h; }
