// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 uninitialized_copy(unsigned short *, unsigned short *,
// unsigned short *), retail 0x0000DF10, 5 bytes.
//
// stlport_wide_string_reserve.cpp calls this by address rather than defining
// it, because retail's own body for it is a five-byte jump (Ghidra reads it
// as thunk_FUN_004179b0) into __copy_trivial at 0x000179B0: the linker folded
// this instantiation's code onto the narrow one's and left a stub at its own
// address for the one caller that still reaches it externally.
//
// A plain forwarding definition reproduces that stub without reproducing the
// jump by hand: __cdecl, three pointers passed straight through with nothing
// else live across the call, so MSVC 7.1 sibling-call optimizes the whole
// function into a single jmp to the already-matched __copy_trivial. Giving it
// a translation unit of its own, rather than adding the definition next to
// the declaration in stlport_wide_string_reserve.cpp, keeps that file's own
// already-matched reserve() call site untouched -- merely having a body for
// this function visible anywhere in that TU shifted reserve()'s register
// allocation for the call (eax/ecx instead of edx/eax for the two loads
// feeding the push sequence), even with the body placed textually after
// reserve() and instantiated only at the end of the file.

namespace _STL
{

void *__cdecl __copy_trivial(const void *first, const void *last, void *result);

unsigned short *__cdecl uninitialized_copy(unsigned short *first,
		unsigned short *last, unsigned short *result)
{
	return static_cast<unsigned short *>(__copy_trivial(first, last, result));
}

}
