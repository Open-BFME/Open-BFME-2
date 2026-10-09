// ?friend_parseLightPointLevelDefinition@LightPointSystem@@SAXPAVINI@@@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/shims/iniexception
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/INIException.h"
#include <vector>
class Rva004211CA;
class LightPointOverrideFields
{
public:
    LightPointOverrideFields() : m_next(0), m_override(false), m_index(-1) {}
    Rva004211CA *m_next;
    bool m_override;
    int m_index;
};
class Rva004211CA : public LightPointOverrideFields
{
public:
    Rva004211CA();
    virtual ~Rva004211CA();
    AsciiString m_name;
    UnicodeString m_label;
    _STL::vector<unsigned int> m_values;
};
Rva004211CA::Rva004211CA() : m_name(), m_label(), m_values() {}
class ModuleData;
struct Rva00421263Vec { const ModuleData **begin, **end; };
class INI;
class LightPointSystem
{
public:
    const ModuleData *rva00421263(const Rva00421263Vec *, const StringBase<char> &) const;
    static void friend_parseLightPointLevelDefinition(INI *ini);
};
class Rva004213A2 { public: Rva004213A2 &operator=(const Rva004213A2 &); };
class Rva004214C3 { public: void rva004214C3(const ModuleData *); };
class Rva00421520;
extern Rva00421520 *g_00E03158;
class Overridable { public: Overridable *friend_getFinalOverride(); };
struct FieldParse;
extern const FieldParse g_00C3BE74[];
class INI
{
public:
    const char *getNextToken(const char * = 0);
    void initFromINI(void *, const FieldParse *);
    int pad[2];
    int loadType;
};

void LightPointSystem::friend_parseLightPointLevelDefinition(INI *ini)
{
    if (!g_00E03158) return;
    AsciiString name(ini->getNextToken());
    if (ini->loadType == 2)
    {
        Rva004211CA *found = (Rva004211CA *)reinterpret_cast<const LightPointSystem *>(g_00E03158)->rva00421263(
            (const Rva00421263Vec *)((char *)g_00E03158 + 12), *reinterpret_cast<const StringBase<char> *>(&name));
        if (!found) throw INIException(3, "Light point level %s not found in map.ini", name.str());
        Rva004211CA *level = new Rva004211CA;
        Rva004211CA *base = found;
        if (found->m_next) base = (Rva004211CA *)((Overridable *)found->m_next)->friend_getFinalOverride();
        *(Rva004213A2 *)level = *(const Rva004213A2 *)base;
        base->m_next = level;
        level->m_override = true;
        ini->initFromINI(level, g_00C3BE74);
    }
    else
    {
        Rva004211CA *level = new Rva004211CA;
        level->m_name = name;
        ini->initFromINI(level, g_00C3BE74);
        ((Rva004214C3 *)g_00E03158)->rva004214C3((const ModuleData *)level);
    }
}
