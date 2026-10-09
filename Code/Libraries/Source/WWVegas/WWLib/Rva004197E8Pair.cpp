// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/bfmealloc /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native 419789..4198EB: 60-byte value copy followed by string-key pair
// copies, placement construction and 68-byte hash-node creation. The key
// and member calls are target facts; original application identities remain
// unknown. Algorithms follow the verified neighbouring 41890F/41894C family.
#include <memory>
#include "Common/Rva00418A12StringHash.h"

struct Rva00419789Block { unsigned words[8]; };
struct Rva00419789
{
    Rva00419789(const Rva00419789 &other);
    ~Rva00419789();
    AsciiString m_00;
    Rva004188B6Part m_04;
    unsigned m_10;
    Rva00419789Block m_14;
    unsigned char m_34;
    unsigned m_38;
};
struct Rva004197E8
{
    Rva004197E8(const Rva004197E8 &other);
    Rva004197E8(const AsciiString &key, const Rva00419789 &value);
    AsciiString key;
    Rva00419789 value;
};
struct Rva004198C6Node
{
    Rva004198C6Node *next;
    Rva004197E8 value;
};
class Rva004198C6Host
{
public:
    void *newNode(const void *value);
};
typedef char Rva00419789Extent[sizeof(Rva00419789)==60?1:-1];
typedef char Rva004197E8Extent[sizeof(Rva004197E8)==64?1:-1];
typedef char Rva004198C6Extent[sizeof(Rva004198C6Node)==68?1:-1];

Rva00419789::Rva00419789(const Rva00419789 &other)
    : m_00(other.m_00), m_04(other.m_04), m_10(other.m_10),
      m_14(other.m_14), m_34(other.m_34), m_38(other.m_38)
{
}
Rva004197E8::Rva004197E8(const Rva004197E8 &other)
    : key(other.key), value(other.value)
{
}
Rva004197E8::Rva004197E8(const AsciiString &key, const Rva00419789 &value)
    : key(key), value(value)
{
}
void Rva0041985EConstruct(Rva004197E8 *output, const Rva004197E8 &value)
{
    new (output) Rva004197E8(value);
}
void *Rva004198C6Host::newNode(const void *value)
{
    Rva004198C6Node *node = reinterpret_cast<Rva004198C6Node *>(
        _STL::allocator<char>::allocate(sizeof(Rva004198C6Node), 0));
    node->next = 0;
    Rva0041985EConstruct(&node->value, *reinterpret_cast<const Rva004197E8 *>(value));
    return node;
}
