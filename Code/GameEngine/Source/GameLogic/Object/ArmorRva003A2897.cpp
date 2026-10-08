// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva003A2897@Rva003A2897@@QAE_NW4NameKeyType@@@Z @ 0x003A2897 86B
// Honest address name: __thiscall Armor-map remover beside ArmorHashMapErase twin 0x003A28ED.
// Target evidence: 86B retail, rowed hashtable clear 0x1DBCDC find 0x2888D4
// and hash_map erase 0x1E2861, 3 callers 0x003A2CD0 0x003C0A24 0x003C0A58, empty check at
// +0x14, 0 clears all else find+erase one, bool return. Flags copied from ArmorRva003A28ED sibling.
#include <hash_map>
#include <cstddef>
enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    NAMEKEY_MAX = 1 << 23,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
namespace rts
{
template <typename T> struct hash
{
    size_t operator()(const T &value) const { return (size_t)value; }	// Zero Hour's rts::hash<NameKeyType>, inline
};
}
class ArmorTemplate
{
public:
    float m_damageCoefficient[38];
};
typedef std::hash_map<
    NameKeyType,
    ArmorTemplate,
    rts::hash<NameKeyType>,
    std::equal_to<NameKeyType> > ArmorTemplateMap;
struct ArmorMapHolder
{
    char m_pad[4];
    unsigned char m_mapSpace[0x10];
    int m_count;
    ArmorTemplateMap &map() { return *(ArmorTemplateMap *)m_mapSpace; }
};
class Rva003A2897
{
public:
    bool rva003A2897(NameKeyType key);
private:
    char m_pad[0x118];
    ArmorMapHolder *m_holder;
};
bool Rva003A2897::rva003A2897(NameKeyType key)
{
    ArmorMapHolder *holder = m_holder;
    if (holder->m_count == 0)
        return false;
    if (key == NAMEKEY_INVALID)
    {
        holder->map().clear();
        return true;
    }
    ArmorTemplateMap::iterator it = holder->map().find(key);
    if (it != holder->map().end())
    {
        m_holder->map().erase(it);
        return true;
    }
    return false;
}
