// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// The297B destructor, WB AptCreateAHero callgraph, constructor5142B0
// and both retail vptrs C65D20/C65D1C establish the owner. Exact native
// accesses establish the consumed member layout; the constructor proves
// the trailing flags and full438B storage extent used here.
// Use the constructor-owned s_instance datum (RVA A048D4 / VA E048D4).
// The old separate address-named declaration is removed. Original names
// of saved preview flags and the remaining manager method stay unresolved.
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
	int RemoveCustomRender(const AsciiString *name);
};
class AptPlayer;
// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct DestructorGlobalData
{
	unsigned char m_pad000[0x68];
	bool m_enableBehindBuildingMarkers;
	unsigned char m_pad069[0x9A5 - 0x69];
	bool m_showSelectedUnitMarker;
	unsigned char m_pad9a6[0x9BD - 0x9A6];
	bool m_showObjectHealth;
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
	char m_pad00[0x184];
	bool m_184; // +0x184
};
extern CreateAHeroManager *TheCreateAHeroManager;
extern bool skipCinematicSubsystemExclusions; // VA 0x00DFD944

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

AptCreateAHero::~AptCreateAHero()
{
	TheTransitionHandler->slot9();
	if (s_instance == this)
	{
		for (int i = 0; i < 5; ++i)
		{
			::delete (*reinterpret_cast<CreateAHeroPage *(*)[5]>(&m_pageM))[i];
			(*reinterpret_cast<CreateAHeroPage *(*)[5]>(&m_pageM))[i] = 0;
		}
		{
			AsciiString name("CreateAHero::DrawMapComponent");
			((Rva002246B1 *)reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager))->RemoveCustomRender(&name);
		}
		TheGlobalDataView->m_enableBehindBuildingMarkers = m_42e;
		TheGlobalDataView->m_showSelectedUnitMarker = true;
		TheGlobalDataView->m_showObjectHealth = m_42c;
		TheGlobalDataView->m_D45 = m_42d;
		skipCinematicSubsystemExclusions = m_42d;
		TheCreateAHeroManager->rva0021F5F8();
		TheCreateAHeroManager->m_184 = false;
		s_instance = 0;
	}
}
