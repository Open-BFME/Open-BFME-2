// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// BFME2's create-a-hero screen Apt callbacks, 0x00513A47 onward, bound by
// these names ("AptCreateAHero::PrepareToTakePicture" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The class is named for the strings' prefix. The rotate and
// zoom buttons pass "true" while held: only the first character is tested.

// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include "ascii_string.h"


// TheGlobalData's +0x9D1 flag.
class GlobalData;
extern class GlobalData *TheWritableGlobalData;

struct AptCreateAHeroGlobalData
{
	unsigned char m_pad000[0x9D1];
	bool m_9d1; // +0x9D1
	unsigned char m_pad9d2[0xAC0 - 0x9D2];
	AsciiString m_mapName; // +0xAC0
};

// OpenScreen's collaborators: the shell (rowed Shell::push), the message
// stream's vslot 18 append, and the logic random seed.
class Shell
{
public:
	void push(AsciiString filename, bool shutdownImmediate);
};
extern Shell *TheShell;

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);
};
extern MessageStream *TheMessageStream;

void InitGameLogicRandom(unsigned int seed);

// A create-a-hero sub-screen: vslot 3 shows it, vslot 4 hides it.
class AptCreateAHeroPage
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void show();
	virtual void hide();
	virtual void v05(); virtual void v06();
	virtual void v07(const char *value);
};

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	unsigned char m_pad004[0x58 - 4];
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

// The screen's embedded hero object at +0x27C. 0x005B1288 is a member of
// AptMyHero (rowed in AptMyHero.cpp, which calls AptMyHero's own 0x005B0487
// on the same receiver); AptMyHero's last known field is +0x18C and the
// screen's m_mode follows at +0x40C, so it spans exactly 0x190 bytes here.
class AptCreateAHero;

class AptMyHero
{
public:
	AptMyHero(AptCreateAHero *screen);
	virtual ~AptMyHero();
	void rva005B1288();
private:
	unsigned char m_opaque[0x18C];
};

// Rowed 0x005B23D7 in Code/GameEngine/Source/Common/AptHeroPowerText.cpp.
void __cdecl Rva005B23D7HeroPowersDescription(void *power, const AsciiString &unused, const AsciiString &fallback);

class Coord2D;
struct Rva005B3676Owner;
struct AppearanceOwner;
class Rva005B6B93;
class Rva005B2575;

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
	class Appearance
	{
	public:
		Appearance(AppearanceOwner *owner);
	private:
		unsigned char m_pad[0x10];
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
	void DrawMapComponent(const Coord2D *a, const Coord2D *b, void *c, void *d);	// rowed 0x00514070
	static void OpenScreen(int mode);
private:
	AptMyHero m_myHero; // +0x27C
	int m_mode; // +0x40C
	void *m_page; // +0x410
	void *m_previousPage; // +0x414
	Rva005B6B93 *m_pageM; // +0x418
	Class *m_pageC; // +0x41C
	Appearance *m_pageA; // +0x420
	Powers *m_pageP; // +0x424
	Rva005B2575 *m_pageB; // +0x428
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

// Retail 0x00513A47, 10 bytes: "AptCreateAHero::PrepareToTakePicture".
void AptCreateAHero::PrepareToTakePicture(const char *unused)
{
	m_pictureFrames = 0;
}

// Retail 0x00513A51, 19 bytes: "AptCreateAHero::OnTakePicture", once two
// frames have passed.
void AptCreateAHero::OnTakePicture(const char *unused)
{
	if (m_pictureFrames >= 2)
		m_takePicture = true;
}

// Retail 0x00513A64, 9 bytes: "CreateAHero::RenderPictureGuard" counts the
// frames drawn since PrepareToTakePicture.
void AptCreateAHero::RenderPictureGuard(const void *origin, const void *extent, void *unused3, void *unused4)
{
	++m_pictureFrames;
}

// Retail 0x00513A6D, 59 bytes: "CreateAHeroDemo", an Apt query answering
// "0" when TheGlobalData's +0x9D1 is set, else "1".
void AptCreateAHero::CreateAHeroDemo(int query, char *result, bool skip)
{
	if (result && query == 0 && !skip)
		_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>(((AptCreateAHeroGlobalData *)TheWritableGlobalData)->m_9d1 ? "0" : "1"));
}

// Retail 0x00513AF4, 23 bytes: bound as "CreateAHero"; hands the value to
// the current page's vslot 7 (a tail jump).
void AptCreateAHero::rva00513AF4(const char *value)
{
	if (m_page)
		reinterpret_cast<AptCreateAHeroPage *>(m_page)->v07(value);
}

// Retail 0x00513AA8, 19 bytes: "AptCreateAHero::RotateLeft".
void AptCreateAHero::RotateLeft(const char *pressed)
{
	m_rotateLeft = *pressed == 't';
}

// Retail 0x00513ABB, 19 bytes: "AptCreateAHero::RotateRight".
void AptCreateAHero::RotateRight(const char *pressed)
{
	m_rotateRight = *pressed == 't';
}

// Retail 0x00513ACE, 19 bytes: "AptCreateAHero::ZoomIn".
void AptCreateAHero::ZoomIn(const char *pressed)
{
	m_zoomIn = *pressed == 't';
}

// Retail 0x00513AE1, 19 bytes: "AptCreateAHero::ZoomOut".
void AptCreateAHero::ZoomOut(const char *pressed)
{
	m_zoomOut = *pressed == 't';
}

// Retail 0x005139B0, 151 bytes: "AptCreateAHero::OnShowScreen" switches to
// the page the value's first letter names (A, B, C, M or P), hiding the
// old one and showing the new.
void AptCreateAHero::OnShowScreen(const char *screen)
{
	AptCreateAHeroPage *previous = reinterpret_cast<AptCreateAHeroPage *>(m_page);
	switch (*screen)
	{
	case 'A':
		m_page = m_pageA;
		break;
	case 'B':
		m_page = m_pageB;
		break;
	case 'C':
		m_page = m_pageC;
		break;
	case 'M':
		m_page = m_pageM;
		break;
	case 'P':
		m_page = m_pageP;
		break;
	}
	if (previous != m_page)
	{
		m_previousPage = previous;
		if (previous)
			previous->hide();
		if (m_page)
			reinterpret_cast<AptCreateAHeroPage *>(m_page)->show();
		m_myHero.rva005B1288();
		Rva005B23D7HeroPowersDescription((void *)0, AsciiString::TheEmptyString, AsciiString::TheEmptyString);
	}
}

// Retail 0x00513CDF, 118 bytes: AptCreateAHero::OpenScreen (WorldBuilder,
// AptCreateAHero.cpp line 202; wb-name-unverified). Pushes CreateAHero.apt,
// loads the create-a-hero map and starts it, then hands the mode to the
// open screen.
void AptCreateAHero::OpenScreen(int mode)
{
	TheShell->push(AsciiString("CreateAHero.apt"), false);
	TheMessageStream->appendMessage(0x1D);
	((AptCreateAHeroGlobalData *)TheWritableGlobalData)->m_mapName.set("Maps\\CreateAHero\\CreateAHero.map");
	InitGameLogicRandom(0);
	GameMessage *msg = TheMessageStream->appendMessage(0x1E);
	msg->appendIntegerArgument(7);
	if (s_instance)
		s_instance->m_mode = mode;
}
