// cl: /O1 /DNDEBUG /MD /GX
//
// ??0StatusBitsUpgradeIfEldestKindofModuleData@@QAE@XZ, retail 0x002547D1,
// 58 bytes. StatusBits-eldest data over the rowed StatusBitsUpgrade-
// ModuleData base (0x00254775, size 0x138): an EldestKindof filter at
// +0x138 built through the rowed Rva00485ADCFilter ctor (0x00485ADC).
// The ModuleData factory at 0x002556EC news 0x13C and calls this ctor as
// sole caller. Shape follows ObjectHelperCtor (opaque base with explicit
// vtable assigned from the body; the filter member stays stateless here
// so the single EH state needs no advance). Row supersedes the ctor pin.

class StatusBitsUpgradeModuleData
{
public:
	StatusBitsUpgradeModuleData();
	~StatusBitsUpgradeModuleData();

protected:
	const void *m_vtable; // +0
	unsigned char m_pad04[0x138 - 4]; // +4..+0x137, real base tail
};

class Rva00485ADCFilter
{
public:
	Rva00485ADCFilter();

private:
	unsigned char m_filter[4];
};

class StatusBitsUpgradeIfEldestKindofModuleData : public StatusBitsUpgradeModuleData
{
public:
	StatusBitsUpgradeIfEldestKindofModuleData();

private:
	Rva00485ADCFilter m_eldestKindofFilter; // +0x138
};

// ??0StatusBitsUpgradeIfEldestKindofModuleData@@QAE@XZ @0x2547D1
StatusBitsUpgradeIfEldestKindofModuleData::StatusBitsUpgradeIfEldestKindofModuleData()
	: StatusBitsUpgradeModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00BF25D8);
}
