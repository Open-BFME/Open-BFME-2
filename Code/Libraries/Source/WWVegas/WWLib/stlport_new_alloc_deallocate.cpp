// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport46
//
// _STL::__new_alloc::deallocate, retail 0x000237B0 (12 bytes): the static
// release every STLport allocator ends in. Every container unit emits this
// body as a select-any copy; it is rowed here, in a unit that emits nothing
// else of note, because the unit owning a row this early is first in link order
// for every COMDAT it defines. Its previous owner,
// stlport_rb_tree_insert_unique_nocase.cpp, thereby supplied the kept copy of
// _Construct<AsciiString> and eight other names, all different from retail's
// bodies, which held 50 units out of the link.
//
// The pointer below only makes cl emit the inline static out of line.

#include <memory>

extern void (_STLP_CALL *const g_bfmeNewAllocDeallocate)(void *, size_t);
void (_STLP_CALL *const g_bfmeNewAllocDeallocate)(void *, size_t) = &_STL::__new_alloc::deallocate;
