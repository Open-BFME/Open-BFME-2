// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
// ?rva002B6066@Rva002B6066@@QAEPAU1@PAU1@@Z @0x002B6066 (57B):
// vector single erase for 4-byte elements: if pos+1 != finish copy the tail
// via rowed __copy_ptrs 0x002B4410 (Rva0040DC56Element, tag at ebp+0xB needs
// the body visible here like the erase family), pop one via add -4, release
// the popped element via rowed rva002B2F49 0x002B2F49 with flag 0, return pos.
// Gap between Rva002B5522/Rva002B5558 dtors; same flags as that TU.
namespace _STL
{
typedef int ptrdiff_t;
struct __false_type {};
struct random_access_iterator_tag {};
template <class _InputIter, class _OutputIter, class _Distance>
_OutputIter __copy(_InputIter __first, _InputIter __last, _OutputIter __result, const random_access_iterator_tag &, _Distance *);
template <class _InputIter, class _OutputIter>
inline __declspec(noinline) _OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, const __false_type &)
{
	random_access_iterator_tag __category;
	return __copy(__first, __last, __result, __category, (ptrdiff_t *)0);
}
}

struct Rva0040DC56Element
{
	char m_pad[4];
};

struct Rva002B2F49
{
	void *rva002B2F49(unsigned int flag);
};

class Rva002B6066
{
public:
	Rva0040DC56Element *rva002B6066(Rva0040DC56Element *pos);
private:
	Rva0040DC56Element *m_00;
	Rva0040DC56Element *m_04;
};

// ?rva002B6066@Rva002B6066@@QAEPAU1@PAU1@@Z present-unmatched
Rva0040DC56Element *Rva002B6066::rva002B6066(Rva0040DC56Element *pos)
{
	Rva0040DC56Element *last = m_04;
	Rva0040DC56Element *first = pos + 1;
	if (first != last)
	{
		_STL::__false_type tag;
		_STL::__copy_ptrs(first, last, pos, tag);
	}
	--m_04;
	((Rva002B2F49 *)m_04)->rva002B2F49(0);
	return pos;
}
