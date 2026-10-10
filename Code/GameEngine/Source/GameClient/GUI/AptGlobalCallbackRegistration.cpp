// cl: /O1 /G7 /EHsc /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// Rva00412F14Register, retail 0x00412F14 (987 bytes).
//
// Target evidence: registers the global Apt scripting callbacks with
// TheAptPlayer: six command maps (MouseSetVisibility, CloseWindow, PlaySound,
// OnClickThroughPress/Release, SetBackground) each guarded by a TheAptPlayer
// check, four extern queries (InBetaDemo 1 and InDreamMachineDemo 2 on the
// rowed 0x0041273C query, InGame and DoTrace 0) and three custom renders
// (RenderImage, RenderImageDisabled, TimerOverlay). Every callback is a
// rowed static of the 0x004126xx-0x00412Cxx block except 0x004129DF, newly
// pinned with its sibling renderers' signature. Original name unknown
// (WorldBuilder twin 0x01099C50 is unnamed); the ZH-shaped
// WOLBuddyOverlayRCMenuInit lead was refuted by the literals.
//
// Codegen note: the three callback-holder constructors (rows 0x0023E8D8,
// 0x004106FA and 0x00380AB1) are visible inline-never-inlined with their row
// bodies, the lever of the 0x00512069 registration: retail's compiler knew
// they only read the function pointer, so one pointer temporary and one
// argument-save slot serve all thirteen registrations.
#include "ascii_string.h"

struct TargetRef00217D4C {void *vtable;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);

void *__cdecl operator new(unsigned int);
class Rva0023E8D8Impl { public: virtual ~Rva0023E8D8Impl(); int m_ref; void *m_func; Rva0023E8D8Impl(void *p) : m_ref(0) { m_func = *(void **)p; } };
class Rva0023E8D8 { Rva0023E8D8Impl *m_ptr; public: __declspec(noinline) Rva0023E8D8(void *p) { Rva0023E8D8Impl *q = new Rva0023E8D8Impl(p); m_ptr = q; if (q) ++q->m_ref; } };
struct Rva00080221RefImpl { virtual ~Rva00080221RefImpl() {} int m_ref; Rva00080221RefImpl() : m_ref(0) {} };
struct Impl004106FA : Rva00080221RefImpl { int m_value; Impl004106FA(const int &value) : m_value(value) {} };
class Rva004106FA { public: __declspec(noinline) Rva004106FA(const int *arg) { Impl004106FA *p = new Impl004106FA(*arg); m_impl = p; if (p != 0) ++p->m_ref; } private: Impl004106FA *m_impl; };
class Rva00380AB1Impl { public: virtual ~Rva00380AB1Impl(); int m_ref; void *m_func; Rva00380AB1Impl(void *p) : m_ref(0) { m_func = *(void **)p; } };
class Rva00380AB1 { Rva00380AB1Impl *m_ptr; public: __declspec(noinline) Rva00380AB1(void *p) { Rva00380AB1Impl *q = new Rva00380AB1Impl(p); m_ptr = q; if (q) ++q->m_ref; } };

class AptCommandMap;class AptExternHandler;class AptCustomRender;
template<class T>class AptRef;
template<>class AptRef<AptCommandMap> {
 TargetRef00217D4C *ptr;
public:
 AptRef(void *&function) {
  ((Rva0023E8D8*)this)->Rva0023E8D8::Rva0023E8D8(&function);
 }
 AptRef(const AptRef&r):ptr(r.ptr){if(ptr)++ptr->references;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
template<>class AptRef<AptExternHandler> {
 TargetRef00217D4C *ptr;
public:
 AptRef(void *&function) {
  ((Rva004106FA*)this)->Rva004106FA::Rva004106FA((const int*)&function);
 }
 AptRef(const AptRef&r):ptr(r.ptr){if(ptr)++ptr->references;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
template<>class AptRef<AptCustomRender> {
 TargetRef00217D4C *ptr;
public:
 AptRef(void *&function) {
  ((Rva00380AB1*)this)->Rva00380AB1::Rva00380AB1(&function);
 }
 AptRef(const AptRef&r):ptr(r.ptr){if(ptr)++ptr->references;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
class AptPlayer {
public:
 void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);
 void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>);
 void AddCustomRender(const AsciiString&,AptRef<AptCustomRender>);
};
extern AptPlayer *TheAptPlayer;

class Coord2D;
void bfmeGoDYF(const char *);
void CloseWindow(const char *);
void PlaySound(const char *);
void OnClickThroughPress(const char *);
void OnClickThroughRelease(const char *);
void Rva0046ED80(const char *);
void Rva0041273C(int, char *, bool);
void InGame(int, char *, bool);
void DoTrace(int, char *, bool);
void Rva00412B94(const Coord2D *, const Coord2D *, const char *, const char *);
void Rva004129DF(const Coord2D *, const Coord2D *, const char *, const char *);
void Rva00412BFF(const Coord2D *, const Coord2D *, const char *, const char *);

#define BIND_COMMAND(label, callback) \
	if (TheAptPlayer) { \
		AsciiString name(label); \
		void *function = (void *)&callback; \
		TheAptPlayer->AddCommandMap(name, AptRef<AptCommandMap>(function)); \
	}
#define BIND_QUERY(label, callback, index) \
	{ \
		AsciiString name(label); \
		void *function = (void *)&callback; \
		TheAptPlayer->AddExternHandler(name, index, AptRef<AptExternHandler>(function)); \
	}
#define BIND_RENDER(label, callback) \
	{ \
		AsciiString name(label); \
		void *function = (void *)&callback; \
		TheAptPlayer->AddCustomRender(name, AptRef<AptCustomRender>(function)); \
	}

void __cdecl Rva00412F14Register()
{
	BIND_COMMAND("MouseSetVisibility", bfmeGoDYF)
	BIND_COMMAND("CloseWindow", CloseWindow)
	BIND_COMMAND("PlaySound", PlaySound)
	BIND_COMMAND("OnClickThroughPress", OnClickThroughPress)
	BIND_COMMAND("OnClickThroughRelease", OnClickThroughRelease)
	BIND_COMMAND("SetBackground", Rva0046ED80)
	BIND_QUERY("InBetaDemo", Rva0041273C, 1)
	BIND_QUERY("InDreamMachineDemo", Rva0041273C, 2)
	BIND_QUERY("InGame", InGame, 0)
	BIND_QUERY("DoTrace", DoTrace, 0)
	BIND_RENDER("RenderImage", Rva00412B94)
	BIND_RENDER("RenderImageDisabled", Rva004129DF)
	BIND_RENDER("TimerOverlay", Rva00412BFF)
}
