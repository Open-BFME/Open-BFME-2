// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x004C9FBF, 33 bytes.
// Rva004C9FBF derived copy ctor. The 1-int base copy lives in
// V3PolyCopyCtors.cpp (rowed at 0x004C9F61), so this shard TU sees only its
// declaration and emits the same outlined base call retail has. The derived
// part installs vptr 0xC07E54 then copies +0x08. B2 body-address name: the
// class identity is not recovered.

typedef int Int;

class Rva004C9F61
{
public:
	Rva004C9F61(const Rva004C9F61 &other);
	virtual ~Rva004C9F61();

	Int m_field04;
};

class Rva004C9FBF : public Rva004C9F61
{
public:
	Rva004C9FBF(const Rva004C9FBF &other);
	virtual ~Rva004C9FBF();

	Int m_field08;
};

Rva004C9FBF::Rva004C9FBF(const Rva004C9FBF &other)
	: Rva004C9F61(other)
{
	m_field08 = other.m_field08;
}
