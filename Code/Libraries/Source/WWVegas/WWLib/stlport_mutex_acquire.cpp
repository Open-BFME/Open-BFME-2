// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _STLP_mutex_base::_M_acquire_lock - eight bytes that hand the
// address of the lock word to the spin lock at 0x00007690 and return. The lock
// word is the whole of the object, so `this` is the argument.

typedef long __stl_atomic_t;

namespace _STL
{

template <int __inst>
struct _STLP_mutex_spin
{
	static void __cdecl _M_do_lock(volatile __stl_atomic_t *lock);
};

class _STLP_mutex_base
{
public:
	void _M_acquire_lock();

	volatile __stl_atomic_t _M_lock;
};

void _STLP_mutex_base::_M_acquire_lock()
{
	_STLP_mutex_spin<0>::_M_do_lock(&_M_lock);
}

}
