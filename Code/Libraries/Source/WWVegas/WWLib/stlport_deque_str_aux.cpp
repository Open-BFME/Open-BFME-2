// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0005800A@Rva0005800A@@QAEXABVRva0036CA00Str@@@Z @0x0005800A 132B: deque<Rva0036CA00Str> push_back slow path aux; tCopy plus reserve_map_at_back plus 0x80 byte node allocate plus construct plus set_node plus Release_Ref dtor; caller 0x00058BB4 in 0x00058B90; callees rowed copyCtor reserve allocate Release_Ref.
#include <new.h>
#include "OpaqueRefCounted.h"
#include "../../../../GameEngine/Include/Common/Rva0036CA00Str.h"
// ??1Rva0036CA00Str@@QAE@XZ present-unmatched
inline Rva0036CA00Str::~Rva0036CA00Str()
{
	if (m_item)
		((OpaqueRefCounted *)m_item)->Release_Ref();
}
class Rva0005800A;
namespace _STL {
template <class T> class allocator {
public:
	static T *allocate(unsigned int n, const void *hint);
};
template <class T, class A> class deque {
	friend class ::Rva0005800A;
protected:
	void _M_reserve_map_at_back(unsigned int n);
};
template <class T> struct _Deque_it {
	void _M_set_node(T **n) { _M_node = n; _M_first = *n; _M_last = _M_first + 32; }
	T *_M_cur; T *_M_first; T *_M_last; T **_M_node;
};
}
class Rva0005800A {
public:
	void rva0005800A(const Rva0036CA00Str &t);
private:
	_STL::_Deque_it<Rva0036CA00Str> _M_start;
	_STL::_Deque_it<Rva0036CA00Str> _M_finish;
	Rva0036CA00Str **_M_map;
	unsigned int _M_map_size;
};
inline __declspec(noinline) void Rva0005800A::rva0005800A(const Rva0036CA00Str &t)
{
	Rva0036CA00Str tCopy = t;
	((_STL::deque<void *, _STL::allocator<void *> > *)this)->_M_reserve_map_at_back(1);
	*(_M_finish._M_node + 1) = (Rva0036CA00Str *)_STL::allocator<char>::allocate(0x80, 0);
	new (_M_finish._M_cur) Rva0036CA00Str(tCopy);
	_M_finish._M_set_node(_M_finish._M_node + 1);
	_M_finish._M_cur = _M_finish._M_first;
}

// MilesAudioManager.cpp emits a select-any copy of the same body; defining it
// inline-noinline here keeps one body under the name. The anchor keeps it emitted.
// ?bfmeAnchorRva0005800A absent-from-retail
void bfmeAnchorRva0005800A(Rva0005800A *p, const Rva0036CA00Str &t)
{
	p->rva0005800A(t);
}
