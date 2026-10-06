// ?rva00437053@AptSaveLoad@@QAEXXZ
// partial score=0.72 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Target 0x00437053 is a virtual AptSaveLoad screen update: it dispatches
// states +0x27C, disables the three save/load gadgets while confirmation
// dialogs are pending, and calls the neighboring AptSaveLoad handlers.
// In its saving prompts it builds a FunctorBinding with ECX=this and an
// address-derived thiscall(int) callback at 0x00434337. The callback's
// behavior and owner name remain unresolved.
#include "unicode_string.h"

class GameWindow
{
public:
	int winEnable(bool enable);
};

GameWindow *Rva00222547Get(GameWindow *window);

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *function, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

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
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class AptSaveLoad
{
public:
	void rva00434432();
	void rva00436FF6();
	void rva00435819();
	void rva00437053();

private:
	unsigned char m_pad000[0x27C];
	int m_state;
	unsigned char m_pad280[8];
	GameWindow *m_gameList;
	GameWindow *m_autoSaveList;
	GameWindow *m_fileName;
};

class Rva00434337BaseA
{
};

class Rva00434337BaseB
{
};

class __multiple_inheritance Rva00434337 : public Rva00434337BaseA,
	public Rva00434337BaseB
{
public:
	void rva00434337(int button);
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
typedef void (Rva00434337::*FunctorMethod)(int);

struct FunctorBinding
{
	Rva00434337 *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder() : m_ptr(0) {}
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	void *m_ptr;
};

extern "C" void __cdecl Rva00437FB3(int type,
	const UnicodeString &message, const UnicodeString &title,
	void *emptyCallback, void *saveCallback);
void __cdecl Rva00434EFA();

void AptSaveLoad::rva00437053()
{
	FunctorBinding binding;
	FunctorBinding holderBinding;

	if (m_state == 1)
	{
		rva00434432();
	resetState:
		m_state = 0;
		return;
	}
	if (m_state == 2)
	{
		rva00436FF6();
		goto resetState;
	}

	if (m_state == 14 || m_state == 15 || m_state == 16 || m_state == 17)
	{
		if (m_fileName)
			m_fileName->winEnable(0);
		if (m_gameList)
			m_gameList->winEnable(0);
		if (m_autoSaveList)
			m_autoSaveList->winEnable(0);

		if (m_state == 14)
		{
			TheRva00222A8BTarget->invoke(
				Rva00222547Get((GameWindow *)this),
				"showMessageBox", 1, "Load", 0, 0, 0, 0);
			m_state = 18;
		}
		else if (m_state == 15)
		{
			TheRva00222A8BTarget->invoke(
				Rva00222547Get((GameWindow *)this),
				"showMessageBox", 1, "Save", 0, 0, 0, 0);
			m_state = 19;
		}
		else if (m_state == 16)
		{
			TheRva00222A8BTarget->invoke(
				Rva00222547Get((GameWindow *)this),
				"showMessageBox", 1, "Delete", 0, 0, 0, 0);
			m_state = 20;
		}
		else if (m_state == 17)
		{
			TheRva00222A8BTarget->invoke(
				Rva00222547Get((GameWindow *)this),
				"showMessageBox", 1, "ReplayVersionMismatch", 0, 0, 0, 0);
			m_state = 21;
		}
		return;
	}

	if (m_state == 3)
	{
		TheRva00222A8BTarget->invoke(
			Rva00222547Get((GameWindow *)this),
			"closeDelayed", 1, "OnClosed", 0, 0, 0, 0);
		m_state = 6;
		return;
	}

	if (m_state == 4)
	{
		binding.m_method = &Rva00434337::rva00434337;
		binding.m_target = (Rva00434337 *)this;
		holderBinding = binding;
		Rva0057BC63FunctorHolder saveCallback(holderBinding);
		Rva0057BC63FunctorHolder emptyCallback;
		Rva00437FB3(4,
			TheGameText->fetch("APT:SaveGameProgress", 0),
			TheGameText->fetch("APT:SavingWait", 0),
			emptyCallback.m_ptr, saveCallback.m_ptr);
		m_state = 8;
		return;
	}

	if (m_state == 7)
	{
		rva00435819();
		return;
	}

	if (m_state == 5)
	{
		binding.m_method = &Rva00434337::rva00434337;
		binding.m_target = (Rva00434337 *)this;
		holderBinding = binding;
		Rva0057BC63FunctorHolder saveCallback(holderBinding);
		Rva0057BC63FunctorHolder emptyCallback;
		Rva00437FB3(4,
			TheGameText->fetch("APT:SaveGameProgress", 0),
			TheGameText->fetch("APT:SavingWaitOnMultiplayer", 0),
			emptyCallback.m_ptr, saveCallback.m_ptr);
		m_state = 11;
		return;
	}

	if (m_state == 13)
		Rva00434EFA();
}
