// ?Rva00434EFA@@YAXXZ
// partial score=0.97 date=2026-10-10
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
class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount(0) {}
	virtual void anchor();
	int m_refCount;
};
class Rva0057BC63FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva0057BC63FunctorWrapper(const FunctorBinding &binding) : m_binding(binding) {}
	void invoke();
	FunctorBinding m_binding;
};
void *__cdecl operator new(unsigned int size);
class Rva0057BC63FunctorHolder
{
public:
	__declspec(noinline) Rva0057BC63FunctorHolder(const FunctorBinding &binding)
	{
		m_ptr = new Rva0057BC63FunctorWrapper(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}
	FunctorWrapperHead *m_ptr;
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
struct AptSaveLoadScreen : public AptSaveLoad, public Rva00434337
{
	unsigned char m_pad000[0x27C];
	int m_state;
};
__forceinline FunctorBinding MakeBinding(FunctorTarget *target, FunctorMethod method)
{
	FunctorBinding binding;
	binding.m_target = target;
	binding.m_method = method;
	return binding;
}
typedef void (__cdecl *SaveCallback)(int);
template <class T> __forceinline const T *addressOf(const T &value) { return &value; }
void __cdecl Rva00434EFA()
{
	if (g_Va00E032E0)
	{
		if (Rva00437EDCGet())
			Rva00438083(2, TheGameText->fetch("APT:SaveGameProgress", 0), TheGameText->fetch("APT:MultiplayerGameSaved", 0),
				ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(g_Va00E032E0), reinterpret_cast<FunctorMethod>(&AptSaveLoad::rva00433D71))),
				ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(g_Va00E032E0), reinterpret_cast<FunctorMethod>(&Rva00434337::rva00434337))));
		else
			Rva00437FB3(2, TheGameText->fetch("APT:SaveGameProgress", 0), TheGameText->fetch("APT:MultiplayerGameSaved", 0),
				ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(g_Va00E032E0), reinterpret_cast<FunctorMethod>(&AptSaveLoad::rva00433D71))),
				ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(g_Va00E032E0), reinterpret_cast<FunctorMethod>(&Rva00434337::rva00434337))));
		((AptSaveLoadPromptScreen *)g_Va00E032E0)->m_state = 9;
	}
	else
	{
		Rva00437F61(2, TheGameText->fetch("APT:SaveGameProgress", 0), TheGameText->fetch("APT:MultiplayerGameSaved", 0), CallbackStorage((void *)addressOf(SaveCallback(Rva00433D4D))));
	}
}
