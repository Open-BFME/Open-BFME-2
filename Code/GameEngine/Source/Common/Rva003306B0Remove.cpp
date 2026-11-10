// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=

#pragma comment(linker, "/alternatename:?dummy1@Rva0033068BListener@@QAEXPAXH@Z=?rva005CB26A@Rva005CB26A@@QAEHXZ")
#pragma comment(linker, "/alternatename:?dummy2@Rva0033068BListener@@QAEXPAXH@Z=?invokeMessage@Rva0042C0DBDelegate@@QAEHPAVGameMessage@@@Z")

// stlport
// ?rva003306B0@Rva003306B0@@QAEXPAVCreateAHeroData@@@Z @ 0x003306B0 94B
// Evidence: chain from rowed Release 0x0053FA32; calls rowed find 0x0020E873, rowed forEach 0x0033068B twice, rowed erase 0x001FF51F; vector at +0x10, list at +0x00.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>
#include <algorithm>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::begin() { return this->_M_start; } }

#include "../../Include/Common/Rva0053FA0A.h"

class CreateAHeroData : public Rva0053FA0A {
};

#include "../../Include/Common/Rva0033068BListener.h"

class Rva0033068BList {
public:
	void forEach(void (Rva0033068BListener::*notify)(void *, int), void *arg, int value);
private:
	Rva0033068BListener **m_begin;
	Rva0033068BListener **m_end;
	Rva0033068BListener **m_capacity;
	unsigned int m_index;
};

class Rva003306B0 {
public:
	void rva003306B0(CreateAHeroData *key);
private:
	Rva0033068BList m_list;
	_STL::vector<void *> m_vec;
};

void Rva003306B0::rva003306B0(CreateAHeroData *key)
{
	CreateAHeroData **first = (CreateAHeroData **)m_vec.begin();
	CreateAHeroData **last = (CreateAHeroData **)m_vec.end();
	CreateAHeroData **it = _STL::find(first, last, key);
	if (it == last)
		return;
	m_list.forEach(&Rva0033068BListener::dummy1, this, (int)key);
	m_vec.erase((void **)it);
	m_list.forEach(&Rva0033068BListener::dummy2, this, (int)key);
	key->release();
}
