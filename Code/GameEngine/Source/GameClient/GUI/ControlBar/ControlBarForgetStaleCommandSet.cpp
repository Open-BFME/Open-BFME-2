// cl: /O1 /Oy- /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ControlBar.cpp WB 0x00C2D580: forgetStaleCommandSet; native 0x0031E879..0x0031E8D5.
// Native map cursor has {node, owner}; its value at node+8 is removed from
// map +0x30 and retained in the pointer vector +0x230; stale word +0x0C becomes 1.
// Existing cursor/find/erase owners retain their actual ledger spellings.
// The pointer append uses the existing ModuleData-pointer implementation;
// no inheritance or original vector instantiation is inferred from ICF.
#include "ascii_string.h"
#include <vector>
class ModuleData;
class Rva00056F61;
struct Rva0041534BIter {
    void *m_node;
    Rva00056F61 *m_table;
    Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61 {
public:
    Rva0041534BIter rva0041534B(const AsciiString *);
};
struct VideoPair {
    struct { void *first; void *second; } s;
    VideoPair(void *a, void *b) { s.first=a; s.second=b; }
    VideoPair(const Rva0041534BIter &p) { s.first=p.m_node; s.second=p.m_table; }
    VideoPair(const VideoPair &p) { s.first=p.s.first; s.second=p.s.second; }
};
class Rva000427195 { public: void rva003A37DC(VideoPair); };
struct StaleCommandSetView { char opaque00[0x0C]; int stale; };
struct CommandSetNodeView { void *next; AsciiString key; StaleCommandSetView *value; };
class ControlBar { public: void forgetStaleCommandSet(const AsciiString &); };
void ControlBar::forgetStaleCommandSet(const AsciiString &name)
{
    Rva00056F61 *table = (Rva00056F61 *)((char *)this+0x30);
    Rva0041534BIter it=table->rva0041534B(&name);
    if (it.m_node) {
        StaleCommandSetView *set=((CommandSetNodeView *)it.m_node)->value;
        ((Rva000427195 *)table)->rva003A37DC(VideoPair(it));
        if (set) {
            ((_STL::vector<const ModuleData *> *)((char *)this+0x230))->push_back(reinterpret_cast<const ModuleData *const &>(set));
            set->stale=1;
        }
    }
}
