// cl: /DNDEBUG /MD
// BooleanBitmapSet (WorldBuilder: Source/common/BitmapSet.h). WB's debug
// asserts name the class, its methods and members: the constructor 0x00530F47
// ("numBits>0", "BooleanBitmapSet::BooleanBitmapSet"), SetBit 0x00531008
// ("bit<m_numBitsDiv32*32"; WB's body sets the bit in the +4 words and the
// word's bit in the +8 summary words, as retail does) and DoEnum 0x0053104A
// ("m_summaryBits[m_curBitDiv32]!=0"). The two bodies WB leaves unnamed keep their
// address names.
//
// 0x00530FC5, 67 bytes (unnamed in WB):
// Bitmask-guarded clear of 128B chunks: m_numBitsDiv32 at +0, m_bits at +4, m_summaryBits at +8.
// bitsEnd = m_summaryBits + (m_numBitsDiv32>>5); early out when empty; loop from the top clearing
// 128B via memset only when the bit word is non-zero then clearing the word.
// Callers 0x00533F3D 0x00534031 0x005341B9 in 0x00533BEC 1759B unclaimed.
// Neighbours Disp32FloatGetters/Disp8ByteOneSetters carry no // cl: line so defaults apply.
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")
void operator delete[](void *block);
void *operator new[](unsigned int size);

class BooleanBitmapSet
{
public:
	void rva00530FC5();
	__declspec(noinline) void rva00530FAE();
	void rva00531235();
	BooleanBitmapSet(int numBits);
	bool DoEnum(int *out);
	void SetBit(int bit);
private:
	unsigned int m_numBitsDiv32;
	int *m_bits;
	unsigned int *m_summaryBits;
	unsigned int m_curBitDiv32;
	unsigned int m_extra10;
};

void BooleanBitmapSet::rva00530FC5()
{
	unsigned int count = m_numBitsDiv32;
	int *base = m_bits;
	int *end = base + count;
	unsigned int *bits = m_summaryBits;
	unsigned int *bitsEnd = bits + (count >> 5);
	if (bitsEnd == bits)
		return;
	while (true) {
		--bitsEnd;
		end -= 32;
		if (*bitsEnd != 0) {
			ji_006291ae(end, 0, 128);
			*bitsEnd = 0;
		}
		if (bitsEnd == m_summaryBits)
			break;
	}
}

// ?rva00530FAE@BooleanBitmapSet@@QAEXXZ, retail 0x00530FAE, 23 bytes.
// Frees m_bits at +4 and m_summaryBits at +8 via array delete; offsets match BooleanBitmapSet.
// Callers 0x00533B97 0x00533BA2 in 0x00533B74 plus jmp alias 0x00531235. Callee 0x0002FD80 rowed.
void BooleanBitmapSet::rva00530FAE()
{
	delete[] m_summaryBits;
	delete[] m_bits;
}

BooleanBitmapSet::BooleanBitmapSet(int numBits)
{
	unsigned int c = ((unsigned int)numBits + 0x3ff) >> 5;
	m_curBitDiv32 = 0;
	m_extra10 = 0;
	c &= 0x7ffffe0;
	m_numBitsDiv32 = c;
	m_bits = new int[c];
	m_summaryBits = new unsigned int[m_numBitsDiv32 >> 5];
	ji_006291ae(m_bits, 0, m_numBitsDiv32 << 2);
	ji_006291ae(m_summaryBits, 0, (m_numBitsDiv32 >> 5) * 4);
}

bool BooleanBitmapSet::DoEnum(int *out)
{
	while (m_curBitDiv32 < m_numBitsDiv32) {
		unsigned int word = m_summaryBits[m_curBitDiv32 >> 5];
		if (word != 0) {
			unsigned int shifted = word >> (m_curBitDiv32 & 31);
			if (shifted != 0) {
				while ((shifted & 1) == 0) {
					shifted >>= 1;
					++m_curBitDiv32;
				}
				unsigned int d = ((unsigned int *)m_bits)[m_curBitDiv32] >> m_extra10;
				while (true) {
					if (d == 0) {
						m_extra10 = 0;
						++m_curBitDiv32;
						break;
					}
					if (d & 1) {
						*out = (m_curBitDiv32 << 5) + m_extra10;
						if (++m_extra10 == 32) {
							m_extra10 = 0;
							++m_curBitDiv32;
						}
						return true;
					}
					d >>= 1;
					++m_extra10;
				}
				continue;
			} else {
				m_curBitDiv32 = (m_curBitDiv32 + 31) & ~31u;
			}
		} else {
			m_curBitDiv32 += 32;
		}
	}
	return false;
}
// BooleanBitmapSet::SetBit @ 0x00531008 (57B): __thiscall two-level bit set m_bits at +4 and m_summaryBits at +8; callers in 0x005329C8 0x00532FEA.
void BooleanBitmapSet::SetBit(int bit)
{
	unsigned int u = (unsigned int)bit;
	m_bits[u >> 5] |= 1 << (u & 31);
	unsigned int w = u >> 5;
	m_summaryBits[w >> 5] |= 1u << (w & 31);
}

// Native 531235..53123A is JMP 530FAE with receiver and stack unchanged.
// BitmapSet identity comes from the existing independently named methods;
// this forwarding entry's original spelling and lifetime role are unknown.
void BooleanBitmapSet::rva00531235()
{
    rva00530FAE();
}
