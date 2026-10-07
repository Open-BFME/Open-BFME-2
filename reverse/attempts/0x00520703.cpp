// ?resize@?$vector@URva00520211Element@@V?$allocator@URva00520211Element@@@_STL@@@_STL@@QAEXIURva00520211Element@@@Z
// partial score=0.9 date=2026-10-07
// Target evidence: Ghidra boundary 0x00520703/108, stride 0x50, and calls to
// the rowed erase and fill-insert helpers at 0x0052016A and 0x005205DA. The
// caller at 0x0052076F constructs the 0x50-byte by-value argument.
// Structural inference: this is vector resize; its opaque value and helper
// type views borrow the existing destructor and helper spellings. The target
// proves the byte stride, not the application's record identity.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc

struct Rva00520211Element
{
	char opaque[80];
	~Rva00520211Element();
};

struct Rva005205DAElement
{
	char opaque[80];
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
	typedef unsigned int size_type;
	typedef Type *iterator;

	iterator erase(iterator first, iterator last);
	void _M_fill_insert(iterator position, size_type count, const Type &value);
	void resize(size_type newSize, Type value);

	Type *_M_start;
	Type * volatile _M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
// ?resize@?$vector@URva00520211Element@@V?$allocator@URva00520211Element@@@_STL@@@_STL@@QAEXIURva00520211Element@@@Z present-unmatched
void vector<Type, Allocator>::resize(size_type newSize, Type value)
{
	Type *start = _M_start;
	Type *finish = _M_finish;
	const size_type size = (size_type)(finish - start);
	if (newSize < size) {
		erase(start + newSize, finish);
	} else {
		vector<Rva005205DAElement, allocator<Rva005205DAElement> > *fillView =
			(vector<Rva005205DAElement, allocator<Rva005205DAElement> > *)this;
		Rva005205DAElement *insertEnd = fillView->_M_finish;
		const size_type fillCount = newSize -
			(size_type)(insertEnd - (Rva005205DAElement *)start);
		fillView->_M_fill_insert(
			insertEnd,
			fillCount,
			*(const Rva005205DAElement *)&value);
	}
}

template void vector<Rva00520211Element,
	allocator<Rva00520211Element> >::resize(unsigned int, Rva00520211Element);
}
