// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00524306@Rva00524306@@QAEXABV?$StringBase@D@@@Z @0x00524306 67B.
// Vector erase guarded by TheRva00222A8BTarget: find via rowed
// Rva000BD22FFind then erase via rowed Gen_t vector erase after
// rowed rva00223A94 check. Sibling of 0x005241DF with different callee.
// Prev/next Rva005242D7Chain/Rva00524349Dtor share flags and STL setup.
#include "ascii_string.h"

struct Gen_t_001db910_p4cd;

namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *pos);
	T *begin() { return _M_start; }
	T *end() { return _M_finish; }
private:
	T *_M_start;
	T *_M_finish;
	T *_M_end;
};
}

StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};

class Rva00222A8BTarget : public Rva00223A94
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva00524306
{
public:
	void rva00524306(const StringBase<char> &val);
private:
	_STL::vector<Gen_t_001db910_p4cd, _STL::allocator<Gen_t_001db910_p4cd> > m_vec;
};

void Rva00524306::rva00524306(const StringBase<char> &val)
{
	if (TheRva00222A8BTarget == 0)
		return;
	StringBase<char> *found = Rva000BD22FFind((StringBase<char> *)m_vec.begin(), (StringBase<char> *)m_vec.end(), val);
	if (found == (StringBase<char> *)m_vec.end())
		return;
	((Rva00223A94 *)TheRva00222A8BTarget)->rva00223A94((const AsciiString *)&val);
	m_vec.erase((Gen_t_001db910_p4cd *)found);
}
