// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// class-gate: allow AsciiString donor TU-local StringBase-derived view emits the retail 116B dtor at 0x004E83EB; its temporary calls the out-of-line StringBase ctor 0x00037BA0 and dtor 0x00036410, which the shared header force-inlines
#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"

template <typename T> class StringBase
{
	friend class AsciiString;

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

void _bfme_closeAptScreen(const AsciiString &name);

extern int g_Va00E04478;

class __multiple_inheritance BfmeAptScreenInGameChat
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~BfmeAptScreenInGameChat();
};

// ??1BfmeAptScreenInGameChat@@UAE@XZ @0x004E83EB 116B
// Evidence: unlock lane, AptInGameChat::InitGadgets literal, base pin 0x005126F5, current-window global g_Va00E04478, caller 0x004E84E6.
BfmeAptScreenInGameChat::~BfmeAptScreenInGameChat()
{
	if (g_Va00E04478 == (int)this)
	{
		_bfme_closeAptScreen(AsciiString("AptInGameChat::InitGadgets"));
		g_Va00E04478 = 0;
	}
}
