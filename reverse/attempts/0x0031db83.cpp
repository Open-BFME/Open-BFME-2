// ?rva0031DB83@Rva000427195@@QAEPAPAXABVAsciiString@@@Z
// partial score=0.9752 date=2026-10-08
// cl: /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Native 0x0031DB83..0x0031DBFC; WB 0x00C318E0 gives the same find-or-insert
// expression. Existing table/insert owners retain their ledger identities.
#include "ascii_string.h"
#include <utility>
class Rva00056F61;
struct Rva0041534BIter {
    void *m_node; Rva00056F61 *m_table;
    Rva0041534BIter(void *n,Rva00056F61 *t) : m_node(n),m_table(t) {}
    Rva0041534BIter(const Rva0041534BIter &it) : m_node(it.m_node),m_table(it.m_table) {}
};
class Rva00056F61 { public: Rva0041534BIter rva0041534B(const AsciiString *); };
// Same four-byte payload as the insert owner's opaque byte view. Native
// default insertion initializes the whole word to zero, not an array loop.
struct NoCaseTreeValue4 { unsigned int m_value; NoCaseTreeValue4() : m_value(0) {} };
typedef _STL::pair<const AsciiString,NoCaseTreeValue4> Bef1Pair;
class Rva000427195 {
public:
    void *rva0031C7D6(const Bef1Pair &);
    void **rva0031DB83(const AsciiString &);
};
void **Rva000427195::rva0031DB83(const AsciiString &name)
{
    void *node;
    {
        Rva0041534BIter it=((Rva00056F61 *)this)->rva0041534B(&name);
        node=it.m_node;
    }
    return node==0
        ? (void **)((char *)rva0031C7D6(Bef1Pair(name,NoCaseTreeValue4()))+4)
        : (void **)((char *)node+8);
}
