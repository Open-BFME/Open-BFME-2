// cl: /DNDEBUG /MD
// ?rva00530FC5@Rva00530FC5@@QAEXXZ, retail 0x00530FC5, 67 bytes.
// Bitmask-guarded clear of 128B chunks: m_count at +0, m_data at +4, m_bits at +8.
// bitsEnd = m_bits + (m_count>>5); early out when empty; loop from the top clearing
// 128B via memset only when the bit word is non-zero then clearing the word.
// Callers 0x00533F3D 0x00534031 0x005341B9 in 0x00533BEC 1759B unclaimed.
// Neighbours Disp32FloatGetters/Disp8ByteOneSetters carry no // cl: line so defaults apply.
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")
void operator delete[](void *block);
void *operator new[](unsigned int size);

class Rva00530FC5
{
public:
	void rva00530FC5();
	void rva00530FAE();
	Rva00530FC5 *rva00530F47(int arg);
	bool rva0053104A(int *out);
	void rva00531008(int arg);
private:
	unsigned int m_count;
	int *m_data;
	unsigned int *m_bits;
	unsigned int m_extra0C;
	unsigned int m_extra10;
};

void Rva00530FC5::rva00530FC5()
{
	unsigned int count = m_count;
	int *base = m_data;
	int *end = base + count;
	unsigned int *bits = m_bits;
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
		if (bitsEnd == m_bits)
			break;
	}
}

// ?rva00530FAE@Rva00530FC5@@QAEXXZ, retail 0x00530FAE, 23 bytes.
// Frees m_data at +4 and m_bits at +8 via array delete; offsets match Rva00530FC5.
// Callers 0x00533B97 0x00533BA2 in 0x00533B74 plus jmp alias 0x00531235. Callee 0x0002FD80 rowed.
void Rva00530FC5::rva00530FAE()
{
	delete[] m_bits;
	delete[] m_data;
}

Rva00530FC5 *Rva00530FC5::rva00530F47(int arg)
{
	unsigned int c = ((unsigned int)arg + 0x3ff) >> 5;
	m_extra0C = 0;
	m_extra10 = 0;
	c &= 0x7ffffe0;
	m_count = c;
	m_data = new int[c];
	m_bits = new unsigned int[m_count >> 5];
	ji_006291ae(m_data, 0, m_count << 2);
	ji_006291ae(m_bits, 0, (m_count >> 5) * 4);
	return this;
}

bool Rva00530FC5::rva0053104A(int *out)
{
	while (m_extra0C < m_count) {
		unsigned int word = m_bits[m_extra0C >> 5];
		if (word != 0) {
			unsigned int shifted = word >> (m_extra0C & 31);
			if (shifted != 0) {
				while ((shifted & 1) == 0) {
					shifted >>= 1;
					++m_extra0C;
				}
				unsigned int d = ((unsigned int *)m_data)[m_extra0C] >> m_extra10;
				while (true) {
					if (d == 0) {
						m_extra10 = 0;
						++m_extra0C;
						break;
					}
					if (d & 1) {
						*out = (m_extra0C << 5) + m_extra10;
						if (++m_extra10 == 32) {
							m_extra10 = 0;
							++m_extra0C;
						}
						return true;
					}
					d >>= 1;
					++m_extra10;
				}
				continue;
			} else {
				m_extra0C = (m_extra0C + 31) & ~31u;
			}
		} else {
			m_extra0C += 32;
		}
	}
	return false;
}
// ?rva00531008@Rva00530FC5@@QAEXH@Z @ 0x00531008 (57B): __thiscall two-level bit set m_data at +4 and m_bits at +8; callers in 0x005329C8 0x00532FEA.
void Rva00530FC5::rva00531008(int arg)
{
	unsigned int u = (unsigned int)arg;
	m_data[u >> 5] |= 1 << (u & 31);
	unsigned int w = u >> 5;
	m_bits[w >> 5] |= 1u << (w & 31);
}
