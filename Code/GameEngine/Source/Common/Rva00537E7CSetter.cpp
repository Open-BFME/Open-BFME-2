// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00537E7C@Rva00537E7C@@QAEX_N@Z @0x00537E7C 20B bool setter: if m_b2C != v then m_b2C = v plus virtual [eax+0x10].
// Evidence: packet disassembly; caller 0x00537FCC readByte+setne passes bool; siblings Rva00537F74/Rva00537FA0/Rva00537E90 same this share +0x20/+0x24/+0x28 slots.
class Rva00537E7C
{
public:
	virtual ~Rva00537E7C();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	void rva00537E7C(bool v);

private:
	unsigned char m_pad[0x28];
	bool m_b2C;
};

void Rva00537E7C::rva00537E7C(bool v)
{
	if (v != m_b2C) {
		m_b2C = v;
		v4();
	}
}
