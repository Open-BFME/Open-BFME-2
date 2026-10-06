// cl: /DNDEBUG /MD /EHsc
// ?rva0028C753@Rva0028C753@@QAEPAXI@Z @0x0028C753 42B
// Bit-present table lookup twin of 0x0028C6FB: if bit (idx&31) of word (idx>>5) at +0 is set return table[idx] else 0.
// Evidence: same test plus mov eax [idx*4+VA 0x00DA5F30]; callers 0x00292550 0x0045D908;
// prev rowed Rva0028C725 gives TU flags and ternary shape.
extern const char **BodyStateNames;
#define BfmeTable0028C753 ((void **)&BodyStateNames)

class Rva0028C753
{
public:
	void *rva0028C753(unsigned int idx);

private:
	unsigned int m_bits[8];
};

void *Rva0028C753::rva0028C753(unsigned int idx)
{
	return (m_bits[idx >> 5] & (1u << (idx & 31))) ? BfmeTable0028C753[idx] : 0;
}
