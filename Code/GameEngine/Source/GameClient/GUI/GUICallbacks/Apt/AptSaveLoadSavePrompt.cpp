// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /vmg /vmm
// ?Rva00434EFA@@YAXXZ @0x00434EFA 525B
//
// Saved-game prompt binding. Retail 0x00434EFA..0x00435107; its caller at
// 0x00435160 reaches it when the save prompt is not already open. With the
// save/load screen (AptSaveLoad::s_instance) up it opens the two-button message box
// (0x00438083 when 0x00437EDC says so, else 0x00437FB3) with the member
// callbacks AptSaveLoad 0x00433D71 and 0x00434337 bound through the functor
// holder 0x0057BC63 and sets the screen state +0x27C to 9; otherwise it opens
// the one-button box 0x00437F61 with the static callback 0x00433D4D wrapped by
// the refcounted holder 0x0023E8D8. Strings APT:SaveGameProgress and
// APT:MultiplayerGameSaved come from TheGameText fetch (vtable +0x3C).
//
// Frame note: retail homes the static callback pointer temporary in the
// [ebp-0x14] slot of the if-arm fetch temporary (frame 0x38). cl shares that
// slot only when it can see that the 0x0023E8D8 holder constructor keeps no
// pointer to the temporary (it reads the function pointer through it), so that
// constructor is written below in-class and never inlined with its real body;
// its emitted COMDAT is retail 0x0023E8D8 exactly (row in Rva0023E8D8Ctor.cpp),
// as is the visible functor holder COMDAT (retail 0x0057BC63).
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
class AptSaveLoad {public:
	static AptSaveLoad *s_instance;void rva00433D71(int);void rva00435224();int rva00437053();void rva00434432();void rva00436FF6();void rva00435819();};
class Rva00434337 {public:void rva00434337(int);};
struct FunctorBinding { FunctorBinding(){}
 template<class T> FunctorBinding(T*target,void(T::*f)(int)):m_target(reinterpret_cast<FunctorTarget*>(target)),m_method(reinterpret_cast<FunctorMethod>(f)){}
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
#include <new>
class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder() : m_ptr(0) {}
	Rva0057BC63FunctorHolder(const FunctorBinding &binding)
	{
		m_ptr = new Rva0057BC63FunctorWrapper(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}
	FunctorWrapperHead *m_ptr;
};

struct Rva00080221RefImpl { virtual ~Rva00080221RefImpl() {} int m_ref; Rva00080221RefImpl() : m_ref(0) {} };
class Rva0023E8D8Impl : public Rva00080221RefImpl
{
public:
	void *m_func;
	Rva0023E8D8Impl(void *functionPointerAddress) { m_func = *(void **)functionPointerAddress; }
};
class Rva0023E8D8
{
public:
	__declspec(noinline) Rva0023E8D8(void *p)
	{
		Rva0023E8D8Impl *q = new Rva0023E8D8Impl(p);
		m_ptr = q;
		if (q)
			++q->m_ref;
	}
 Rva0023E8D8(const Rva0023E8D8&r):m_ptr(r.m_ptr){if(m_ptr)++((int*)m_ptr)[1];}
 ~Rva0023E8D8(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}
	void *m_ptr;
};

struct CallbackStorage {
 Rva0023E8D8 holder;
 CallbackStorage(void*p):holder(p){}
 CallbackStorage(const CallbackStorage&callbackStorage):holder(callbackStorage.holder){}
};
struct ScopedFunctor {
 Rva0057BC63FunctorHolder holder;
 ScopedFunctor(){}
 ScopedFunctor(const FunctorBinding& binding):holder(binding){}
 ScopedFunctor(const ScopedFunctor&scopedFunctor):holder(scopedFunctor.holder){if(holder.m_ptr)++((int*)holder.m_ptr)[1];}
 ~ScopedFunctor(){if(holder.m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)holder.m_ptr);}
};

template<class T> __forceinline const FunctorBinding& bindAgain(FunctorBinding& original,FunctorBinding& copy,T*target,void(T::*m)(int)){original.m_target=reinterpret_cast<FunctorTarget*>(target);original.m_method=reinterpret_cast<FunctorMethod>(m);copy=original;return copy;}
struct AptSaveLoadPromptScreen
{
	unsigned char m_pad000[0x27C];
	int m_state;
};


bool Rva00437EDCGet();
extern "C" void __cdecl Rva00437F61(int type,
	const UnicodeString &message, const UnicodeString &title,
	CallbackStorage callback);
struct TreeHintRef00217D4C;
class AptMessageBox { public: static void Show(int, const UnicodeString &, const UnicodeString &, TreeHintRef00217D4C, TreeHintRef00217D4C); };
// Preserve the native one-word callback copies and their existing cleanup sequence.
typedef void (__cdecl *PromptShowCall)(int, const UnicodeString &, const UnicodeString &, ScopedFunctor, ScopedFunctor);
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
	if (AptSaveLoad::s_instance)
	{
		if (Rva00437EDCGet())
			Rva00438083(2, TheGameText->fetch("APT:SaveGameProgress", 0), TheGameText->fetch("APT:MultiplayerGameSaved", 0),
				ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(AptSaveLoad::s_instance), reinterpret_cast<FunctorMethod>(&AptSaveLoad::rva00433D71))),
				ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(AptSaveLoad::s_instance), reinterpret_cast<FunctorMethod>(&Rva00434337::rva00434337))));
		else
			(reinterpret_cast<PromptShowCall>(&AptMessageBox::Show))(2, TheGameText->fetch("APT:SaveGameProgress", 0), TheGameText->fetch("APT:MultiplayerGameSaved", 0),
				ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(AptSaveLoad::s_instance), reinterpret_cast<FunctorMethod>(&AptSaveLoad::rva00433D71))),
				ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(AptSaveLoad::s_instance), reinterpret_cast<FunctorMethod>(&Rva00434337::rva00434337))));
		((AptSaveLoadPromptScreen *)AptSaveLoad::s_instance)->m_state = 9;
	}
	else
	{
		Rva00437F61(2, TheGameText->fetch("APT:SaveGameProgress", 0), TheGameText->fetch("APT:MultiplayerGameSaved", 0), CallbackStorage((void *)addressOf(SaveCallback(Rva00433D4D))));
	}
}

// Retail 0x00435224 (299 B), called by AptSaveLoad::Load and ConfirmationOk:
// warns when the save directory lacks space (two-button message box, the member
// callback 0x00434337 bound through the functor holder), else picks the next
// screen state from the number of human slots of the multiplayer game.
class Rva002DC267 { public: bool rva002DC681() const; };
class GameState;
extern GameState *TheGameState;
class GameSlot { public: bool isHuman() const; };
class GameInfo { public: GameSlot *getSlot(int slotNum); };
extern GameInfo *TheGameInfo;
struct AptSaveLoadModeView
{
	unsigned char m_pad000[0x2A0];
	int m_mode;
};
void AptSaveLoad::rva00435224()
{
	if (TheGameState != 0 && !((const Rva002DC267 *)TheGameState)->rva002DC681())
	{
		(reinterpret_cast<PromptShowCall>(&AptMessageBox::Show))(0, TheGameText->fetch("GUI:Error", 0), TheGameText->fetch("APT:SaveFileDiskFull", 0),
			ScopedFunctor(),
			ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(this), reinterpret_cast<FunctorMethod>(&Rva00434337::rva00434337))));
		((AptSaveLoadPromptScreen *)this)->m_state = 0x17;
		return;
	}

	if (((AptSaveLoadModeView *)this)->m_mode == 0x10 && TheGameInfo != 0)
	{
		int humanCount = 0;
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *slot = TheGameInfo->getSlot(i);
			if (slot != 0 && slot->isHuman())
				++humanCount;
		}
		if (humanCount > 1)
		{
			((AptSaveLoadPromptScreen *)this)->m_state = 5;
			return;
		}
	}
	((AptSaveLoadPromptScreen *)this)->m_state = 4;
}

// Retail 0x00437053 (813 B), the save/load screen's per-frame state step: states
// 1 and 2 run their handlers and reset, 14..17 disable the three lists and show
// the Load/Save/Delete/ReplayVersionMismatch box, 3 closes, 4 and 5 open the
// "saving" prompt with the confirmation callback 0x00434337, 7 and 13 run theirs.
class GameWindow { public: int winEnable(bool enable); };
class Rva00222A8BTarget { public: int invoke(void *owner, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4); };
// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class AptPlayer { public: static int GetLevelIndex(GameWindow *window); };
struct AptSaveLoadWindowsView
{
	unsigned char m_pad000[0x27C];
	int m_state;
	unsigned char m_pad280[0x288 - 0x280];
	GameWindow *m_gameList;
	GameWindow *m_autoSaveList;
	GameWindow *m_fileName;
};
int AptSaveLoad::rva00437053()
{
	AptSaveLoadWindowsView *aptSaveLoadWindowsView = (AptSaveLoadWindowsView *)this;
	if (aptSaveLoadWindowsView->m_state == 1)
	{
		rva00434432();
		aptSaveLoadWindowsView->m_state = 0;
	}
	else if (aptSaveLoadWindowsView->m_state == 2)
	{
		rva00436FF6();
		aptSaveLoadWindowsView->m_state = 0;
	}
	else if (aptSaveLoadWindowsView->m_state == 14 || aptSaveLoadWindowsView->m_state == 15 || aptSaveLoadWindowsView->m_state == 16 || aptSaveLoadWindowsView->m_state == 17)
	{
		if (aptSaveLoadWindowsView->m_fileName)
			aptSaveLoadWindowsView->m_fileName->winEnable(0);
		if (aptSaveLoadWindowsView->m_gameList)
			aptSaveLoadWindowsView->m_gameList->winEnable(0);
		if (aptSaveLoadWindowsView->m_autoSaveList)
			aptSaveLoadWindowsView->m_autoSaveList->winEnable(0);
		if (aptSaveLoadWindowsView->m_state == 14)
		{
			reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)), "showMessageBox", 1, "Load", 0, 0, 0, 0);
			aptSaveLoadWindowsView->m_state = 18;
		}
		else if (aptSaveLoadWindowsView->m_state == 15)
		{
			reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)), "showMessageBox", 1, "Save", 0, 0, 0, 0);
			aptSaveLoadWindowsView->m_state = 19;
		}
		else if (aptSaveLoadWindowsView->m_state == 16)
		{
			reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)), "showMessageBox", 1, "Delete", 0, 0, 0, 0);
			aptSaveLoadWindowsView->m_state = 20;
		}
		else if (aptSaveLoadWindowsView->m_state == 17)
		{
			reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)), "showMessageBox", 1, "ReplayVersionMismatch", 0, 0, 0, 0);
			aptSaveLoadWindowsView->m_state = 21;
		}
	}
	else if (aptSaveLoadWindowsView->m_state == 3)
	{
		reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)), "closeDelayed", 1, "OnClosed", 0, 0, 0, 0);
		aptSaveLoadWindowsView->m_state = 6;
	}
	else if (aptSaveLoadWindowsView->m_state == 4)
	{
		(reinterpret_cast<PromptShowCall>(&AptMessageBox::Show))(4, TheGameText->fetch("APT:SaveGameProgress", 0), TheGameText->fetch("APT:SavingWait", 0),
			ScopedFunctor(),
			ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(this), reinterpret_cast<FunctorMethod>(&Rva00434337::rva00434337))));
		aptSaveLoadWindowsView->m_state = 8;
	}
	else if (aptSaveLoadWindowsView->m_state == 7)
		rva00435819();
	else if (aptSaveLoadWindowsView->m_state == 5)
	{
		(reinterpret_cast<PromptShowCall>(&AptMessageBox::Show))(4, TheGameText->fetch("APT:SaveGameProgress", 0), TheGameText->fetch("APT:SavingWaitOnMultiplayer", 0),
			ScopedFunctor(),
			ScopedFunctor(MakeBinding(reinterpret_cast<FunctorTarget *>(this), reinterpret_cast<FunctorMethod>(&Rva00434337::rva00434337))));
		aptSaveLoadWindowsView->m_state = 11;
	}
	else if (aptSaveLoadWindowsView->m_state == 13)
		Rva00434EFA();
	return 1;
}
