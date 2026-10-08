// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva004692BA@Rva004692BA@@QAEXPAVRva004692BAFactory@@@Z, retail
// 0x004692BA..0x0046936B (177 bytes, EH, RET 4). Rebuilds the horde's melee
// formation object at +0x1AC: the old one is destroyed with the global
// delete (slot 0 with flags 0, then ::operator delete), then a new one comes
// from the given factory's slot 1, else from the factory the owning object
// keeps at +0x258, else a HordeMeleeSwarm (rowed constructor 0x005843DA) is
// allocated; either way it is built for the outer object 0x11C bytes before
// this interface. Its slot 1 then gets the member count, the size of the
// 0x1C-byte record range at +0x6C/+0x70. WorldBuilder's twin (0x010B2C90) is
// unnamed, so the names stay address-derived.

class Rva004692BAFormation
{
public:
	virtual ~Rva004692BAFormation();
	virtual void setMemberCount(int count);		// slot 1
};

class HordeMeleeSwarm : public Rva004692BAFormation
{
public:
	HordeMeleeSwarm(void *owner);
private:
	unsigned char m_pad04[0x18 - 0x04];
};

class Rva004692BAFactory
{
public:
	virtual void slot0();
	virtual Rva004692BAFormation *create(void *owner);	// slot 1
};

struct Rva004692BAObject
{
	unsigned char m_pad000[0x258];
	Rva004692BAFactory *m_factory258;
};

class Rva004692BA
{
public:
	void rva004692BA(Rva004692BAFactory *factory);

private:
	char *outer() { return reinterpret_cast<char *>(this) - 0x11C; }
	Rva004692BAObject *object() { return *reinterpret_cast<Rva004692BAObject **>(reinterpret_cast<char *>(this) - 0x118); }

	unsigned char m_pad000[0x6C];
	char *m_membersBegin6C;					// +0x6C, 0x1C-byte records
	char *m_membersEnd70;					// +0x70
	unsigned char m_pad074[0x1AC - 0x74];
	Rva004692BAFormation *m_formation1AC;	// +0x1AC
};

void Rva004692BA::rva004692BA(Rva004692BAFactory *factory)
{
	if (m_formation1AC)
		::delete m_formation1AC;

	if (factory)
		m_formation1AC = factory->create(outer());
	else if (object()->m_factory258)
		m_formation1AC = object()->m_factory258->create(outer());
	else
		m_formation1AC = new HordeMeleeSwarm(outer());

	m_formation1AC->setMemberCount((m_membersEnd70 - m_membersBegin6C) / 0x1C);
}
