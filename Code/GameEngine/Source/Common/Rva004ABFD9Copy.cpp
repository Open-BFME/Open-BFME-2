// cl: /O1 /EHsc /MD
//
// ??0Rva004ABFD9@@QAE@ABV0@@Z @0x004ABF47 102B: copy constructor of the class
// whose destructor is the rowed ??1Rva004ABFD9 (0x004ABFD9, vtable 0x00C549F8
// slot 0 via ??_GRva004ABFD9 0x004AC021). It copies the polymorphic base
// through the unrowed copy constructor 0x004ABCE6 (pinned under the registry's
// key type, since the object registers its offset-0 base), installs vtable
// 0x00C549F8, copies the member at +8 (rowed Rva003ED658 copy 0x003ED658) and
// three plain fields, then inserts itself into the global registry 0x00E03CE0
// (rowed Rva00E03CE0::Rva004ABEAE 0x004ABEAE). Identities are address-derived.

struct Rva001408C0Target
{
	Rva001408C0Target(const Rva001408C0Target &other);
	virtual ~Rva001408C0Target();

	int m_04;
};

struct Rva00E03CE0
{
	void Rva004ABEAE(Rva001408C0Target *key);
};

extern Rva00E03CE0 g_00E03CE0;

class Rva003ED658
{
public:
	Rva003ED658(const Rva003ED658 &other);
	~Rva003ED658();

private:
	char m_pad[0xC];
};

class Rva004ABFD9 : public Rva001408C0Target
{
public:
	Rva004ABFD9(const Rva004ABFD9 &other);
	virtual ~Rva004ABFD9();

private:
	Rva003ED658 m_08;
	int m_14;
	int m_18;
	short m_1C;
};

Rva004ABFD9::Rva004ABFD9(const Rva004ABFD9 &other) :
	Rva001408C0Target(other),
	m_08(other.m_08),
	m_14(other.m_14),
	m_18(other.m_18),
	m_1C(other.m_1C)
{
	g_00E03CE0.Rva004ABEAE(this);
}
