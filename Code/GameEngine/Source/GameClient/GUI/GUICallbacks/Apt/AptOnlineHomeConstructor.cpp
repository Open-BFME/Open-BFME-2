// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
//
// AptOnline::OnlineHome::OnlineHome, retail 0x005B9BBC (1135 bytes).
//
// Identity (target evidence): WorldBuilder names the body
// AptOnlineHome::AptOnlineHome; it builds the 0x60-byte Apt screen base
// 0x0056DC4C, installs the vftable 0x00C73B70 and, for the first instance
// (0x00E06480), translates the "." font placeholder, binds the online home
// images and icons, the "AptOnline::OnlineHome::..." commands (rowed
// handlers 0x005B930C/0x005B9B6B), the InitGadgets screen reference and the
// NumTickerFields query, then posts peer request 0x17 and refreshes
// (0x005B977B). The binding idiom is the matched AptOnlineLogin and
// AptScoreScreen constructors'.

#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

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
class AptOverButtonHandler;

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
private:
	_STL::vector<AsciiString> m_names;
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The 0x60-byte Apt screen base (constructor 0x0056DC4C); its command map
// adder is at +0x04.
class Rva0056DC4C
{
public:
	Rva0056DC4C(void *shell);
	virtual ~Rva0056DC4C();
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
private:
	unsigned char m_pad1C[0x60 - 0x1C];
};

class Rva00222A8BTarget
{
public:
	void rva002239FA(const AsciiString &window, const AsciiString &image);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

class GlobalLanguage
{
public:
	unsigned char m_pad00[0x0C];
	AsciiString m_0C; // +0x0C
};

extern GlobalLanguage *TheGlobalLanguageData;

// The 492-byte GameSpy peer request.
class BfmeOpaqueOwnedRecord492
{
public:
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
	int m_requestType; // +0x00
private:
	unsigned char m_pad004[0x1EC - 0x04];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void addRequest(const BfmeOpaqueOwnedRecord492 &request); // slot 6
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

extern int g_Va00E06480; // the first online home screen

class GameWindow;

// The online home's gadget windows (0x00DD3BC0).
static const char *s_gadgets[] = {
	"OnlineHome/Gadgets/Image",
	"OnlineHome/Gadgets/ImageLevelIconMain",
	"OnlineHome/instance101/factionImageA",
	"OnlineHome/instance101/factionImageB",
	"OnlineHome/instance101/factionImageC",
	"OnlineHome/instance101/factionImageD"
};

class AptOnline
{
public:
	class OnlineHome;
};

class AptOnline::OnlineHome : public Rva0056DC4C
{
public:
	OnlineHome(AptOnline *shell);
	virtual ~OnlineHome();
	void OfficialSite(const char *unused);
	void OnOpened(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void NumTickerFields(int query, char *value, bool set);
	void rva005B977B();
private:
	int m_60;
	UnicodeString m_64;
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptOnline::OnlineHome::OnlineHome(AptOnline *shell)
	: Rva0056DC4C(shell),
	  m_60(0),
	  m_64(L".")
{
	if (g_Va00E06480 != 0)
		return;
	g_Va00E06480 = (int)this;
	if (TheGlobalLanguageData)
		m_64.translate(TheGlobalLanguageData->m_0C);
	TheRva00222A8BTarget->rva002239FA(AsciiString(s_gadgets[0]), AsciiString("ScrollShroud"));
	TheRva00222A8BTarget->rva002239FA(AsciiString(s_gadgets[1]), AsciiString("ScrollShroud"));
	TheRva00222A8BTarget->rva002239FA(AsciiString(s_gadgets[2]), AsciiString("AptIconMen"));
	TheRva00222A8BTarget->rva002239FA(AsciiString(s_gadgets[3]), AsciiString("AptIconElves"));
	TheRva00222A8BTarget->rva002239FA(AsciiString(s_gadgets[4]), AsciiString("AptIconDwarves"));
	TheRva00222A8BTarget->rva002239FA(AsciiString(s_gadgets[5]), AsciiString("AptIconIsengard"));
	TheRva00222A8BTarget->rva002239FA(AsciiString(s_gadgets[4]), AsciiString("AptIconMordor"));
	TheRva00222A8BTarget->rva002239FA(AsciiString(s_gadgets[5]), AsciiString("AptIconWild"));
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::OnlineHome::OfficialSite);
		AsciiString name("AptOnline::OnlineHome::OfficialSite");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::OnlineHome::OnOpened);
		AsciiString name("AptOnline::OnlineHome::OnOpened");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::OnlineHome::InitGadgets);
		AsciiString name("AptOnlineHome::InitGadgets");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::OnlineHome::NumTickerFields);
		AsciiString name("OnlineHome::NumTickerFields");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	BfmeOpaqueOwnedRecord492 request;
	request.m_requestType = 0x17;
	TheGameSpyPeerMessageQueue->addRequest(request);
	rva005B977B();
}
