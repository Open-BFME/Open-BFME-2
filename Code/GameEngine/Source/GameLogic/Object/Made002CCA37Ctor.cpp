// cl: /GX /DNDEBUG /MD
//
// ??0Made002CCA37@@QAE@XZ @0x0050B1FC (32B).
// DOTNugget ctor: calls the pin-only base ??0Made002CC5E1@@QAE@XZ at
// 0x00507C2D (343B, consistent pin), zeroes the two tail dwords at +0x1A4 and
// +0x1A8 (the 8 bytes past the 0x1A4 base news size to the 0x1AC derived news
// size per WeaponNuggetParse.cpp parseDOTNugget), then stores the derived
// vtable 0x00864C38 (DIR32 filled by the gate). Caller is
// ?parseDOTNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at 0x002CCA5C
// (Code/GameEngine/Source/GameLogic/Object/WeaponNuggetParse.cpp), which news
// 0x1AC and runs this ctor. The /O1 and-zero idiom (and [m],0 for =0) matches
// the recipe table.

class Made002CC5E1
{
public:
	Made002CC5E1();
	virtual ~Made002CC5E1();

private:
	char m_pad[0x1A4 - 4];
};

class Made002CCA37 : public Made002CC5E1
{
public:
	Made002CCA37();

private:
	int m_1A4;
	int m_1A8;
};

Made002CCA37::Made002CCA37()
{
	m_1A4 = 0;
	m_1A8 = 0;
}
