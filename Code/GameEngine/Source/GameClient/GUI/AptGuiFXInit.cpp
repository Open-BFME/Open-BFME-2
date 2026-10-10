// Reference lead: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameClient/GUI/AptGuiFXRegisterCallbacks.cpp.
// WB F650A0 names AptGuiFX::Init, source AptGuiFX.cpp:74; native boundary
// 0x380B0C..0x380C1E is 274 bytes. Target adds registry value13, load slot50
// with two trailing arguments, and the strategic-message singleton.
// Existing BFME2 53-byte holders own callback construction; their argument
// is the address of a function pointer, not the function pointer itself.
// The AptRef reference-count operations agree with the registration provider.
// 0x3806D4 ignores its incoming receiver; the member/free union preserves
// its existing ledger spelling and the native no-receiver call ABI.
// The filename address contains the one-word StringBase<char> representation;
// g_Va00E022E8 is an existing neutral data name, not a new identity assertion.
// Bank: O1 emits274, all calls/instructions align, but callback stack slots
// are distinct: frame14 vs retail10, second callback -1C vs retail -18,
// savedESP -20 vs -1C. A shared callback fixes frame but changes stack slots.
// O2 emits320 and cannot be admitted. No source/ledger claim of exactness.
// cl: /O1 /Ob1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// BFME2's GuiFX screen Apt callback "AptGuiFX::OnInitialized", a static
// callback bound by that name through the holder 0x0023E8D8 by the
// screen's registration 0x00380B0C; that binding is its only reference.
// The class is named for the string's prefix.

// The GuiFX movie's ready flag (0x00E022E0, beside the "GuiFX.apt" name at
// 0x00E022E8).
extern bool g_Va00E022E0;

class AptGuiFX
{
public:
	static void OnInitialized(const char *unused);
	
};

// Retail 0x003808E8, 8 bytes: "AptGuiFX::OnInitialized" marks the GuiFX
// movie ready.
void AptGuiFX::OnInitialized(const char *unused)
{
	g_Va00E022E0 = true;
}

#include "ascii_string.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern unsigned int g_Va00E022E8;
extern void *TheRva00222A8BOwner;
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class AptRefCounted { public: void *m_vtbl; int m_refCount; };
class AptCommandMap : public AptRefCounted {};
class AptCustomRender : public AptRefCounted {};
// The two callback-holder constructors (rows 0x0023E8D8 Rva0023E8D8Ctor.cpp
// and 0x00380AB1 Rva00380AB1Ctor.cpp) are visible inline-never-inlined with
// their row bodies: retail's compiler knew they only read the function
// pointer, which shares the pointer temporary and the argument-save slot
// across the registrations (frame 0x10).
void *__cdecl operator new(unsigned int);
class Rva0023E8D8Impl { public: virtual ~Rva0023E8D8Impl(); int m_ref; void *m_func; Rva0023E8D8Impl(void *p) : m_ref(0) { m_func = *(void **)p; } };
class Rva0023E8D8 { Rva0023E8D8Impl *m_ptr; public: __declspec(noinline) Rva0023E8D8(void *p) { Rva0023E8D8Impl *q = new Rva0023E8D8Impl(p); m_ptr = q; if (q) ++q->m_ref; } };
class Rva00380AB1Impl { public: virtual ~Rva00380AB1Impl(); int m_ref; void *m_func; Rva00380AB1Impl(void *p) : m_ref(0) { m_func = *(void **)p; } };
class Rva00380AB1 { Rva00380AB1Impl *m_ptr; public: __declspec(noinline) Rva00380AB1(void *p) { Rva00380AB1Impl *q = new Rva00380AB1Impl(p); m_ptr = q; if (q) ++q->m_ref; } };

template<class T> class AptRef {
public:
 T *m_ptr;
 AptRef(void *);
 AptRef(const AptRef &other):m_ptr(other.m_ptr) {if(m_ptr) ++m_ptr->m_refCount;}
 ~AptRef(){if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}
};
template<> inline AptRef<AptCommandMap>::AptRef(void *p) { ((Rva0023E8D8*)this)->Rva0023E8D8::Rva0023E8D8(p); }
template<> inline AptRef<AptCustomRender>::AptRef(void *p) { ((Rva00380AB1*)this)->Rva00380AB1::Rva00380AB1(p); }
class AptPlayer {
public:
 void AddCommandMap(const AsciiString &,AptRef<AptCommandMap>);
 void AddCustomRender(const AsciiString &,AptRef<AptCustomRender>);
};
class GuiFXWindowLoader {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
 SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
#undef SLOT
 virtual int loadWindow(AsciiString directory,AsciiString file,int arg1,int arg2);
};
struct Rva001408C0Target;
class Rva002239B2 {public:void rva002239B2(const void *,Rva001408C0Target *);};
class Coord2D;
void rva00380869(Coord2D *,Coord2D *);
class Rva003806D4 {public:void rva003806D4();};
class AptStrategicMessageBox {public:static void CreateSingleton();};
void Rva00380B0CInit() {
 if (g_bfmeAptWindowManager) {
  g_Va00E022E0=false;
  reinterpret_cast<Rva002239B2 *>(g_bfmeAptWindowManager)->rva002239B2(&g_Va00E022E8,reinterpret_cast<Rva001408C0Target *>(13));
  TheRva00222A8BOwner=reinterpret_cast<void *>(reinterpret_cast<GuiFXWindowLoader *>(g_bfmeAptWindowManager)->loadWindow("Apt\\",*reinterpret_cast<AsciiString *>(&g_Va00E022E8),1,0));
  if (g_bfmeAptWindowManager) {
   AsciiString name("AptGuiFX::OnInitialized");
   void (__cdecl *callback)()=reinterpret_cast<void (__cdecl *)()>(AptGuiFX::OnInitialized);
   reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->AddCommandMap(name,AptRef<AptCommandMap>(&callback));
  }
  {
   AsciiString name("ToolTipText");
   void (__cdecl *callback)()=reinterpret_cast<void (__cdecl *)()>(rva00380869);
   reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->AddCustomRender(name,AptRef<AptCustomRender>(&callback));
  }
  union {void (Rva003806D4::*member)();void (__cdecl *call)();} create;
  create.member=&Rva003806D4::rva003806D4;
  create.call();
  AptStrategicMessageBox::CreateSingleton();
 }
}


