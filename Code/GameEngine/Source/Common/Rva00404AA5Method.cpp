// cl: /MD
// ?rva00404AA5@Rva00404781@@QAEPAV1@XZ retail 0x00404AA5 12B
// Evidence: __thiscall chain lane calls 0x0040475C rowed ?rva0040475C@Rva00404781@@QAEXXZ; push esi mov esi ecx call mov eax esi pop esi ret returns this
class Rva00404781
{
public:
	void rva0040475C();
	Rva00404781 *rva00404AA5();
private:
	float m_a[20]; // +0x00
	float m_b[20]; // +0x50
	unsigned int m_flags0; // +0xA0
	unsigned int m_flags1; // +0xA4
};

Rva00404781 *Rva00404781::rva00404AA5()
{
	rva0040475C();
	return this;
}
