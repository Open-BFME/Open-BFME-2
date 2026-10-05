// cl: /O1 /GX /arch:SSE /DNDEBUG /MD
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
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0025523F();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0025523F=??_GSpecialEnemySenseUpdateModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00BF1AD8[] = {
	(const void *)&vfn_0025523F,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000B69A1,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_0050B5C6
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
