// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001E7E25@Rva001E7E25@@QAEXXZ retail 0x001E7E25 83B: clears pointer array via virtual slot 0 plus delete then vector erase plus flag clears.
// Evidence: frameless thiscall with ebx index esi vector plus loop test ecx je plus push 0 call [eax] push eax call 0x0002FD60 then push end push begin call 0x0031BD55 erase then and [edi+0x10] 0 plus bytes [edi+0x14] [edi+0x15] 0; callers 0x001E86EE 0x00268364 0x00268A59 0x0026E87A 0x0026EBD4.
#include <vector>

// vector<void*> begin/end/clear are expanded inline here; their out-of-line copies
// would differ from retail's. Declared imported and force-inlined, they are not emitted.
namespace _STL {
template <> void **vector<void *>::erase(void **first, void **last);
}
// Rva001E72B4Dtor.cpp spells the same begin/end specializations: one shared block.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
void vector<void *>::clear() { erase(begin(), end()); }
template <> __declspec(dllimport) __forceinline
size_t vector<void *>::size() const { return this->_M_finish - this->_M_start; }
template <> __declspec(dllimport) __forceinline
void *&vector<void *>::operator[](size_t n) { return this->_M_start[n]; }
}
#include <new>
class Rva001E7E25Elem
{
public:
	virtual void *rvaGet(int arg);
};
class Rva001E7E25
{
public:
	void rva001E7E25();
private:
	char m_pad00[4];
	_STL::vector<void *> m_vec04;
	int m_10;
	unsigned char m_14;
	unsigned char m_15;
};
void Rva001E7E25::rva001E7E25()
{
	for (unsigned int i = 0; i < m_vec04.size(); ++i)
	{
		Rva001E7E25Elem *elem = (Rva001E7E25Elem *)m_vec04[i];
		if (elem)
		{
			void *p = elem->rvaGet(0);
			::operator delete(p);
		}
	}
	m_vec04.clear();
	m_10 = 0;
	m_14 = 0;
	m_15 = 0;
}
