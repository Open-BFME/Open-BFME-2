// cl: /O1 /G7 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/stlp_nodealloc
// stlport
// Native73F170..73F231 removes a queued12-byte record under mutex0C.
// WB queue enqueue plus existing owner/callers establish AsyncServiceQueue;
// original element meaning remains unresolved. Record0 is an atomically copied
// owning pointer and record4 controls early return. Layout count4/list8/event14
// is native evidence. Visible noinline31B reference copy closes the item and
// list erase return temporary-home swap; both helpers31/42 are independently
// byte-and-relocation exact and already owned in their original units.
#include <memory>
#include <list>
#include <utility>

// Neutral target layout view for the list element copied at 0x73EEE0.
// Target evidence establishes the helper-managed refcounted pointer at +0,
// an otherwise unknown dword at +4, and a handle at +8 whose pointee count
// is incremented at +0xC when non-null. Donor BridgeFXInfo semantics remain
// a provenance hypothesis, not a target identity claim.
class OpaqueRefCounted { public: void Release_Ref(); };
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
class Rva0036CA00Str {
public:
    Rva0036CA00Str() : m_item(0) {}
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
    ~Rva0036CA00Str() { if (m_item) ((OpaqueRefCounted *)m_item)->Release_Ref(); }
    void *m_item;
};
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
inline __declspec(noinline) __declspec(nothrow) Rva0036CA00Str::Rva0036CA00Str(const Rva0036CA00Str &other):m_item(other.m_item){if(m_item)InterlockedIncrement((long volatile*)((char*)m_item+4));}
struct TargetNestedHandleData { unsigned char Unknown[12]; unsigned int RefCount; };
struct TargetNestedHandle { TargetNestedHandleData *item; };
struct Rva0073EEE0ListValue {
    Rva0036CA00Str helperManagedPointer;
    unsigned int unknown_04;
    TargetNestedHandle handle_08;
    Rva0073EEE0ListValue() {handle_08.item=0;}
    Rva0073EEE0ListValue(const Rva0073EEE0ListValue &other);
    __declspec(noinline) ~Rva0073EEE0ListValue();
};
typedef std::list<Rva0073EEE0ListValue> TargetListAt0073EEE0;
extern "C" void __cdecl free(void *p);
struct ListNode0073EFFC {
    ListNode0073EFFC *m_next;
    ListNode0073EFFC *m_prev;
    Rva0073EEE0ListValue m_value;
};
namespace _STL {
template<> __declspec(noinline) TargetListAt0073EEE0::iterator TargetListAt0073EEE0::erase(TargetListAt0073EEE0::iterator where) {
 ListNode0073EFFC *pNode=(ListNode0073EFFC*)where._M_node;
 ListNode0073EFFC *pNext=pNode->m_next;
 ListNode0073EFFC *pPrev=pNode->m_prev;
 pPrev->m_next=pNext;
 pNext->m_prev=pPrev;
 pNode->m_value.~Rva0073EEE0ListValue();
 free(pNode);
 return TargetListAt0073EEE0::iterator((_STL::_List_node<Rva0073EEE0ListValue>*)pNext);
}
}

class MilesMutexGuard {public: MilesMutexGuard(void*,int);~MilesMutexGuard();void *mutex;bool held;};
class Rva0040F9D {public:bool set();bool reset();char bytes[8];};
class Rva0073EE21 {public:Rva0073EE21();char bytes[16];};
struct OpaqueRefElement4 {void *item;OpaqueRefElement4 &operator=(const OpaqueRefElement4&);};
class AsyncServiceQueue {
 public:
 TargetListAt0073EEE0::iterator enqueue(Rva0036CA00Str item);
 Rva0036CA00Str rva0073F170(TargetListAt0073EEE0::iterator where);

 int active,count; TargetListAt0073EEE0 queued; char mutex[8];Rva0040F9D available;TargetListAt0073EEE0 secondary;Rva0040F9D completed;Rva0040F9D drained;
};
// Native73F170..73F231: locked removal returns the owned helper reference.
// A nonzero element word04 leaves the queue untouched and returns null.
Rva0036CA00Str AsyncServiceQueue::rva0073F170(TargetListAt0073EEE0::iterator where){
 MilesMutexGuard guard(mutex,0);
 if(where->unknown_04)return Rva0036CA00Str();
 Rva0036CA00Str item(where->helperManagedPointer);
 queued.erase(where);
 --count;
 if(queued.empty())available.reset();
 return item;
}
