// ??1Rva005173F8@@UAE@XZ
// partial score=0.94 date=2026-10-08
// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// WB AptOnlineShell::~AptOnlineShell at 0x0145BAD0 supplies the identity
// lead and member order. Retail 0x005173F8 independently proves the two
// vptrs at 0/218, screens at 280, strings at 28C/294, record at 29C,
// and the singleton cleanup calls. Keep the already pinned opaque ABI
// owner until the complete class identity is reconciled with its other views.
// Base prefixes and record layout reuse their separately matched destructors.
#include "ascii_string.h"
#include <vector>
namespace _STL {
template <> void **vector<void *, allocator<void *> >::erase(void **, void **);
}

class GameWindow {
public: GameWindow();
protected: virtual ~GameWindow();
private: unsigned char unknown[0x218 - 4];
};
class Rva005248D0 {
public: virtual ~Rva005248D0();
private: unsigned char unknown[0x58 - 4];
};
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0 {
public: virtual ~_bfme_AptGameWindow();
private: AsciiString filename270;
};
struct Rva00416088 {
    unsigned int m_00, m_04;
    AsciiString m_08, m_0C;
    ~Rva00416088();
};

struct AptOnlineSubScreen {
    virtual void *deleteInstance(int flags);
    virtual void v1();
    virtual void v2();
    unsigned char m_pad04[0x5C - 4];
    const char *m_name;
};

struct LANGameInfo;
extern LANGameInfo *g_Rva00E02EEC;
extern int g_Va00E04904;
void __cdecl TearDownGameSpy();
void __cdecl Rva00511F73Run();

class Rva005173F8 : public _bfme_AptGameWindow {
public:
    virtual ~Rva005173F8();
private:
    unsigned char m_pad274[0x280 - 0x274];
    _STL::vector<void *> m_screens;
    AsciiString m_pendingScreen;
    AptOnlineSubScreen *m_currentScreen;
    AsciiString m_currentName;
    unsigned int m_inviteState;
    Rva00416088 m_invite;
};

Rva005173F8::~Rva005173F8()
{
    for (_STL::vector<void *>::iterator i = m_screens.begin(); i != m_screens.end(); ++i) {
        AptOnlineSubScreen *screen = (AptOnlineSubScreen *)*i;
        void *allocation = 0;
        if (screen) allocation = screen->deleteInstance(0);
        ::operator delete(allocation);
    }
    m_screens.erase(m_screens.begin(), m_screens.end());
    if (g_Va00E04904 == (int)this) {
        TearDownGameSpy();
        g_Rva00E02EEC = 0;
        g_Va00E04904 = 0;
        Rva00511F73Run();
    }
}
