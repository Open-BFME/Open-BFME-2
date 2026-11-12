// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00511F73Run@@YAXXZ @0x00511F73 141B evidence: calls Save 0x00511730 StringBase ctor releaseBuffer RemoveCommandMap RemoveExternHandler Get 0x00381452 erase 0x002B7250; strings AptMessenger OnMessengerBttn IsOpen; global TheRva00222A8BTarget; g_00E048C4
// Free function saving gadget then AptMessenger lookups via AsciiString locals then erase via Get.
#include "ascii_string.h"
#include <new>
void __cdecl Rva00511730(int unused);
#include "../../Include/Common/Rva00224455.h"
#include "../../Include/GameClient/Rva002244CA.h"
class Rva00222A8BTarget;
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
int __cdecl Rva00381452Get();
#include "../../Include/GameLogic/CreateAHeroData.h"
// 0x00A048C4: one retail global, defined (as g_Va00E048C4) by Rva007B6880Thunks.cpp,
// whose dtor thunk and Rva007ABBB3CtorInits.cpp's initializer address the same object.
extern unsigned int g_Va00E048C4;
void __cdecl Rva00511F73Run()
{
	Rva00511730(0);
	{
		AsciiString s1("AptMessenger::OnMessengerBttn");
		((Rva00224455 *)g_bfmeAptWindowManager)->RemoveCommandMap(&s1);
	}
	{
		AsciiString s2("AptMessenger::IsOpen");
		((Rva002244CA *)g_bfmeAptWindowManager)->RemoveExternHandler(&s2);
	}
	((Rva002B7250 *)Rva00381452Get())->rva002B7250((CreateAHeroData *)&g_Va00E048C4);
}

// Registration counterpart to Rva00511F73Run: retail 0x00512069..0x0051211C.
// Reuse the existing observer storage and player global names. Native 179B
// registers the two independently named static messenger callbacks.
struct Rva002BA8F1Listener;
#include "../../Include/Common/Rva005A0B4CList.h"
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
// The two callback-holder constructors (rows 0x0023E8D8 in Rva0023E8D8Ctor.cpp
// and 0x004106FA in Rva00080221Ctor.cpp) are visible here as inline,
// never-inlined definitions with their row bodies. Retail's compiler knew they
// only read the function pointer, so the pointer temporary and the argument
// save slot are shared by both registrations (frame 0x10); declared out of
// line, cl keeps them apart (frame 0x14).
#include "../../Include/Common/Rva00080221RefImpl.h"
class Rva0023E8D8Impl : public Rva00080221RefImpl { public: void *m_func; Rva0023E8D8Impl(void *p) { m_func = *(void **)p; } };
class Rva0023E8D8 { Rva0023E8D8Impl *m_ptr; public: __declspec(noinline) Rva0023E8D8(void *p) { Rva0023E8D8Impl *q = new Rva0023E8D8Impl(p); m_ptr = q; if (q) ++q->m_ref; } };
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
 AptRef(const AptRef&aptRef):ptr(aptRef.ptr){if(ptr)++ptr->references;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
template<>class AptRef<AptExternHandler> {
 TargetRef00217D4C *ptr;
public:
 AptRef(void *&function) {
  ((Rva004106FA*)this)->Rva004106FA::Rva004106FA((const int*)&function);
 }
 AptRef(const AptRef&aptRef):ptr(aptRef.ptr){if(ptr)++ptr->references;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
#include "../../../Libraries/Source/Apt/AptPlayerClass.h"
class AptMessenger {
public:static void OnMessengerBttn(const char*);static void IsOpen(int,char*,bool);
};
void __cdecl Rva00512069Register()
{
 ((Rva005A0B4CList*)Rva00381452Get())->append((Rva002BA8F1Listener*)&g_Va00E048C4);
 {
  AsciiString name("AptMessenger::OnMessengerBttn");
  void *function=(void*)&AptMessenger::OnMessengerBttn;
  ((AptPlayer *)g_bfmeAptWindowManager)->AddCommandMap(name,AptRef<AptCommandMap>(function));
 }
 {
  AsciiString name("AptMessenger::IsOpen");
  void *function=(void*)&AptMessenger::IsOpen;
  ((AptPlayer *)g_bfmeAptWindowManager)->AddExternHandler(name,0,AptRef<AptExternHandler>(function));
 }
}
