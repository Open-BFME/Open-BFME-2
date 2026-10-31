// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002AE435@@YAHPBVThing@@PAV?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@@Z @0x002AE435 64B
// Target evidence: checks the key at Thing+0x74 through the rowed armor
// lookup, then when that test and getDrawable both succeed appends a second
// getDrawable result to the caller's Drawable* list. It returns true on all
// paths. The global and helper names are already used by matched source.
// Structural inference: the callback identity is unknown; Thing and list types
// follow the rowed helper signatures and existing target field access.
#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base();
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}

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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class ArmorTemplate;
class Rva0035516C
{
public:
	bool rva003551B5(NameKeyType key) const;
};
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;

class Drawable;
#include "../../Common/Thing/thing.h"

int rva002AE435(const Thing *thing, std::list<Drawable *> *output)
{
	NameKeyType key = *(const NameKeyType *)((const char *)thing + 0x74);
	if (((Rva0035516C *)(void *)TheAiOrdersManager)->rva003551B5(key)) {
		if (thing->getDrawable() != 0)
			output->push_back(thing->getDrawable());
	}
	return 1;
}
