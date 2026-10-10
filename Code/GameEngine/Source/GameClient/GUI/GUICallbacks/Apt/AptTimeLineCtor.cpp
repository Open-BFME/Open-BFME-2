// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005202C8@@QAE@PAX@Z
// Retail 0x005202C8..0x005204E4 (540 bytes).
// The time line (post-game graph) screen constructor: WorldBuilder twin
// AptTimeLine::AptTimeLine (AptTimeLine.cpp:104-118) with the same member
// stores; the AptTimeline* image names and the "Should only be one!"
// singleton check identify it. Base _bfme_AptGameWindow 0x0051268C;
// vtables 0x00C675DC and 0x00C675D8 (+0x218); members: player vector
// +0x288 (dtor 0x0052012B) / focus vector +0x2B8 resized to 8 x 1.0 through
// 0x0030E910 / Rva0051C0E7 +0x2C4; s_instance at VA 0x00E0491C; the stats
// object Rva005BEA06 (0x18 bytes) at +0x280; status images at +0x298..
// +0x2AC through findImageByName 0x002D92F6; then the window manager's
// background call 0x002233A6. Caller: factory 0x002D2147 (0x2F4 bytes).
#include <vector>
#include <string.h>
#include "ascii_string.h"

class GameWindow
{
public:
	GameWindow();
protected:
	virtual ~GameWindow();
private:
	unsigned char unknown[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	unsigned char unknown[0x58 - 4];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString filename270;
	unsigned char m_pad274[8];
};

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

// The Apt window manager (0x00DFE4CC) and its background switch 0x002233A6.
class Rva00222A8BTarget
{
public:
	void rva002233A6(int);
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva005BEA06
{
public:
	Rva005BEA06();
private:
	unsigned char m_pad[0x18];
};

struct Rva0051C0E7
{
	Rva0051C0E7();
	~Rva0051C0E7();
	unsigned char m_pad[0x30];
};

struct Rva00520211Element
{
	~Rva00520211Element();
};

struct RvaVector
{
	void rva0030E910(unsigned n, float value);
};

class Rva005202C8 : public _bfme_AptGameWindow
{
public:
	enum { PS_VICTORIOUS, PS_DEFEATED, PS_DISCONNECTED, PS_COUNT = 4 };
	Rva005202C8(void *context);
	virtual ~Rva005202C8();
	static Rva005202C8 *s_instance;
private:
	int m_27C;
	Rva005BEA06 *m_stats;			// +0x280
	int m_284;
	_STL::vector<Rva00520211Element> m_players;	// +0x288
	bool m_294;
	const Image *m_imagePlayerStatus[PS_COUNT];	// +0x298
	const Image *m_imageFortressBuilt;	// +0x2A8
	const Image *m_imageRegionsUnited;	// +0x2AC
	float m_2B0;
	int m_2B4;
	_STL::vector<int> m_focus;		// +0x2B8
	Rva0051C0E7 m_2C4;
};

Rva005202C8::Rva005202C8(void *context)
	: _bfme_AptGameWindow(context)
	, m_27C(0)
	, m_stats(0)
	, m_284(0)
	, m_294(false)
	, m_imageFortressBuilt(0)
	, m_imageRegionsUnited(0)
	, m_2B0(-1.0f)
	, m_2B4(-1)
{
	if (s_instance)
		return;
	s_instance = this;
	m_stats = new Rva005BEA06;
	memset(m_imagePlayerStatus, 0, sizeof(m_imagePlayerStatus));
	((RvaVector *)&m_focus)->rva0030E910(8, 1.0f);
	if (TheMappedImageCollection)
	{
		m_imagePlayerStatus[PS_VICTORIOUS] = TheMappedImageCollection->findImageByName("AptTimelineVictorious");
		m_imagePlayerStatus[PS_DEFEATED] = TheMappedImageCollection->findImageByName("AptTimelineDefeated");
		m_imagePlayerStatus[PS_DISCONNECTED] = TheMappedImageCollection->findImageByName("AptTimelineDisconnected");
		m_imageFortressBuilt = TheMappedImageCollection->findImageByName("AptTimelineFortress");
		m_imageRegionsUnited = TheMappedImageCollection->findImageByName("AptTimelineTakeTerritory");
	}
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva002233A6(1);
}

// ??1Rva005202C8@@UAE@XZ, retail 0x005204EF..0x005205CF (224 bytes, EH):
// the time line screen's destructor (scalar deleting destructor 0x005206E2,
// table 0x00C675DC slot 0; pinned there as ??1Rva005204EF). It empties the
// static list at 0x00E04920 through its rowed range erase, hides the shell
// for modes 1 and 8, deletes the stats object (rowed destructor 0x005BEA22),
// runs the unrowed mode-1 reset 0x00521260, clears s_instance, then the
// members and the base die: +0x2C4, the focus vector, the player vector
// (rowed 0x0052012B) and _bfme_AptGameWindow.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> inline _Vector_base<int, allocator<int> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
}

class Shell
{
public:
	void rva0035BF4C(bool show);
};
extern Shell *TheShell;

struct Rva005334A4Element
{
	unsigned char m_data[0x10];
};
namespace _STL {
template<> vector<Rva005334A4Element>::iterator vector<Rva005334A4Element>::erase(iterator first, iterator last);
}
extern _STL::vector<Rva005334A4Element> g_Va00E04920;

class Rva005BEA22
{
public:
	~Rva005BEA22();
};

void Rva00521260Reset();

Rva005202C8::~Rva005202C8()
{
	g_Va00E04920.erase(g_Va00E04920.begin(), g_Va00E04920.end());
	if (m_284 == 1 || m_284 == 8)
	{
		if (TheShell)
			TheShell->rva0035BF4C(false);
	}
	delete reinterpret_cast<Rva005BEA22 *>(m_stats);
	m_stats = 0;
	if (m_284 == 1)
		Rva00521260Reset();
	s_instance = 0;
}
