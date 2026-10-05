// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
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
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

extern "C" const void *const vtbl_00C6A520[];  // ??_7GroupOrder@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6A520=??_7GroupOrder@@6B@")

#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

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

class Rva0036E346
{
public:
	int rva0036E346();

public:
	char m_pad0[4];
	ListNode *m_head;
};

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class GroupOrder : public EmptyBase
{
public:
	GroupOrder(Rva0036E346 *holder);

private:
	void *m_vtable;
	_STL::vector<ScienceType> m_sciences;
	void *m_id10;
	void *m_unused14;
};

GroupOrder::GroupOrder(Rva0036E346 *holder)
	: m_vtable(reinterpret_cast<void *>(((unsigned int)vtbl_00C6A520)))
	, m_sciences()
{
	m_id10 = reinterpret_cast<void *>(++g_Va00E05F74);
	m_unused14 = NULL;
	if (m_id10 == 0)
		m_id10 = reinterpret_cast<void *>(++g_Va00E05F74);
	m_sciences.reserve(holder->rva0036E346());
	for (ListNode *cur = holder->m_head->m_next; cur != holder->m_head; cur = cur->m_next)
		m_sciences.push_back(cur->m_obj->getScience());
}
