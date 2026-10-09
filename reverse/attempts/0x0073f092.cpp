// ?rva0073F092@AsyncServiceQueue@@QAE?AVRva0036CA00Str@@K@Z
// partial score=0.2702702702702703 date=2026-10-09
// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// stlport

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
Rva0073EEE0ListValue::Rva0073EEE0ListValue(const Rva0073EEE0ListValue &other)
    : helperManagedPointer(other.helperManagedPointer),
      unknown_04(other.unknown_04) {
    handle_08.item = other.handle_08.item;
    if (handle_08.item)
        ++handle_08.item->RefCount;
}
typedef std::list<Rva0073EEE0ListValue> TargetListAt0073EEE0;
__declspec(noinline) void ForceTargetListAt0073EEE0(
    TargetListAt0073EEE0 &list, const Rva0073EEE0ListValue &item) {
    list.push_back(item);
}

typedef char TargetListValueSize12[(sizeof(Rva0073EEE0ListValue) == 12) ? 1 : -1];

// ??1Rva0073EEE0ListValue@@QAE@XZ @0x0073EF44 64B: releases the +8 handle via
// the rowed fastcall ReleaseTreeHintRef00217D4C, then the +0 helper pointer
// via the inlined Release_Ref. Callers: scalar-deleting ??_G at 0x0073EFB5,
// _M_create_node unwind at 0x0073EFD1, list erase at 0x0073F061, list clear at
// 0x0073F37F, EH funclet Unwind@00bab390.
Rva0073EEE0ListValue::~Rva0073EEE0ListValue() {
    if (handle_08.item)
        ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)(handle_08.item->Unknown + 8));
}
void Rva0073EEE0ListValue_Delete(Rva0073EEE0ListValue *p) { delete p; }

// ?clear@Rva0073EECA@@QAEXXZ @0x0073EECA 22B: null-checked release of the +0
// TreeHint handle via the rowed fastcall, then zero. Sole caller 0x0073EF84.
struct Rva0073EECA { TargetNestedHandleData *m_handle; void clear(); void set(TargetNestedHandleData *other); };
void Rva0073EECA::clear() {
    if (m_handle) {
        ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)(m_handle->Unknown + 8));
        m_handle = 0;
    }
}
// ?set@Rva0073EECA@@QAEXPAUTargetNestedHandleData@@@Z @0x0073EF84 31B:
// self-guarded attach: clear old, store new, AddRef. Sole caller 0x0073F3ED.
void Rva0073EECA::set(TargetNestedHandleData *other) {
    if (other != m_handle) {
        clear();
        m_handle = other;
        if (other)
            ++other->RefCount;
    }
}

// ?EraseTargetListNode0073EFFC@@YGXPAPAXPAUListNode0073EFFC@@@Z @0x0073EFFC 42B: unlinks the
// node, destroys its 12B value via the rowed ??1, frees it, stores next.
// Callers: 0x0073F026, list erase paths 0x0073F170/0x0073F231.
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

// ?rva0073F061@Rva0073F061@@QAEXXZ, retail 0x0073F061 49B. Clears the
// heap-sentinel node list of Rva0073EEE0ListValue: destroys each value via
// the rowed ??1Rva0073EEE0ListValue (0x0073EF44), frees the node via the
// rowed _free (0x00030830), then resets the sentinel links. Caller
// 0x0073F368 frees the sentinel afterwards. Node layout reuses
// ListNode0073EFFC (value at +8, same as retail lea ecx,[ebx+8]).
struct Rva0073F061 { ListNode0073EFFC *m_head; void rva0073F061(); void rva0073F368(); };
void Rva0073F061::rva0073F061() {
    ListNode0073EFFC *cur = m_head->m_next;
    if (cur != m_head) {
        ListNode0073EFFC *b;
        do {
            b = cur;
            cur = cur->m_next;
            b->m_value.~Rva0073EEE0ListValue();
            free(b);
        } while (cur != m_head);
    }
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}
void Rva0073F061::rva0073F368()
{
    rva0073F061();
    ListNode0073EFFC *sentinel = m_head;
    if (sentinel)
        free(sentinel);
}

// WB AsyncServiceQueue::enqueue and native73F37F..73F451 establish this
// queue operation; owner field04 is the count, list08, mutex0C, event14.
// The 12-byte element remains target-owned rather than donor BridgeFXInfo.
class MilesMutexGuard {public: MilesMutexGuard(void*,int);~MilesMutexGuard();void *mutex;bool held;};
class Rva0040F9D {public:bool set();bool reset();char bytes[8];};
class Rva0073EE21 {public:Rva0073EE21();char bytes[16];};
struct OpaqueRefElement4 {void *item;OpaqueRefElement4 &operator=(const OpaqueRefElement4&);};
class AsyncServiceQueue {
 public: Rva0036CA00Str rva0073F092(unsigned long timeout);
 TargetListAt0073EEE0::iterator enqueue(Rva0036CA00Str item);
 Rva0036CA00Str rva0073F231(ListNode0073EFFC *node,unsigned long timeout);
 int active,count; TargetListAt0073EEE0 queued; char mutex[8];Rva0040F9D available;TargetListAt0073EEE0 secondary;Rva0040F9D completed;Rva0040F9D drained;
};
TargetListAt0073EEE0::iterator AsyncServiceQueue::enqueue(Rva0036CA00Str item) {
 MilesMutexGuard guard(mutex,0);
 bool wasEmpty=queued.empty();
 Rva0073EEE0ListValue entry;
 reinterpret_cast<OpaqueRefElement4*>(&entry.helperManagedPointer)->operator=(*reinterpret_cast<OpaqueRefElement4*>(&item));
 entry.unknown_04=0;
 reinterpret_cast<Rva0073EECA*>(&entry.handle_08)->set(reinterpret_cast<TargetNestedHandleData*>(new Rva0073EE21));
 queued.push_back(entry);
 ++count;
 if(wasEmpty)available.set();
 TargetListAt0073EEE0::iterator last=queued.end();
 --last;
 return last;
}


class Rva00041118Obj;
class Rva00041078 {public:Rva00041078(Rva00041118Obj**,int,int);~Rva00041078();bool rva00041078(unsigned long,int,int*);char bytes[100];};
struct QueueCompletionRef {
 TargetNestedHandleData *item;
 QueueCompletionRef(TargetNestedHandleData *p):item(p){if(item)++item->RefCount;}
 ~QueueCompletionRef(){if(item)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)(item->Unknown+8));}
};
Rva0036CA00Str AsyncServiceQueue::rva0073F231(ListNode0073EFFC *node,unsigned long timeout) {
 if(!active)return Rva0036CA00Str();
 QueueCompletionRef completion(node->m_value.handle_08.item);
 Rva00041118Obj *objects[2]={reinterpret_cast<Rva00041118Obj*>(completion.item),reinterpret_cast<Rva00041118Obj*>(&completed)};
 Rva00041078 wait(objects,2,1);
 if(!wait.rva00041078(timeout,0,0))return Rva0036CA00Str();
 ListNode0073EFFC *first=node;
 Rva0036CA00Str item(first->m_value.helperManagedPointer);
 secondary.erase(TargetListAt0073EEE0::iterator((_STL::_List_node<Rva0073EEE0ListValue>*)first));
 --count;
 if(secondary.empty())drained.reset();
 return item;
}

Rva0036CA00Str AsyncServiceQueue::rva0073F092(unsigned long timeout) {
 if(!active)return Rva0036CA00Str();
 Rva00041118Obj *objects[2]={reinterpret_cast<Rva00041118Obj*>(&drained),reinterpret_cast<Rva00041118Obj*>(&completed)};
 Rva00041078 wait(objects,2,1);
 if(!wait.rva00041078(timeout,0,0))return Rva0036CA00Str();
 Rva0036CA00Str item(secondary.front().helperManagedPointer);
 secondary.pop_front();
 --count;
 if(secondary.empty())drained.reset();
 return item;
}
