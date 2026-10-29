// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport 4.5.3 locale::facet destructor, seven bytes: the compiler's own
// vptr store for the facet vftable at 0x00BBB9BC and a return, because the
// body is empty and the reference count in _Refcount_Base needs no teardown.
//
// The linker folded every facet subclass whose destructor is also empty into
// this one body - a trivial subclass destructor optimises down to the same
// single store, since its own vftable store is dead the moment the base one
// follows it. That is why the scalar deleting destructors of the derived
// facets at 0x000072C0 all call here.

namespace _STL
{

class _Refcount_Base
{
protected:
	explicit _Refcount_Base(unsigned int count) : _M_ref_count(count) {}

private:
	volatile int _M_ref_count;
};

class locale
{
public:
	class facet : private _Refcount_Base
	{
	protected:
		explicit facet(unsigned int refs = 0)
			: _Refcount_Base(1), _M_delete(refs == 0) {}
		virtual ~facet();

	private:
		const bool _M_delete;
	};
};

inline locale::facet::~facet()
{
}

}

// locale::facet::~facet is a header inline in STLport: one other unit emits a
// select-any copy of it, so a strong definition here was a duplicate symbol in
// the linked build. This anchor only makes this unit emit its copy for the
// ledger row; it is not retail code.
struct bfmeFacetEmitter : _STL::locale::facet
{
	static void emit(bfmeFacetEmitter *p);
};
#pragma inline_depth(0)
// ?emit@bfmeFacetEmitter@@SAXPAU1@@Z present-unmatched
void bfmeFacetEmitter::emit(bfmeFacetEmitter *p)
{
	p->_STL::locale::facet::~facet();
}
#pragma inline_depth()
