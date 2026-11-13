// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /EHsc /MD
// ??1Rva005D40A6@@UAE@XZ retail 0x005D40A6 114B.
// Constructor5D4433..5D46E3 owns688 bytes including its27-byte catch handler;
// WB15A67C0/StrategicHUDChecklistUIItemMovieClip.cpp and the four binding suffixes
// independently establish the checklist role. Preserve the existing neutral
// class owner until original target spelling is independently established.
// Native five-slot tableC759D0: dtor, empty RET4, then three empty RET hooks.
// Native caller4395 passes a float to slot1; the other three empty hooks take
// no argument words. Original hook names remain unknown.
// Native member offsets: level4/name8/mapsC/render-names18/display24/text28,
// color2C/floats30,38/word34 and seven individually initialized flag bits3C.
// WB15A7470 names the254-byte Update callback. Native flag bits gate width/height
// readiness and three Fire setters; inverse-scale reference before multiplication
// keeps the target member-first SSE load without altering arithmetic.
// Private helper415D has caller-clean ECX/name ABI and WB15A7790 RetrieveTextWidth;
// height4287 uses the same capture/value lifetime and native scale.y. Result
// is initialized after handler teardown to retain native BL; three adjacent
// height locals preserve native addressable storage. SetText/Wrap/Height paths
// use native virtual slots04/20/40 and float hook04.
// Catch states9/10 and handler5D46C8 prove free-display then rethrow.
// Renderer: FISTP is required by retail under SSE; the two-instruction helper
// follows the proven codegen blocker already present in Rva005D2B2FMethod.cpp.
// Dtor with vtable 0x008759D0, DisplayString at +0x24 freed via manager slot 0x3C,
// UnicodeString at +0x28, Rva00524265 at +0x18, Rva0052413E at +0x0c, AsciiString
// at +0x08. EH states 3/2/1/0/-1. Unblocks 0x0057A2B0 0x005D4141.
// Evidence: callees rowed releaseBuffer narrow/wide plus rowed dtors, manager 0x009FEAD8 slot 0x3C.
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include "ascii_string.h"
#include "unicode_string.h"
#include <math.h>
#include <stdlib.h>

#include "../../Include/Common/FloatPair.h"
class GameFont;
#include "../../Include/GameClient/DisplayString.h"
struct ChecklistFontDesc { AsciiString name; int size; bool bold; };
#include "../../Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;
#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../Include/GameClient/DisplayStringManager.h"

extern DisplayStringManager *TheDisplayStringManager;

class Rva00524265
{
public:
	Rva00524265();
	~Rva00524265();
private:
	char m_pad[0x0c];
};

#include "../../Include/Common/Rva0052413E.h"

class Rva005D40A6
{
public:
 Rva005D40A6(int,const AsciiString &,const ChecklistFontDesc &);
 void OnClicked(const char *); void OnRollOver(const char *); void OnRollOut(const char *);
 void RenderText(const FloatPair &,const FloatPair &,unsigned int,unsigned int);
 // ?UpdateHeight@Rva005D40A6@@QAEXXZ @0x005D4395 158B: renamed from
 // placeholder rva005D4395 — the WorldBuilder twin names
 // ChecklistUIItemMovieClip::UpdateHeight at EA's own file (strings); the
 // receiver class stays the guessed view until its family reconciles with the
 // landed Flash spelling.
 void UpdateHeight(); void Update(); void rva005D46E3(const UnicodeString &); void rva005D472C();
 virtual ~Rva005D40A6();
 virtual void rva0047A69C(float);
 virtual void rva000B3FD0Slot08(); virtual void rva000B3FD0Slot0C();
 virtual void rva000B3FD0Slot10();
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0c;
	Rva00524265 m_18;
	DisplayString *m_24;
 UnicodeString m_28;
 unsigned int m_color2C; float m_float30; int m_word34; float m_float38;
 unsigned char flag0:1, flag1:1, flag2:1, flag3:1, flag4:1, flag5:1, flag6:1, flag7:1;
};

Rva005D40A6::~Rva005D40A6()
{
	if (TheDisplayStringManager != 0 && m_24 != 0)
		TheDisplayStringManager->freeDisplayString(m_24);
}

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

namespace StrategicHUD { class ChecklistUIItemMovieClip; }
class StrategicHUD::ChecklistUIItemMovieClip
{
public:
	void Flash();
private:
	int m_00;
	void *m_04;
	const char *m_08;
};
void StrategicHUD::ChecklistUIItemMovieClip::Flash()
{
	const char *s = m_08 ? m_08 + 8 : "";
	Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_04, s, "Flash");
}

#include "../../Include/Common/Rva000B3F84Pair.h"
#include "../../Include/Common/AsciiStringRef.h"
#include "../../Include/Common/AsciiStringPlusString.h"
struct AsciiStringPlusStringText : AsciiStringPlusString {
    operator AsciiString(); Rva000B3F84Pair m_text;
};
inline AsciiStringPlusString operator+(const AsciiString &a,const AsciiString &b) {
    AsciiStringPlusString result; result.m_string=&a; result.m_second.m_string=&b; return result;
}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right) {
    Rva000B3F84Pair text; text.init(right); AsciiStringPlusStringText result;
    static_cast<AsciiStringPlusString &>(result)=left; result.m_text=text; return result;
}

class __single_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(const char *);
#include "../../Include/Common/DelegateDesc.h"
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
#include "../../Include/Common/FunctorHeader.h"
class Rva00579E47 { public:
    Rva00579E47(const DelegateDesc &);
    Rva00579E47(const Rva00579E47 &other):ptr(other.ptr) { if(ptr) ++ptr->refs; }
    FunctorHeader *ptr;
};
template<class T> class AptRef : public Rva00579E47 { public:
    AptRef(DelegateDesc d):Rva00579E47(d) {}
    ~AptRef() { if(ptr) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(ptr)); }
};
class AptCommandMap;
#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"
static __forceinline DelegateDesc MakeBinding(FunctorMethod f,FunctorTarget *functorTarget) { return DelegateDesc(f,functorTarget); }

class AptCustomRender;
class AptCustomRenderAdder { public: void AddCustomRender(const AsciiString &,AptRef<AptCustomRender>); };
Rva005D40A6::Rva005D40A6(int level,const AsciiString &name,const ChecklistFontDesc &fontDesc)
 :m_04(level),m_08(name),m_24(0),m_color2C(0xffffffff),m_float30(0),m_word34(0),m_float38(0)
{
 flag0=false; flag1=true; flag2=true; flag3=true; flag4=true; flag5=false; flag6=false;
 AsciiString prefix; prefix.format("_level%u.",m_04);
 reinterpret_cast<AptCustomRenderAdder *>(&m_18)->AddCustomRender(prefix+m_08+"_RenderText",
  AptRef<AptCustomRender>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D40A6::RenderText),reinterpret_cast<FunctorTarget *>(this))));
 reinterpret_cast<AptCommandMapAdder *>(&m_0c)->AddCommandMap(prefix+m_08+"_OnClicked",
  AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D40A6::OnClicked),reinterpret_cast<FunctorTarget *>(this))));
 reinterpret_cast<AptCommandMapAdder *>(&m_0c)->AddCommandMap(prefix+m_08+"_OnRollOver",
  AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D40A6::OnRollOver),reinterpret_cast<FunctorTarget *>(this))));
 reinterpret_cast<AptCommandMapAdder *>(&m_0c)->AddCommandMap(prefix+m_08+"_OnRollOut",
  AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D40A6::OnRollOut),reinterpret_cast<FunctorTarget *>(this))));
 m_24=TheDisplayStringManager->newDisplayString();
 try {
  const FloatPair &scale=*(const FloatPair *)g_bfmeAptWindowManager->vslot15();
  float maxScale=scale.x<scale.y?scale.x:scale.y;
  GameFont *font=TheFontLibrary->getFont(&fontDesc.name,fontDesc.size*maxScale,fontDesc.bold);
  m_24->setColors(m_color2C,0); m_24->setFont(font);
 } catch(...) { TheDisplayStringManager->freeDisplayString(m_24); throw; }
}
void Rva005D40A6::OnClicked(const char *) { if(!g_bfmeAptWindowManager->field318) rva000B3FD0Slot08(); }
void Rva005D40A6::OnRollOver(const char *) { rva000B3FD0Slot0C(); }
void Rva005D40A6::OnRollOut(const char *) { rva000B3FD0Slot10(); }
void Rva005D40A6::rva0047A69C(float) {}
void Rva005D40A6::rva000B3FD0Slot08() {}
void Rva005D40A6::rva000B3FD0Slot0C() {}
void Rva005D40A6::rva000B3FD0Slot10() {}

static __forceinline int checklistRound(float value) {
 int result;
 __asm { fld [value] }
 __asm { fistp [result] }
 return result;
}
void Rva005D40A6::RenderText(const FloatPair &position,const FloatPair &size,unsigned int,unsigned int)
{
 if(flag5 && flag6) {
  int width,height; m_24->getSize(&width,&height);
  int x=checklistRound((float)floor(position.x+0.5f));
  int y=checklistRound((float)floor((size.y-height+1.0f)*0.5f+position.y));
  m_24->draw(x,y);
 }
}

struct Rva0057ACEBData { int word0,word4; };
#include "../../Include/Common/Rva0057ACEB.h"
class Rva005D4E22 { public: Rva005D4E22(bool *,AsciiString *); int word0,word4; };
class AptExternHandler;
template<> class AptRef<AptExternHandler> : public Rva0057ACEB {
 public: __forceinline AptRef(Rva005D4E22 data):Rva0057ACEB(reinterpret_cast<const Rva0057ACEBData *>(&data)) {}
 AptRef(const AptRef &other):Rva0057ACEB(other) { if(impl) ++reinterpret_cast<int *>(impl)[1]; }
 ~AptRef() { if(impl) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(impl)); }
};
class AptSingleExternHandlerAdder { public:
 AptSingleExternHandlerAdder(const AsciiString &,int,AptRef<AptExternHandler>);
 ~AptSingleExternHandlerAdder(); AsciiString name;
};
namespace StrategicHUD {
static __declspec(noinline) bool RetrieveTextWidth(const AsciiString &path,int level,int *output) {
 AsciiString value; bool ready=false;
 {
  AsciiString name; name.format("_level%u.%s_TextWidth",level,path.str());
  AptSingleExternHandlerAdder handler(name,0,AptRef<AptExternHandler>(Rva005D4E22(&ready,&value)));
  Rva00524EF4AptCall(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),reinterpret_cast<void *>(level),path.str(),"GetTextWidth");
 }
 bool result=false;
 if(ready) {
  const FloatPair &scale=*(const FloatPair *)g_bfmeAptWindowManager->vslot15();
  float v=static_cast<float>(atof(value.str()));
  *output=checklistRound(static_cast<float>(floor(v*scale.x+0.5f))); result=true;
 }
 return result;
}
}
// WorldBuilder StrategicHUD::RetrieveHeight, WB VA 0x015A7B30 (strings lead, score 2.0).
namespace StrategicHUD {
static __declspec(noinline) bool RetrieveHeight(const AsciiString &path,int level,float *output) {
 AsciiString value; bool ready=false;
 {
  AsciiString name; name.format("_level%u.%s_Height",level,path.str());
  AptSingleExternHandlerAdder handler(name,0,AptRef<AptExternHandler>(Rva005D4E22(&ready,&value)));
  Rva00524EF4AptCall(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),reinterpret_cast<void *>(level),path.str(),"GetHeight");
 }
 bool result=false;
 if(ready) {
  const FloatPair &scale=*(const FloatPair *)g_bfmeAptWindowManager->vslot15();
  float v=static_cast<float>(atof(value.str())); *output=scale.y*v; result=true;
 }
 return result;
}
}
int __cdecl Rva00527925Fire(void *,void *,const char *,const char *,const float *);
void Rva005D40A6::UpdateHeight() {
 struct { int width; float value; int height; } local;
 m_24->getSize(&local.width,&local.height);
 local.value=local.height*((const FloatPair *)g_bfmeAptWindowManager->vslot16())->y;
 Rva00527925Fire(g_bfmeAptWindowManager,reinterpret_cast<void *>(m_04),m_08.str(),"SetHeight",&local.value);
 if(StrategicHUD::RetrieveHeight(m_08,m_04,&local.value)) {
  flag5=true;
  if(local.value!=m_float30) { float old=m_float30; m_float30=local.value; rva0047A69C(old); }
 }
}
void Rva005D40A6::rva005D46E3(const UnicodeString &text) {
 if(text.compare(m_28)) {
  m_24->setText(text); m_28=text; flag5=false; UpdateHeight();
 }
}
void Rva005D40A6::rva005D472C() {
 int width;
 if(StrategicHUD::RetrieveTextWidth(m_08,m_04,&width)) {
  m_word34=width; m_24->setWordWrap(width); flag5=false; UpdateHeight(); flag6=true;
 }
}

void __cdecl Rva005277D9Fire(Rva00222A8BTarget *,void *,const char *,const char *,bool *);
void Rva005D40A6::Update() {
 if(!flag6) { rva005D472C(); if(!flag6)return; }
 if(!flag5) { UpdateHeight(); if(!flag5)return; }
 if(!flag1) {
  bool value=flag0;
  Rva005277D9Fire(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),reinterpret_cast<void *>(m_04),m_08.str(),"SetChecked",&value);
  flag1=true;
 }
 if(!flag3) {
  bool value=flag2;
  Rva005277D9Fire(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),reinterpret_cast<void *>(m_04),m_08.str(),"SetCheckVisibility",&value);
  flag3=true;
 }
 if(!flag4) {
  const FloatPair &inverse=*(const FloatPair *)g_bfmeAptWindowManager->vslot16();
  float value=m_float38*inverse.y;
  Rva00527925Fire(g_bfmeAptWindowManager,reinterpret_cast<void *>(m_04),m_08.str(),"SetY",&value);
  flag4=true;
 }
}
