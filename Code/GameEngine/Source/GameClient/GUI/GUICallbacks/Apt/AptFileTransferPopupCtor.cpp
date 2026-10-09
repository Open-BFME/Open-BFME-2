// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
//
// ??0Rva00583015Obj@@QAE@PAX@Z @0x00583359 860B: BFME2's map file transfer
// popup constructor (0x7C bytes; allocated by the rowed initializer
// 0x005836B5 and destroyed by 0x00583015 through the singleton VA 0x00E06398).
// Target evidence: pinned base ctor 0x002D2C34 (unwind state 0 runs the rowed
// ??1Rva005248D0 at 0x005248D0); vptr 0x00C6FA9C; the GameInfo argument kept
// at +0x58 (read by the rowed FileTransfer::PlayerColor 0x00583034); the
// eight player rows at +0x5C start at -1 and each human slot of the game
// (rowed getConstSlot 0x003FF2BE and isHuman 0x003FF0F1) takes the next row:
// its name goes to FileTransfer::PlayerName%d; FileTransfer:PlayerColor:%d
// is bound to PlayerColor with the slot index; the rowed ProcessProgress
// 0x00583121 clears its status. The remaining rows are blanked and bound with
// slot -1; then the three loading captions are fetched from TheGameText.
// The first instance announces FileTransferPopUpOpen (owner 13) through the
// rowed invoke 0x00222A8B. WorldBuilder's twin 0x0156B1E0 is
// AptFileTransferPopup::AptFileTransferPopup (assert "Should only be one!");
// the row keeps the pinned address name.

#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

class GameSlot
{
public:
	bool isHuman() const;

	unsigned char m_pad00[0x30];
	UnicodeString m_name; // +0x30
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(int index) const;
};

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

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

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

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

class AptCommandMapAdder
{
private:
	unsigned char m_names[0xC];
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[0xC];
};

class Rva002D2C34
{
public:
	void rva002D2C34();
};

class __declspec(novtable) Rva005248D0
{
public:
	__forceinline Rva005248D0() { ((Rva002D2C34 *)this)->rva002D2C34(); }
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
};

// The open file transfer popup (VA 0x00E06398).
extern int g_Va00E06398;

class FileTransfer
{
public:
	void PlayerColor(int slot, char *result, bool skip);
};

class AptFileTransferPopup
{
public:
	void ProcessProgress(int player, int percent, UnicodeString text);
};

class Rva00583015Obj : public Rva005248D0
{
public:
	Rva00583015Obj(void *argument);
	virtual ~Rva00583015Obj();

private:
	GameInfo *m_game; // +0x58
	int m_rows[8]; // +0x5C
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
Rva00583015Obj::Rva00583015Obj(void *argument)
	: m_game((GameInfo *)argument)
{
	if (g_Va00E06398 != 0)
		return;
	g_Va00E06398 = (int)this;
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke((void *)13, "FileTransferPopUpOpen", 0, 0, 0, 0, 0, 0);
	for (int *row = m_rows; row != m_rows + 8; ++row)
		*row = -1;
	int count = 0;
	for (int i = 0; i < 8; ++i)
	{
		const GameSlot *slot = ((GameInfo *)argument)->getConstSlot(i);
		if (slot == 0 || !slot->isHuman())
			continue;
		m_rows[i] = count;
		AsciiString name;
		name.format("FileTransfer::PlayerName%d", count);
		g_bfmeAptWindowManager->bfmeSetText(name, slot->m_name, false);
		name.format("FileTransfer:PlayerColor:%d", count);
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&FileTransfer::PlayerColor);
		m_externHandlers.AddExternHandler(name, i, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		((AptFileTransferPopup *)this)->ProcessProgress(count, 0, UnicodeString(L" "));
		++count;
	}
	if (count < 8)
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&FileTransfer::PlayerColor);
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		do
		{
			AsciiString name;
			name.format("FileTransfer::PlayerName%d", count);
			g_bfmeAptWindowManager->bfmeSetText(name, UnicodeString(L" "), false);
			name.format("FileTransfer::Status%d", count);
			g_bfmeAptWindowManager->bfmeSetText(name, UnicodeString(L" "), false);
			name.format("FileTransfer:PlayerColor:%d", count);
			m_externHandlers.AddExternHandler(name, -1, AptRef<AptExternHandler>(binding));
			++count;
		} while (count < 8);
	}
	{
		AsciiString name("APT:FileTransferLoadingPlayerName");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("GUI:PlayerName"), false);
	}
	{
		AsciiString name("APT:FileTransferLoadingProgress");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("GUI:Progress"), false);
	}
	{
		AsciiString name("APT:FileTransferLoadingStatus");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("GUI:Status"), false);
	}
}
