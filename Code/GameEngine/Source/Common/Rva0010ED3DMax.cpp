// cl: /MD
// ?rva0010ED3D@Rva0010ED3D@@QAEXH@Z at 0x0010ED3D (15B).
// Conditional max setter at +0x3C: if (v > m_val3C) m_val3C = v.
// Evidence: retail mov eax [esp+4]; cmp eax [ecx+0x3C]; jle; mov [ecx+0x3C] eax; ret 4;
// callers at 0x000A7FCF 0x000A8064 in 0x000A7EFA.
class Rva0010ED3D
{
public:
	void rva0010ED3D(int v);
private:
	char m_pad[0x3C];
	int m_val3C;
};

void Rva0010ED3D::rva0010ED3D(int v)
{
	if (v > m_val3C)
		m_val3C = v;
}
