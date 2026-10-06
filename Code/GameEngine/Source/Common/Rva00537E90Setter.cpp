// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00537E90@Rva00537E90@@QAEXM@Z @0x00537E90 29B float setter: if m_f28 != v then m_f28 = v plus virtual [eax+0x14].
// Evidence: packet disassembly; sibling Rva00537EAD has float at +0x28; caller 0x00537FCC reads real then calls here.
class Rva00537E90
{
public:
	virtual ~Rva00537E90();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void rva00537E90(float v);

private:
	unsigned char m_pad[0x24];
	float m_f28;
};

void Rva00537E90::rva00537E90(float v)
{
	if (v != m_f28) {
		m_f28 = v;
		v5();
	}
}
