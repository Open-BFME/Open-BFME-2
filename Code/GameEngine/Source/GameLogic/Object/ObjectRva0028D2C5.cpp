// cl: /MD
//
// ?rva0028D2C5@Object@@QBEMPAX@Z @0x0028D2C5 (54B).
// Object float gate: if the template byte at +0x113 carries 0x40 and the
// caller block's dword at +0xC equals 6, returns the shared 1.0f at
// 0x00BBB8D8; else when the helper at this+0x254 is present tail-calls its
// vtable slot 2 with the same arg; otherwise returns the shared 0.0f at
// 0x00BBAEAC. Retail shape is template flag test plus arg field compare
// plus fld 1.0f, else helper load plus test plus vtable jmp, else fld 0.0f.
// Caller at 0x00508784. Layout from retail immediates only; helper, template
// and arg holder keep address tokens so no identity is invented.


struct Rva0028D2C5Template
{
	unsigned char m_pad[0x113];
	unsigned char m_byte113;
};

struct Rva0028D2C5Arg
{
	char m_pad[0xC];
	int m_valC;
};

class Rva0028D2C5Helper
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual float slot2(void *a);
};

class Object
{
public:
	float rva0028D2C5(void *a) const;

private:
	char m_pad00[4];
	Rva0028D2C5Template *m_template;
	char m_pad08[0x254 - 8];
	Rva0028D2C5Helper *m_helper254;
};

float Object::rva0028D2C5(void *a) const
{
	if ((m_template->m_byte113 & 0x40) != 0) {
		if (((Rva0028D2C5Arg *)a)->m_valC == 6)
			return 1.0f;
	} else {
		Rva0028D2C5Helper *helper = m_helper254;
		if (helper)
			return helper->slot2(a);
	}
	return 0.0f;
}
