// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva002AE3F4@Rva002AE3F4@@QAEXW4ObjectID@@@Z @0x002AE3F4 65B add-if-missing on the ObjectID list at this+0x754: rowed find 0x0029B694, then the rowed native append 0x002A1B6F. Body is 0x002AE3F4..0x002AE432 with `ret 4` at 0x2AE432 and 0xCC padding after.
//
// Two spellings, both established from retail's own call displacements rather
// than inferred from the near miss:
//
// 1. OPERAND ORDER. Retail compares `mov ecx,[esi] / cmp ecx,[eax]`, so end()
//    is the LEFT operand of `==`. Spelled that way the sentinel is never
//    rematerialised into a second register and the body drops the `push edi`
//    the reverse order needs -- exact size and exact instruction count.
//
// 2. THE APPEND IS NOT push_back. Retail's append call at 0x002AE42B targets
//    0x002A1B6F, whereas the matched add-if-missing sibling Rva002A1111.cpp
//    reaches 0x0005548F. Same source shape, different list flavour: this list
//    is the one whose append is the rowed four-byte native ABI
//    (Rva002A1B6FNativeList), so it is declared with that append. Calling the
//    template push_back emits the same bytes but resolves to the wrong callee,
//    and the gate then rejects the REL32.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


enum ObjectID
{
	OBJECTID_NONE = 0
};

namespace _STL
{
template <class _InputIter, class _Tp>
_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

// Declared, never defined here: the definition is the matched row
// ?append@Rva002A1B6FNativeList@@QAEXABQAX@Z at 0x002A1B6F
// (Code/GameEngine/Source/Common/Rva002A1316.cpp).
// ?append@Rva002A1B6FNativeList@@QAEXABQAX@Z present-unmatched
class Rva002A1B6FNativeList
{
public:
	void append(void *const &value);
};

class Rva002AE3F4
{
public:
	void rva002AE3F4(ObjectID val);
private:
	char _pad[0x754];
	Rva002A1B6FNativeList m_list;
};

void Rva002AE3F4::rva002AE3F4(ObjectID val)
{
	// The native list carries only the head pointer at this+0x754, so the
	// search views it as the STLport list it is.
	_STL::list<ObjectID> &lst = *(reinterpret_cast<_STL::list<ObjectID> *>(&m_list));
	void const *element = &val;
	if (lst.end() == _STL::find(lst.begin(), lst.end(), val))
		m_list.append(*reinterpret_cast<void *const *>(element));
}