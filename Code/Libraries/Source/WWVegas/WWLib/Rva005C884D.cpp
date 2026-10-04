// cl: /O1 /MD
// ?rva005C884D@Rva005C884D@@QAEXG@Z, retail 0x005C884D, 41 bytes.
// Saturating word add at +0x44 with 0xFFFF clamp on carry; callers 0x00569719/0x005697DA pass dword.
// Evidence: unlock lane; prev Rva005C87F8Adjust /O1; vslot none; naming __thiscall ret 4.
class Rva005C884D
{
public:
	void rva005C884D(unsigned short val);
private:
	unsigned char m_pad00[0x44];
	unsigned short m_44; // +0x44
};

void Rva005C884D::rva005C884D(unsigned short val)
{
	unsigned short old = m_44;
	int sum = (int)old + (int)val;
	if (sum < (int)old)
		m_44 = 0xFFFF;
	else
		m_44 = (unsigned short)(old + val);
}
