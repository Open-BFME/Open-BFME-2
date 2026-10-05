// cl: /O1 /DNDEBUG /MD
//
// ?rva003C4B2D@@YAXPAXPAXPAXPAX@Z @0x003C4B2D 58B (dump range 18).
// Cdecl insert-or-splice: compares the +0x20 keys of *a and c; when c's is
// smaller, shifts through rowed STL __copy_trivial_backward and stores c
// at *a, otherwise forwards (b, c, d) to the pinned cdecl-3 0x003BD4C3
// (whose custom body is banked-blocked; the pin only spells this call
// site). Shared add-esp cleanup proves both callees cdecl.
namespace _STL
{
void *__copy_trivial_backward(const void *first, const void *last, void *result);
}
void rva003BD4C3(void *a, void *b, void *c);

void __cdecl rva003C4B2D(void *a, void *b, void *c, void *d)
{
	if (*(int *)((char *)c + 0x20) < *(int *)((char *)*(void **)a + 0x20)) {
		_STL::__copy_trivial_backward(a, b, (char *)b + 4);
		*(void **)a = c;
	}
	else {
		rva003BD4C3(b, c, d);
	}
}
