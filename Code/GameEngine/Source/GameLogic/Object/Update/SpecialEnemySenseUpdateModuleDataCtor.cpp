// cl: /GX /DNDEBUG /MD
//
// ??0SpecialEnemySenseUpdateModuleData@@QAE@XZ, retail 0x0025404A, 65 bytes.
// EH ctor: single state-0 store, vtable 0x00BF1AD8 at +0, filter member at
// +8 built by the pinned nullary ctor, 0.0f at +0xC, 1 at +0x10. Table
// 0xBF1B88 holds SpecialEnemyFilter@8 ScanRange@C ScanInterval@10; factory
// 0x25409C news 0x14; ctor ends where the 17B proc begins. InheritUpgrade
// V4 recipe verbatim: empty CreateModuleData base as the sole unwindable
// (state 0, no transitions, no -1) plus body in retail order with the
// filter driven by the construct-method alias pin.

// Retail VA 0x00BF1AD8 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
extern "C" void __identifier("??1Coord2D@@QAE@XZ")();
extern "C" void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
extern "C" void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
extern "C" void __identifier("??_GSpecialEnemySenseUpdateModuleData@@UAEPAXI@Z")();
extern "C" void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
extern "C" void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
extern "C" const void *const vtbl_00BF1AD8[] = {
	(const void *)&__identifier("??_GSpecialEnemySenseUpdateModuleData@@UAEPAXI@Z"),
	(const void *)&__identifier("??1Coord2D@@QAE@XZ"),
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
};

class Rva003623E5Member
{
public:
	void construct();

private:
	int m_value;
};

class CreateModuleData
{
public:
	CreateModuleData() {}
	~CreateModuleData();

private:
};

class SpecialEnemySenseUpdateModuleData : public CreateModuleData
{
public:
	SpecialEnemySenseUpdateModuleData();

private:
	void *m_vtable;
	unsigned int m_unused04;
	Rva003623E5Member m_filter;
	float m_scanRange;
	int m_scanInterval;
};

// ??0SpecialEnemySenseUpdateModuleData@@QAE@XZ
SpecialEnemySenseUpdateModuleData::SpecialEnemySenseUpdateModuleData()
{
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00BF1AD8));
	m_filter.construct();
	m_scanRange = 0.0f;
	m_scanInterval = 1;
}
