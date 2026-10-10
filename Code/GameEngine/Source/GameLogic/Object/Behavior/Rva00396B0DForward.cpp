// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Native 0x00396A5C..0x00396B0D: 177B RET4 name-key lookup. The unnamed
// WorldBuilder counterpart 0x00EB8240 has the same two scoped string copies,
// signed-key map search and fallback. The existing 24B forwarder below supplies
// Object::getControllingPlayer's result, independently establishing Player*.
// Target fields: Player+0x58 is copied through StringBase<char>'s copy worker;
// the tree is at receiver+0x68 and its node's mapped string is at +0x14.
// NameAmount00396A5C models only the observed mapped prefix: its second word
// at node+0x18 is read by neighbouring 0x00396B25 as an unsigned money amount.
// No original owner/value name or unobserved value suffix is asserted here.
// Retail's fallback at VA 0x00C1A4B0 is the complete NUL-terminated "kq".
// The actual map specialization's _M_find is independently verified as the
// whole 56B signed-key fold at 0x00388F63, with no relocations. /O1 reproduces
// the shared EH prolog and both frame homes; the existing forwarder stays exact.
#include "ascii_string.h"
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T, L>& a,
                              const _Rb_tree_iterator<T, R>& b)
{ return a._M_node != b._M_node; }
}
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const AsciiString &);
    NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Player
{
public:
    char m_pad00[0x58];
    AsciiString m_name58;
};
struct NameAmount00396A5C { AsciiString m_name; unsigned int m_amount; };
typedef _STL::map<int,NameAmount00396A5C> NameAmountMap;
class Rva00396A5C
{
public:
    int rva00396A5C(Player *player);
private:
    char m_pad00[0x68];
    NameAmountMap m_map68;
};
int Rva00396A5C::rva00396A5C(Player *player)
{
    if (player) {
        AsciiString name(player->m_name58);
        int key = TheNameKeyGenerator->nameToKey(name);
        NameAmountMap::iterator it = m_map68.find(key);
        if (it != m_map68.end()) {
            AsciiString mapped(it->second.m_name);
            return TheNameKeyGenerator->nameToKey(mapped);
        }
    }
    return TheNameKeyGenerator->nameToKey("kq");
}

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class Rva00396B0D
{
public:
	int rva00396B0D(void);

private:
	char m_pad00[4];
	Rva00396A5C *m_lookup04;
	Object *m_object08;
};

int Rva00396B0D::rva00396B0D(void)
{
	Object *object = m_object08;
	Rva00396A5C *lookup = m_lookup04;
	return lookup->rva00396A5C(object->getControllingPlayer());
}
