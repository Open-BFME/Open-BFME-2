// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHs /O1 -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// class-gate: allow AsciiString donor TU-local StringBase-derived view emits the retail dtor at 0x0051CBC6; its temporary calls the out-of-line StringBase ctor 0x00037BA0 and releaseBuffer 0x00036410 like the InGameChat and CampaignReview precedents
#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class Rva0051CBC6;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

class Shell
{
public:
	void hide(bool shutdownImmediate);
};

void _bfme_closeAptScreen(const AsciiString &name);

struct GlobalA01E48;
extern struct GlobalA01E48 *g_Va00A01E48;
extern int g_00E04914;
extern "C" void __cdecl free(void *ptr);

struct FreeBuf
{
	void *p;
	~FreeBuf() { if (p) free(p); }
};

class __multiple_inheritance Rva0051CBC6
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~Rva0051CBC6();

private:
	char m_pad21C[100];
	int m_280;
	char m_pad284[8];
	FreeBuf m_28c;
	char m_pad290[32];
	AsciiString m_2b0;
	char m_pad2b4[12];
	AsciiString m_2c0;
};

// ??1Rva0051CBC6@@UAE@XZ, RVA 0x0051CBC6, 188 bytes.
// AptScoreScreen dtor: resets both vtables, closes AptScoreScreen via
// InitGadgets literal, hides Shell when slot 0x280 is empty, clears
// g_00E04914, releases string slots 0x2c0 and 0x2b0, frees pointer 0x28c,
// then the rowed _bfme_AptGameWindow base dtor. Evidence: vtable stores
// 0x00866FAC and 0x00866FA8, string AptScoreScreen::InitGadgets, callees
// 0x00037BA0 0x0041149A 0x00036410 0x0035BF4C 0x00030830 0x005126F5 all rowed
// or pinned, caller 0x0051CE56 is the ??_G deleting dtor.
Rva0051CBC6::~Rva0051CBC6()
{
	_bfme_closeAptScreen(AsciiString("AptScoreScreen::InitGadgets"));
	if (m_280 == 0 && g_Va00A01E48 != 0)
		((Shell *)g_Va00A01E48)->hide(false);
	g_00E04914 = 0;
}
