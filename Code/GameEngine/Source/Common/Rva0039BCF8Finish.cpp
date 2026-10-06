// cl: /DNDEBUG /MD /EHsc
// ?rva0039BCF8@Rva0039BCF8@@QAEPAPAXPAX@Z @0x0039BCF8 48B vector erase-first helper over +0x304 via rowed voidptr erase.
// Linear search for val then rowed erase; returns erase iterator or end.
// Evidence: callee rowed vector<void*>::erase 0x001FF51F; caller 0x0055A925 passes outer this as val with inner this at +0x10; stride 4 with 0x304/0x308 begin/end; EAX holds end/erase-return on all exits so non-void.
//
// The bank was an explicit `if (first == last) return last;` guard ahead of a
// range-for, which measures 42 diffbytes at the retail size. Writing the same
// semantics as a find-style two-condition while loop -- `while (it != last &&
// *it != val) ++it;` then a single `if (it != last) return erase(it);` --
// drops it to 27 diffbytes at the same 48 bytes, because retail has exactly one
// loop and one exit test, so the extra pre-test block the bank forced is
// dropped with it. Remaining residue is one register choice: see
// reverse/re_attempts.log.

namespace _STL
{
template <typename T> class allocator
{
};
template <typename T, typename A = allocator<T> > class vector
{
public:
	T *m_begin;
	T *m_end;
	T *m_cap;
	void **erase(void **pos);
};
}

class Rva0039BCF8
{
public:
	void **rva0039BCF8(void *val);

	char m_pad[0x304];
	_STL::vector<void *> m_vec;
};

void **Rva0039BCF8::rva0039BCF8(void *val)
{
	void **it = m_vec.m_begin;
	if (it == m_vec.m_end)
		return it;
	while (it != m_vec.m_end) {
		if (*it == val)
			return m_vec.erase(it);
		++it;
	}
	return it;
}
