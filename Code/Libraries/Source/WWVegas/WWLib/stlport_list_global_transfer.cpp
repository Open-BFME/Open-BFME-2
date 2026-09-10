// cl: /Od /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Dedicated TU for STLport _List_global<bool>::_Transfer. Retail built this
// helper unoptimised (/Od) so __tmp lives on the stack. Do not edit the
// list instantiate units; they already hold matched bodies.

#include <list>

_STLP_BEGIN_NAMESPACE

void __cdecl _List_global<bool>::_Transfer(
	_List_node_base *__position,
	_List_node_base *__first,
	_List_node_base *__last)
{
	if (__position != __last) {
		__last->_M_prev->_M_next = __position;
		__first->_M_prev->_M_next = __last;
		__position->_M_prev->_M_next = __first;

		_List_node_base *__tmp = __position->_M_prev;
		__position->_M_prev = __last->_M_prev;
		__last->_M_prev = __first->_M_prev;
		__first->_M_prev = __tmp;
	}
}

_STLP_END_NAMESPACE
