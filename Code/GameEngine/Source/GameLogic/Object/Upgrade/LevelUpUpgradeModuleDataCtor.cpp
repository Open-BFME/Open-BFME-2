// cl: /O1 /DNDEBUG /MD
//
// ??0LevelUpUpgradeModuleData@@QAE@XZ, retail 0x0025467E, 32 bytes.
// Frameless ctor over the rowed OpenContainModuleData base (0x253487):
// vtable literal 0x00BF24A0 installed last (overwriting the base folded
// vtable), LevelsToGain zero at +0x118 plus LevelCap zero at +0x11C
// matching the own table at 0x00C574AC. Identity is the LevelUpUpgrade pool
// key at 0x4B3D61 in the same cluster plus the chained buildFieldParse at
// 0x4B3DA6 plus the ModuleData factory at 0x25469E which news 0x120.
// Shape follows ChinookAIUpdateModuleDataCtor (explicit vtable last over a
// rowed base with trailing zeros).

class OpenContainModuleData
{
public:
	OpenContainModuleData();

private:
	unsigned char m_pad[0x118];
};

class LevelUpUpgradeModuleData : public OpenContainModuleData
{
public:
	LevelUpUpgradeModuleData();

private:
	int m_levelsToGain; // +0x118
	int m_levelCap; // +0x11C
};

// ??0LevelUpUpgradeModuleData@@QAE@XZ @0x25467E
LevelUpUpgradeModuleData::LevelUpUpgradeModuleData()
{
	m_levelsToGain = 0;
	m_levelCap = 0;
	*(const void **)this = reinterpret_cast<const void *>(0x00BF24A0);
}
