// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva004BF951::~
// Rva004BF951 at 0x004BF951 (pinned opaque MI base dtor: SEH; identity
// unproven). Each class below derives (in order) from the opaque base, a
// shared empty polymorphic base, and its own empty polymorphic base, giving
// vptrs at +0x00/+0x0C/+0x10; the empty bases have implicit trivial
// destructors, so the derived destructor stores all three vptrs and
// tail-calls the base destructor. The +0x0C secondary is shared across most
// of the family (0xC5AD78; one body uses 0xC5B770, patched per row).
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva004BF951
{
public:
	virtual ~Rva004BF951();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva004C07B1_B2
{
public:
	virtual void f2();
};

class Rva004C07B1 : public Rva004BF951, public MiBase1, public Rva004C07B1_B2
{
public:
	virtual ~Rva004C07B1();
};

Rva004C07B1::~Rva004C07B1()
{
}

class Rva004C089E_B2
{
public:
	virtual void f2();
};

class Rva004C089E : public Rva004BF951, public MiBase1, public Rva004C089E_B2
{
public:
	virtual ~Rva004C089E();
};

Rva004C089E::~Rva004C089E()
{
}

class Rva004C0988_B2
{
public:
	virtual void f2();
};

class Rva004C0988 : public Rva004BF951, public MiBase1, public Rva004C0988_B2
{
public:
	virtual ~Rva004C0988();
};

Rva004C0988::~Rva004C0988()
{
}

class Rva004C0A4C_B2
{
public:
	virtual void f2();
};

class Rva004C0A4C : public Rva004BF951, public MiBase1, public Rva004C0A4C_B2
{
public:
	virtual ~Rva004C0A4C();
};

Rva004C0A4C::~Rva004C0A4C()
{
}

class Rva004C131B_B2
{
public:
	virtual void f2();
};

class Rva004C131B : public Rva004BF951, public MiBase1, public Rva004C131B_B2
{
public:
	virtual ~Rva004C131B();
};

Rva004C131B::~Rva004C131B()
{
}

class Rva004C1EF7_B2
{
public:
	virtual void f2();
};

class Rva004C1EF7 : public Rva004BF951, public MiBase1, public Rva004C1EF7_B2
{
public:
	virtual ~Rva004C1EF7();
};

Rva004C1EF7::~Rva004C1EF7()
{
}

class Rva004C2016_B2
{
public:
	virtual void f2();
};

class Rva004C2016 : public Rva004BF951, public MiBase1, public Rva004C2016_B2
{
public:
	virtual ~Rva004C2016();
};

Rva004C2016::~Rva004C2016()
{
}

class Rva004C1BAB_B2
{
public:
	virtual void f2();

private:
	char m_pad04[0xEC];
};

class Rva004C1BAB_B3
{
public:
	virtual void f3();
};

class Rva004C1BAB : public Rva004BF951, public MiBase1, public Rva004C1BAB_B2, public Rva004C1BAB_B3
{
public:
	virtual ~Rva004C1BAB();
};

Rva004C1BAB::~Rva004C1BAB()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f3@Rva004C1BAB_B3@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2@Rva004C0A4C_B2@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
// ?xfer@StructureBody@@MAEXPAVXfer@@@Z @ 0x004C0A16 54B gap via rowed Version1 base ActiveBody IsLightCRC XferObjectID.
// Slot 3 xfer of StructureBody (vtable 0x0085B660); Version1 then base then conditional ObjectID at +0x100.
// Evidence: Version1 0x000053EE, base ActiveBody pin 0x004BF1E8, IsLightCRC slot 0x10, XferObjectID 0x003060B2.
class Xfer
{
public:
    class Version;
    Xfer();
    virtual ~Xfer();
    void Version1();
    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;
};
class ActiveBody
{
protected:
    virtual void xfer(Xfer *xfer);
};
enum ObjectID
{
    OBJECTID_DUMMY = 0
};
void XferObjectID(Xfer *, ObjectID *);
class StructureBody : public ActiveBody
{
protected:
    virtual void xfer(Xfer *xfer);
private:
    char m_pad04[0x100 - 4];
    ObjectID m_id;
};
void StructureBody::xfer(Xfer *xfer)
{
    xfer->Version1();
    ActiveBody::xfer(xfer);
    if (!xfer->IsLightCRC())
    {
        XferObjectID(xfer, &m_id);
    }
}
