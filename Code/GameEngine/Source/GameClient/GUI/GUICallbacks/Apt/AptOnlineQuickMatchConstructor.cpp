// cl: /DBFME_ASCII_DTOR_DECL /vmg /vmm /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
//
// ??0OnlineQuickMatch@AptOnline@@QAE@PAV1@@Z, retail 0x005BAB7E..0x005BAECA
// (844 bytes, EH, ret 4); pinned until now as ??0Rva005BAB7E@@QAE@PAVAptOnline@@@Z.
//
// The online quick match screen: the shell's factory (0x00516E4E) allocates
// 0xA0 bytes and calls this with the shell. Identity: it installs vftable
// 0x00C73E24 and binds the rowed AptOnline::OnlineQuickMatch callbacks
// (PlayGame 0x005BA34B, Cancel 0x005BAAA3, WidenSearch 0x005BAA2B,
// StartSimple 0x005BA344, OnFoundMovieDone 0x005BA359, InitGadgets
// 0x005BA94A) to this object, so it is that class's constructor (the class
// spelling follows those rows).
// Body: the rowed screen base 0x0056DC4C keeps the shell at +0x58; the
// members are the state +0x60, QuickMatchPreferences +0x64 (rowed ctor
// 0x005DF1A3), three flags +0x78..+0x7A, the gadget mask +0x7C, the color
// window ref +0x80 (pinned ctor 0x0007B719) and seven words +0x84..+0x9C.
// While the Apt window manager exists and no instance is registered at
// 0x00E06550 it registers itself, caches the AptCustomMatchSelected /
// Unselected images (+0x94 / +0x98), binds the callbacks through the
// command map adder at +0x04 (rowed 0x0052458E, functor holder 0x0057BC63)
// and the InitGadgets screen ref (rowed 0x00411458), refreshes the map
// cache (pinned 0x00305749), resets the staging room (TheGameSpyGame vslot
// 10), deletes the 0x00E063F8 object, pokes TheGameSpyInfo (vslot 47) and
// runs the shell's rowed 0x00516F08.
// Pattern and views follow the matched AptOnlineStatsConstructor.cpp.

#include "ascii_string.h"

class GameWindow;
class Rva00323674
{
public:
	int rva00323674() const;
	Rva00323674(GameWindow *window);
	~Rva00323674();
	GameWindow *m_window; // +0x00
};
class AptOnline;
class Image;
#include "../../../../../Include/GameClient/Rva005248D0.h"
class Rva0056DC4C:public Rva005248D0 {
public:
    Rva0056DC4C(void*);
    virtual ~Rva0056DC4C();
protected:
    AptOnline *m_owner; // +0x58
    int unknown5c;
};
#include "../../../../../Include/Common/UserPreferences.h"
#include "../../../../../Include/Common/QuickMatchPreferencesClass.h"
class AptOnline
{
public:
    void rva00516F08();

    class OnlineQuickMatch : public Rva0056DC4C
    {
    public:
        OnlineQuickMatch(AptOnline *shell);
        virtual ~OnlineQuickMatch();
        void StartSimple(const char *unused);
        void PlayGame(const char *unused);
        void OnFoundMovieDone(const char *unused);
        void WidenSearch(const char *unused);
        void Cancel(const char *unused);
        void InitGadgets(const char *name, void *argument, GameWindow *window);
        int rva005BAECA(int window, int msg, unsigned char key, int flags);

    private:
        int m_state; // +0x60
        QuickMatchPreferences m_prefs; // +0x64
        bool m_78, m_simple, m_foundMovie;
        unsigned int m_gadgets; // +0x7C
        Rva00323674 m_color; // +0x80
        GameWindow *m_numPlayers, *m_side, *m_connectionSpeed, *m_ladder;
        const Image *m_selectedImage, *m_unselectedImage;
        int m_9C;
    };
};
#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;
typedef void(FunctorTarget::*FunctorMethod)(int);
#include "../../../../../Include/GameClient/FunctorBinding.h"
struct Rva0057BC63FunctorHolder {Rva0057BC63FunctorHolder(const FunctorBinding &);Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &o):ptr(o.ptr){if(ptr)++ptr->references;}TargetRef00217D4C *ptr;~Rva0057BC63FunctorHolder(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}};
template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(FunctorBinding binding) : Rva0057BC63FunctorHolder(binding) {}
};
class AptCommandMap;
#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

#include "../../../../../Include/GameClient/Image.h"

class MapMetaData;
#include "../../../../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern int g_Va00E06550;

#include "../../../../../Include/GameNetwork/GameSpyStagingRoom.h"
extern GameSpyStagingRoom *TheGameSpyGame;

#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva005A6D47
{
public:
	virtual ~Rva005A6D47();
};
struct NAT;
extern NAT *TheNAT;	// 0x00E063F8, data row in NATProcessGlobalMessage.cpp

// The functor binding keeps the multiple-inheritance member pointer form
// ({function, 0}); the callbacks are widened through this view.
class QuickMatchBindingView
{
public:
	virtual void v00();
};
class QuickMatchFunctorTarget : public AptOnline::OnlineQuickMatch, public QuickMatchBindingView
{
};
typedef void (QuickMatchFunctorTarget::*QuickMatchCallback)(const char *);
typedef void (QuickMatchFunctorTarget::*QuickMatchInitGadgets)(const char *, void *, GameWindow *);

AptOnline::OnlineQuickMatch::OnlineQuickMatch(AptOnline *owner)
	: Rva0056DC4C(owner), m_state(0), m_78(false), m_simple(false), m_foundMovie(false),
	  m_gadgets(0), m_color(0), m_numPlayers(0), m_side(0), m_connectionSpeed(0),
	  m_ladder(0), m_selectedImage(0), m_unselectedImage(0), m_9C(0)
{
	if (g_bfmeAptWindowManager && !g_Va00E06550) {
		g_Va00E06550 = (int)this;
		{
			AsciiString name("AptCustomMatchSelected");
			m_selectedImage = TheMappedImageCollection->findImageByName(name);
		}
		{
			AsciiString name("AptCustomMatchUnselected");
			m_unselectedImage = TheMappedImageCollection->findImageByName(name);
		}
		{
			FunctorBinding::Method method = reinterpret_cast<FunctorBinding::Method>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::PlayGame));
			AsciiString name("AptOnline::OnlineQuickMatch::PlayGame");
			((AptCommandMapAdder *)((char *)this + 4))->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorBinding::Method method = reinterpret_cast<FunctorBinding::Method>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::Cancel));
			AsciiString name("AptOnline::OnlineQuickMatch::Cancel");
			((AptCommandMapAdder *)((char *)this + 4))->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorBinding::Method method = reinterpret_cast<FunctorBinding::Method>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::WidenSearch));
			AsciiString name("AptOnline::OnlineQuickMatch::WidenSearch");
			((AptCommandMapAdder *)((char *)this + 4))->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorBinding::Method method = reinterpret_cast<FunctorBinding::Method>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::StartSimple));
			AsciiString name("AptOnline::OnlineQuickMatch::StartSimple");
			((AptCommandMapAdder *)((char *)this + 4))->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorBinding::Method method = reinterpret_cast<FunctorBinding::Method>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::OnFoundMovieDone));
			AsciiString name("AptOnline::OnlineQuickMatch::OnFoundMovieDone");
			((AptCommandMapAdder *)((char *)this + 4))->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorBinding::Method method = reinterpret_cast<FunctorBinding::Method>(static_cast<QuickMatchInitGadgets>(&AptOnline::OnlineQuickMatch::InitGadgets));
			AsciiString name("AptOnlineQuickMatch::InitGadgets");
			_bfme_setAptScreenRef(name,
				AptRef<AptScreenInitGadgets>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		TheMapCache->updateCache();
		TheGameSpyGame->reset();
		if (TheNAT) {
			::delete (Rva005A6D47 *)TheNAT;
			TheNAT = 0;
		}
		if (TheGameSpyInfo)
			TheGameSpyInfo->leaveStagingRoom();
		m_owner->rva00516F08();
	}
}
