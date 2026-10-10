// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ??1Rva00513BAB@@UAE@XZ, retail 0x00513BAB..0x00513CD4 (297 bytes, EH). The
// create-a-hero screen's destructor (the class AptCreateAHero of
// AptCreateAHeroConstructor.cpp, whose deleting destructor 0x00513DB4 keeps
// the address-derived name Rva00513BAB; vtables 0x00C65D20 / 0x00C65D1C).
// It stops the transition handler, and when this is the live screen
// (0x00A048D4): deletes the five pages at +0x418, removes the
// "CreateAHero::DrawMapComponent" renderer, restores the preview flags it
// saved at +0x42C..+0x42E into the global data, resets the hero manager and
// clears the singleton; then the hero (+0x27C) and the Apt window base go.
#include "ascii_string.h"

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

class AptMyHero
{
public:
	virtual ~AptMyHero();
private:
	unsigned char m_opaque[0x18C];
};

class CreateAHeroPage
{
public:
	virtual ~CreateAHeroPage();
};

class GameWindowTransitionsHandler
{
public:
#define V(n) virtual void slot##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
#undef V
	virtual void slot9();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva002246B1
{
public:
	int rva002246B1(const AsciiString *name);
};
extern class AptPlayer *TheAptPlayer;

struct DestructorGlobalData
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
class GlobalData;
extern GlobalData *TheWritableGlobalData;
#define TheGlobalDataView ((DestructorGlobalData *)TheWritableGlobalData)

class CreateAHeroManager
{
public:
	void rva0021F5F8();
	unsigned char m_pad[0x184];
	bool m_184;
};
extern CreateAHeroManager *TheCreateAHeroManager;
extern unsigned char g_Va00DFD944;

class Rva00513BAB;
extern Rva00513BAB *g_Va00E048D4;

class Rva00513BAB : public _bfme_AptGameWindow
{
public:
	virtual ~Rva00513BAB();
private:
	AptMyHero m_myHero; // +0x27C
	int m_mode; // +0x40C
	void *m_page; // +0x410
	void *m_previousPage; // +0x414
	CreateAHeroPage *m_pages[5]; // +0x418
	bool m_42c;
	bool m_42d;
	bool m_42e;
};

Rva00513BAB::~Rva00513BAB()
{
	TheTransitionHandler->slot9();
	if (g_Va00E048D4 == this)
	{
		for (int i = 0; i < 5; ++i)
		{
			::delete m_pages[i];
			m_pages[i] = 0;
		}
		{
			AsciiString name("CreateAHero::DrawMapComponent");
			((Rva002246B1 *)TheAptPlayer)->rva002246B1(&name);
		}
		TheGlobalDataView->m_68 = m_42e;
		TheGlobalDataView->m_9A5 = true;
		TheGlobalDataView->m_9BD = m_42c;
		TheGlobalDataView->m_D45 = m_42d;
		g_Va00DFD944 = m_42d;
		TheCreateAHeroManager->rva0021F5F8();
		TheCreateAHeroManager->m_184 = false;
		g_Va00E048D4 = 0;
	}
}
