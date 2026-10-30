// ?reset@IngameNoticeDisplay@@UAEXXZ
// Slot 9 (reset) of the IngameNoticeDisplay subsystem table; the fields
// (+0xC descriptor, +0x10 group vector, +0x1C..+0x24 frames) are those
// IngameNoticeDisplay.cpp reads, and ~IngameNoticeDisplay 0x004E61C8 calls it.
// @0x004E5D6E 68B via STL clear: for_each delete + erase + zero + 0xff000000 store
// cl: /MD /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <vector>
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *, allocator<void *> >::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *, allocator<void *> >::end()
{ return _M_finish; }
template <> void **vector<void *, allocator<void *> >::erase(void **, void **);
}

class Rva004E5A78;

struct Rva004E5CB0Deleter
{
	void operator()(Rva004E5A78 *p) const;
};

struct Rva004E5D6EChild
{
	unsigned char m_pad[0x18];
	unsigned int m_field18;
};

struct Rva004E61C8Inner;
class IngameNoticeDisplay : public SubsystemInterface
{
public:
	virtual ~IngameNoticeDisplay();
	virtual void init();
	virtual void reset();
private:
	Rva004E61C8Inner *m_c; // +0xc
	_STL::vector<void *, _STL::allocator<void *> > m_vec; // +0x10
	int m_1c;
	int m_20;
	int m_24;
};
void IngameNoticeDisplay::reset()
{
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	_STL::for_each((Rva004E5A78 **)m_vec.begin(), (Rva004E5A78 **)m_vec.end(), Rva004E5CB0Deleter());
	_STL::vector<void *, _STL::allocator<void *> > *pv = &m_vec;
	pv->erase(pv->begin(), pv->end());
	((Rva004E5D6EChild *)m_c)->m_field18 = 0xff000000;
}
