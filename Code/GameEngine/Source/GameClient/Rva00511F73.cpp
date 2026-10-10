// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00511F73Run@@YAXXZ @0x00511F73 141B evidence: calls Save 0x00511730 StringBase ctor releaseBuffer rva00224455 rva002244CA Get 0x00381452 erase 0x002B7250; strings AptMessenger OnMessengerBttn IsOpen; global TheRva00222A8BTarget; g_00E048C4
// Free function saving gadget then AptMessenger lookups via AsciiString locals then erase via Get.
#include "ascii_string.h"
void __cdecl Rva00511730(int unused);
class Rva00224455
{
public:
	int rva00224455(const AsciiString *key);
};
class Rva002244CA
{
public:
	int rva002244CA(const AsciiString *key);
};
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
int __cdecl Rva00381452Get();
class CreateAHeroData { char m_pad[0x140]; };
// 0x00A048C4: one retail global, defined (as g_Va00E048C4) by Rva007B6880Thunks.cpp,
// whose dtor thunk and Rva007ABBB3CtorInits.cpp's initializer address the same object.
extern unsigned int g_Va00E048C4;
void __cdecl Rva00511F73Run()
{
	Rva00511730(0);
	{
		AsciiString s1("AptMessenger::OnMessengerBttn");
		((Rva00224455 *)TheRva00222A8BTarget)->rva00224455(&s1);
	}
	{
		AsciiString s2("AptMessenger::IsOpen");
		((Rva002244CA *)TheRva00222A8BTarget)->rva002244CA(&s2);
	}
	((Rva002B7250 *)Rva00381452Get())->rva002B7250((CreateAHeroData *)&g_Va00E048C4);
}

// Registration counterpart to Rva00511F73Run: retail 0x00512069..0x0051211C.
// Reuse the existing observer storage and player global names. Native 179B
// registers the two independently named static messenger callbacks.
struct Rva002BA8F1Listener;
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener*);};
struct TargetRef00217D4C {void *vtable;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
// The two callback-holder constructors (rows 0x0023E8D8 in Rva0023E8D8Ctor.cpp
// and 0x004106FA in Rva00080221Ctor.cpp) are visible here as inline,
// never-inlined definitions with their row bodies. Retail's compiler knew they
// only read the function pointer, so the pointer temporary and the argument
// save slot are shared by both registrations (frame 0x10); declared out of
// line, cl keeps them apart (frame 0x14).
void *__cdecl operator new(unsigned int);
class Rva0023E8D8Impl { public: virtual ~Rva0023E8D8Impl(); int m_ref; void *m_func; Rva0023E8D8Impl(void *p) : m_ref(0) { m_func = *(void **)p; } };
class Rva0023E8D8 { Rva0023E8D8Impl *m_ptr; public: __declspec(noinline) Rva0023E8D8(void *p) { Rva0023E8D8Impl *q = new Rva0023E8D8Impl(p); m_ptr = q; if (q) ++q->m_ref; } };
struct Rva00080221RefImpl { virtual ~Rva00080221RefImpl() {} int m_ref; Rva00080221RefImpl() : m_ref(0) {} };
struct Impl004106FA : Rva00080221RefImpl { int m_value; Impl004106FA(const int &value) : m_value(value) {} };
class Rva004106FA { public: __declspec(noinline) Rva004106FA(const int *arg) { Impl004106FA *p = new Impl004106FA(*arg); m_impl = p; if (p != 0) ++p->m_ref; } private: Impl004106FA *m_impl; };
class AptCommandMap;class AptExternHandler;
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
class AptPlayer {
public:
 void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);
 void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>);
};
class AptMessenger {
public:static void OnMessengerBttn(const char*);static void IsOpen(int,char*,bool);
};
void __cdecl Rva00512069Register()
{
 ((Rva005A0B4CList*)Rva00381452Get())->append((Rva002BA8F1Listener*)&g_Va00E048C4);
 {
  AsciiString name("AptMessenger::OnMessengerBttn");
  void *function=(void*)&AptMessenger::OnMessengerBttn;
  ((AptPlayer*)TheRva00222A8BTarget)->AddCommandMap(name,AptRef<AptCommandMap>(function));
 }
 {
  AsciiString name("AptMessenger::IsOpen");
  void *function=(void*)&AptMessenger::IsOpen;
  ((AptPlayer*)TheRva00222A8BTarget)->AddExternHandler(name,0,AptRef<AptExternHandler>(function));
 }
}
