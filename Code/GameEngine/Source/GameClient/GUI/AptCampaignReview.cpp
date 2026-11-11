// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI /Ireference/open-bfme-1/game/GameEngine/Include/GameClient
#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"
//
// AptCampaignReview destructor, retail 0x00512894 (125 bytes); BFME 1
// donor class BfmeAptScreenCampaignReview (b1 0x0050DBD0, 159 bytes).
// The CampaignReview constructor and callback name identify this cleanup
// body, which resets both interface vtables before it closes the screen.
// The class carries the WorldBuilder name the constructor unit
// (AptCampaignReview.cpp) and its rowed members use, so that unit's
// virtual destructor reference resolves here.

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"


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

#include "../../../Include/GameClient/Shell.h"

void _bfme_closeAptScreen(const AsciiString &name);

extern const void *BfmeAptScreenCampaignReviewVftable[];
extern const void *BfmeAptScreenCampaignReviewSecondaryVftable[];
extern Shell *TheShell;
extern void *g_obj12F495C;

class __multiple_inheritance AptCampaignReview
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~AptCampaignReview();
};

AptCampaignReview::~AptCampaignReview()
{
	_bfme_closeAptScreen(AsciiString("AptCampaignReview::InitGadgets"));

	if(TheShell)
		TheShell->hide(false);

	g_obj12F495C = 0;
}
