// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// class-gate: allow AsciiString donor TU-local StringBase-derived view emits the retail 125B dtor at 0x00512894; its temporary calls the out-of-line StringBase ctor 0x00037BA0 and dtor 0x00036410, which the shared header force-inlines
#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"
//
// BfmeAptScreenCampaignReview destructor, retail 0x0050DBD0 (159 bytes).
// The CampaignReview constructor and callback name identify this cleanup
// body, which resets both interface vtables before it closes the screen.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();

	void *m_data;
};

class AsciiString
{
public:
	AsciiString(const char *text) { ((StringBase<char> *)this)->StringBase<char>::StringBase(text); }
	AsciiString(const AsciiString &other) { ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&other); }
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
private:
	void *m_text;
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

extern const void *BfmeAptScreenCampaignReviewVftable[];
extern const void *BfmeAptScreenCampaignReviewSecondaryVftable[];
extern Shell *TheShell;
extern void *g_obj12F495C;

class __multiple_inheritance BfmeAptScreenCampaignReview
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~BfmeAptScreenCampaignReview();
};

BfmeAptScreenCampaignReview::~BfmeAptScreenCampaignReview()
{
	_bfme_closeAptScreen(AsciiString("AptCampaignReview::InitGadgets"));

	if(TheShell)
		TheShell->hide(false);

	g_obj12F495C = 0;
}
