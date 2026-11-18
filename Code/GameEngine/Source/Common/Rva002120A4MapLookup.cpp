// ?rva002120A4@Rva002120A4@@QAEHW4NameKeyType@@@Z
// partial score=0.97 date=2026-09-27
// ?rva002120A4@Rva002120A4@@QAEHW4NameKeyType@@@Z
// partial score=0.97 date=2026-09-27
// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002120A4@Rva002120A4@@QAEHW4NameKeyType@@@Z, retail 0x002120A4 30B.
// NameKeyType map value lookup at this+0x218 via the public twin of Armor
// _M_find 0x002888D4 (same key-only body; private made public here to call
// it legally). Returns the dword at node+8 and 0 on miss. Unblocks
// 0x004FBDB0 and 0x003F409F. Callers at 0x003F40A8 and 0x004FBDB9.
// Evidence: ret-4 thiscall; lea arg plus add ecx-0x218 plus call shape.
#define private public
#include <hash_map>
#include <cstddef>
// _M_find (retail's 47-byte body at 0x002888D4) inlines the key hash, the bucket
// count and the bucket read; declaration-only forms of those made this TU's copy
// call them. Bind to the kept retail copies instead of emitting them.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Suppress this TU's non-retail non-const vector<void*> begin/end copies.
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::const_reference vector<void *>::operator[](size_type __n) const { return *(begin() + __n); }
}

#include "../../../../reference/open-bfme-1/game/GameEngine/Include/Common/NameKeyType.h"





namespace rts
{
template <class T> struct hash
{
	size_t operator()(const T &value) const;
};
}
// Identity hash (row 0x00169440); inlined into _M_find as retail does.
namespace rts { template <> __declspec(dllimport) __forceinline size_t hash<NameKeyType>::operator()(const NameKeyType &value) const { return (size_t)value; } }

typedef _STL::hash_map<NameKeyType, int, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType> > NameKeyIntMap;

class Rva002120A4
{
public:
	int rva002120A4(NameKeyType key);

private:
	unsigned char m_pad[0x218];
	NameKeyIntMap m_map;
};

int Rva002120A4::rva002120A4(NameKeyType key)
{
	void *node = (void *)m_map._M_ht._M_find(key);
	return node != 0 ? *(int *)((char *)node + 8) : 0;
}
