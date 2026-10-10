// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
//
// AptCreateAHero::AptCreateAHero, retail 0x005142B0 (1407 bytes, EH, ret 4).
//
// The create-a-hero screen constructor (strings "AptCreateAHero::...",
// vftables 0x00C65D20/0x00C65D1C over the Apt window base 0x0051268C,
// singleton 0x00E048D4). Identity: it binds the rowed screen callbacks
// (OnShowScreen 0x005139B0 ... ZoomOut 0x00513AE1, the "CreateAHero"
// over-button handler 0x00513AF4) in AptCreateAHeroCallbacks.cpp and builds
// the five pages: manager 0x28 (0x005B6B93), class 0x2C (rowed), appearance
// 0x10 (rowed), powers 0x74 (rowed) and bonus 0x08 (0x005B25E7). Pattern is
// the matched Apt screen constructors' (AptMainMenuConstructor.cpp).

#include <vector>
#include <string.h>
#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

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

// The image binder at +0x40 of the Apt window half (0x00524306 family):
// window name to image name.
class Rva00524306
{
public:
	void rva00524767(const AsciiString &name, const AsciiString &image);
private:
	_STL::vector<AsciiString> m_names;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C
private:
	unsigned char m_pad028[0x40 - 0x28];
public:
	Rva00524306 m_imageAdder; // +0x40
private:
	unsigned char m_pad04C[0x58 - 0x4C];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};


class AptCustomRender;

class AptCustomRenderAdder
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
};

class AptScreenInitGadgets;
class AptOverButtonHandler;
class AptPlayer
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
};
extern AptPlayer *TheAptPlayer;

class AptCreateAHero;
class AptMyHero
{
public:
	AptMyHero(AptCreateAHero *screen);
	virtual ~AptMyHero();
private:
	unsigned char m_opaque[0x18C];
};

struct AppearanceOwner;
struct Rva005B3676Owner;
class Rva005B6B93
{
public:
	Rva005B6B93(AptCreateAHero *screen);
private:
	unsigned char m_pad[0x28];
};
class Rva005B25E7
{
public:
	Rva005B25E7(AptCreateAHero *screen);
private:
	unsigned char m_pad[0x08];
};
class Rva005B4A46
{
public:
	Rva005B4A46(AppearanceOwner *owner);
private:
	unsigned char m_pad[0x10];
};
struct GlobalData2
{
	unsigned char m_pad000[0x68];
	bool m_68;
	unsigned char m_pad069[0x9A5 - 0x69];
	bool m_9A5;
	unsigned char m_pad9a6[0x9BD - 0x9A6];
	bool m_9BD;
	unsigned char m_pad9be[0xD45 - 0x9BE];
	bool m_D45;
};
extern GlobalData2 *TheWritableGlobalData;
class CreateAHeroManager
{
public:
	unsigned char m_pad[0x184];
	bool m_184;
};
extern CreateAHeroManager *TheCreateAHeroManager;

class AptCreateAHero : public _bfme_AptGameWindow
{
public:
	class Class
	{
	public:
		Class(Rva005B3676Owner *owner);
	private:
		unsigned char m_pad[0x2C];
	};
	class Powers
	{
	public:
		Powers(Rva005B3676Owner *owner);
	private:
		unsigned char m_pad[0x74];
	};
	AptCreateAHero(void *context);
	virtual ~AptCreateAHero();
	void PrepareToTakePicture(const char *unused);
	void OnTakePicture(const char *unused);
	void RotateLeft(const char *pressed);
	void RotateRight(const char *pressed);
	void ZoomIn(const char *pressed);
	void ZoomOut(const char *pressed);
	void OnShowScreen(const char *screen);
	void RenderPictureGuard(const void *origin, const void *extent, void *unused3, void *unused4);
	void CreateAHeroDemo(int query, char *result, bool skip);
	void rva00513AF4(const char *value);
	void rva00514070(void *a, void *b, void *c, void *d);
private:
	AptMyHero m_myHero; // +0x27C
	int m_mode; // +0x40C
	void *m_page; // +0x410
	void *m_previousPage; // +0x414
	Rva005B6B93 *m_pageM; // +0x418
	Class *m_pageC; // +0x41C
	Rva005B4A46 *m_pageA; // +0x420
	Powers *m_pageP; // +0x424
	Rva005B25E7 *m_pageB; // +0x428
	bool m_42c; // +0x42C
	bool m_42d;
	bool m_42e;
	bool m_takePicture; // +0x42F
	bool m_rotateLeft; // +0x430
	bool m_rotateRight; // +0x431
	bool m_zoomIn; // +0x432
	bool m_zoomOut; // +0x433
	int m_pictureFrames; // +0x434
	static AptCreateAHero *s_instance; // 0x00A048D4
};

class Rva005248D0CustomRenders
{
public:
	unsigned char m_pad[0x34];
	AptCustomRenderAdder m_customRenders; // +0x34
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptCreateAHero::AptCreateAHero(void *context)
	: _bfme_AptGameWindow(context), m_myHero(this), m_mode(0), m_page(0), m_previousPage(0)
{
	m_42c = TheWritableGlobalData->m_9BD;
	m_42d = TheWritableGlobalData->m_D45;
	m_42e = TheWritableGlobalData->m_68;
	m_takePicture = false;
	m_rotateLeft = false;
	m_rotateRight = false;
	m_zoomIn = false;
	m_zoomOut = false;
	m_pictureFrames = 0;
	memset(&m_pageM, 0, 0x14);
	TheCreateAHeroManager->m_184 = true;
	TheWritableGlobalData->m_9BD = false;
	TheWritableGlobalData->m_9A5 = false;
	TheWritableGlobalData->m_D45 = true;
	TheWritableGlobalData->m_68 = false;
	s_instance = this;
	m_pageM = new Rva005B6B93(this);
	m_pageC = new Class((Rva005B3676Owner *)this);
	m_pageA = new Rva005B4A46((AppearanceOwner *)this);
	m_pageP = new Powers((Rva005B3676Owner *)this);
	m_pageB = new Rva005B25E7(this);
#define BIND_COMMAND(handler, label) \
	{ \
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCreateAHero::handler); \
		AsciiString name(label); \
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}
	BIND_COMMAND(OnShowScreen, "AptCreateAHero::OnShowScreen")
	BIND_COMMAND(PrepareToTakePicture, "AptCreateAHero::PrepareToTakePicture")
	BIND_COMMAND(OnTakePicture, "AptCreateAHero::OnTakePicture")
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCreateAHero::RenderPictureGuard);
		AsciiString name("CreateAHero::RenderPictureGuard");
		((Rva005248D0CustomRenders *)static_cast<Rva005248D0 *>(this))->m_customRenders.AddCustomRender(name, AptRef<AptCustomRender>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCreateAHero::rva00514070);
		AsciiString name("CreateAHero::DrawMapComponent");
		TheAptPlayer->AddCustomRender(name, AptRef<AptCustomRender>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCreateAHero::CreateAHeroDemo);
		AsciiString name("CreateAHeroDemo");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	BIND_COMMAND(RotateLeft, "AptCreateAHero::RotateLeft")
	BIND_COMMAND(RotateRight, "AptCreateAHero::RotateRight")
	BIND_COMMAND(ZoomIn, "AptCreateAHero::ZoomIn")
	BIND_COMMAND(ZoomOut, "AptCreateAHero::ZoomOut")
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCreateAHero::rva00513AF4);
		AsciiString name("CreateAHero");
		m_overButtonHandlers.AddOverButtonHandler(name, AptRef<AptOverButtonHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
}
