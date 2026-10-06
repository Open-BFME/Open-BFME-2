// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005DC87B::~
// Rva005DC87B at 0x005DC87B (row in Rva005DC73CDerived.cpp). Each class below
// stores its own vtable and tail-calls the base destructor; the base itself
// is only declared here (defined once in Rva005DC73CDerived.cpp), because a
// same-TU definition would capture the call locally instead of at the ledger
// address. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class Rva005DC87B
{
public:
	virtual ~Rva005DC87B();
};

class Rva005A9ACD : public Rva005DC87B
{
public:
	virtual ~Rva005A9ACD();
};

Rva005A9ACD::~Rva005A9ACD()
{
}

class Rva005A9CB3 : public Rva005DC87B
{
public:
	virtual ~Rva005A9CB3();
};

Rva005A9CB3::~Rva005A9CB3()
{
}
