// cl: /O1 /DNDEBUG /MD
//
// ?releaseWeaponLock@Object@@QAEXW4WeaponLockType@@@Z @0x0028D8B6 (53B).
// Zero Hour inlines this as m_weaponSet.releaseWeaponLock(lockType); BFME 2
// makes it out of line and adds two things the bytes show: nothing happens
// while bit 0 of the +0x94 status byte is set, and the contain module at
// +0x250 (when present) hears about the release first through its virtual
// slot 91 (0x16C). The WeaponSet member sits at +0x330; its
// releaseWeaponLock 0x002C8B9B is the ZH body (NOT_LOCKED early out,
// PERMANENTLY / TEMPORARILY cases) plus a model-condition clear on the owner.
// Slot 91's name and the +0x94 bit's meaning are not proven.

enum WeaponLockType
{
	NOT_LOCKED,
	LOCKED_TEMPORARILY,
	LOCKED_PERMANENTLY
};

template <int N> class ObjectReleaseWeaponLockContainSlots : public ObjectReleaseWeaponLockContainSlots<N - 1>
{
public:
	virtual void gap(char (*)[N + 1]) = 0;
};

template <> class ObjectReleaseWeaponLockContainSlots<0>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class ContainModuleInterface : public ObjectReleaseWeaponLockContainSlots<90>
{
public:
	virtual void releaseWeaponLock(WeaponLockType lockType) = 0; // slot 91
};

class WeaponSet
{
public:
	void releaseWeaponLock(WeaponLockType lockType);
};

class Object
{
public:
	void releaseWeaponLock(WeaponLockType lockType);

private:
	unsigned char m_pad000[0x94];
	unsigned char m_status94;                 // +0x94, bit 0 blocks the release
	unsigned char m_pad095[0x250 - 0x95];
	ContainModuleInterface *m_contain;        // +0x250
	unsigned char m_pad254[0x330 - 0x254];
	WeaponSet m_weaponSet;                    // +0x330
};

void Object::releaseWeaponLock(WeaponLockType lockType)
{
	if (m_status94 & 1)
		return;

	ContainModuleInterface *contain = m_contain;
	if (contain)
		contain->releaseWeaponLock(lockType);

	m_weaponSet.releaseWeaponLock(lockType);
}
