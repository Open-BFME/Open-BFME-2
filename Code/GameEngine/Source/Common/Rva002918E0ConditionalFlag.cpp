// cl: /DNDEBUG /MD
// Open-BFME: conditional flag reset reconstructed from retail RVA 0x002918E0.

class Rva002918E0Object
{
public:
	void set(unsigned char value);
	void rva004B239A(unsigned char a, unsigned char b);

private:
	char m_pad0[0x2D];
	unsigned char m_flag;
	char m_pad2E;
	unsigned char m_secondary;
	unsigned char m_extra;
};

void Rva002918E0Object::set(unsigned char value)
{
	m_flag = value;
	if (value != 0)
		m_secondary = 0;
}

// ?rva004B239A@Rva002918E0Object@@QAEXEE@Z @0x004B239A 25B. Two-flag setter
// of the same class: stores a to +0x2F with conditional clear of +0x2D,
// then stores b to +0x30. Evidence: identical byte idiom to sibling set
// at 0x004B23B3 plus overlapping callers 0x0048C8F9 and 0x0048D0BE.
void Rva002918E0Object::rva004B239A(unsigned char a, unsigned char b)
{
	m_secondary = a;
	if (a != 0)
		m_flag = 0;
	m_extra = b;
}
