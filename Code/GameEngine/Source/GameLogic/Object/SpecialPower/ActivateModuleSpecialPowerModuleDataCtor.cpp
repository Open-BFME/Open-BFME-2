// cl: /O1 /DNDEBUG /MD
// stlport
//
// ??0ActivateModuleSpecialPowerModuleData@@QAE@XZ, retail 0x00256DA1,
// 36 bytes. ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54,
// 0xC8 bytes per the ToggleHidden row): the implicit _STL::vector<int>
// member at +0xC8 builds through the folded Vector_base at 0x211E58 (int
// spelling reuses the existing pin), and the compiler installs the derived
// vtable 0x00BF3F60 between the vector setup and call (TransitionDamageFX
// precedent; non-dtor virtual so no EH prolog draws). Class size 0xD4 proven
// by the ActivateModuleSpecialPower data factory (news 0xD4, sole caller at
// 0x256DE9). Row supersedes the ctor pin.

#include <vector>

class Rva0044EB54
{
public:
	Rva0044EB54();
	virtual void unused();

protected:
	// +0x00 vptr; remainder opaque to 0xC8 (ToggleHidden-inferred size).
	unsigned char m_opaque[0xC4];
};

class ActivateModuleSpecialPowerModuleData : public Rva0044EB54
{
public:
	ActivateModuleSpecialPowerModuleData();

private:
	// +0xC8 vector (implicit default init; ends at the rowed 0xD4 size).
	_STL::vector<int> m_vectorC8;
};

// ??0ActivateModuleSpecialPowerModuleData@@QAE@XZ @0x00256DA1
ActivateModuleSpecialPowerModuleData::ActivateModuleSpecialPowerModuleData()
	: Rva0044EB54()
{
}
