// cl: /O1 /GX- /MD
//
// ?init@W3DProjectedShadow@@QAE_NXZ, retail 0x0010BDF8..0x0010BE72
// (122B), thiscall, returns bool.
//
// Zero Hour's W3DProjectedShadow::init in its BFME 2 form: it allocates two
// 0x74-byte shadow projectors into +0x58 and +0x5C instead of one, frees the
// first again when the second allocation fails, and finishes through the
// rowed 0x0010953E (the same call the decal factory makes after init).
//
// Evidence (target): the only caller is the matched two-texture decal
// factory 0x0010C2D5, which calls this body on a freshly constructed shadow
// and abandons it when it returns false (the pin in symbols.csv). Each
// projector is built by the rowed base constructor 0x000F0F2B and then gets
// vtable 0x007CFA00, which the data ledger names ??_7Rva00109610@@6B@ (its
// matched destructor is Rva00109610Dtor.cpp). The failure path calls vtable
// slot 0 with 0 and passes the result to operator delete: MSVC's ::delete of
// a class with a virtual destructor. Class names are the ledger's
// address-derived owners; the projector's original name is not recovered.

// The 0x74-byte projector: the rowed base constructor 0x000F0F2B, then the
// derived vtable. Only the base constructor and the virtual destructor are
// modelled.
class Rva000F0F2B
{
public:
	Rva000F0F2B() throw();
	virtual ~Rva000F0F2B();
protected:
	char m_body[0x68 - 4];
};

class Rva00109610 : public Rva000F0F2B
{
public:
	Rva00109610();
	virtual ~Rva00109610();
private:
	char m_tail[0x74 - 0x68];
};

inline Rva00109610::Rva00109610()
{
}

// The rowed 0x0010953E, called on the shadow once both projectors exist.
class Rva0010959E
{
public:
	void rva0010953E();
};

class W3DProjectedShadow
{
public:
	bool init();

private:
	char m_pad00[0x58];
	Rva00109610 *m_projector;		// +0x58
	Rva00109610 *m_secondProjector;		// +0x5C
};

bool W3DProjectedShadow::init()
{
	m_projector = new Rva00109610;
	if (!m_projector)
		return false;

	m_secondProjector = new Rva00109610;
	if (!m_secondProjector)
	{
		::delete m_projector;
		m_projector = 0;
		return false;
	}

	reinterpret_cast<Rva0010959E *>(this)->rva0010953E();
	return true;
}
