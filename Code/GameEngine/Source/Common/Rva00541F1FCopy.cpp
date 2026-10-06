// cl: /O1 /EHsc /DNDEBUG /MD
//
// ??0Rva00541F1F@@QAE@ABV0@@Z @0x00541F1F 83B: copy constructor. It copies
// the rowed polymorphic base Rva0053FADE (0x0053FADE), installs vtable
// 0x00C69514, then copies the member-plus-vector holders at +0x24 (rowed
// Rva00541913 copy 0x00541913) and +0x44 (rowed Rva00541A6E copy
// 0x00541A6E). Identities are address-derived.

class Rva0053FADE
{
public:
	Rva0053FADE(const Rva0053FADE &other);
	virtual ~Rva0053FADE();

private:
	char m_pad[0x20];
};

class Rva00541913
{
public:
	Rva00541913(const Rva00541913 &that);
	~Rva00541913();

private:
	char m_pad[0x20];
};

class Rva00541A6E
{
public:
	Rva00541A6E(const Rva00541A6E &that);
	~Rva00541A6E();

private:
	char m_pad[0x20];
};

class Rva00541F1F : public Rva0053FADE
{
public:
	Rva00541F1F(const Rva00541F1F &other);
	virtual ~Rva00541F1F();

private:
	Rva00541913 m_24;
	Rva00541A6E m_44;
};

Rva00541F1F::Rva00541F1F(const Rva00541F1F &other) :
	Rva0053FADE(other),
	m_24(other.m_24),
	m_44(other.m_44)
{
}
