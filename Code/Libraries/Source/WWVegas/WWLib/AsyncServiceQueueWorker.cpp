// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/stlp_nodealloc
// platformsdk
// stlport
// Native constructor73F708 starts callback73F6FC with this same16B owner.
// Its holder4 and event8 establish stop handleC; retain the existing owner name.
// The local waitResult and visible STLport splice/destructor reproduce native
// sentinel caching and return path. STLport4.5.3 _list.h is the donor; the
// worker control flow and owned12B record layout are reconstructed from retail.
// Native full worker73F55C..73F6FC is416B, not the old228B fragment.
// Catch funclet73F640 returns continuation73F646; thread entry73F6FC calls
// the worker and RET4. Existing AsyncServiceQueue enqueue/removal sources
// prove the 12B owning record and queue fields; native verifies mutex20.
#include <list>
#include <windows.h>
class OpaqueRefCounted {public:void Release_Ref();};
class Rva0036CA00Str {public:void *m_item;Rva0036CA00Str():m_item(0){}Rva0036CA00Str(const Rva0036CA00Str&);~Rva0036CA00Str(){if(m_item)((OpaqueRefCounted*)m_item)->Release_Ref();}};
struct TargetNestedHandleData {char pad[12];unsigned count;};
struct TargetNestedHandle {TargetNestedHandleData *item;};
struct Rva0073EEE0ListValue {Rva0036CA00Str helperManagedPointer;unsigned unknown_04;TargetNestedHandle handle_08;Rva0073EEE0ListValue();Rva0073EEE0ListValue(const Rva0073EEE0ListValue&);~Rva0073EEE0ListValue();};
typedef _STL::list<Rva0073EEE0ListValue> WorkList;
namespace _STL {

// STLport4.5.3 _list.h single-node splice; keep real body visible.
template<> __declspec(noinline) void WorkList::splice(iterator position,list&,iterator item){
 iterator next=item;++next;
 if(position._M_node==item._M_node||position._M_node==next._M_node)return;
 _List_global_inst::_Transfer(position._M_node,item._M_node,next._M_node);
}
}
class MilesMutexGuard {public:MilesMutexGuard(void*,int);~MilesMutexGuard();void *mutex;bool held;};
class Rva0040F9D {public:bool set();bool reset();char pad[4];HANDLE handle;};
class WorkOperation {public:virtual void slot0();virtual void run();};
struct AsyncQueueWorkerOwner {int active,count;WorkList queued;char mutexC[8];Rva0040F9D available;WorkList secondary;char m_secondaryMutex[8];Rva0040F9D drained;};
class Rva0073F708 {
public:AsyncQueueWorkerOwner *owner;char pad4[8];HANDLE stopHandle;unsigned run();
};
unsigned Rva0073F708::run(){
 for(;;){
  HANDLE handles[2]={stopHandle,owner->available.handle};
  DWORD waitResult=WaitForMultipleObjects(2,handles,0,0xffffffff);
  if(waitResult==0)return 0;
  WorkList pending;
  {
   MilesMutexGuard lock(owner->mutexC,0);
   if(owner->queued.empty())continue;
   pending.splice(pending.end(),owner->queued,owner->queued.begin());
   if(owner->queued.empty())owner->available.reset();
   pending.front().unknown_04=1;
  }
  Rva0073EEE0ListValue &item=pending.front();
  try {((WorkOperation*)item.helperManagedPointer.m_item)->run();}catch(...){}
  {
   MilesMutexGuard lock(owner->m_secondaryMutex,0);
   if(owner->active==1){
    bool wasEmpty=owner->secondary.empty();
    owner->secondary.splice(owner->secondary.end(),pending,pending.begin());
    if(wasEmpty)owner->drained.set();
   }
   item.unknown_04=2;
   ((Rva0040F9D*)item.handle_08.item)->set();
  }
  if(!owner->active){MilesMutexGuard lock(owner->mutexC,0);--owner->count;}
 }
}

// Actual unsigned stdcall thread callback passed by matched constructor73F708.
unsigned __stdcall workerThreadProc(void* worker) {return static_cast<Rva0073F708*>(worker)->run();}
