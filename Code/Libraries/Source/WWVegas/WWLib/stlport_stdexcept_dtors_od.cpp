// cl: /Od /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The same nine destructors as stlport_stdexcept_dtors.cpp, at /Od, because
// retail holds the two halves at different optimisation settings. Each ??1
// here carries the full unoptimised frame - push ebp, mov ebp esp, this spilled
// to [ebp-4] and reloaded before every use - while the scalar deleting
// destructors the linker kept, at 0x00024B00 and up, are the /O2 shape with
// this in esi and no frame at all. So the ??1 COMDAT the linker chose came out
// of a different object than the ??_G COMDAT, and one source file cannot
// produce both.

#include <stdexcept>


namespace _STL
{

__Named_exception::~__Named_exception() _STLP_NOTHROW_INHERENTLY
{
}

const char *__Named_exception::what() const _STLP_NOTHROW_INHERENTLY
{
	return _M_name;
}

logic_error::~logic_error() _STLP_NOTHROW_INHERENTLY
{
}

runtime_error::~runtime_error() _STLP_NOTHROW_INHERENTLY
{
}

domain_error::~domain_error() _STLP_NOTHROW_INHERENTLY
{
}

invalid_argument::~invalid_argument() _STLP_NOTHROW_INHERENTLY
{
}

length_error::~length_error() _STLP_NOTHROW_INHERENTLY
{
}

out_of_range::~out_of_range() _STLP_NOTHROW_INHERENTLY
{
}

range_error::~range_error() _STLP_NOTHROW_INHERENTLY
{
}

overflow_error::~overflow_error() _STLP_NOTHROW_INHERENTLY
{
}

underflow_error::~underflow_error() _STLP_NOTHROW_INHERENTLY
{
}

}
