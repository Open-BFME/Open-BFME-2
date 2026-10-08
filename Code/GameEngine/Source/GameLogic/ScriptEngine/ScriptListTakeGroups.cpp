// cl: /O1 /G7 /arch:SSE /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /DNDEBUG /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB Scripts.cpp provides pointer-to-list argument semantics and named
// doTakeGroup/takeGroup/takeGroups; retail proves measured offsets and
// extents. takeScripts is now recovered separately in BfmeOwnerZKRelink.cpp.
//
// ?takeGroups@ScriptList@@QAEXPAV1@PAPAUScriptGroupLink@@1@Z, retail
// 0x003B7DAC (141 bytes, EH, RET 12): collect the address of every link of
// the source chain in a deque, then take each group from the back through
// doTakeGroup. ?takeGroup@ScriptList@@... retail 0x003B8A9B (48 bytes, RET
// 20): find the group in the chain and take it to the given slot (or the
// fallback). doTakeGroup (0x003B89C9, 210 bytes) is not yet rowed; its WB
// name is pinned.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
struct BfmeScriptSlotAddress { unsigned int address; };
namespace _STL {
template<> struct __type_traits<BfmeScriptSlotAddress> : __type_traits_aux<1> {};
}
#include <deque>



struct ScriptGroupLink { ScriptGroupLink *next; int index; int link; };
struct BfmeNodeZK;
struct ScriptEntryLink { ScriptEntryLink *next; int index; int link; };
struct ScriptSetRecord { char prefix[14]; short references; void *nodes; };
class Rva003B573E {
public:
    int rva003B7F8E(Rva003B573E *other,int index);
    char prefix[12]; ScriptSetRecord *records; char suffix[16];
};
class Rva003B40A1Holder { public: void *captureGroup(void *record); };
struct CapturedGroup { int unknown; ScriptGroupLink *groups; ScriptEntryLink *scripts; };
class BfmeKeyZK;
struct BfmeNodeZK;
class BfmeOwnerZK { public: void bfmeMoveZK(BfmeKeyZK*,BfmeNodeZK**,BfmeNodeZK**); };
class ScriptList {
public:
    __declspec(noinline) void doTakeGroup(ScriptList *source,ScriptGroupLink **from,ScriptGroupLink **to);
    __declspec(noinline) void takeGroups(ScriptList *source,ScriptGroupLink **from,ScriptGroupLink **to);
    __declspec(noinline) void takeScripts(ScriptList *source,BfmeNodeZK **from,BfmeNodeZK **to);
    void takeGroup(ScriptList *source,ScriptGroupLink **head,ScriptGroupLink *group,ScriptGroupLink **fallback,ScriptGroupLink **where);
    int unknown; ScriptGroupLink *groups; ScriptEntryLink *scripts;
    Rva003B573E groupSet; char scriptSet[32];
};
void ScriptList::takeGroup(ScriptList *source,ScriptGroupLink **head,ScriptGroupLink *group,ScriptGroupLink **fallback,ScriptGroupLink **where)
{
    ScriptGroupLink **slot=head;
    while(*slot != group) {
        if(!*slot) return;
        slot=&(*slot)->next;
    }
    doTakeGroup(source,slot,where?where:fallback);
}
void ScriptList::takeGroups(ScriptList *source,ScriptGroupLink **from,ScriptGroupLink **to)
{
    _STL::deque<BfmeScriptSlotAddress> slots;
    BfmeScriptSlotAddress slot;
    slot.address=reinterpret_cast<unsigned int>(from);
    for(;*reinterpret_cast<ScriptGroupLink**>(slot.address);slot.address=reinterpret_cast<unsigned int>(&(*reinterpret_cast<ScriptGroupLink**>(slot.address))->next))
        slots.push_back(slot);
    while(!slots.empty()) {
        doTakeGroup(source,reinterpret_cast<ScriptGroupLink**>(slots.back().address),to);
        slots.pop_back();
    }
}
