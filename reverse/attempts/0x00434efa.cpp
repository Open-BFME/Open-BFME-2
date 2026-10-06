// ?Rva00434EFA@@YAXXZ
// partial score=0.8 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
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
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	void *m_ptr;
};

class Rva0023E8D8
{
public:
	Rva0023E8D8(void *callback);
	void *m_ptr;
};

struct AptSaveLoadPromptScreen
{
	unsigned char m_pad000[0x27C];
	int m_state;
};

extern int g_Va00E032E0;

bool Rva00437EDCGet();
extern "C" void __cdecl Rva00437F61(int type,
	const UnicodeString &message, const UnicodeString &title,
	Rva0023E8D8 callback);
extern "C" void __cdecl Rva00437FB3(int type,
	const UnicodeString &message, const UnicodeString &title,
	Rva0057BC63FunctorHolder secondCallback,
	Rva0057BC63FunctorHolder firstCallback);
extern "C" bool __cdecl Rva00438083(int type,
	const UnicodeString &message, const UnicodeString &title,
	Rva0057BC63FunctorHolder secondCallback,
	Rva0057BC63FunctorHolder firstCallback);

void __cdecl Rva00434EFA()
{
	FunctorBinding binding;
	FunctorBinding holderBinding;
	if (g_Va00E032E0)
	{
		bool showConfirmation = Rva00437EDCGet();
		binding.m_target = (void *)g_Va00E032E0;
		binding.m_function = 0x00834337;
		binding.m_adjustment = 0;
		holderBinding = binding;
		if (showConfirmation)
		{
			Rva0057BC63FunctorHolder firstCallback(holderBinding);
			binding.m_target = (void *)g_Va00E032E0;
			binding.m_function = 0x00833D71;
			binding.m_adjustment = 0;
			holderBinding = binding;
			Rva0057BC63FunctorHolder secondCallback(holderBinding);
			UnicodeString title = TheGameText->fetch(
				"APT:MultiplayerGameSaved", 0);
			UnicodeString message = TheGameText->fetch(
				"APT:SaveGameProgress", 0);
			Rva00438083(2, message, title, secondCallback, firstCallback);
		}
		else
		{
			Rva0057BC63FunctorHolder firstCallback(holderBinding);
			binding.m_target = (void *)g_Va00E032E0;
			binding.m_function = 0x00833D71;
			binding.m_adjustment = 0;
			holderBinding = binding;
			Rva0057BC63FunctorHolder secondCallback(holderBinding);
			UnicodeString title = TheGameText->fetch(
				"APT:MultiplayerGameSaved", 0);
			UnicodeString message = TheGameText->fetch(
				"APT:SaveGameProgress", 0);
			Rva00437FB3(2, message, title, secondCallback, firstCallback);
			((AptSaveLoadPromptScreen *)g_Va00E032E0)->m_state = 9;
		}
		return;
	}

	void *callback = (void *)0x00833D4D;
	Rva0023E8D8 holder(&callback);
	UnicodeString title = TheGameText->fetch("APT:MultiplayerGameSaved", 0);
	UnicodeString message = TheGameText->fetch("APT:SaveGameProgress", 0);
	Rva00437F61(2,
		message, title, holder);
}
