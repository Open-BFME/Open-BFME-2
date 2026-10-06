// cl: /MD /GX-
// ?rva00270BA8@Rva00270BA8@@QAEPAVRva00270025@@XZ @0x00270BA8 49B
// Lazy getter for Rva00270025 at +0x354: new 0x74 and ctor on first use then return it.
// Evidence: calls ctor 0x00270025 just landed; new 0x74; callers at 0x002736E3 0x00273765; honest Rva names.
class Rva00270025
{
public:
	Rva00270025();
	virtual ~Rva00270025();
private:
	void *m_04[14];
	int m_3c[14];
};

void *__cdecl operator new(unsigned int size) throw();

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
private:
	unsigned char m_pad[0x354];
	Rva00270025 *m_354;
};

Rva00270025 *Rva00270BA8::rva00270BA8()
{
	if (!m_354)
		m_354 = new Rva00270025;
	return m_354;
}
