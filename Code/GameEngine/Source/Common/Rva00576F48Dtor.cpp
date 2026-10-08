// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??1Rva00576F48@@UAE@XZ, retail 0x00576F48..0x00576FBA (114 bytes, EH): the
// destructor its rowed scalar deleting destructor 0x00577073 calls (vtable
// 0x00C6E858). Through the +0x14 object's +0x0C object's +0x04 field it tells
// the field's target 0 (rowed getter 0x00574AAC, rowed 0x005CB84A), runs slot
// 10 of the object two rowed pointer-chase getters reach when there is one,
// then runs the +0x18 owner's rowed 0x00319B31 before the rowed base
// destructor Rva005D2015 (EH state 0).

class Rva005D2015
{
public:
	virtual ~Rva005D2015();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva005CB84A
{
public:
	void rva005CB84A(int value);
};

class Rva00574AACAddDwordField
{
public:
	int get() const;
};

class Rva00328A83PtrChaseField
{
public:
	int get() const;
};

class Rva0042D703PtrChaseField
{
public:
	int get() const;
};

class Rva00319B0AOwner
{
public:
	void rva00319B31();
};

class Rva00576F48Target
{
public:
#define V(n) virtual void t##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
#undef V
	virtual void slot10();
};

struct Rva00576F48Inner
{
	unsigned char m_pad00[0x04];
	void *m_field04;						// +0x04
};

struct Rva00576F48Source
{
	unsigned char m_pad00[0x0C];
	Rva00576F48Inner *m_inner0C;			// +0x0C
};

class Rva00576F48 : public Rva005D2015
{
public:
	virtual ~Rva00576F48();
private:
	Rva00576F48Source *m_source14;			// +0x14
	Rva00319B0AOwner *m_owner18;			// +0x18
};

Rva00576F48::~Rva00576F48()
{
	reinterpret_cast<Rva005CB84A *>(static_cast<const Rva00574AACAddDwordField *>(m_source14->m_inner0C->m_field04)->get())->rva005CB84A(0);
	const Rva0042D703PtrChaseField *chase = (const Rva0042D703PtrChaseField *)static_cast<const Rva00328A83PtrChaseField *>(m_source14->m_inner0C->m_field04)->get();
	if (Rva00576F48Target *target = (Rva00576F48Target *)chase->get())
		target->slot10();
	m_owner18->rva00319B31();
}
