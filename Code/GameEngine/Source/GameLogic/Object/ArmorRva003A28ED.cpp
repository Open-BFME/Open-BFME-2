// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva003A28ED@Rva003A28ED@@QAE_NW4NameKeyType@@@Z @ 0x003A28ED 86B
// Honest address name: __thiscall Armor-map remover beside ArmorHashMapErase.
// Target evidence: 86B retail, rowed hashtable clear 0x1DBCDC find 0x2888D4
// and hash_map erase 0x1E2861, 2 callers 0x3C0A61 0x3C4492, empty check at
// +0x14, -1 clears all else find+erase one, bool return. Prev/next are
// address neighbours, flags copied from ArmorHashMapErase sibling.
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
class Rva003A28ED
{
public:
    bool rva003A28ED(NameKeyType key);
private:
    char m_pad[0x11C];
    ArmorMapHolder *m_holder;
};
bool Rva003A28ED::rva003A28ED(NameKeyType key)
{
    ArmorMapHolder *holder = m_holder;
    if (holder->m_count == 0)
        return false;
    if (key == (NameKeyType)-1)
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
