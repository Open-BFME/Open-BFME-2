// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// BFME1 9cbfb55 INILightPointLevel.cpp supplies the semantic class guide.
// WB 0x010EE1D0 and retail 0x004212E4..0x00421312 prove initialization of
// the 36-byte light-point level: override link/flag/index, narrow/wide strings
// and vector<unsigned int>. Preserve Rva004211CA, the existing vtable and
// destructor owner. The actual STLport vector base constructor supplies the
// witnessed stack allocator temporary and all three zeroed pointers.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<unsigned int,allocator<unsigned int> >::~_Vector_base(); }
// The base constructor stays a nothrow call to its kept copy (0x00211E58).
namespace _STL { template <> _Vector_base<unsigned int,allocator<unsigned int> >::_Vector_base(const allocator<unsigned int> &) throw(); }
// vector<unsigned int>'s constructor and destructor inline at every use here;
// imported force-inline so this unit emits no COMDAT copies of them: its /O1
// copies differ from retail's kept /Od bodies (0x00025100 for the ctor).
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<unsigned int, allocator<unsigned int> >::vector(const allocator<unsigned int> &__a)
	: _Vector_base<unsigned int, allocator<unsigned int> >(__a) {}
template <> __declspec(dllimport) __forceinline
vector<unsigned int, allocator<unsigned int> >::~vector() { _Destroy(this->_M_start, this->_M_finish); }
}
namespace _STL { template <> void allocator<unsigned int>::deallocate(unsigned int *, unsigned int) const; }
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
#include "Common/INIException.h"
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
extern Rva00421520 *TheLightPointSystem;
#include "../../../Include/Common/Overridable.h"
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };
extern "C" {
void __identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva00339B50_ParseSpecialAbilities@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x0083BE74: 2 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C3BE74[3] = {
	{ "Name", (FieldParseProc)&__identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "SpecialAbilities", (FieldParseProc)&__identifier("?Rva00339B50_ParseSpecialAbilities@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ 0, 0, 0, 0 }
};
class INI
{
public:
    const char *getNextToken(const char * = 0);
    void initFromINI(void *, const FieldParse *);
    int pad[2];
    int loadType;
};
// ?friend_parseLightPointLevelDefinition@LightPointSystem@@SAXPAVINI@@@Z
// @0x00421572 (297B): parses one light-point level definition: clone-find via
// the rowed 0x00421263 with override-chain head swap, else fresh level; both
// feed initFromINI. Evidence: WB 0x10EDF90 branch structure + retail 297B;
// found reassigned (no separate base) to keep the ESI/EDI roles.
void LightPointSystem::friend_parseLightPointLevelDefinition(INI *ini)
{
    if (!TheLightPointSystem) return;
    AsciiString name(ini->getNextToken());
    if (ini->loadType == 2)
    {
        Rva004211CA *found = (Rva004211CA *)reinterpret_cast<const LightPointSystem *>(TheLightPointSystem)->rva00421263(
            (const Rva00421263Vec *)((char *)TheLightPointSystem + 12), *reinterpret_cast<const StringBase<char> *>(&name));
        if (!found) throw INIException(3, "Light point level %s not found in map.ini", name.str());
        Rva004211CA *level = new Rva004211CA;
        if (found->m_next) found = (Rva004211CA *)((Overridable *)found->m_next)->friend_getFinalOverride();
        *(Rva004213A2 *)level = *(const Rva004213A2 *)found;
        found->m_next = level;
        level->m_override = true;
        ini->initFromINI(level, g_00C3BE74);
    }
    else
    {
        Rva004211CA *level = new Rva004211CA;
        level->m_name = name;
        ini->initFromINI(level, g_00C3BE74);
        ((Rva004214C3 *)TheLightPointSystem)->rva004214C3((const ModuleData *)level);
    }
}
