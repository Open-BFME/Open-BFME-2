// cl: /MD
// Donor evidence: BFME1 rva0083F090 is a mutex-protected monotonically
// increasing index. Target evidence: a unique 39-byte body at 0x0001BF60 has
// the same call, global loads/stores and return shape. The target owner/name
// remains address-derived because no target caller or boundary name is known.

namespace _STL {
template<int N> struct _STLP_mutex_spin
{
	static void __cdecl _M_do_lock(volatile long *lock);
};
}

// Target lock word at VA 0x00DDEF48 in zero-filled .data, immediately after
// the matched nextIndexRva0083F090 global at VA 0x00DDEF44.
volatile long indexLockRva0083F090;
extern int nextIndexRva0083F090;
// nextIndexRva0083F090: matched references place it at VA 0xddef44 (zero-filled .bss).
int nextIndexRva0083F090;

int __cdecl rva0083F090()
{
	_STL::_STLP_mutex_spin<0>::_M_do_lock(&indexLockRva0083F090);
	int next = nextIndexRva0083F090++;
	indexLockRva0083F090 = 0;
	return next;
}
