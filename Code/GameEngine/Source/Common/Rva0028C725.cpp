// cl: /DNDEBUG /MD /EHsc
// ?rva0028C725@Rva0028C725@@QAEPAXI@Z @0x0028C725 42B
// Bit-present table lookup twin of 0x0028C6FB: if bit (idx&31) of word (idx>>5) at +0 is set return table[idx] else 0.
// Evidence: same test plus mov eax [idx*4+VA 0x00DBC2C8]; sole caller 0x002914AF;
// prev rowed Rva0028C6FB gives TU flags and ternary shape.
extern const char **VeterancyNames104;
#define BfmeTable0028C725 ((void **)&VeterancyNames104)

class Rva0028C725
{
public:
	void *rva0028C725(unsigned int idx);

private:
	unsigned int m_bits[8];
};

void *Rva0028C725::rva0028C725(unsigned int idx)
{
	return (m_bits[idx >> 5] & (1u << (idx & 31))) ? BfmeTable0028C725[idx] : 0;
}
