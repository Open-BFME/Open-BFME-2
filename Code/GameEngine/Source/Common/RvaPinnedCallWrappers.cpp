// cl: /DNDEBUG /MD /EHsc
// Small member wrappers around callees retail does not name; class and
// method names are address-derived.

// Native 0x0052A65A, 16B: run 0x0052A4B5 on this, then set +0x0C. The
// stack argument is unused.
class Rva0052A4B5
{
public:
	void rva0052A4B5();
	void rva0052A65A(int unused);

private:
	char m_pad00[0x0C];
	bool m_0c;
};
void Rva0052A4B5::rva0052A65A(int)
{
	rva0052A4B5();
	m_0c = true;
}

// Native 0x00132D5B, 21B: run bfmeGo937B (0x00132129), then pass the +0x40
// sub-object to 0x001321A7, both on this.
class BfmeThing937B
{
public:
	void bfmeGo937B();
	void rva001321A7(void *sub);
	void rva00132D5B();

private:
	char m_pad00[0x40];
	char m_40[4];
};
void BfmeThing937B::rva00132D5B()
{
	bfmeGo937B();
	rva001321A7(m_40);
}

// Native 0x00409EA0, 19B: InitButtonList, then the 4-byte element count of
// the +0x3C/+0x40 range.
class CreateAHeroHero
{
public:
	void InitButtonList();
	int rva00409EA0();

private:
	char m_pad00[0x3C];
	void **m_begin;
	void **m_end;
};
int CreateAHeroHero::rva00409EA0()
{
	InitButtonList();
	return m_end - m_begin;
}

// Native 0x004ECE93, 21B: the +0x20 source's 0x002C59CE value for the
// argument, else 0.
class Rva002C59CE
{
public:
	float rva002C59CE(int key);
};

class Rva004ECE93
{
public:
	float rva004ECE93(int key);

private:
	char m_pad00[0x20];
	Rva002C59CE *m_source;
};
float Rva004ECE93::rva004ECE93(int key)
{
	if (m_source)
		return m_source->rva002C59CE(key);
	return 0.0f;
}

extern int g_Va00DE1B40;

// Native 0x000C0386, 19B: run 0x000BFDFE unless +0xB8 already equals the
// global at 0x00DE1B40.
class Rva000BFDFE
{
public:
	void rva000BFDFE();
	void rva000C0386();

private:
	char m_pad00[0xB8];
	int m_b8;
};
void Rva000BFDFE::rva000C0386()
{
	if (g_Va00DE1B40 != m_b8)
		rva000BFDFE();
}
