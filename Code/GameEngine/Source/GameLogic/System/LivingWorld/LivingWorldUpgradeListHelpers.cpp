// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Two stdcall living-world upgrade-list walkers (WB 0x00B57F60 is the
// second, unnamed): each non-null entry of a vector of upgrade templates is
// handed to the player's upgrade hooks (WB names 0x002E1588
// LivingWorldPlayer::AddUpgrade and 0x002E15BC RemoveUpgrade).
//  - rva0020ED51, retail 0x0020ED51 (61 B): adds every entry of the given
//    list, forwarding the flag; reached through the forwarders 0x0020F2F1
//    and 0x0020F309. The pinned spelling passes the player and the flag as
//    plain words.
//  - Rva0020EE29::rva0020ED8E, retail 0x0020ED8E (71 B): removes every entry
//    of the object's +0xD4 list; called from the battle hand-over 0x0020F832,
//    which loads ECX=this (mov ecx,ebx) for it: a thiscall member of the
//    region manager that never reads ECX.
#include <vector>

// The walkers read the vector's size() and begin() const inline; their unreferenced
// copies here differed from retail's. Declared imported and
// force-inlined, they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
size_t vector<void *>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
vector<void *>::const_iterator vector<void *>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t __n) const { return *(begin() + __n); }
}

class Rva002E15BC; // Opaque parameter spelling retained for the stdcall provider.
#include "../../../../Include/GameLogic/LivingWorldPlayer.h"

struct Rva0020ED8EUpgradeOwner
{
	char m_pad00[0xD4];
	_STL::vector<void *> m_upgrades;	// +0xD4
};

void __stdcall rva0020ED51(void *list, int player, int flag)
{
	const _STL::vector<void *> &upgrades = *(const _STL::vector<void *> *)list;
	for (unsigned int i = 0; i < upgrades.size(); ++i)
	{
		if (upgrades[i])
			((LivingWorldPlayer *)player)->AddUpgrade(upgrades[i], *(bool *)&flag);
	}
}

#include "../../../../Include/GameLogic/Rva0020EE29.h"

void Rva0020EE29::rva0020ED8E(void *ownerWord, void *player)
{
	Rva0020ED8EUpgradeOwner *owner = (Rva0020ED8EUpgradeOwner *)ownerWord;
	const _STL::vector<void *> &upgrades = owner->m_upgrades;
	for (unsigned int i = 0; i < upgrades.size(); ++i)
	{
		if (upgrades[i])
			((LivingWorldPlayer *)player)->RemoveUpgrade(upgrades[i]);
	}
}
