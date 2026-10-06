// cl: /MD
struct Rva00291198Dest
{
	unsigned char m_pad[0xC0];
	int m_C0;
};
class Rva00291198Host
{
public:
	void rva00291198(Rva00291198Dest *d);
	void rva002910B7(Rva00291198Dest *d);
private:
	unsigned char m_pad[0x460];
	int m_460;
};
// ?rva00291198@Rva00291198Host@@QAEXPAURva00291198Dest@@@Z
void Rva00291198Host::rva00291198(Rva00291198Dest *d)
{
	rva002910B7(d);
	d->m_C0 = m_460;
}
