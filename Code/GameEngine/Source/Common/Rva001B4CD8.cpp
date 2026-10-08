// cl: /DNDEBUG /MD
// ?rva001B4CD8@Rva001B4CD8@@QAEXXZ RVA 0x001B4CD8 23B
// Evidence: leaf lane; calls pinned 0x001B4C7A Rva001B4C7ATarget::rva001B4C7A
//   on this, then frees the pointer at +0 via rowed 0x00030830 free if non-null;
//   callers 0x001B4D45 and jmp 0x001B4D09.
extern "C" void __cdecl free(void *);

// The callee is the rowed STLport _List_base<BfmeVectorRecord001B4A39>::clear.
struct BfmeVectorRecord001B4A39;
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class _List_base
{
public:
	void clear();
};
}

class Rva001B4CD8
{
public:
	void rva001B4CD8();

private:
	void *m_ptr; // +0 freed if non-null
};

void Rva001B4CD8::rva001B4CD8()
{
	((_STL::_List_base<BfmeVectorRecord001B4A39, _STL::allocator<BfmeVectorRecord001B4A39> > *)this)->clear();
	void *p = m_ptr;
	if (p != 0)
		free(p);
}
