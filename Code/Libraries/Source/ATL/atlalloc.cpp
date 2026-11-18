// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Microsoft Visual C++ .NET 2003 ATL 7.1 atlalloc.h: the buffer manager behind
// _ATL_SAFE_ALLOCA. Its node is a next pointer plus four bytes of x86 padding,
// which is the eight the retail Allocate adds to the request and the eight it
// steps past on the way out.

// size_t and the dllimport CRT malloc/free come from the real headers; this
// TU is not /MD, so _DLL makes <stdlib.h> declare them dllimport (the
// retail bodies call msvcr71 through the IAT).
#define _DLL
#include <stdlib.h>
#undef _DLL
#include <string.h>

// SIZE_T stays unsigned int: the SDKs ULONG_PTR is unsigned long, which
// would re-mangle Allocate(SIZE_T) from PAXI to PAXK. BYTE likewise has no
// SIZE_T-free Windows header in this include set.
typedef unsigned int SIZE_T;
typedef unsigned char BYTE;

namespace ATL
{

class CCRTAllocator
{
public:
    static void *Allocate(size_t nBytes) throw() { return malloc(nBytes); }
    static void Free(void *p) throw() { free(p); }
};

namespace _ATL_SAFE_ALLOCA_IMPL
{

template <class Allocator>
class CAtlSafeAllocBufferManager
{
private:
    struct CAtlSafeAllocBufferNode
    {
        CAtlSafeAllocBufferNode *m_pNext;
        BYTE _pad[4];

        void *GetData() { return (this + 1); }
    };

    CAtlSafeAllocBufferNode *m_pHead;

public:
    CAtlSafeAllocBufferManager() : m_pHead(0) {}

    void *Allocate(SIZE_T nRequestedSize);
    ~CAtlSafeAllocBufferManager();
};

template <class Allocator>
void *CAtlSafeAllocBufferManager<Allocator>::Allocate(SIZE_T nRequestedSize)
{
    CAtlSafeAllocBufferNode *p =
        (CAtlSafeAllocBufferNode *)Allocator::Allocate(nRequestedSize + sizeof(CAtlSafeAllocBufferNode));
    if (p == 0)
        return 0;

    // Add buffer to the list
    p->m_pNext = m_pHead;
    m_pHead = p;

    return p->GetData();
}

template <class Allocator>
CAtlSafeAllocBufferManager<Allocator>::~CAtlSafeAllocBufferManager()
{
    // Walk the list and free the buffers
    while (m_pHead != 0)
    {
        CAtlSafeAllocBufferNode *p = m_pHead;
        m_pHead = m_pHead->m_pNext;
        Allocator::Free(p);
    }
}

template void *CAtlSafeAllocBufferManager<CCRTAllocator>::Allocate(SIZE_T);
template CAtlSafeAllocBufferManager<CCRTAllocator>::~CAtlSafeAllocBufferManager();

}
}
