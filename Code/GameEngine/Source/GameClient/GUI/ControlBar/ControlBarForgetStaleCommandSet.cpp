// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2
// stlport
// ControlBar.cpp WB 0x00C2D580: forgetStaleCommandSet; native 0x0031E879..0x0031E8D5.
// Native map cursor has {node, owner}; its value at node+8 is removed from
// map +0x30 and retained in the pointer vector +0x230; stale word +0x0C becomes 1.
// Existing cursor/find/erase owners retain their actual ledger spellings.
// The pointer append uses the existing ModuleData-pointer implementation;
// no inheritance or original vector instantiation is inferred from ICF.
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
class ModuleData;
class Rva00056F61;
struct Rva0041534BIter
{
public:
	Rva0041534BIter(void *n,Rva00056F61 *t) : m_node(n),m_table(t) {}
	Rva0041534BIter(const Rva0041534BIter &it) : m_node(it.m_node),m_table(it.m_table) {}
	void *m_node; // +0x00
	Rva00056F61 *m_table; // +0x04
};
class Rva00056F61
{
public:
	__declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
	void *rva00056F61(const AsciiString *key);
};
struct VideoPair {
    struct { void *first; void *second; } s;
    VideoPair(void *a, void *b) { s.first=a; s.second=b; }
    VideoPair(const Rva0041534BIter &p) { s.first=p.m_node; s.second=p.m_table; }
    VideoPair(const VideoPair &videoPair) { s.first=videoPair.s.first; s.second=videoPair.s.second; }
};
class Rva000427195 { public: void rva003A37DC(VideoPair); };
struct StaleCommandSetView { char opaque00[0x0C]; int stale; };
struct CommandSetNodeView { void *next; AsciiString key; StaleCommandSetView *value; };
typedef bool Bool;
#include "subsystem_interface.h"
class ControlBar : public SubsystemInterface { public: void forgetStaleCommandSet(const AsciiString &); };
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
