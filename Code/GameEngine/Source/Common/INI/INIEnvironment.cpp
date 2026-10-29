// cl: /GX /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
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
#include <map>

struct FieldParse;
class INI
{
public:
    const char *getNextToken(const char *separators = 0);
    void initFromINI(void *what, const FieldParse *fields);
    static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
};

struct FieldParse
{
    const char *token;
    void (*parse)(INI *, void *, void *, const void *);
    const void *userData;
    int offset;
};

// Retail's own five-record SkyboxTextureSet table, transcribed from .rdata at RVA
// 0x008082F0 (VA 0x00C082F0, file offset 0x008077F0): SkyboxTexture{N,E,S,W,T},
// each parsed with INI::parseAsciiString (rowed 0x0002F11E) into the five
// StringBase members of the 24-byte set at +4/+8/+0xC/+0x10/+0x14, a null
// user-data column throughout, then the zero terminator. `extern` on the
// definition keeps the table external, without which a const array at namespace
// scope takes MSVC internal linkage and leaves this unit's own reference to it
// unresolved.
extern const FieldParse g_00C082F0[];
const FieldParse g_00C082F0[] =
{
    { "SkyboxTextureN", &INI::parseAsciiString, 0, 4 },
    { "SkyboxTextureE", &INI::parseAsciiString, 0, 8 },
    { "SkyboxTextureS", &INI::parseAsciiString, 0, 12 },
    { "SkyboxTextureW", &INI::parseAsciiString, 0, 16 },
    { "SkyboxTextureT", &INI::parseAsciiString, 0, 20 },
    { 0, 0, 0, 0 }
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

struct NoCaseTreeValue4 {
    char m_body[4];
    NoCaseTreeValue4() { *(void **)m_body = 0; }
};
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;
class Rva000427195 {
public:
    void *rva0020D638(const NocasePair &src);
};
class Rva00056F61;
struct Rva0041534BIter {
    void *m_node;
    Rva00056F61 *m_table;
    Rva0041534BIter(void *n, Rva00056F61 *table) : m_node(n), m_table(table) {}
};

class Rva00056F61
{
public:
    void *rva00056F61(const AsciiString *key);
    // Same proven read-only exception contract as Rva00056F61IterFind.cpp.
    __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *key);
    // 0x0020D67C: 121-byte find-or-insert worker, thiscall/ret 4; returns
    // node+8, the pointer payload. WB 0x00B4FB10 confirms conditional pair
    // construction, insertion through 0x0020D638, and temporary-key cleanup.
    void *rva0020D67C(const AsciiString *key);
};

// Reuse the existing global's symbol from Rva007B6880Thunks.cpp.
extern unsigned int g_Va00DFF494;

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

// Native 0x0020D67C..0x0020D6F5 RET4; WB 0x00B4FB10 and the parser
// above prove name-keyed pointer-slot lookup/default insertion. The lookup
// has no C++ throws, so its iterator storage can end before the pair.
void *Rva00056F61::rva0020D67C(const AsciiString *key)
{
    void *node;
    {
        Rva0041534BIter found = rva0041534B(key);
        node = found.m_node;
    }
    return node == 0
        ? (char *)((Rva000427195 *)this)->rva0020D638(NocasePair(*key, NoCaseTreeValue4())) + 4
        : (char *)node + 8;
}

