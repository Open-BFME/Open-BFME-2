// ?rva002167A3@BannerUI@@QAEXXZ
// partial score=0.7 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva002167A3@BannerUI@@QAEXXZ retail 0x002167A3..0x00216A2E (651B).
// BannerUI vtable 0x007E59E4 slot 12 (slot 1 is the rowed BannerUI::init);
// WorldBuilder 0x00B6D7B0 is the twin (the DeleteBanner / SetBannerState /
// SetBannerProgress / APT:BannerTimer%d / BANNERUI:SummaryTitle strings of
// BannerUI.cpp). Unless the Apt movie is gone (+0x34) it deletes the banners
// marked for removal (+0x18) through the Apt "DeleteBanner" call then for
// every banner maps the army state (GameLogic +0x184 forwarder 0x0023D075;
// 0->0 2->1 3->2 else 3) and pushes state / progress (engage progress
// 0x0023D096 times 100) / timer (0x0023D0AC frames over the frame rate
// g_Va00DBA4E4 as minutes and seconds around the language time separator)
// changes to the movie; an available banner fires OnBannerButton. A pending
// summary index +0x38 shows the BANNERUI:SummaryTitle message for that
// banner's army through ControlBar 0x00405C04 and is cleared.
// Banner record layout: BannerUI.cpp's BfmePod28 (+0x0C state +0x10 progress
// +0x14 timer +0x18 delete flag).
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

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
template <class T> class allocator { public: allocator() {} };
template <class T, class A> class vector {
public:
	typedef T *iterator;
	iterator begin() { return _M_start; }
	iterator end() { return _M_finish; }
	unsigned int size() const { return _M_finish - _M_start; }
	T &operator[](unsigned int n) { return _M_start[n]; }
	iterator erase(iterator position);
private:
	iterator _M_start;
	iterator _M_finish;
	iterator _M_end_of_storage;
};
}

class Rva00222A8BTarget;
int Rva002162CFInvoke(Rva00222A8BTarget *target, void *movie, const char *name, const unsigned int &slot);
int Rva00216332Call(void *target, void *movie, const char *name, const unsigned int *slot, void *const *value);
int Rva0021639AInvoke(Rva00222A8BTarget *target, void *movie, const char *name, const unsigned int &slot, const int &value);

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &window, const UnicodeString &text, bool html);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

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
};

class BannerUI
{
public:
	static const char *GetStateString(int state);
	void OnBannerButton(int slot);
	void rva002167A3();

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

void BannerUI::rva002167A3()
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
		int state = bannerStateFor(TheGameLogic->rva0023D075(banner->bannerID));
		if (state != banner->state) {
			const char *stateString = GetStateString(state);
			Rva00216332Call(g_bfmeAptWindowManager, m_movie, "SetBannerState", &banner->slot, (void *const *)&stateString);
			banner->state = state;
		}
		if (banner->state == 0)
			OnBannerButton(banner->slot);
		int progress;
		int timer;
		if (banner->state == 1) {
			progress = (int)(TheGameLogic->rva0023D096(banner->bannerID) * 100.0f);
			timer = TheGameLogic->rva0023D0AC(banner->bannerID) / g_Va00DBA4E4;
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
		{
			UnicodeString title = TheGameText->fetch("BANNERUI:SummaryTitle", 0);
			TheControlBar->bfmeShowDN((BfmeMsgDN *)&Rva00406BB0(title, m_banners[m_summaryIndex].bannerID));
		}
		m_summaryIndex = (unsigned int)-1;
	}
}
