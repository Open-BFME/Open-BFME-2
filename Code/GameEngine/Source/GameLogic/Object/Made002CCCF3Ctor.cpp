// cl: /O1 /GX /DNDEBUG /MD
//
// ??0Made002CCCF3@@QAE@XZ @0x0050BF8F (48B).
// FireLogicNugget ctor: calls the pin-only base ??0Made002CC5E1@@QAE@XZ at
// 0x00507C2D (343B, consistent pin), zeroes three tail dwords at +0x1A4/+0x1A8
// /+0x1AC (xor eax,eax plus three movs, the /O1 three-zero idiom saving 1B
// over three and-zero stores), stores the derived vtable 0x008650B8 (DIR32),
// then stores 0x2710 (10000) at +0x1B0. News size 0x1B4 and field parser
// 0x0050BDED per WeaponNuggetParse.cpp parseFireLogicNugget (caller at
// 0x002CCD18), which news 0x1B4 and runs this ctor. Sibling of the DOTNugget
// ctor ??0Made002CCA37@@QAE@XZ at 0x0050B1FC (two and-zero stores).

class Made002CC5E1
{
public:
	Made002CC5E1();
	virtual ~Made002CC5E1();

private:
	char m_pad[0x1A4 - 4];
};

class Made002CCCF3 : public Made002CC5E1
{
public:
	Made002CCCF3();

private:
	int m_1A4;
	int m_1A8;
	int m_1AC;
	int m_1B0;
};

Made002CCCF3::Made002CCCF3()
{
	m_1A4 = 0;
	m_1A8 = 0;
	m_1AC = 0;
	m_1B0 = 0x2710;
}
