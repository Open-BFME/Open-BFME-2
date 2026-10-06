// cl: /DNDEBUG /MD
// ?Rva005635DEPut@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@ABURva005635DEPayload@@@Z @0x005635DE (22B): ostream payload put.
// Outputs the 4-byte payload as long via rowed _M_put_num J at 0x0055C000.
// Caller at 0x005635F4 prints key then " = " then value then newline, same as
// Rva001F84A7Put 0x001F84A7 precedent (which uses K unsigned long for
// TreeHintPayload). Prev Rva005635CD next GpuDrawModuleTemplate parse.
namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
};

template <class C, class T, class N>
basic_ostream<C, T> &_M_put_num(basic_ostream<C, T> &os, N value);
}

struct Rva005635DEPayload
{
	long value;
};

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva005635DEPut(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const Rva005635DEPayload &payload)
{
	_STL::_M_put_num(os, payload.value);
	return os;
}
