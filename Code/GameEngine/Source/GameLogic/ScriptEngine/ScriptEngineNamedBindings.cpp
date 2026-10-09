// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// STLport map source is primary guide (same reference family as target
// named lookup and rowed TeamLess tree). Retail208968/208B2C independently
// construct (receiver1A10C,name), insert zero into 190B8/190C4 and replace
// mapped dword with Object74/Team34. Their original method names remain
// unknown; the target containers and field access establish these roles.
#include <map>
#include "ascii_string.h"
typedef _STL::pair<AsciiString, AsciiString> NameKey;
typedef _STL::pair<const NameKey, int> NameValue;
struct TeamLess0019B850 : _STL::less<NameKey> {};
typedef _STL::map<NameKey, int, TeamLess0019B850> NameMap;
class Object
{
public:
    int getID() const { return m_id; }
private:
    char m_before[0x74];
    int m_id;
};
class Team
{
public:
    int getID() const { return m_id; }
private:
    char m_before[0x34];
    int m_id;
};
class ScriptEngine
{
public:
    void rva00208968(const AsciiString &name, Object *object);
    void rva00208B2C(const AsciiString &name, Team *team);
private:
    char m_beforeMaps[0x190B8];
    NameMap m_objects;
    NameMap m_teams;
    char m_beforeScope[0x1A10C - 0x190B8 - 24];
    AsciiString m_scope;
};
void ScriptEngine::rva00208968(const AsciiString &name, Object *object)
{
    NameKey key(m_scope, name);
    NameMap::iterator it = m_objects.insert(_STL::make_pair(key, 0)).first;
    it->second = object->getID();
}
void ScriptEngine::rva00208B2C(const AsciiString &name, Team *team)
{
    NameKey key(m_scope, name);
    NameMap::iterator it = m_teams.insert(_STL::make_pair(key, 0)).first;
    it->second = team->getID();
}
