// cl: /GX- /MD /DNDEBUG
// stlport46
// ?Rva005E59FCCopy@@YAPAHPAU_Rb_tree_node_base@_STL@@0PAHABU__true_type@2@@Z, retail 0x005E59FC, 40 bytes.
// Copies int keys from map<int void*> RB nodes (value at +16) to int array with null-dest guard.
// Callers are vector range-init 0x005E5F43 allocate-and-copy 0x005F4D62 and assign 0x005F4F74.
// Callee _M_increment 0x00024250 rowed. Tag is unused __true_type for 4-arg __uninitialized_copy shape.

#define _STLP_USE_STATIC_LIB 1
#include <map>

int *__cdecl Rva005E59FCCopy(_STL::_Rb_tree_node_base *first, _STL::_Rb_tree_node_base *last, int *result, const _STL::__true_type &tag)
{
	int *d = result;
	for (; first != last; first = _STL::_Rb_global<bool>::_M_increment(first), ++d)
	{
		if (d)
			*d = *(int *)((char *)first + 16);
	}
	return d;
}
