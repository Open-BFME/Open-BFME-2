// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#pragma pointers_to_members(full_generality, multiple_inheritance)
#include <stdlib.h>
#include "../../../Include/GameClient/Bfme2GameWindow.h"
// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// AptScoreScreenCallbacks.cpp).
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);
#include "../../../Include/GameClient/FunctorBinding.h"
class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};
class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);
template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};
class AptCommandMap;
class AptExternHandler;
#include "../../../../Libraries/Source/Apt/AptCommandMapAdder.h"
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);
#include "../../../Include/GameClient/Rva005248D0.h"
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();

private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};
void _bfme_closeAptScreen(const AsciiString &name);
// The open in-game chat screen (VA 0x00E04478).
extern int g_Va00E04478;
class AptInGameChat : public _bfme_AptGameWindow
{
public:
	virtual ~AptInGameChat();
};

// ??1AptInGameChat@@UAE@XZ @0x004E83EB 116B (WB AptInGameChat.cpp line 224 names the class and its InitGadgets screen key)
// Evidence: unlock lane, AptInGameChat::InitGadgets literal, base pin 0x005126F5, current-window global g_Va00E04478, caller 0x004E84E6.
AptInGameChat::~AptInGameChat()
{
	if (g_Va00E04478 == (int)this)
	{
		_bfme_closeAptScreen(AsciiString("AptInGameChat::InitGadgets"));
		g_Va00E04478 = 0;
	}
}
