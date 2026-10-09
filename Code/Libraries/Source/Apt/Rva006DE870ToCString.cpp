// cl: /DNDEBUG /MD /EHsc
// ?rva006DE870@AptValue@@QBEXPAD@Z @0x006DE870 (111B).
// Copies the value's string form into a caller buffer: converts through the
// rowed AptValue::toString 0x006DD6C0 into a scoped EAStringC and copies its
// bytes through the terminator. Evidence: calls 0x006D2F90 (scoped string
// constructor), 0x006DD6C0 on this, 0x00620090 (c_str) and 0x006D3010 (dtor);
// the callee proves the AptValue receiver, constness follows toString.

class EAStringC
{
	void *m_pData;

public:
	EAStringC();
	~EAStringC();
	const char *rva00620090() const;
};

class AptValue
{
public:
	void toString(EAStringC &out) const;
	void rva006DE870(char *dst) const;
};

void AptValue::rva006DE870(char *dst) const
{
	EAStringC text;
	toString(text);
	const char *src = text.rva00620090();
	char c;
	do
	{
		c = *src++;
		*dst++ = c;
	} while (c != 0);
}
