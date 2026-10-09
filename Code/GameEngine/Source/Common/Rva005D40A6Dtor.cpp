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
#include "ascii_string.h"
#include "unicode_string.h"

struct FloatPair { float x,y; };
class GameFont;
class DisplayString { public:
 virtual ~DisplayString(); virtual void setText(UnicodeString); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void setFont(GameFont *); virtual void slot1C(); virtual void setWordWrap(int);
 virtual void slot24(); virtual void setColor(unsigned int,unsigned int);
 virtual void slot2C(); virtual void slot30(); virtual void draw(int,int);
 virtual void slot38(); virtual void getSize(int *,int *);
};
struct ChecklistFontDesc { AsciiString name; int size; bool bold; };
class FontLibrary { public: GameFont *getFont(const AsciiString *,float,bool); };
extern FontLibrary *TheFontLibrary;
class BfmeAptWindowManager { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual void slot38();
 virtual const FloatPair &getScale(); virtual const FloatPair &getInverseScale();
 char pad04[0x318-4]; int suppressClick318;
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void managerSlot04() = 0;
	virtual void managerSlot08() = 0;
	virtual void managerSlot0C() = 0;
	virtual void managerSlot10() = 0;
	virtual void managerSlot14() = 0;
	virtual void managerSlot18() = 0;
	virtual void managerSlot1C() = 0;
	virtual void managerSlot20() = 0;
	virtual void managerSlot24() = 0;
	virtual void managerSlot28() = 0;
	virtual void managerSlot2C() = 0;
	virtual void managerSlot30() = 0;
	virtual void managerSlot34() = 0;
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *s);
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva00524265
{
public:
	Rva00524265();
	~Rva00524265();
private:
	char m_pad[0x0c];
};

class Rva0052413E
{
public:
	Rva0052413E();
	~Rva0052413E();
private:
	char m_pad[0x0c];
};

class Rva005D40A6
{
public:
 Rva005D40A6(int,const AsciiString &,const ChecklistFontDesc &);
 void OnClicked(const char *); void OnRollOver(const char *); void OnRollOut(const char *);
 void RenderText(const FloatPair &,const FloatPair &,unsigned int,unsigned int);
 void rva005D4395(); void rva005D46E3(const UnicodeString &); void rva005D472C();
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
extern Rva00222A8BTarget *TheRva00222A8BTarget;

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
	Rva00524EF4AptCall(TheRva00222A8BTarget, m_04, s, "Flash");
}

class Rva000B3F84Pair { public: Rva000B3F84Pair() {} Rva000B3F84Pair *init(const char *); const char *m_ptr; int m_len; };
struct AsciiStringRef { const AsciiString *m_string; };
struct AsciiStringPlusString : AsciiStringRef { AsciiStringRef m_second; };
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
struct DelegateDesc {
    DelegateDesc(FunctorMethod f,FunctorTarget *p):object(p),method(f) {}
    FunctorTarget *object; FunctorMethod method;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct FunctorHeader { void *vptr; int refs; };
class Rva00579E47 { public:
    Rva00579E47(const DelegateDesc &);
    Rva00579E47(const Rva00579E47 &r):ptr(r.ptr) { if(ptr) ++ptr->refs; }
    FunctorHeader *ptr;
};
template<class T> class AptRef : public Rva00579E47 { public:
    AptRef(DelegateDesc d):Rva00579E47(d) {}
    ~AptRef() { if(ptr) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(ptr)); }
};
class AptCommandMap;
class AptCommandMapAdder { public:
    void AddCommandMap(const AsciiString &,AptRef<AptCommandMap>);
};
static __forceinline DelegateDesc MakeBinding(FunctorMethod f,FunctorTarget *p) { return DelegateDesc(f,p); }

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
  const FloatPair &scale=g_bfmeAptWindowManager->getScale();
  float maxScale=scale.x<scale.y?scale.x:scale.y;
  GameFont *font=TheFontLibrary->getFont(&fontDesc.name,fontDesc.size*maxScale,fontDesc.bold);
  m_24->setColor(m_color2C,0); m_24->setFont(font);
 } catch(...) { TheDisplayStringManager->freeDisplayString(m_24); throw; }
}
void Rva005D40A6::OnClicked(const char *) { if(!g_bfmeAptWindowManager->suppressClick318) rva000B3FD0Slot08(); }
void Rva005D40A6::OnRollOver(const char *) { rva000B3FD0Slot0C(); }
void Rva005D40A6::OnRollOut(const char *) { rva000B3FD0Slot10(); }
void Rva005D40A6::rva0047A69C(float) {}
void Rva005D40A6::rva000B3FD0Slot08() {}
void Rva005D40A6::rva000B3FD0Slot0C() {}
void Rva005D40A6::rva000B3FD0Slot10() {}

extern "C" __declspec(dllimport) double __cdecl floor(double);
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
class Rva0057ACEB { public: Rva0057ACEB(const Rva0057ACEBData *); void *impl; };
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
extern "C" __declspec(dllimport) double __cdecl atof(const char *);
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
  const FloatPair &scale=g_bfmeAptWindowManager->getScale();
  float v=static_cast<float>(atof(value.str()));
  *output=checklistRound(static_cast<float>(floor(v*scale.x+0.5f))); result=true;
 }
 return result;
}
}
static __declspec(noinline) bool Rva005D4287(const AsciiString &path,int level,float *output) {
 AsciiString value; bool ready=false;
 {
  AsciiString name; name.format("_level%u.%s_Height",level,path.str());
  AptSingleExternHandlerAdder handler(name,0,AptRef<AptExternHandler>(Rva005D4E22(&ready,&value)));
  Rva00524EF4AptCall(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),reinterpret_cast<void *>(level),path.str(),"GetHeight");
 }
 bool result=false;
 if(ready) {
  const FloatPair &scale=g_bfmeAptWindowManager->getScale();
  float v=static_cast<float>(atof(value.str())); *output=scale.y*v; result=true;
 }
 return result;
}
int __cdecl Rva00527925Fire(void *,void *,const char *,const char *,const float *);
void Rva005D40A6::rva005D4395() {
 struct { int width; float value; int height; } local;
 m_24->getSize(&local.width,&local.height);
 local.value=local.height*g_bfmeAptWindowManager->getInverseScale().y;
 Rva00527925Fire(g_bfmeAptWindowManager,reinterpret_cast<void *>(m_04),m_08.str(),"SetHeight",&local.value);
 if(Rva005D4287(m_08,m_04,&local.value)) {
  flag5=true;
  if(local.value!=m_float30) { float old=m_float30; m_float30=local.value; rva0047A69C(old); }
 }
}
void Rva005D40A6::rva005D46E3(const UnicodeString &text) {
 if(text.compare(m_28)) {
  m_24->setText(text); m_28=text; flag5=false; rva005D4395();
 }
}
void Rva005D40A6::rva005D472C() {
 int width;
 if(StrategicHUD::RetrieveTextWidth(m_08,m_04,&width)) {
  m_word34=width; m_24->setWordWrap(width); flag5=false; rva005D4395(); flag6=true;
 }
}
