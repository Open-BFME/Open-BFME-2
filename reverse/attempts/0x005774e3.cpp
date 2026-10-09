// ??0Rva00576F48@@QAE@PAURva00577634Owner@@H@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva00576F48@@QAE@PAURva00577634Owner@@H@Z, retail 0x005774E3..0x005775C1
// (222 bytes, EH, RET 8): the constructor of the class whose destructor
// ??1Rva00576F48@@UAE@XZ (0x00576F48, Rva00576F48Dtor.cpp) and scalar deleting
// destructor 0x00577073 are rowed; both store the same vtable 0x00C6E858.
//
// The base Rva005D2015 (rowed ctor 0x005D206B) takes the owner's +0x10, the
// owner's +0x0C object's +0x04 field through the rowed getter 0x005ED28A, and
// the id; then +0x14 keeps the owner and +0x18 the id (an object: its rowed
// 0x00319B0A runs next, mirroring the destructor's 0x00319B31). When the two
// rowed pointer-chase getters 0x00328A83 / 0x0042D703 reach a target, its
// slot 1 gets the id's image (rowed Rva005D2355Get), slot 6 a ref-counted
// wrapper of the id (rowed ctor 0x005773DB; released inline through the
// rowed 0x0007DEEF) and slot 8 runs; finally the field's rowed getter
// 0x00574AAC target gets the id's pinned 0x00318C32 value through the rowed
// 0x005CB84A (the destructor passes 0 there).
//
// Evidence (target): the only caller is the banked 0x00577634
// (reverse/attempts/0x00577634.cpp: new 0x1C-byte entry for the +0x18 object
// and the id); the vtable and field offsets match the rowed destructor.
// Names stay address-derived.

class Rva005D2015
{
public:
	Rva005D2015(int a, int owner, int c);
	virtual ~Rva005D2015();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva005ED28AAddDwordField
{
public:
	int get() const;
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

class Rva005CB84A
{
public:
	void rva005CB84A(int value);
};

class Rva00319B0AOwner
{
public:
	void rva00319B0A();
};

class Rva00318C32
{
public:
	int rva00318C32();
};

class Image;
struct Rva005D2355In;
const Image *Rva005D2355Get(Rva005D2355In *in);

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Ref-counted value wrapper built by the rowed ctor; released inline.
class Rva005773DB
{
public:
	Rva005773DB(const int *arg);
	~Rva005773DB()
	{
		if (m_impl)
			ReleaseTreeHintRef00217D4C(m_impl);
	}
private:
	TargetRef00217D4C *m_impl;
};

class Rva005774E3Target
{
public:
	virtual void slot0();
	virtual void slot1(const Image *image);
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6(Rva005773DB *value);
	virtual void slot7();
	virtual void slot8();
};

struct Rva00576F48Inner
{
	unsigned char m_pad00[0x04];
	void *m_field04;			// +0x04
};

struct Rva00577634Owner
{
	unsigned char m_pad00[0x0C];
	Rva00576F48Inner *m_inner0C;	// +0x0C
	int m_10;				// +0x10
};

class Rva00576F48 : public Rva005D2015
{
public:
	Rva00576F48(Rva00577634Owner *owner, int id);
	virtual ~Rva00576F48();
private:
	Rva00577634Owner *m_owner14;	// +0x14
	int m_id18;			// +0x18
};

Rva00576F48::Rva00576F48(Rva00577634Owner *owner, int id)
	: Rva005D2015(owner->m_10, static_cast<const Rva005ED28AAddDwordField *>(owner->m_inner0C->m_field04)->get(), id),
	  m_owner14(owner), m_id18(id)
{
	((Rva00319B0AOwner *)id)->rva00319B0A();
	const Rva0042D703PtrChaseField *chase = (const Rva0042D703PtrChaseField *)static_cast<const Rva00328A83PtrChaseField *>(m_owner14->m_inner0C->m_field04)->get();
	if (Rva005774E3Target *target = (Rva005774E3Target *)chase->get())
	{
		target->slot1(Rva005D2355Get((Rva005D2355In *)m_id18));
		{
			int value = m_id18;
			Rva005773DB wrapped(&value);
			target->slot6(&wrapped);
		}
		target->slot8();
	}
	Rva005CB84A *field = (Rva005CB84A *)static_cast<const Rva00574AACAddDwordField *>(m_owner14->m_inner0C->m_field04)->get();
	field->rva005CB84A(((Rva00318C32 *)m_id18)->rva00318C32());
}
