// cl: /MD
// ??0Rva0039627D@@QAE@PAPAXABUBfmeStringRecord004071F7@@@Z @0x0039627D 29B
// Two-arg ctor: m0(*p) plus copy of BfmeStringRecord004071F7 at +4 via rowed
// copy ctor 0x004071F7. Caller at 0x00396943 constructs at dst from (p record).
// Sibling copy ctor at 0x003962AE takes single struct arg with add eax 4.
struct BfmeStringRecord004071F7 {
	unsigned char m_body[12];
	BfmeStringRecord004071F7(const BfmeStringRecord004071F7 &other);
};

struct Rva0039627D {
	void *m_00;
	BfmeStringRecord004071F7 m_04;
	Rva0039627D(void **p, const BfmeStringRecord004071F7 &rec);
	Rva0039627D(const Rva0039627D &other);
};

Rva0039627D::Rva0039627D(void **p, const BfmeStringRecord004071F7 &rec) : m_00(*p), m_04(rec)
{
}

Rva0039627D::Rva0039627D(const Rva0039627D &other) : m_00(other.m_00), m_04(other.m_04)
{
}
