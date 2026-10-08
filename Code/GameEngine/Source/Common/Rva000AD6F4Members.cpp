// cl: /MD
//
// Opaque destructors that call Rva000AD6F4::clear at 0x000AD6F4 (pinned
// opaque guarded-delete helper: nulls its pointer at +0 then ::deletes it;
// exact method unproven) on a member at +0x04. Each class below stores its
// own vtable, adjusts this to the member, and tail-calls the helper; the
// helper type is only declared here (defined nowhere -- it resolves via the
// pin). Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva000AD6F4
{
public:
	void clear();

public:
	char m_pad[8];
};

class Rva00328A75
{
public:
	virtual ~Rva00328A75();

private:
	Rva000AD6F4 m_member04;
};

Rva00328A75::~Rva00328A75()
{
	m_member04.clear();
}

class Rva005C65F1
{
public:
	void rva005C65F1();
};

class Rva00577936
{
public:
	virtual ~Rva00577936();
	virtual void rva00577966();

private:
	Rva000AD6F4 m_member04;
};

Rva00577936::~Rva00577936()
{
	m_member04.clear();
}

void Rva00577936::rva00577966()
{
	return (*(Rva005C65F1 **)m_member04.m_pad)->rva005C65F1();
}

class Rva005F83DF
{
public:
	virtual ~Rva005F83DF();

private:
	Rva000AD6F4 m_member04;
};

Rva005F83DF::~Rva005F83DF()
{
	m_member04.clear();
}

// ?rva00577914@Rva00577914@@QAEXXZ @0x00577914 26B: virt slot4 on [m08+0x3C] with m0C then tail clear on +0x14; caller 0x00577E53 45B; prev Release next dtor; no donor.
class Rva00577914Virt
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void virt4(int);
};

struct Rva00577914Mid
{
	char m_pad[0x3C];
	Rva00577914Virt *m_obj;
};

class Rva00577914
{
public:
	void rva00577914();
private:
	int m_00;
	int m_04;
	Rva00577914Mid *m_08;
	int m_0C;
	int m_10;
	Rva000AD6F4 m_14;
};

void Rva00577914::rva00577914()
{
	m_08->m_obj->virt4(m_0C);
	m_14.clear();
}

// Rva000AD71D: a class over Rva00328A75 whose destructor is the 5-byte jmp 0x000AD71D (rowed in
// Rva000AD71DDtor.cpp). Its scalar deleting destructor 0x000ADE29 calls that stub; the
// destructor is only declared here, and the tag constructor (no retail
// counterpart) makes this TU emit the vtable and with it the deleting
// destructor.
struct EmitVtableTag;
class Rva000AD71D : public Rva00328A75
{
public:
	Rva000AD71D(EmitVtableTag *);
	virtual ~Rva000AD71D();
};

// ?<Rva000AD71D::Rva000AD71D> absent-from-retail
Rva000AD71D::Rva000AD71D(EmitVtableTag *)
{
}
