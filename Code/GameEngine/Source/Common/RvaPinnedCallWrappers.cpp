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

// Native 0x005FAF9F, 19B: run 0x005FED59 on this, then hand this to
// 0x005FADEF on the +0x28 owner.
class Rva005FED59;

class Rva005FAF9FOwner
{
public:
	void rva005FADEF(Rva005FED59 *child);
};

class Rva005FED59
{
public:
	void rva005FED59() const;
	void rva005FAF9F();

private:
	char m_pad00[0x28];
	Rva005FAF9FOwner *m_owner;
};
void Rva005FED59::rva005FAF9F()
{
	rva005FED59();
	m_owner->rva005FADEF(this);
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
