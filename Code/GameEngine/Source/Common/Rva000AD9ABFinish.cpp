// cl: /O1 /MD
//
// ?rva000AD9AB@Rva000AD9AB@@QAEXHH_N@Z @0x000AD9AB 83B
// Rectangular-grid bit setter: bounds-check x/y against width (+0x08) and
// height (+0x0c), form the byte index pitch(+0x34)*y + (x>>3), range-check it
// against the begin/end byte pointers (+0x44/+0x48), then set/clear bit (x&7).
// Address-derived name; near-twin of the BFME1 BfmeMaskAX::bfmeMarkAX family.

struct Rva000AD9ABBytes
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char &operator[](int index) { return m_begin[index]; }
};

class Rva000AD9AB
{
public:
	void rva000AD9AB(int x, int y, bool value);
	void rva000AD9FE();
	void rva000ADB89(int x, int y, bool value);
	void rva000ADBE3(int x, int y, bool value);
	void rva000ADC41(int x, int y, unsigned char value);

private:
	char m_pad00[8];
	int m_width;
	int m_height;
	char m_pad10[0x24];
	int m_pitch;
	char m_pad38[0x0c];
	Rva000AD9ABBytes m_bits;
	char m_pad4C[0x68 - 0x4C];
	Rva000AD9ABBytes m_plane68;
	char m_pad70[0x80 - 0x70];
	Rva000AD9ABBytes m_plane80;
	char m_pad88[0x8C - 0x88];
	Rva000AD9ABBytes m_plane8C;
};

void Rva000AD9AB::rva000AD9AB(int x, int y, bool value)
{
	Rva000AD9AB *self = this;

	if (x < 0)
		return;
	if (y < 0)
		return;
	if (y >= self->m_height)
		return;
	if (x >= self->m_width)
		return;

	int index = self->m_pitch * y + (x >> 3);
	if ((unsigned int)index >= self->m_bits.size())
		return;

	unsigned char *slot = self->m_bits.m_begin + index;
	if (value)
		*slot |= (unsigned char)(1 << (x & 7));
	else
		*slot &= (unsigned char)~(1 << (x & 7));
}

// ?rva000AD9FE@Rva000AD9AB@@QAEXXZ, retail 0x000AD9FE, 28 bytes.
// Zero-fill of the bit plane at +0x44/+0x48 via rowed fill 0x000ABC25.
// Evidence: gap between 0x000AD9AB and 0x000ADA1A; same +0x44/+0x48 layout.
namespace _STL { void __cdecl fill(unsigned char *, unsigned char *, const unsigned char &); }
void Rva000AD9AB::rva000AD9FE()
{
	unsigned char tmp = 0;
	_STL::fill(m_bits.m_begin, m_bits.m_end, tmp);
}

// ?rva000ADB89@Rva000AD9AB@@QAEXHH_N@Z @0x000ADB89 90B: bit setter on the
// +0x68/+0x6C plane, same shape as rva000ADBE3 (early x copy, inlined
// size/operator[], cur-load before mask).
void Rva000AD9AB::rva000ADB89(int x, int y, bool value)
{
	int xx = x;
	if (xx < 0)
		return;
	if (y < 0)
		return;
	if (y >= m_height)
		return;
	if (xx >= m_width)
		return;

	int index = m_pitch * y + (xx >> 3);
	int size = (int)m_plane68.size();
	if ((unsigned int)index >= (unsigned int)size)
		return;

	unsigned char cur = m_plane68[index];
	unsigned char mask = (unsigned char)(1 << (xx & 7));
	if (value)
		cur |= mask;
	else
		cur &= (unsigned char)~mask;
	m_plane68[index] = cur;
}

// ?rva000ADBE3@Rva000AD9AB@@QAEXHH_N@Z @0x000ADBE3 94B: bit setter on the
// +0x80/+0x84 plane, same bounds/index shape as rva000AD9AB but with a
// byte-local modify-store.
void Rva000AD9AB::rva000ADBE3(int x, int y, bool value)
{
	int xx = x;
	if (xx < 0)
		return;
	if (y < 0)
		return;
	if (y >= m_height)
		return;
	if (xx >= m_width)
		return;

	int index = m_pitch * y + (xx >> 3);
	int size = (int)m_plane80.size();
	if ((unsigned int)index >= (unsigned int)size)
		return;

	unsigned char cur = m_plane80[index];
	unsigned char mask = (unsigned char)(1 << (xx & 7));
	if (value)
		cur |= mask;
	else
		cur &= (unsigned char)~mask;
	m_plane80[index] = cur;
}

// ?rva000ADC41@Rva000AD9AB@@QAEXHHM@Z @0x000ADC41 64B: byte setter on the
// +0x8C/+0x90 plane. Byte index is width*y + x (no shift); stores the value
// byte directly instead of flipping a bit.
void Rva000AD9AB::rva000ADC41(int x, int y, unsigned char value)
{
	if (x < 0)
		return;
	if (y < 0)
		return;
	if (y >= m_height)
		return;
	if (x >= m_width)
		return;

	int index = m_width * y + x;
	if ((unsigned int)index >= m_plane8C.size())
		return;

	m_plane8C[index] = value;
}
