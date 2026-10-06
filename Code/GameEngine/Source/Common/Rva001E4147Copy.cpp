// cl: /MD
// ?rva001E4147@Rva001E4147@@QAEXPAURva001E4147Twelve@@@Z @0x001E4147 24B: copy 12B from src+0x38 to this+0x14 if src.
// Evidence: 12 callers e.g. 0x0026457D 0x0026B4C1 0x0026D588; 3x movsd shape.
struct Rva001E4147Twelve { int a; int b; int c; };
class Rva001E4147
{
public:
	void rva001E4147(Rva001E4147Twelve *src);
	char _0[0x14];
	Rva001E4147Twelve m_14;
};

void Rva001E4147::rva001E4147(Rva001E4147Twelve *src)
{
	if (src)
		m_14 = *(Rva001E4147Twelve *)((char *)src + 0x38);
}
