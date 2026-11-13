// cl: /Oy-
// Family-4 split-range processors (68B each): each function processes the
// pointer range [a, b) with the element helper when the aligned span is 64
// bytes or less, else it runs the head helper over the first 64 bytes and
// the tail helper over the rest, returning the tail/head result. The b and c
// parameters are volatile-qualified: that is what keeps the compiler pushing
// them from memory instead of staging them in preserved registers. Helpers
// are the rowed STLport insertion sorts; the processors are their
// __final_insertion_sort callers.
// The helpers are the rowed STLport __insertion_sort and
// __unguarded_insertion_sort instantiations of three sort families; they
// are called through the (pointer, pointer, int) shape the bodies were
// matched with.
enum Rva0021B68DKey;
struct Rva0021B68DCmp { int m_state; };
class Rva004F6093Holder;
#include "../../../Libraries/Source/WWVegas/WWLib/Rva002BBC1CCmp.h"
struct Rva003C3AB0Item;
struct Rva003C3AB0Cmp { int m_state; };
namespace _STL
{
template <class _RandomAccessIter, class _Compare>
void __insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
template <class _RandomAccessIter, class _Compare>
void __unguarded_insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
}
typedef int (*RangeHelper)(void *a, void * volatile b, volatile int c);
#define SORT_HELPER(fn, It, Cmp) 	((RangeHelper)(void (*)(It, It, Cmp))&_STL::fn<It, Cmp>)
#define Copy0021D289 SORT_HELPER(__insertion_sort, Rva0021B68DKey *, Rva0021B68DCmp)
#define Copy0021D2B6 SORT_HELPER(__unguarded_insertion_sort, Rva0021B68DKey *, Rva0021B68DCmp)
#define Copy002B833C SORT_HELPER(__insertion_sort, Rva004F6093Holder *, Rva002BBC1CCmp)
#define Copy002B6351 SORT_HELPER(__unguarded_insertion_sort, Rva004F6093Holder *, Rva002BBC1CCmp)
#define Copy003C6437 SORT_HELPER(__insertion_sort, Rva003C3AB0Item **, Rva003C3AB0Cmp)
#define Copy003C3AB0 SORT_HELPER(__unguarded_insertion_sort, Rva003C3AB0Item **, Rva003C3AB0Cmp)

int Proc0021D905(void *first, void * volatile last, volatile int comp)
{
	if ((((char *)last - (char *)first) & ~3) > 0x40)
	{
		Copy0021D289(first, (char *)first + 0x40, comp);
		return Copy0021D2B6((char *)first + 0x40, last, comp);
	}
	return Copy0021D289(first, last, comp);
}

int Proc002B9177(void *first, void * volatile last, volatile int comp)
{
	if ((((char *)last - (char *)first) & ~3) > 0x40)
	{
		Copy002B833C(first, (char *)first + 0x40, comp);
		return Copy002B6351((char *)first + 0x40, last, comp);
	}
	return Copy002B833C(first, last, comp);
}

int Proc003C6973(void *first, void * volatile last, volatile int comp)
{
	if ((((char *)last - (char *)first) & ~3) > 0x40)
	{
		Copy003C6437(first, (char *)first + 0x40, comp);
		return Copy003C3AB0((char *)first + 0x40, last, comp);
	}
	return Copy003C6437(first, last, comp);
}
