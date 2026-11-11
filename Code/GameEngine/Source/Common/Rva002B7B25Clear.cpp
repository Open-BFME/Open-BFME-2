// cl: /O1 /Ireference/shims/bfmealloc
// stlport
// ?rva002B7B25@Rva002B7B25@@QAEXXZ retail 0x002B7B25 76 bytes.
// Chain lane: erase vector at +0x10c via rowed STL erase 0x0031BD55,
// then call just-landed Rva002E21D1::rva002E21D1 on each element of
// vector at +0x8c. Evidence: callee 0x002E21D1 rowed by own landing;
// same erase row and loop shape as 0x002E21D1; neighbours /O1.
#include <vector>

// vector<void*> members otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

#include "../../Include/GameLogic/Rva002E21D1.h"

class Rva002B7B25
{
public:
	void rva002B7B25();
private:
	char m_pad[0x8c];
	_STL::vector<void *> m_8c;
	char m_pad98[0x10c - 0x98];
	_STL::vector<void *> m_10c;
};

// ?rva002B7B25@Rva002B7B25@@QAEXXZ
void Rva002B7B25::rva002B7B25()
{
	_STL::vector<void *> *v = &m_10c;
	v->erase(v->begin(), v->end());
	for (unsigned int i = 0; i < m_8c.size(); ++i) {
		((Rva002E21D1 *)m_8c[i])->rva002E21D1();
	}
}
