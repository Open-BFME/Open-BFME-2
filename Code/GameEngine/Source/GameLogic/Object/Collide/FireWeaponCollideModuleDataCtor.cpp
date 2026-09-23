// cl: /O1 /DNDEBUG /MD /GX-
//
// ??0FireWeaponCollideModuleData@@QAE@XZ, retail 0x00254A36 (68 bytes).
// Frameless ModuleData ctor: installs vtable 0x00C4ED70 explicitly (novtable)
// ahead of the two 128-bit status-mask resets through the rowed
// bitset<128>::reset at 0x0024CA24, clears the +0x08 word, zeroes both mask
// structs with the CRT memset import, and clears the fire-once flag. Base
// CollideModuleData contributes no out-of-line call (its chain is trivial
// here). /GX- is the lever: the declared virtual dtor plus the post-store
// calls would otherwise emit an __EH_prolog frame; with EH disabled the body
// stays frameless. Class size 0x30 proven by the data factory 0x00254A7A
// (sole caller, news 0x30). Donor: BFME1 FireWeaponCollide.cpp (ZH header
// keeps UnsignedInt masks; BFME2 widens both to 128-bit masks and drops the
// template NULL init, leaving +0x04 unstored).

#include <string.h>

namespace _STL
{

template <unsigned _Bits>
class bitset
{
public:
	unsigned long m_words[(_Bits + 31) / 32];
	bitset<_Bits> &reset();
};

}

class __declspec(novtable) BehaviorModuleData
{
public:
	virtual ~BehaviorModuleData();

protected:
	void *m_unsourced04;	// +0x04, retail never stores it
	int m_zeroed08;	// +0x08, and-zeroed by the derived ctor
};

class __declspec(novtable) CollideModuleData : public BehaviorModuleData
{
};

class __declspec(novtable) FireWeaponCollideModuleData : public CollideModuleData
{
public:
	FireWeaponCollideModuleData();

private:
	_STL::bitset<128> m_requiredStatus;	// +0x0C
	_STL::bitset<128> m_forbiddenStatus;	// +0x1C
	bool m_fireOnce;	// +0x2C
};

FireWeaponCollideModuleData::FireWeaponCollideModuleData()
{
	*(unsigned int *)this = 0x00C4ED70;
	m_requiredStatus.reset();
	m_forbiddenStatus.reset();
	m_zeroed08 = 0;
	memset(&m_requiredStatus, 0, sizeof(m_requiredStatus));
	memset(&m_forbiddenStatus, 0, sizeof(m_forbiddenStatus));
	m_fireOnce = false;
}
