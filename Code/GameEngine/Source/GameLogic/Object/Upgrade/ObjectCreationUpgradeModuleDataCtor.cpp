// cl: /GX /MD /DNDEBUG
//
// ??0ObjectCreationUpgradeModuleData@@QAE@XZ, retail 0x004B425B, 128 bytes.
// Frameless zero-init ctor: explicit vtable 0x00C577C8, two zero ints at
// +0x08/+0x0C, shared member-construct at +0x10 (rowed 0x25342C, 0x110-byte
// Rva0025342CMember), then zero ints/floats through +0x138, false at +0x13C,
// -1/0/0 at +0x140 (tail-pointer plus direct duplicate, OpenContain
// precedent: mixed paths are not folded), zeros at +0x144/+0x148/+0x14C and
// false at +0x150. No globals, one callee. Factory news 0x154.

#include "../../../../Include/GameLogic/Module/Rva0025342CMember.h"

// The retail table at RVA 0x008577C8: 31 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GObjectCreationUpgradeModuleData@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
}
extern const void *const g_00C577C8[31] = {
	(const void *)&__identifier("??_GObjectCreationUpgradeModuleData@@UAEPAXI@Z"), // slot 0 0x004B45CC
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"), // slot 2 0x00065212
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 3 0x0047A69C
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 4 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 6 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 7 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z"), // slot 14 0x000B69A1
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15 0x0047A699
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 16 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 17 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 18 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 19 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 20 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 21 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 22 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 23 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 24 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 25 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 26 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 27 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 28 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 29 0x000D43D0
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 30 0x0050B5C6
};

class __declspec(novtable) ObjectCreationUpgradeModuleData
{
public:
	ObjectCreationUpgradeModuleData();

private:
	void *m_vtable;			// +0x00
	unsigned int m_04;		// +0x04 (retail never stores)
	int m_08;			// +0x08
	int m_0C;			// +0x0C
	Rva0025342CMember m_10;		// +0x10
	int m_120;			// +0x120
	int m_124;			// +0x124
	int m_128;			// +0x128
	float m_12C;			// +0x12C
	float m_130;			// +0x130
	float m_134;			// +0x134
	float m_138;			// +0x138
	bool m_13C;			// +0x13C
	unsigned char m_pad13D[3];
	int m_140;			// +0x140
	int m_144;			// +0x144
	int m_148;			// +0x148
	int m_14C;			// +0x14C
	bool m_150;			// +0x150
};

// ??0ObjectCreationUpgradeModuleData@@QAE@XZ @0x4B425B
ObjectCreationUpgradeModuleData::ObjectCreationUpgradeModuleData()
{
	*(const void **)this = g_00C577C8;
	m_08 = 0;
	m_0C = 0;
	m_10.construct();
	m_120 = 0;
	m_124 = 0;
	m_128 = 0;
	float *fp = &m_12C;
	fp[0] = 0.0f;
	fp[1] = 0.0f;
	fp[2] = 0.0f;
	m_138 = 0.0f;
	m_13C = false;
	int *tail = &m_140;
	tail[0] = -1;
	tail[1] = 0;
	tail[2] = 0;
	m_140 = -1;
	m_14C = 0;
	m_150 = false;
	m_144 = 0;
	m_148 = 0;
}
