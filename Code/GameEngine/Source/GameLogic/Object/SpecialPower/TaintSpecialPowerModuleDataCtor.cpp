// cl: /O1 /MD /DNDEBUG /arch:SSE
// ??0TaintSpecialPowerModuleData@@QAE@XZ at retail 0x004C4AB8 (51 bytes,
// frameless): base call into the opaque intermediate 0x004930A0 (pinned),
// explicit vtable store at +0, zeros at +0x7C/+0x84/+0x88, 10.0f at +0x80
// matching the Taint table (TaintObject at +0x7C, TaintRadius at +0x80,
// TaintFX at +0x84, TaintOCL at +0x88). Factory at 0x00251EE4 is the sole
// caller. Row supersedes the ctor pin.
// Retail VA 0x00C5D608 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_004C4AEB();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_004C4AEB=??_GTaintSpecialPowerModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C5D608[] = {
	(const void *)&vfn_004C4AEB,
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

class Rva004930A0
{
public:
	Rva004930A0();

protected:
	unsigned char m_pad[0x7C];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class TaintSpecialPowerModuleData : public Rva004930A0
{
public:
	TaintSpecialPowerModuleData();

	int m_taintObject;
	float m_taintRadius;
	int m_taintFX;
	int m_taintOCL;
};

TaintSpecialPowerModuleData::TaintSpecialPowerModuleData()
	: Rva004930A0()
{
	int *taintObject = &m_taintObject;
	*(unsigned int *)this = ((unsigned int)vtbl_00C5D608);
	*taintObject = 0;
	m_taintFX = 0;
	m_taintOCL = 0;
	m_taintRadius = 10.0f;
}
