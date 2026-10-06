// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00587548@Rva00587D9C@@UAEXPAXH@Z, retail 0x00587548 52B.
// Slot 12 offset 0x30 of vtable 0x0086FF38 (class of ??0Rva00587D9C 0x00587D9C).
// Bounds-checked vec60 store: if idx<0 or idx>=size return; vec[idx].m_b0C=1,
// vec[idx].m_i10=0. Stride 0x3c proves 60-byte elements (BfmePod60 stand-in
// with byte at +0xC and dword at +0x10, same shape as BfmePod60Ctor 0x00587500).
// First void* arg unused, second int is idx (ret 8). Same recipe as rowed
// Rva00586D8E slots 10/11 (Rva00586D8EVSlots.cpp) with 60B stride.
#include <vector>

struct BfmePod60S12
{
	char _pad00[0x0c];
	unsigned char m_b0C;
	char _pad0D[3];
	int m_i10;
	char _tail[60 - 0x14];
};

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class Rva00587D9C : public Rva005D6FCC
{
public:
	virtual ~Rva00587D9C();
	virtual void rva00587548(void *arg, int idx);
private:
	_STL::vector<BfmePod60S12> m_vec; // +8
	bool m_flag; // +0x14
	void *m_other; // +0x18
};

void Rva00587D9C::rva00587548(void *arg, int idx)
{
	(void)arg;
	if (idx < 0)
		return;
	if ((unsigned)idx >= m_vec.size())
		return;
	m_vec[idx].m_b0C = 1;
	m_vec[idx].m_i10 = 0;
}
