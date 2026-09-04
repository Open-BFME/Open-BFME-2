// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The nine standard exception classes, whose vftables sit consecutively at
// 0x007BDA44..0x007BDA98 with nothing claimed but the what() they all share.
// STLport declares each destructor in <stdexcept> and leaves the body to the
// library, so this unit supplies them; defining them is also what makes MSVC
// emit each class's vftable and the scalar deleting destructor beside it,
// which is the row that matters - the image parks all nine of those together
// at 0x00024B00..0x00024C00, one every 32 bytes.

#include <stdexcept>

namespace _STL
{

__Named_exception::~__Named_exception() _STLP_NOTHROW_INHERENTLY
{
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
