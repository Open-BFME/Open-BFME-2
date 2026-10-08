// cl: /MD

// ?rva0041FE86@Rva0041FE86@@QAEXXZ, retail 0x0041FE86, 101 bytes. Init method:
// zeroes the 20-dword array at +0x18 plus the 20-byte array at +0x70 then sets
// defaults plus -1 at +0x68 then derives +0xC as 3-or-2 from TheGameLogic
// 0x00DFE78C+0x114 == 3 then tail-calls virtual slot 0x60.
// Target evidence: or -1 plus xor-first plus sete-inc-inc plus tail jmp;
// TheGameLogic precedent GameLogicRva003BC6C7Wrapper plus at114 precedent
// Rva002BA8F1AddPlayer; sole caller at 0x004201BA.

struct Rva00DFE78CHolder
{
	char m_pad[0x114];
	int m_114;
};

extern class GameLogic *TheGameLogic;

class Rva0041FE86
{
public:
	virtual void virt00() = 0;
	virtual void virt01() = 0;
	virtual void virt02() = 0;
	virtual void virt03() = 0;
	virtual void virt04() = 0;
	virtual void virt05() = 0;
	virtual void virt06() = 0;
	virtual void virt07() = 0;
	virtual void virt08() = 0;
	virtual void virt09() = 0;
	virtual void virt10() = 0;
	virtual void virt11() = 0;
	virtual void virt12() = 0;
	virtual void virt13() = 0;
	virtual void virt14() = 0;
	virtual void virt15() = 0;
	virtual void virt16() = 0;
	virtual void virt17() = 0;
	virtual void virt18() = 0;
	virtual void virt19() = 0;
	virtual void virt20() = 0;
	virtual void virt21() = 0;
	virtual void virt22() = 0;
	virtual void virt23() = 0;
	virtual void virt24() = 0;
	void rva0041FE86();
private:
	char m_pad04[0x8];
	int m_0C;
	char m_pad10[0x8];
	int m_dword18[0x14];
	int m_68;
	int m_6C;
	unsigned char m_byte70[0x14];
	unsigned char m_84;
	unsigned char m_85;
	unsigned char m_86;
	char m_pad87;
	int m_88;
	int m_8C;
	unsigned char m_90;
	unsigned char m_91;
};

void Rva0041FE86::rva0041FE86()
{
	for (int i = 0; i < 0x14; ++i)
	{
		m_dword18[i] = 0;
		m_byte70[i] = 0;
	}
	m_68 = -1;
	m_8C = 0;
	m_84 = 0;
	m_85 = 0;
	m_86 = 0;
	m_6C = 0;
	m_88 = 0;
	m_90 = 0;
	m_91 = 0;
	m_0C = ((*(Rva00DFE78CHolder **)&TheGameLogic)->m_114 == 3 ? 3 : 2);
	virt24();
}
