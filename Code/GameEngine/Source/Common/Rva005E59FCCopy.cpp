// cl: /GX- /MD /DNDEBUG
// ?Rva005E59FCCopy@@YAPAHPAU_Rb_tree_node_base@_STL@@0PAHABU__true_type@2@@Z, retail 0x005E59FC, 40 bytes.
// Copies int keys from map<int void*> RB nodes (value at +16) to int array with null-dest guard.
// Callers are vector range-init 0x005E5F43 allocate-and-copy 0x005F4D62 and assign 0x005F4F74.
// Callee _M_increment 0x00024250 rowed. Tag is unused __true_type for 4-arg __uninitialized_copy shape.

namespace _STL
{

struct _Rb_tree_node_base
{
	char _M_color;
	char _M_pad[3];
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *) throw();
};

struct __true_type
{
};

}

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
