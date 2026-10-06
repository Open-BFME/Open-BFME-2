// cl: /MD
// ?rva0056B89F@LivingWorldArmyIconSubObject@@QAEEXZ @0x0056B89F 56B: predicate over +0xbc index and +0xac inner (+0x58 mask +0x5e flag) with +0xc0 flag, tail-jmps to Rva005C41C9::rva005C4B26. Evidence: caller 0x0056BA07 passes result to Rva005C4B56::rva005C4B96(E), tail target pin ?rva005C4B26@Rva005C41C9@@QAEEXZ, neighbour Rva0056B8F4 // cl: /O1 /Oy- /MD and Rva005C4180Refresh v17 shape.
struct Inner0056B89F
{
	char _00[0x58];
	int m_58;
	char _5C[2];
	unsigned char m_5E;
};

class Rva005C41C9
{
public:
	unsigned char rva005C4B26();
};

class LivingWorldArmyIconSubObject
{
private:
	char _00[0xAC];
	Inner0056B89F *m_ac;
	char _B0[0x0C];
	int m_bc;
	unsigned char m_c0;
public:
	unsigned char rva0056B89F();
};

unsigned char LivingWorldArmyIconSubObject::rva0056B89F()
{
	int idx = m_bc;
	if (idx == -1)
		return 0;
	Inner0056B89F *inner = m_ac;
	if ((inner->m_58 & (1 << idx)) == 0)
		return 0;
	if (inner->m_5E == 0 || m_c0 != 0)
		return ((Rva005C41C9 *)this)->rva005C4B26();
	return 0;
}
