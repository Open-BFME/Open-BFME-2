// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /I.
// stlport
// ?update@BannerUI@@QAEXXZ retail 0x002167A3..0x00216A2E (651B).
// Same-TU callee lever: stateString's address goes to Rva00216332Call
// (0x00216332) and progress's to Rva0021639AInvoke (0x0021639A); with both
// rowed bodies owned here as select-any definitions cl proves the
// addresses do not escape and shares the frame slots as retail does. The
// summary message object Rva00406BB0 is 12 bytes (its ctor 0x00406B6A stores
// the army id at +8), which gives retail's frame 0x20 and its slot at -0x2C.
// GetStateString (0x00215EA4) is rowed as a free function in a BannerUI
// namespace, which this unit's class BannerUI cannot spell; it and the three
// GameLogic +0x184 forwarders are called through address-named views pinned
// at their rowed addresses. rva0023D096 returns a float (fmul by 100, _ftol).
// BannerUI vtable 0x007E59E4 slot 12 (slot 1 is the rowed BannerUI::init);
// WorldBuilder 0x00B6D7B0 is the twin (the DeleteBanner / SetBannerState /
// SetBannerProgress / APT:BannerTimer%d / BANNERUI:SummaryTitle strings of
// BannerUI.cpp). Unless the Apt movie is gone (+0x34) it deletes the banners
// marked for removal (+0x18) through the Apt "DeleteBanner" call then for
// every banner maps the army state (GameLogic +0x184 forwarder 0x0023D075;
// 0->0 2->1 3->2 else 3) and pushes state / progress (engage progress
// 0x0023D096 times 100) / timer (0x0023D0AC frames over the frame rate
// BfmeLogicFramesPerSecond as minutes and seconds around the language time separator)
// changes to the movie; an available banner fires OnBannerButton. A pending
// summary index +0x38 shows the BANNERUI:SummaryTitle message for that
// banner's army through ControlBar 0x00405C04 and is cleared.
// Banner record layout: BannerUI.cpp's BfmePod28 (+0x0C state +0x10 progress
// +0x14 timer +0x18 delete flag).
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

class Rva00215EA4BannerState { public: static const char *GetStateString(int state); };
class GameLogicFwd { public: int rva0023D075(int); float rva0023D096(int); int rva0023D0AC(int); };
struct BfmePod28
{
	unsigned int slot;
	int bannerID;
	const void *typeEntry;
	int state;
	int progress;
	int timer;
	bool pendingDelete;
};

namespace _STL {
// Bind the single-element erase to the rowed BfmePod28 erase.
template <> BfmePod28 *vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *position);
}

class Rva00222A8BTarget { public: int invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4); };
AsciiString __cdecl Rva0022288EGet(unsigned int value);
AsciiString __cdecl Rva00222834Get(int value);
static inline const char *Rva002162CFStr(const AsciiString &asciiString) { return ((const StringBase<char> *)&asciiString)->str(); }
int Rva002162CFInvoke(Rva00222A8BTarget *target, void *movie, const char *name, const unsigned int &slot);
__forceinline const char *GetStr00216332(const AsciiString &asciiString, void *const *extra, void **a1)
{
	char *t = *(char **)(void *)&asciiString;
	*a1 = *(void **)extra;
	return t ? t + 8 : "";
}
// Row owner: retail 0x00216332, 104 bytes. Kept visible for caller analysis.
__declspec(noinline) inline int __cdecl Rva00216332Call(void *target, void *level, const char *func, const unsigned int *val, void *const *extra)
{
    void *a1;
    return ((Rva00222A8BTarget *)target)->invoke(level, func, 2, GetStr00216332(Rva0022288EGet(*val), extra, &a1), a1, 0, 0, 0);
}
// Row owner: retail 0x0021639A, 149 bytes. Kept visible for caller analysis.
__declspec(noinline) inline int __cdecl Rva0021639AInvoke(Rva00222A8BTarget *target, void *movie, const char *name, const unsigned int &slot, const int &value)
{
	return target->invoke(movie, name, 2, Rva002162CFStr(Rva0022288EGet(slot)), (void *)Rva002162CFStr(Rva00222834Get(value)), 0, 0, 0);
}

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &window, const UnicodeString &text, bool html);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;

class GlobalLanguage
{
public:
	char m_pad00[0x14];
	AsciiString m_timeSeparator;
};
extern GlobalLanguage *TheGlobalLanguageData;

class GameTextInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual UnicodeString fetch(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;

struct BfmeMsgDN;
class ControlBar
{
public:
	void bfmeShowDN(BfmeMsgDN *msg);
};
extern ControlBar *TheControlBar;

class Rva00216094
{
public:
	virtual ~Rva00216094();
};
class Rva00406BB0
{
public:
	Rva00406BB0(const StringBase<unsigned short> &text, int armyID);
	__forceinline ~Rva00406BB0() { ((Rva00216094 *)this)->Rva00216094::~Rva00216094(); }
private:
	void *m_vtbl;
	void *m_text;
	int m_armyID;
};

class BannerUI
{
public:
	void OnBannerButton(int slot);
	void update();

	static __forceinline int bannerStateFor(int armyState)
	{
		switch (armyState) {
		case 0:
			return 0;
		case 2:
			return 1;
		case 3:
			return 2;
		default:
			return 3;
		}
	}

private:
	unsigned char m_pad00[0x24];
	void *m_movie;
	_STL::vector<BfmePod28, _STL::allocator<BfmePod28> > m_banners;
	bool m_movieGone;
	unsigned char m_pad35[3];
	unsigned int m_summaryIndex;
};

void BannerUI::update()
{
	if (m_movieGone)
		return;
	for (BfmePod28 *it = m_banners.begin(); it != m_banners.end(); ) {
		if (it->pendingDelete) {
			Rva002162CFInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_movie, "DeleteBanner", it->slot);
			it = m_banners.erase(it);
		} else {
			++it;
		}
	}
	for (BfmePod28 *banner = m_banners.begin(); banner != m_banners.end(); ++banner) {
		int state = bannerStateFor(((GameLogicFwd *)TheGameLogic)->rva0023D075(banner->bannerID));
		if (state != banner->state) {
			const char *stateString = Rva00215EA4BannerState::GetStateString(state);
			Rva00216332Call(g_bfmeAptWindowManager, m_movie, "SetBannerState", &banner->slot, (void *const *)&stateString);
			banner->state = state;
		}
		if (banner->state == 0)
			OnBannerButton(banner->slot);
		int progress;
		int timer;
		if (banner->state == 1) {
			progress = (int)(((GameLogicFwd *)TheGameLogic)->rva0023D096(banner->bannerID) * 100.0f);
			timer = ((GameLogicFwd *)TheGameLogic)->rva0023D0AC(banner->bannerID) / BfmeLogicFramesPerSecond;
		} else {
			progress = 0;
			timer = -1;
		}
		if (progress != banner->progress) {
			Rva0021639AInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_movie, "SetBannerProgress", banner->slot, progress);
			banner->progress = progress;
		}
		if (timer != banner->timer) {
			AsciiString windowName;
			windowName.format("APT:BannerTimer%d", banner->slot);
			UnicodeString text;
			if (timer >= 0) {
				int minutes = timer / 60;
				int seconds = timer % 60;
				UnicodeString separator(L":");
				if (TheGlobalLanguageData)
					separator.translate(TheGlobalLanguageData->m_timeSeparator);
				text.format(L"%d%s%02d", minutes, separator.str(), seconds);
			}
			g_bfmeAptWindowManager->bfmeSetText(windowName, text, false);
			banner->timer = timer;
		}
	}
	if (m_summaryIndex < m_banners.size()) {
		TheControlBar->bfmeShowDN((BfmeMsgDN *)&Rva00406BB0(TheGameText->fetch("BANNERUI:SummaryTitle", 0), m_banners.begin()[m_summaryIndex].bannerID));
		m_summaryIndex = (unsigned int)-1;
	}
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   2186916 reads ?GetStateString@BannerUI@@YAPBDH@Z
#pragma comment(linker, "/alternatename:?GetStateString@Rva00215EA4BannerState@@SAPBDH@Z=?GetStateString@BannerUI@@YAPBDH@Z")
//   4217860 reads ?rva00405C04@Rva00405A50@@QAEXPAVBfmeThingGX@@@Z
#pragma comment(linker, "/alternatename:?bfmeShowDN@ControlBar@@QAEXPAUBfmeMsgDN@@@Z=?rva00405C04@Rva00405A50@@QAEXPAVBfmeThingGX@@@Z")
//   2347125 reads ?rva0023D075@GameLogic@@QAEHH@Z
#pragma comment(linker, "/alternatename:?rva0023D075@GameLogicFwd@@QAEHH@Z=?rva0023D075@GameLogic@@QAEHH@Z")
//   2347158 reads ?rva0023D096@GameLogic@@QAEMH@Z
#pragma comment(linker, "/alternatename:?rva0023D096@GameLogicFwd@@QAEMH@Z=?rva0023D096@GameLogic@@QAEMH@Z")
//   2347180 reads ?rva0023D0AC@GameLogic@@QAEHH@Z
#pragma comment(linker, "/alternatename:?rva0023D0AC@GameLogicFwd@@QAEHH@Z=?rva0023D0AC@GameLogic@@QAEHH@Z")
