// cl: /DNDEBUG /MD
// ?Rva001F84A7Put@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@ABUTreeHintPayload001F8ACB@@@Z @0x001F84A7 (22B): ostream TreeHintPayload put.
// Outputs the 4-byte payload as unsigned long via rowed _M_put_num at
// 0x001F60AA. Caller at 0x001F8BD0 prints key then " = " then value then
// newline. Prev _M_create_node next Rb_tree clear.
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

struct TreeHintPayload001F8ACB
{
	unsigned long value;
};

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F84A7Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const TreeHintPayload001F8ACB &payload)
{
	_STL::_M_put_num(os, payload.value);
	return os;
}
