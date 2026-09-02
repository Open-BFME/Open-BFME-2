// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _STLP_mutex_spin<0>::_M_do_lock, the spin lock behind
// _STLP_mutex. The upstream body from vendor/stlport/stl/_threads.c: swap the
// lock word, and on contention spin __max times - squaring a volatile junk
// value four times per iteration to burn cycles - before falling back to
// sleeping with a doubling delay.
//
// _S_nsec_sleep is folded in rather than called: retail's second loop tests
// the log against 20 and reaches Sleep directly.

typedef long __stl_atomic_t;

extern "C" __declspec(dllimport) long __stdcall InterlockedExchange(
		long *target, long value);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

namespace _STL
{

inline __stl_atomic_t _Atomic_swap(volatile __stl_atomic_t *p, __stl_atomic_t q)
{
	return InterlockedExchange((long *)p, q);
}

template <int __inst>
struct _STLP_mutex_spin
{
	enum { __low_max = 30, __high_max = 1000 };

	static unsigned __max;
	static unsigned __last;

	static void __cdecl _M_do_lock(volatile __stl_atomic_t *lock);
	static void __cdecl _S_nsec_sleep(int log_nsec);
};

template <int __inst>
unsigned _STLP_mutex_spin<__inst>::__max = _STLP_mutex_spin<__inst>::__low_max;

template <int __inst>
unsigned _STLP_mutex_spin<__inst>::__last = 0;

template <int __inst>
__forceinline void __cdecl _STLP_mutex_spin<__inst>::_S_nsec_sleep(int log_nsec)
{
	if (log_nsec <= 20)
		Sleep(1);
	else
		Sleep(1 << (log_nsec - 20));
}

template <int __inst>
void __cdecl _STLP_mutex_spin<__inst>::_M_do_lock(volatile __stl_atomic_t *lock)
{
	if (_Atomic_swap(lock, 1))
	{
		unsigned my_spin_max = _STLP_mutex_spin<0>::__max;
		unsigned my_last_spins = _STLP_mutex_spin<0>::__last;
		volatile unsigned junk = 17;
		unsigned i;

		for (i = 0; i < my_spin_max; ++i)
		{
			if (i < my_last_spins / 2 || *lock)
			{
				junk *= junk;
				junk *= junk;
				junk *= junk;
				junk *= junk;
			}
			else
			{
				if (!_Atomic_swap(lock, 1))
				{
					_STLP_mutex_spin<0>::__last = i;
					_STLP_mutex_spin<0>::__max = _STLP_mutex_spin<0>::__high_max;
					return;
				}
			}
		}

		_STLP_mutex_spin<0>::__max = _STLP_mutex_spin<0>::__low_max;

		for (i = 0;; ++i)
		{
			int log_nsec = i + 6;

			if (log_nsec > 27)
				log_nsec = 27;
			if (!_Atomic_swap(lock, 1))
				break;
			_S_nsec_sleep(log_nsec);
		}
	}
}

template struct _STLP_mutex_spin<0>;

}
