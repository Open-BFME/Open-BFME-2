// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva002000A4@RankInfoStore@@UAEXXZ @0x002000A4 51B
// vtable slot 9 (offset 0x24) of 0x007E2704 = class of ??0RankInfoStore@@QAE@XZ.
// Iterates vector at +0xC..+0x10, calls rowed deleteOverrides 0x001E35ED,
// erases via rowed vector<void*> erase 0x001FF51F when it returns 0.
// Evidence: leaf packet; prev Rva0023C6A4Check.cpp, next RankInfoCtor.cpp.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
}

#include "../../Include/Common/Overridable.h"

class RankInfoStore
{
public:
	virtual void rva002000A4();
private:
	char m_pad04[0xC - 4];
	_STL::vector<void *> m_vec;
};

void RankInfoStore::rva002000A4()
{
	_STL::vector<void *>::iterator it = m_vec.begin();
	while (it != m_vec.end())
	{
		Overridable *overridable = (Overridable *)*it;
		if (overridable == 0)
			continue;
		if (overridable->deleteOverrides() == 0)
			it = m_vec.erase(it);
		else
			++it;
	}
}
