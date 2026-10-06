// cl: /MD
//
// ?rva00142C30@Rva00142C30@@QAEPAXH@Z, RVA 0x00142C30, 11B.
// Indexed fetch from inline array at +0x30: mov eax [esp+4] mov eax [ecx+eax*4+0x30].
// Evidence: caller at 0x0014BF83 passes loop index in ebx with this in ebp;
// count at +0xB0 via 0x00142C20 and base array 0x30-0xAC zeroed by ctor 0x00142EE0;
// same array released by dtor 0x00142FE0; honest address name.

class Rva00142C30
{
	char m_pad[0x30];
	void *m_items[32];

public:
	void *rva00142C30(int index);
};

void *Rva00142C30::rva00142C30(int index)
{
	return m_items[index];
}
