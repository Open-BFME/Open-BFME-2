// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva000C79C9::~
// Rva000C79C9 at 0x000C79C9 (pinned opaque MI base dtor: SEH; identity
// unproven). Each class below derives (in order) from the opaque base, a
// shared empty polymorphic base, and its own empty polymorphic base, giving
// vptrs at +0x00/+0x0C/+0x10; the empty bases have implicit trivial
// destructors, so the derived destructor stores all three vptrs and
// tail-calls the base destructor. The +0x0C secondary is shared across the
// family. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class Rva000C79C9
{
public:
	virtual ~Rva000C79C9();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva000CA119_B2
{
public:
	virtual void f2();
};

class Rva000CA119 : public Rva000C79C9, public MiBase1, public Rva000CA119_B2
{
public:
	virtual ~Rva000CA119();
};

Rva000CA119::~Rva000CA119()
{
}

class Rva000CAEC6_B2
{
public:
	virtual void f2();
};

class Rva000CAEC6 : public Rva000C79C9, public MiBase1, public Rva000CAEC6_B2
{
public:
	virtual ~Rva000CAEC6();
};

Rva000CAEC6::~Rva000CAEC6()
{
}
