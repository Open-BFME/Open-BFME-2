// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
// ??0Rva005EA85A@@QAE@PAXHABVAsciiString@@@Z, retail 0x005EA7C6, 120 bytes.
// Derived ctor of Rva005EA85A: fetches region UnicodeString, derives ally and
// enemy counts by 36, builds base DynamicAutoResolveMovieClip then stores input
// at +8 and derived table C781DC. Evidence: leaf lane, caller 0x005EA89F,
// callee 0x005FC5F7 rowed in StrategicHUDDynamicAutoResolveMovieClip,
// fetch 0x0020E89C rowed, releaseBuffer rowed, vtable C781DC per next 0x005EA83E.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva0020E89C
{
public:
    UnicodeString rva0020E89C();
};

namespace StrategicHUD
{
class DynamicAutoResolveMovieClip
{
public:
    DynamicAutoResolveMovieClip(int level, const AsciiString &name, const UnicodeString &regionName, int numAllies, int numEnemies);
    virtual ~DynamicAutoResolveMovieClip();
    virtual void notifyOpen() = 0;
    virtual void notifyClosed() = 0;
    virtual void notifySkipButtonClicked() = 0;
    virtual void notifyAllyPanelLoaded(int index, int level, const AsciiString &name) = 0;
    virtual void notifyAllyPanelUnloaded(int index) = 0;
    virtual void notifyEnemyPanelLoaded(int index, int level, const AsciiString &name) = 0;
    virtual void notifyEnemyPanelUnloaded(int index) = 0;
private:
    void *m_impl;
};
}

struct Rva005EA7C6Host
{
    char m_pad[0x24];
    Rva0020E89C *m_fetcher;
};

struct Rva005EA7C6Input
{
    char m_pad00[0x0c];
    Rva005EA7C6Host *m_host;
    char m_pad10[0x10 - 0x04];
    int m_allyLo;
    int m_allyHi;
    char m_pad24[0x04];
    int m_enemyLo;
    int m_enemyHi;
};

struct EmitVtableTag;

static inline Rva0020E89C *Rva005EA7C6GetFetcher(void *input)
{
    return ((Rva005EA7C6Input *)input)->m_host->m_fetcher;
}

class Rva005EA85A : public StrategicHUD::DynamicAutoResolveMovieClip
{
public:
    Rva005EA85A(void *input, int level, const AsciiString &name);
    Rva005EA85A(EmitVtableTag *);
    virtual ~Rva005EA85A();
    virtual void notifyOpen() {}
    virtual void notifyClosed() {}
    virtual void notifySkipButtonClicked() {}
    virtual void notifyAllyPanelLoaded(int, int, const AsciiString &) {}
    virtual void notifyAllyPanelUnloaded(int) {}
    virtual void notifyEnemyPanelLoaded(int, int, const AsciiString &) {}
    virtual void notifyEnemyPanelUnloaded(int) {}
private:
    void *m_input;
};

Rva005EA85A::Rva005EA85A(void *input, int level, const AsciiString &name)
    : DynamicAutoResolveMovieClip(level, name, Rva005EA7C6GetFetcher(input)->rva0020E89C(),
        (((Rva005EA7C6Input *)input)->m_allyHi - ((Rva005EA7C6Input *)input)->m_allyLo) / 36,
        (((Rva005EA7C6Input *)input)->m_enemyHi - ((Rva005EA7C6Input *)input)->m_enemyLo) / 36)
    , m_input(input)
{
}

// ?<Rva005EA85A::Rva005EA85A> absent-from-retail
Rva005EA85A::Rva005EA85A(EmitVtableTag *) : DynamicAutoResolveMovieClip(0, AsciiString(), UnicodeString(), 0, 0), m_input(0)
{
}
