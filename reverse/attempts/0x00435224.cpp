// ?rva00435224@AptSaveLoad@@QAEXXZ
// partial score=0.72 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Retail 0x00435224 is called by AptSaveLoad::Load and ConfirmationOk. It
// warns when the save directory lacks space, then chooses the next screen
// state from the multiplayer human-slot count.
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

class GameState;
extern GameState *TheGameState;

class Rva002DC267
{
public:
	bool rva002DC681() const;
};

struct FunctorBinding
{
	void *m_target;
	unsigned int m_pad;
	unsigned int m_function;
	unsigned int m_adjustment;
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder() : m_ptr(0) {}
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	void *m_ptr;
};

class GameSlot
{
public:
	bool isHuman() const;
};

class GameInfo
{
public:
	GameSlot *getSlot(int slotNum);
};

struct LANGameInfo;
extern LANGameInfo *g_Rva00E02EEC;

extern "C" void __cdecl Rva00437FB3(int type,
	const UnicodeString &message, const UnicodeString &title,
	Rva0057BC63FunctorHolder &emptyCallback,
	Rva0057BC63FunctorHolder &saveCallback);

class AptSaveLoad
{
public:
	void rva00435224();

private:
	unsigned char m_pad000[0x27C];
	int m_state;
	unsigned char m_pad280[0x2A0 - 0x280];
	int m_mode;
};

void AptSaveLoad::rva00435224()
{
	if (TheGameState != 0 &&
		!((const Rva002DC267 *)TheGameState)->rva002DC681())
	{
		FunctorBinding binding;
		FunctorBinding holderBinding;
		binding.m_adjustment = 0;
		binding.m_function = 0x00834337;
		binding.m_target = this;
		holderBinding = binding;
		Rva0057BC63FunctorHolder saveCallback(holderBinding);
		Rva0057BC63FunctorHolder emptyCallback;
		Rva00437FB3(0,
			TheGameText->fetch("GUI:Error", 0),
			TheGameText->fetch("APT:SaveFileDiskFull", 0),
			emptyCallback, saveCallback);
		m_state = 0x17;
		return;
	}

	if (m_mode == 0x10 && g_Rva00E02EEC != 0)
	{
		int humanCount = 0;
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *slot = ((GameInfo *)g_Rva00E02EEC)->getSlot(i);
			if (slot != 0 && slot->isHuman())
				++humanCount;
		}
		if (humanCount > 1)
		{
			m_state = 5;
			goto state_done;
		}
	}
	m_state = 4;
state_done:
	;
}
