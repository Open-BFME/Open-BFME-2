// cl: /MD
//
// ?rva00362499@Rva00362499@@QAEEXZ retail 0x00362499 15 bytes. Dual null check
// returning 1 only if both +4 and +8 are non-zero. Evidence: two callers
// 0x003624C4 and 0x003627B8, no callees, 15B xor-first compare shape.

class Rva00362499
{
public:
	unsigned char rva00362499();
private:
	char m_00[4];
	void *m_04;
	void *m_08;
};

unsigned char Rva00362499::rva00362499()
{
	return m_08 != 0 && m_04 != 0;
}
