// ??0ObjectCreationUpgradeModuleData@@QAE@XZ
// partial score=0.95 date=2026-09-22
// cl: /O1 /GX /MD /DNDEBUG /arch:SSE

// ??0ObjectCreationUpgradeModuleData@@QAE@XZ, retail 0x004B425B, 128 bytes.
// Upgrade-side ModuleData for object-creation upgrades. Identity is the own
// vtable 0x00C577C8 plus the 0x154 factory news size (friend_newModuleData at
// 0x24FFAC, matched) plus the rowed buildFieldParse proc at 0x4B4084
// (UpgradeObject table). Shape follows AttributeModifierAuraUpdateModuleDataCtor:
// explicit vtable slot with no virtuals emitted, Rva0025342CMember at +0x10
// via the rowed 0x25342C construct, zeroed tail from +0x120 with SSE float
// zeros and or-minus-one flags at +0x140.

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_pad[0x110];
};

class ObjectCreationUpgradeModuleData
{
public:
	ObjectCreationUpgradeModuleData();

private:
	const void *m_vtable; // +0x00
	int m_unused04; // +0x04, left uninitialized like retail
	int m_field08; // +0x08
	int m_field0C; // +0x0C
	Rva0025342CMember m_member10; // +0x10
	int m_field120; // +0x120
	int m_field124; // +0x124
	int m_field128; // +0x128
	float m_field12C; // +0x12C
	float m_field130; // +0x130
	float m_field134; // +0x134
	float m_field138; // +0x138
	unsigned char m_field13C; // +0x13C
	unsigned char m_pad13D[3];
	int m_field140; // +0x140
	int m_field144; // +0x144
	int m_field148; // +0x148
	int m_field14C; // +0x14C
	unsigned char m_field150; // +0x150
	unsigned char m_pad151[3];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ??0ObjectCreationUpgradeModuleData@@QAE@XZ @0x4B425B
ObjectCreationUpgradeModuleData::ObjectCreationUpgradeModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C577C8);
	m_field08 = 0;
	m_field0C = 0;
	m_member10.construct();
	m_field120 = 0;
	m_field124 = 0;
	m_field128 = 0;
	float *floatTriple = &m_field12C;
	floatTriple[0] = 0.0f;
	floatTriple[1] = 0.0f;
	floatTriple[2] = 0.0f;
	_ReadWriteBarrier();
	m_field138 = 0.0f;
	m_field13C = 0;
	int *flagTriple = &m_field140;
	flagTriple[0] |= -1;
	flagTriple[1] = 0;
	flagTriple[2] = 0;
	_ReadWriteBarrier();
	flagTriple[0] |= -1;
	_ReadWriteBarrier();
	m_field14C = 0;
	m_field150 = 0;
	m_field144 = 0;
	m_field148 = 0;
}
