// cl: /MD
//
// ?rva002DBA6A@BfmeSubobject00229875@@QAEXXZ, retail 0x002DBA6A, 79 bytes.
// Clear/reset of BfmeSubobject00229875: calls slot-4 virtual (+0x10) on each
// of the eight 0x1AC elements at +4, memsets blocks at +0xD64 (0x10) and
// +0xD74 (0x28) via rowed ji_006291ae thunk, zeroes dword at +0xDA0 and sets
// byte at +0xD9C to 1. Evidence: layout proven by SaveGameInfoCopyBFME2.cpp
// (vptr 0xBE7460, 8x0x1AC at +4, blocks, flag, word); callers 0x002DC5DD and
// 0x002DD173 operate on object44 (esi+0x44); prev Rva002DBA3FXfer shares
// /O1 /MD. Honest address name; owner class proven by layout and callers.
#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual const char *typeName() const;
	virtual void xfer();
};

struct BfmeSaveElement002295D7 : Snapshot
{
	virtual void unkSlot4();
	char _pad[0x1AC - 4];
};

struct BfmeSaveBlock4 { unsigned int values[4]; };
struct BfmeSaveBlock10 { unsigned int values[10]; };

class BfmeSubobject00229875
{
public:
	void rva002DBA6A();
private:
	void *m_vptr;
	BfmeSaveElement002295D7 m_elements[8];
	BfmeSaveBlock4 m_blockD64;
	BfmeSaveBlock10 m_blockD74;
	unsigned char m_flagD9C;
	unsigned char _padD9D[3];
	unsigned int m_wordDA0;
};

void BfmeSubobject00229875::rva002DBA6A()
{
	for (int i = 0; i < 8; ++i)
		m_elements[i].unkSlot4();
	memset(&m_blockD64, 0, sizeof(m_blockD64));
	memset(&m_blockD74, 0, sizeof(m_blockD74));
	m_wordDA0 = 0;
	m_flagD9C = 1;
}
