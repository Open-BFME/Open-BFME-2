// ??0PhysicsBehaviorModuleData@@QAE@XZ
// partial score=0.85 date=2026-09-23
// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0PhysicsBehaviorModuleData@@QAE@XZ, retail 0x00390119, 176 bytes.
// V1 banked 0.85: explicit m_vtable plus retail-order body; wall is early
// 5.0 load plus post-vtable store interleave. See memory.md 2026-09-23.
extern const int LogicFramesPerSecond;

class PhysicsBehaviorModuleData
{
public:
	PhysicsBehaviorModuleData();

private:
	void *m_vtable; // +0
	int m_unused04; // +4
	float m_08; // +8
	float m_0C; // +0xC
	float m_10; // +0x10
	float m_14; // +0x14
	int m_18; // +0x18
	int m_1C; // +0x1C
	int m_20; // +0x20
	int m_24; // +0x24
	float m_28; // +0x28
	float m_2C; // +0x2C
	float m_30; // +0x30
	float m_34; // +0x34
	float m_38; // +0x38
	float m_3C; // +0x3C
	unsigned char m_40; // +0x40
	unsigned char m_41; // +0x41
	unsigned char m_42; // +0x42
	unsigned char m_43; // +0x43
	float m_44; // +0x44
	float m_48; // +0x48
	float m_4C; // +0x4C
	int m_50; // +0x50
	int m_54; // +0x54
	unsigned char m_58; // +0x58
	unsigned char m_59; // +0x59
	unsigned char m_5A; // +0x5A
	unsigned char m_5B; // +0x5B
};

// ??0PhysicsBehaviorModuleData@@QAE@XZ @0x390119
PhysicsBehaviorModuleData::PhysicsBehaviorModuleData()
{
	m_08 = 1.3f;
	m_0C = 1.3f;
	m_2C = 1.3f;
	m_30 = 1.3f;
	m_3C = 0.0f;
	m_40 = 0;
	m_41 = 0;
	m_42 = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_59 = 0;
	m_vtable = reinterpret_cast<void *>(0x00C4ED70);
	m_10 = 0.33f;
	m_14 = 0.66f;
	m_24 = 2;
	m_28 = 5.0f;
	m_34 = 0.33f;
	m_38 = 0.66f;
	m_44 = 0.33f;
	m_48 = 0.66f;
	m_4C = 1.0f;
	m_18 = LogicFramesPerSecond;
	m_1C = LogicFramesPerSecond + LogicFramesPerSecond;
	m_20 = LogicFramesPerSecond;
}
