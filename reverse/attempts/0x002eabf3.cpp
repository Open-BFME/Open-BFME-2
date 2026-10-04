// ?rva002EABF3@Rva002EABF3@@QAE_NXZ
// partial score=0.94 date=2026-10-04
// cl: /O1 /MD
// ?rva002EABF3@Rva002EABF3@@QAE_NXZ @0x002EABF3 33B
// Ring canPush: next write index with wrap at 0x1FF compared against m_read.
// Evidence: mov/sub/inc/neg/sbb/and wrap then xor/cmp/setne vs +0x800; callers at 0x002EBD46/0x002EBD80 test al.
class Rva002EABF3
{
public:
	bool rva002EABF3();
private:
	unsigned int m_slots[0x200];
	int m_read;
	int m_write;
};

// ?rva002EABF3@Rva002EABF3@@QAE_NXZ present-unmatched
bool Rva002EABF3::rva002EABF3()
{
	int w = m_write;
	int d = w - 0x1FF;
	int next = w + 1;
	int mask = d ? -1 : 0;
	next &= mask;
	return next != m_read;
}
