// cl: /Ireference/shims/moduledata /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??0GroupOrder@@QAE@PAVRva0036E346@@@Z, retail 0x00548A25, 157 bytes.
// Base ctor overload gathering required Sciences from holder list:
// vtable 0xC6A520 at +0, vector<ScienceType> at +4 via folded empty base,
// fresh nonzero ID from absolute 0xE05F74 at +0x10, null at +0x14,
// reserve(holder count) plus push_back loop over Objects (Science at +0x74)
// via rowed reserve 0x002A1410 and push_back 0x002E01C6.
// Evidence: same vtable-ID-vector layout as copy ctor 0x005488E9;
// five derived ModuleData ctors (0x00546AD0 0x00546C26 0x00546ECE
// 0x00547963 0x00547F88) call this base then overwrite the vtable.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "Common/Snapshot.h"

#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

enum ScienceType
{
	SCIENCE_NONE = 0
};
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
// Keep the first compatible ScienceType destructor's allocator identity.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
// Retail's push_back overflow path (0x00148D00) calls the shared four-byte
// allocate at 0x00068E15; this unit's malloc-wired copy differed from it.
template <> ScienceType *allocator<ScienceType>::allocate(size_t, const void *) const;
}


extern int g_Va00E05F74;

class Object
{
public:
	__forceinline ScienceType getScience() const
	{
		return *(const ScienceType *)((const char *)this + 0x74);
	}

private:
	char m_pad[0x78];
};

struct ListNode
{
	ListNode *m_next;
	char m_pad4[4];
	Object *m_obj;
};

#include "../../../Include/GameLogic/Rva0036E346.h"

class Rva0036E346;

class GroupOrder : public Snapshot
{
public:
	GroupOrder();
	GroupOrder(const GroupOrder &other);
	GroupOrder(Rva0036E346 *holder);
	virtual ~GroupOrder();
	virtual void xfer(Xfer *xfer); // slot 3 of 0x0086A520

private:
	_STL::vector<ScienceType> m_list; // +4
	unsigned int m_10; // +0x10 fresh nonzero id (copy and holder ctors)
	unsigned int m_14; // +0x14
};

GroupOrder::GroupOrder(Rva0036E346 *holder)
	: m_list()
{
	m_10 = ++g_Va00E05F74;
	m_14 = 0;
	if (m_10 == 0)
		m_10 = ++g_Va00E05F74;
	m_list.reserve(holder->rva0036E346());
	for (ListNode *cur = holder->m_head->m_next; cur != holder->m_head; cur = cur->m_next)
		m_list.push_back(cur->m_obj->getScience());
}
