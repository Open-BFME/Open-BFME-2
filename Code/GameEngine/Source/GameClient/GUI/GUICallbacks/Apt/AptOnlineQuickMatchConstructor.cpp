// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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
class Image;

class Rva0056DC4C
{
public:
	Rva0056DC4C(void *);
	virtual ~Rva0056DC4C();
	unsigned char pad[0x60 - 4];
};

class QuickMatchPreferences
{
public:
	QuickMatchPreferences();
	virtual ~QuickMatchPreferences();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva00323674
{
public:
	Rva00323674(GameWindow *window);
	~Rva00323674();
	GameWindow *m_window;
};

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
struct FunctorBinding
{
	FunctorBinding(FunctorMethod m, FunctorTarget *t) : target(t), method(m) {}
	FunctorTarget *target;
	unsigned pad;
	FunctorMethod method;
};
class FunctorWrapperHead
{
public:
	void *vt;
	int count;
};
class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &x) : ptr(x.ptr)
	{
		if (ptr) ++ptr->count;
	}
	FunctorWrapperHead *ptr;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(FunctorBinding b) : Rva0057BC63FunctorHolder(b) {}
	~AptRef()
	{
		if (ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);
	}
};
class AptCommandMap;
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>);
};
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

class MapCache
{
public:
	void updateCache();
};
extern MapCache *TheMapCache;

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern int g_Va00E06550;

class GameSpyStagingRoom
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09)
#undef G
	virtual void reset(); // slot 10
};
extern GameSpyStagingRoom *TheGameSpyGame;

class GameSpyInfoInterface
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19)
	G(20) G(21) G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29)
	G(30) G(31) G(32) G(33) G(34) G(35) G(36) G(37) G(38) G(39)
	G(40) G(41) G(42) G(43) G(44) G(45) G(46)
#undef G
	virtual void slot47(); // +0xBC
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva005A6D47
{
public:
	virtual ~Rva005A6D47();
};
extern Rva005A6D47 *g_Va00E063F8;

class AptOnline
{
public:
	void rva00516F08();
	class OnlineQuickMatch;
};

class AptOnline::OnlineQuickMatch : public Rva0056DC4C
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

private:
	AptOnline *shell() { return *(AptOnline **)((char *)this + 0x58); }
	AptCommandMapAdder *commandMaps() { return (AptCommandMapAdder *)((char *)this + 4); }

	int m_state; // +0x60
	QuickMatchPreferences m_prefs; // +0x64
	bool m_78;
	bool m_simple; // +0x79
	bool m_foundMovie; // +0x7A
	unsigned int m_gadgets; // +0x7C
	Rva00323674 m_color; // +0x80
	GameWindow *m_numPlayers; // +0x84
	GameWindow *m_side; // +0x88
	GameWindow *m_connectionSpeed; // +0x8C
	GameWindow *m_ladder; // +0x90
	const Image *m_selectedImage; // +0x94
	const Image *m_unselectedImage; // +0x98
	int m_9C;
};

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
			FunctorMethod method = reinterpret_cast<FunctorMethod>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::PlayGame));
			AsciiString name("AptOnline::OnlineQuickMatch::PlayGame");
			commandMaps()->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::Cancel));
			AsciiString name("AptOnline::OnlineQuickMatch::Cancel");
			commandMaps()->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::WidenSearch));
			AsciiString name("AptOnline::OnlineQuickMatch::WidenSearch");
			commandMaps()->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::StartSimple));
			AsciiString name("AptOnline::OnlineQuickMatch::StartSimple");
			commandMaps()->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(static_cast<QuickMatchCallback>(&AptOnline::OnlineQuickMatch::OnFoundMovieDone));
			AsciiString name("AptOnline::OnlineQuickMatch::OnFoundMovieDone");
			commandMaps()->AddCommandMap(name,
				AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(static_cast<QuickMatchInitGadgets>(&AptOnline::OnlineQuickMatch::InitGadgets));
			AsciiString name("AptOnlineQuickMatch::InitGadgets");
			_bfme_setAptScreenRef(name,
				AptRef<AptScreenInitGadgets>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		TheMapCache->updateCache();
		TheGameSpyGame->reset();
		if (g_Va00E063F8) {
			::delete g_Va00E063F8;
			g_Va00E063F8 = 0;
		}
		if (TheGameSpyInfo)
			TheGameSpyInfo->slot47();
		shell()->rva00516F08();
	}
}
