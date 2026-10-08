// ?rva0020D67C@Rva00056F61@@QAEPAXPBVAsciiString@@@Z
// partial score=0.9752 date=2026-10-08
// cl: /O1 /GX /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "ascii_string.h"
#include <map>

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
    Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61 {
public:
    Rva0041534BIter rva0041534B(const AsciiString *key);
    void *rva0020D67C(const AsciiString *key);
};

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
