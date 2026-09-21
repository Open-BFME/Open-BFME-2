// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0UnpauseSpecialPowerUpgradeModuleData@@QAE@XZ, retail 0x004B544A, 32
// bytes. Frameless ctor over the rowed OpenContain base (0x253487): vtable
// literal 0x00BF2558 (folded with the base), SpecialPowerTemplate 0 at
// +0x118, ObeyRechageOnTrigger false at +0x11C (own table 0x00857EF0 both
// fields; the UnpauseSpecialPowerUpgrade pool-key function at 0x4B5405 ends
// where this ctor begins; factory at 0x25018E news 0x120 and pushes the
// rowed chained proc). The TU-local base keeps an explicit vtable slot
// (DestroyEnvironment precedent, so no vtable is emitted); the and-zero
// floats above the vtable on its own (GiveOrRestore inverse: no barrier).

class OpenContainModuleData
{
public:
	OpenContainModuleData();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class UnpauseSpecialPowerUpgradeModuleData : public OpenContainModuleData
{
public:
	UnpauseSpecialPowerUpgradeModuleData();

private:
	int m_specialPowerTemplate; // +0x118
	bool m_obeyRechargeOnTrigger; // +0x11C
	unsigned char m_padTail[0x120 - 0x11D]; // +0x11D, retail never stores
};

// ??0UnpauseSpecialPowerUpgradeModuleData@@QAE@XZ @0x4B544A
UnpauseSpecialPowerUpgradeModuleData::UnpauseSpecialPowerUpgradeModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00BF2558);
	m_specialPowerTemplate = 0;
	m_obeyRechargeOnTrigger = false;
}
