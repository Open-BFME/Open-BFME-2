// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva005241DF@Rva005241DF@@QAEXABVAsciiString@@@Z @0x005241DF 67B.
// Vector erase guarded by TheRva00222A8BTarget: find via rowed
// Rva000BD22FFind then erase via rowed Gen_t vector erase after
// rowed rva002244CA check. Callers in 0x005B1830/0x005B190D.
// Neighbours Rva005241B0Dtor/Rva00524265Dtor share flags and STL setup.
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

class Rva002244CA
{
public:
	int rva002244CA(const AsciiString *key);
};

class Rva00222A8BTarget : public Rva002244CA
{
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva005241DF
{
public:
	void rva005241DF(const StringBase<char> &val);
private:
	_STL::vector<Gen_t_001db910_p4cd, _STL::allocator<Gen_t_001db910_p4cd> > m_vec;
};

void Rva005241DF::rva005241DF(const StringBase<char> &val)
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) == 0)
		return;
	StringBase<char> *found = Rva000BD22FFind((StringBase<char> *)m_vec.begin(), (StringBase<char> *)m_vec.end(), val);
	if (found == (StringBase<char> *)m_vec.end())
		return;
	((Rva002244CA *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->rva002244CA((const AsciiString *)&val);
	m_vec.erase((Gen_t_001db910_p4cd *)found);
}
