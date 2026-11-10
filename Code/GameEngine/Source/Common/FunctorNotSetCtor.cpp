// cl: /DNDEBUG /MD
//
// ??0FunctorNotSet@@QAE@XZ, retail 0x002035E2, 19 bytes. FunctorNotSet
// default ctor (frameless leaf: CRT std::exception base through the
// msvcr71 import at 0x00BBA600 plus explicit vtable 0x00BD3B54 over the
// novtable model). The 0x0C-byte std::exception child thrown by the
// null-operation guards (TimedOperationRef::update 0x003FE6A0 plus 7
// family sites construct it into the frame slot, then _CxxThrowException
// with the 0x00D0B644 throw info); the throw info's catchable array names
// the type FunctorNotSet with base exception, which proves the name.
// Dedicated TU: the throw-site callers live elsewhere, and the
// TimedOperationRef TU keeps its own address-derived spelling through
// the standing alias pin.

#include <exception>

extern "C" const void *const vtbl_00BD3B54[];  // ??_7FunctorNotSet@@6B@

class __declspec(novtable) FunctorNotSet : public exception
{
public:
	FunctorNotSet();
	virtual ~FunctorNotSet();
};

// ??0FunctorNotSet@@QAE@XZ @0x2035E2
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline FunctorNotSet::FunctorNotSet()
	: exception()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BD3B54);
}

// ?bfmeAnchorFunctorNotSetCtor absent-from-retail
void *bfmeAnchorFunctorNotSetCtor(void *where)
{
	((FunctorNotSet *)where)->FunctorNotSet::FunctorNotSet();
	return where;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline FunctorNotSet::~FunctorNotSet()
{
}

// ?bfmeAnchorFunctorNotSetDtor absent-from-retail
void bfmeAnchorFunctorNotSetDtor(FunctorNotSet *functorNotSet)
{
	functorNotSet->FunctorNotSet::~FunctorNotSet();
}
