// ?rva0073F170@AsyncServiceQueue@@QAE?AVRva0036CA00Str@@PAUListNode0073EFFC@@@Z
// partial score=0.9740932642487047 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc
// stlport
// Native73F170..73F231 RET8 returns an owning reference after removing an
// uncancelled node. WB AsyncServiceQueue enqueue supplies subsystem identity;
// target proves list08/count04/mutex0C/event14 and twelve-byte payload.
#include <list>
class OpaqueRefCounted {public:void Release_Ref();};
class Rva0036CA00Str {public:
 Rva0036CA00Str():m_item(0){}
 __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
 ~Rva0036CA00Str(){if(m_item)((OpaqueRefCounted *)m_item)->Release_Ref();}
 void *m_item;
};
struct Rva0073EEE0ListValue {
 Rva0036CA00Str helperManagedPointer;unsigned unknown_04;void *handle_08;
 Rva0073EEE0ListValue(const Rva0073EEE0ListValue &);
 __declspec(noinline) ~Rva0073EEE0ListValue();
};
typedef _STL::list<Rva0073EEE0ListValue> TargetListAt0073EEE0;
namespace _STL {template<> __declspec(noinline) TargetListAt0073EEE0::iterator TargetListAt0073EEE0::erase(TargetListAt0073EEE0::iterator);}
struct ListNode0073EFFC {ListNode0073EFFC *next,*previous;Rva0073EEE0ListValue value;};
class MilesMutexGuard {public:MilesMutexGuard(void *,int);~MilesMutexGuard();void *mutex;bool held;};
class Rva0040F9D {public:bool reset();char bytes[8];};
class AsyncServiceQueue {public:
 Rva0036CA00Str rva0073F170(ListNode0073EFFC *node);
 int active,count;TargetListAt0073EEE0 queued;char mutex[8];Rva0040F9D available;
};
Rva0036CA00Str AsyncServiceQueue::rva0073F170(ListNode0073EFFC *node)
{
 MilesMutexGuard guard(mutex,0);
 if(node->value.unknown_04)return Rva0036CA00Str();
 TargetListAt0073EEE0::iterator where((_STL::_List_node<Rva0073EEE0ListValue> *)node);
 Rva0036CA00Str item(where->helperManagedPointer);
 queued.erase(where);
 --count;
 if(queued.empty())available.reset();
 return item;
}
