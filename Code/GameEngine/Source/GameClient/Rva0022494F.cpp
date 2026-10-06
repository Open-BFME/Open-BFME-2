// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0022494F@Rva0022494F@@QAEXXZ @0x0022494F 37B
// Reset with two string releases plus table tail-jmp to rowed clear 0x0022380B.
// Evidence: chain lane calls rowed releaseBuffer 0x00036410 twice plus rowed 0x0022380B; and byte +0x24 0xf4 plus and +8 0 plus or +0xc -1; caller at 0x00224BBD.
#include "ascii_string.h"

class Rva00223591
{
public:
	void rva0022380B();
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

class Rva0022494F
{
public:
	void rva0022494F();
private:
	AsciiString m_a;
	AsciiString m_b;
	int m_8;
	int m_c;
	Rva00223591 m_table;
	unsigned char m_24;
};

void Rva0022494F::rva0022494F()
{
	m_a.clear();
	m_b.clear();
	m_24 &= 0xf4;
	m_8 = 0;
	m_c = -1;
	return m_table.rva0022380B();
}
