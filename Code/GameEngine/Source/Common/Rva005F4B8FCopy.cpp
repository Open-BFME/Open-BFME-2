// cl: /GX- /MD /DNDEBUG
// ?Rva005F4B8FCopy@@YAPAHPAU_Rb_tree_node_base@_STL@@0PAHABUinput_iterator_tag@2@1@Z, retail 0x005F4B8F, 37 bytes.
// __copy with input_iterator_tag for map<int void*> RB nodes: copies int keys at +16 to int array.
// Evidence: STL _algobase __copy(first last result input_iterator_tag Distance asterisk); caller 0x005F4DA7 passes NULL Distance; callee _M_increment 0x00024250 rowed.
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
struct input_iterator_tag
{
};
struct __false_type
{
};
struct __true_type
{
};
}
struct BfmeE12 { float x, y, z; };
namespace _STL
{
template <class T>
struct allocator
{
	T *allocate(unsigned int n, void const *hint) const;
};
}
int *__cdecl Rva005E59FCCopy(_STL::_Rb_tree_node_base *first, _STL::_Rb_tree_node_base *last, int *result, const _STL::__true_type &tag);
struct Rva005F4D62
{
	char _pad[8];
	_STL::allocator<BfmeE12 *> _alloc;
	int *rva005F4D62(unsigned int n, _STL::_Rb_tree_node_base *first, _STL::_Rb_tree_node_base *last);
};
int *__cdecl Rva005F4B8FCopy(_STL::_Rb_tree_node_base *first, _STL::_Rb_tree_node_base *last, int *result, const _STL::input_iterator_tag &tag1, int *dist)
{
	for (; first != last; first = _STL::_Rb_global<bool>::_M_increment(first))
	{
		*result = *(int *)((char *)first + 16);
		++result;
	}
	return result;
}
int *__cdecl Rva005F4DA7Copy(_STL::_Rb_tree_node_base *first, _STL::_Rb_tree_node_base *last, int *result, const _STL::__false_type &tag)
{
	_STL::input_iterator_tag tag1;
	return Rva005F4B8FCopy(first, last, result, tag1, (int *)0);
}
int *__cdecl Rva005F4F59Copy(_STL::_Rb_tree_node_base *first, _STL::_Rb_tree_node_base *last, int *result)
{
	_STL::__false_type tag;
	return Rva005F4DA7Copy(first, last, result, tag);
}
int *Rva005F4D62::rva005F4D62(unsigned int n, _STL::_Rb_tree_node_base *first, _STL::_Rb_tree_node_base *last)
{
	int *new_start = (int *)this->_alloc.allocate(n, 0);
	_STL::__true_type tag2;
	Rva005E59FCCopy(first, last, new_start, tag2);
	return new_start;
}
