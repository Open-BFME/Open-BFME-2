// cl: /O1 /MD
//
// ?rva0056C21B@Rva0056C21B@@QAEXMM@Z @0x0056C21B 59B.
// Fan-out: for each of the m_08 entries in the 0xA8-stride array at m_14,
// invoke the pinned 0x004047E3 float-pair probe with the same (a,b).
// Honest address-derived name.
class Rva004047E3
{
public:
	void rva004047E3(float a, float b);
};

class Rva0056C21B
{
public:
	void rva0056C21B(float a, float b);
private:
	char m_pad[8];
	unsigned int m_08;
	char m_pad0C[8];
	Rva004047E3 *m_14;
};

void Rva0056C21B::rva0056C21B(float a, float b)
{
	for (unsigned int i = 0, off = 0; i < m_08; ++i, off += 0xA8)
		((Rva004047E3 *)((char *)m_14 + off))->rva004047E3(a, b);
}
