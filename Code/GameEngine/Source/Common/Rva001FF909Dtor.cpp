// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva001FF909@@UAE@XZ, retail 0x001FF909..0x001FF9E4 (219 bytes, EH):
// a subsystem's destructor (opaque pin of its scalar deleting destructor;
// table 0x00BE25B4). It ::deletes every non-null object of its first
// owned-pointer vector (+0x0C) and empties it, ::deletes every object of
// its second (+0x18) by index and empties it (both through the rowed
// vector<void *> range erase 0x0031BD55), then both vectors' storage goes
// to GameFree and the rowed SubsystemInterface destructor runs. Retail's
// unwind map: SubsystemInterface (state 0), the +0x0C and +0x18 vectors
// (states 1, 2) through the shared free-first-pointer body 0x0007FAB3.
// Owner and element identities are not established.
// The two vectors are spelled with their owned-object pointer type, not
// vector<void *>, whose out-of-line destructor is the /Od body 0x00027370;
// only the shared range erase is reached through the vector<void *> spelling.
#include <vector>

class Rva001FF909Owned;
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> inline _Vector_base<Rva001FF909Owned *, allocator<Rva001FF909Owned *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> vector<void *>::iterator vector<void *>::erase(iterator first, iterator last);
}

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
}

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva001FF909Owned
{
public:
	virtual ~Rva001FF909Owned();
};

class Rva001FF909 : public SubsystemInterface
{
public:
	virtual ~Rva001FF909();
private:
	_STL::vector<Rva001FF909Owned *> m_first;	// +0x0C
	_STL::vector<Rva001FF909Owned *> m_second;	// +0x18
};

Rva001FF909::~Rva001FF909()
{
	for (_STL::vector<Rva001FF909Owned *>::iterator it = m_first.begin(); it != m_first.end(); )
	{
		Rva001FF909Owned *owned = *it++;
		if (owned)
			::delete owned;
	}
	_STL::vector<void *> &first = reinterpret_cast<_STL::vector<void *> &>(m_first);
	first.erase(first.begin(), first.end());
	for (unsigned int i = 0; i < m_second.size(); ++i)
		::delete m_second[i];
	_STL::vector<void *> &second = reinterpret_cast<_STL::vector<void *> &>(m_second);
	second.erase(second.begin(), second.end());
}
