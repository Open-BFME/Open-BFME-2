// cl: /DNDEBUG /MD
// ?Rva001F9006Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABUTreeHintPayload001F8ACB@@@Z @0x001F9006 31B: guarded forward to rowed Rva001F8BA1Write.
// Evidence: mov eax [esp+0x10] cmp [eax] 0 je ret then push eax plus three pushes plus call 0x001F8BA1 plus add esp 0x10; callers at 0x001FB632 0x001FB64A in writeINI; prev/next rows give TU context.
namespace _STL
{
template <class C> class char_traits
{
};
template <class C, class T> class basic_ostream
{
};
}

struct TreeHintPayload001F8ACB
{
	unsigned long value;
};

void Rva001F8BA1Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const TreeHintPayload001F8ACB &value);

void Rva001F9006Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const TreeHintPayload001F8ACB &value)
{
	if (value.value == 0)
		return;
	Rva001F8BA1Write(os, pad, key, value);
}
