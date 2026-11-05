// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva002A1B07@@QAE@XZ @0x002A1B07 22B.
// Default ctor constructing the Drawable-pointer list member at +4 through
// the pinned List_base ctor with a stack allocator temp. Evidence: thiscall
// no-arg ret; lea ecx [esi+4] plus lea-push temp allocator matching the
// pinned List_base 0x00239BB0; caller at 0x002A3C1B; +0 left uninitialized.
#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
class FreelistPool
{
public:
	void *pop();
	int m_00; // +0x00
	void *m_04; // +0x04
	void *m_head; // +0x08
};
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
class Drawable;
class Rva002A1B07
{
public:
	Rva002A1B07();
private:
	int m_00;
	_STL::list<Drawable *> m_list04;
};
Rva002A1B07::Rva002A1B07()
{
}
