// ?Rva00434EFA@@YAXXZ
// partial score=0.9 date=2026-10-09
// ?Rva00434EFA@@YAXXZ
// Bank refreshed 2026-10-09: real member-pointer relocations, complete owning callbacks.
// Target 434EFA..435107=525B; this emits523B/frame3C vs native38.
// Retail retains original/copy binding buffers at -34/-44; current -38/-48.
// All callback/string lifetimes and common state27C=9 are represented.
// Original function name and first callback owner remain unknown.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHs /vmg /vmm
// Retail 0x00434EFA binds the saved-game prompt's button handling. Its
// caller at 0x00435160 reaches it when the save prompt is not already open.
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const class AsciiString &label,
		bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// Target callback slots are address evidence. The holder records are four
// dwords; the final two are an address and this-adjustment word.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
class AptSaveLoad {public:void rva00433D71(int);};
class Rva00434337 {public:void rva00434337(int);};
struct FunctorBinding { FunctorBinding(){}
 template<class T> FunctorBinding(T*t,void(T::*f)(int)):m_target(reinterpret_cast<FunctorTarget*>(t)),m_method(reinterpret_cast<FunctorMethod>(f)){}
 FunctorTarget*m_target;unsigned int m_pad;FunctorMethod m_method;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	void *m_ptr;
};

class Rva0023E8D8
{
public:
	Rva0023E8D8(void *callback);
 Rva0023E8D8(const Rva0023E8D8&r):m_ptr(r.m_ptr){if(m_ptr)++((int*)m_ptr)[1];}
 ~Rva0023E8D8(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}
	void *m_ptr;
};

struct CallbackStorage {
 Rva0023E8D8 holder;
 CallbackStorage(void*p):holder(p){}
 CallbackStorage(const CallbackStorage&r):holder(r.holder){}
};
struct ScopedFunctor {
 Rva0057BC63FunctorHolder holder;
 ScopedFunctor(const FunctorBinding& binding):holder(binding){}
 ScopedFunctor(const ScopedFunctor&r):holder(r.holder){if(holder.m_ptr)++((int*)holder.m_ptr)[1];}
 ~ScopedFunctor(){if(holder.m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)holder.m_ptr);}
};

template<class T> __forceinline const FunctorBinding& bindAgain(FunctorBinding& original,FunctorBinding& copy,T*t,void(T::*m)(int)){original.m_target=reinterpret_cast<FunctorTarget*>(t);original.m_method=reinterpret_cast<FunctorMethod>(m);copy=original;return copy;}
struct AptSaveLoadPromptScreen
{
	unsigned char m_pad000[0x27C];
	int m_state;
};

extern int g_Va00E032E0;

bool Rva00437EDCGet();
extern "C" void __cdecl Rva00437F61(int type,
	const UnicodeString &message, const UnicodeString &title,
	CallbackStorage callback);
extern "C" void __cdecl Rva00437FB3(int type,
	const UnicodeString &message, const UnicodeString &title,
	ScopedFunctor secondCallback,
	ScopedFunctor firstCallback);
extern "C" bool __cdecl Rva00438083(int type,
	const UnicodeString &message, const UnicodeString &title,
	ScopedFunctor secondCallback,
	ScopedFunctor firstCallback);

void Rva00433D4D(int);
void __cdecl Rva00434EFA() {
 FunctorBinding binding; FunctorBinding holderBinding;
 if(g_Va00E032E0) {
  bool confirm=Rva00437EDCGet();
  binding.m_target=reinterpret_cast<FunctorTarget*>(g_Va00E032E0);
  binding.m_method=reinterpret_cast<FunctorMethod>(&Rva00434337::rva00434337);
  holderBinding=binding;
  if(confirm) {
   Rva00438083(2,TheGameText->fetch("APT:SaveGameProgress",0),TheGameText->fetch("APT:MultiplayerGameSaved",0),
    ScopedFunctor(bindAgain(binding,holderBinding,(AptSaveLoad*)g_Va00E032E0,&AptSaveLoad::rva00433D71)), ScopedFunctor(holderBinding));
  }else {
   Rva00437FB3(2,TheGameText->fetch("APT:SaveGameProgress",0),TheGameText->fetch("APT:MultiplayerGameSaved",0),
    ScopedFunctor(bindAgain(binding,holderBinding,(AptSaveLoad*)g_Va00E032E0,&AptSaveLoad::rva00433D71)), ScopedFunctor(holderBinding));
  }
  ((AptSaveLoadPromptScreen*)g_Va00E032E0)->m_state=9;
 }else {
  void (__cdecl *callback)(int)=Rva00433D4D;
  Rva00437F61(2,TheGameText->fetch("APT:SaveGameProgress",0),TheGameText->fetch("APT:MultiplayerGameSaved",0),CallbackStorage(&callback));
 }
}
