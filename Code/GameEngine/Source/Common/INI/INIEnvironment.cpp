// cl: /GX /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?iniParseEnvironmentSkyboxTextureDefinition@@YAXPAVINI@@@Z @0x0020D6F5 177B.
// Target identity: WB 0x00B4F600 names this function and INIEnvironment.cpp;
// game.dat block registration 0x007AD845 binds "SkyboxTextureSet" to it.
// Target behavior: duplicate names return before allocation; a new 24-byte set
// is inserted, looked up again, and parsed. The table at VA 0x00C082F0 contains
// SkyboxTexture{N,E,S,W,T}, parseAsciiString 0x0002F11E, offsets 4..20, then zero.
// Donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/Common/INI/INISkyboxTextureSet.cpp. Compiling the clean
// donor under BFME2 settings placed no bodies; its parser supplied the semantic
// structure. Target adaptation uses BFME2's one-argument string set and existing
// address-named constructor/map workers. Their original class names are unknown.
#include "ascii_string.h"
#include <new>

struct FieldParse;
class INI
{
public:
    const char *getNextToken(const char *separators = 0);
    void initFromINI(void *what, const FieldParse *fields);
};

// Same 24-byte view as the verified constructor at 0x0020D4E3.
class Rva0020D583
{
public:
    Rva0020D583();
    virtual ~Rva0020D583();
private:
    StringBase<char> m_04, m_08, m_0c, m_10, m_14;
};

class Rva00056F61
{
public:
    void *rva00056F61(const AsciiString *key);
    // 0x0020D67C: 121-byte find-or-insert worker, thiscall/ret 4; returns
    // node+8, the pointer payload. WB 0x00B4FB10 confirms conditional pair
    // construction, insertion through 0x0020D638, and temporary-key cleanup.
    void *rva0020D67C(const AsciiString *key);
};

// Reuse the existing global's symbol from Rva007B6880Thunks.cpp.
extern unsigned int g_Va00DFF494;
extern const FieldParse g_00C082F0[];

void iniParseEnvironmentSkyboxTextureDefinition(INI *ini)
{
    AsciiString name;
    ((StringBase<char> *)&name)->set(ini->getNextToken());
    Rva00056F61 *sets = (Rva00056F61 *)&g_Va00DFF494;
    if (sets->rva00056F61(&name))
        return;

    Rva0020D583 *set = new Rva0020D583();
    *(Rva0020D583 **)sets->rva0020D67C(&name) = set;
    Rva0020D583 *stored = *(Rva0020D583 **)sets->rva0020D67C(&name);
    ini->initFromINI(stored, g_00C082F0);
}
