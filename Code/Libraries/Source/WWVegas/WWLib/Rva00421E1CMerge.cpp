// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00421E1CMerge@@YAXAAUMiniList00421E1C@@0VRva00421A16@@@Z @0x00421E1C 98B
// Merge two intrusive lists ordered by nearer-point comparator 0x00421A16.
// Evidence: callee 0x00421A16 row Rva00421A16DistCompare, callees 0x00024470
// _Transfer rows, caller 0x004236F5 sort-like body calling twice with a
// 12-byte by-value functor at ebp+0x10 (lea ecx) and payloads at node+8.

namespace _STL {
struct _List_node_base {
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};
template <class _Dummy>
class _List_global {
public:
	static void __cdecl _Transfer(_List_node_base *__position, _List_node_base *__first, _List_node_base *__last);
};
}

struct MiniList00421E1C {
	_STL::_List_node_base *_M_data;
};

struct DataNode00421E1C : public _STL::_List_node_base {
	const float *_M_value;
};

class Rva00421A16 {
public:
	bool rva00421A16(const float *a, const float *b);
	float m_pos[3];
};

void __cdecl Rva00421E1CMerge(MiniList00421E1C &__that, MiniList00421E1C &__x, Rva00421A16 __comp)
{
	_STL::_List_node_base *__first1 = __that._M_data->_M_next;
	_STL::_List_node_base *__last1 = __that._M_data;
	_STL::_List_node_base *__first2 = __x._M_data->_M_next;
	_STL::_List_node_base *__last2 = __x._M_data;
	while (__first1 != __last1 && __first2 != __last2) {
		if (__comp.rva00421A16(((DataNode00421E1C *)__first2)->_M_value, ((DataNode00421E1C *)__first1)->_M_value)) {
			_STL::_List_node_base *__next = __first2->_M_next;
			_STL::_List_global<bool>::_Transfer(__first1, __first2, __next);
			__first2 = __next;
		} else {
			__first1 = __first1->_M_next;
		}
	}
	if (__first2 != __last2) {
		_STL::_List_global<bool>::_Transfer(__last1, __first2, __last2);
	}
}
