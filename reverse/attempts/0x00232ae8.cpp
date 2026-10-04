// ?rva00232AE8@Keyboard@@AAEXXZ
// partial score=0.97 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
// ?rva00232AE8@Keyboard@@AAEXXZ @0x00232AE8 147B. Clears key vector then re-adds flagged slots.
// Evidence: erase row 0x003FA4DB plus push_back row 0x00539A2E plus rva00232A42 pin plus slot 0x3c virtual plus LINK BONUS.
#include <vector>

struct BfmePod8 { int a[2]; };
struct BfmeE8 { unsigned char m0; unsigned char m1; unsigned short m2; int m4; };
struct KeySlot { unsigned char m0; unsigned char m1; unsigned char m2; unsigned char m3; unsigned char m4; unsigned char m5; unsigned char m6; unsigned char m7; };

class Keyboard
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void slot3C();
private:
	void rva00232A42();
	void rva00232AE8();
	unsigned char m_pad04[0x10 - 0x04];
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_keys;
	unsigned char m_pad1C[0x1e - 0x1c];
	KeySlot m_slots[256];
	unsigned char m_pad822[0xe1c - 0x81e];
	int m_inputFrame;
};

void Keyboard::rva00232AE8()
{
	*(unsigned short *)&m_slots[15] = 1;
	*(unsigned char *)((char *)&m_slots[15] - 1) = 1;
	*(int *)((char *)&m_slots[15] + 2) = m_inputFrame;
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > *pod = (_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > *)&m_keys;
	pod->erase(pod->begin(), pod->end());
	for (int i = 0; i < 256; ++i) {
		if (i == 15)
			continue;
		if ((m_slots[i].m0 & 2) == 0)
			continue;
		BfmeE8 e;
		e.m0 = (unsigned char)i;
		e.m2 = 1;
		e.m1 = 0;
		e.m4 = m_inputFrame;
		m_keys.push_back(e);
	}
	if (m_keys.begin() != m_keys.end()) {
		rva00232A42();
		slot3C();
	}
}
