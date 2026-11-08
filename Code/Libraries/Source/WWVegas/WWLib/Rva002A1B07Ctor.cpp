// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva002A1B07@@QAE@XZ @0x002A1B07 22B.
// Default ctor constructing the Drawable-pointer list member at +4 through
// the pinned List_base ctor with a stack allocator temp. Evidence: thiscall
// no-arg ret; lea ecx [esi+4] plus lea-push temp allocator matching the
// pinned List_base 0x00239BB0; caller at 0x002A3C1B; +0 left uninitialized.
#include <list>

// The shared pool constructor, node creator and destructors are owned by
// their existing retail providers. Keep their specializations declared here
// so this caller does not emit another allocator implementation.
class Drawable;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &);
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base();
template <> list<Drawable *>::~list();
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &);
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
