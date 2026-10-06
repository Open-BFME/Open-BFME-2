// cl: /MD
// ?rva000E4567@Rva000E4567@@QAEXXZ retail 0x000E4567 56B
// Evidence: Release ref at +0x28 via dec +4 plus virtual destroy; clear +0x20 +0x24 via 0x0004D75B; zeroes +0x80 +0x28 +0x2C +0x4C; callers 0x000E504B 0x000E599F 0x000E5B00
struct RefCounted00217D4C
{
	virtual void destroy();
	int references;
};

struct BfmeResetResource
{
	void Release_Ref();
};

struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};

class Rva000E4567
{
public:
	void rva000E4567();
private:
	char m_pad00[0x20];
	BfmeResetTextureRef m_20;
	BfmeResetTextureRef m_24;
	RefCounted00217D4C *m_28;
	int m_2C;
	char m_pad30[0x1C];
	int m_4C;
	char m_pad50[0x30];
	unsigned char m_80;
};

void Rva000E4567::rva000E4567()
{
	RefCounted00217D4C *p = m_28;
	m_80 = 0;
	if (p)
	{
		if (--p->references == 0)
			p->destroy();
		m_28 = 0;
	}
	m_20.clear();
	m_24.clear();
	m_2C = 0;
	m_4C = 0;
}
