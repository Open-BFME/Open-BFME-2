// cl: /O1 /G7 /Oy- /Ob2 /EHsc /MD /Ireference/shims/bfme2_ascii
// Native 0x0021386C..0x002138E5 RET4; the next CC is padding.
// WB b63e90 and CreateSound at 0x0021399A identify a name-keyed sound slot.
// The mapped word is at node+8 on a hit or insert-result+4 on a miss.
#include "ascii_string.h"
// Preserve the existing insert provider identity without asserting the opaque
// record layout of its donor instantiation. The caller supplies the proven
// eight-byte {AsciiString, pointer} object through its reference ABI.
struct Rva00212A16Record;
namespace _STL
{
template<class A, class B> struct pair;
template<class T> struct hash;
template<class T> struct _Select1st;
template<class T> struct equal_to;
template<class T> class allocator;
template<class V, class K, class H, class S, class E, class A> class hashtable
{
public:
    V &_M_insert(const V &);
};
}
typedef _STL::pair<const Rva00212A16Record, Rva00212A16Record> InsertPair;
typedef _STL::hashtable<InsertPair, Rva00212A16Record, _STL::hash<Rva00212A16Record>,
    _STL::_Select1st<InsertPair>, _STL::equal_to<Rva00212A16Record>,
    _STL::allocator<InsertPair> > InsertTable;
class Rva00056F61;
#include "../../../Include/GameClient/Rva0041534BIter.h"
struct SoundPair21386C
{
    AsciiString name;
    void *sound;
    SoundPair21386C(const AsciiString &asciiString, void *s) : name(asciiString), sound(s) {}
};
#include "../../../Include/GameClient/Rva00056F61.h"
void *Rva00056F61::rva0021386C(const AsciiString *key)
{
    void *node;
    {
        Rva0041534BIter found = rva0041534B(key);
        node = found.m_node;
    }
    return !node
        ? (char *)&((InsertTable *)this)->_M_insert(
            *(const InsertPair *)&static_cast<const SoundPair21386C &>(SoundPair21386C(*key, 0))) + 4
        : (char *)node + 8;
}


