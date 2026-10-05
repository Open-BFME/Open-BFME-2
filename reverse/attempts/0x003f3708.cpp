// ?rva003F3708@Rva003F3708@@QAEPAUElem003B2540@@H@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /MD
// ?rva003F3708@Rva003F3708@@QAEPAUElem003B2540@@H@Z @0x003F3708 49B: thiscall vector erase by key.
// Evidence: ret 4 one int arg; lea edx [ecx+0x1a8] begin end stride 0x18 cmp [eax+8] vs arg; call vector<Elem003B2540>::erase row 0x003F3578; returns erase iterator or end; caller 0x0020EA3F unblocks 0x0020EA22.
struct Elem003B2540
{
	char m_pad[8];
	int m_key;
	char m_pad2[12];
};
namespace _STL {
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
	T *erase(T *);
};
}
class Rva003F3708
{
public:
	char m_pad[0x1a8];
	_STL::vector<Elem003B2540> m_vec;
	Elem003B2540 *rva003F3708(int key);
};

// ?rva003F3708@Rva003F3708@@QAEPAUElem003B2540@@H@Z present-unmatched
Elem003B2540 *Rva003F3708::rva003F3708(int key)
{
	Elem003B2540 *begin = m_vec._M_start;
	Elem003B2540 *end = m_vec._M_finish;
	if (begin == end)
		return end;
	do {
		if (begin->m_key == key)
			return m_vec.erase(begin);
		++begin;
	} while (begin != end);
	return end;
}
