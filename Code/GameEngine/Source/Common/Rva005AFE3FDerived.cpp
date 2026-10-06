// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005AFE3F::~
// Rva005AFE3F at 0x005AFE3F (pinned opaque base dtor; identity unproven).
// Each class below stores its own vtable and tail-calls the base destructor;
// the base itself is only declared here (defined nowhere -- it resolves via
// the pin), because a same-TU definition would capture the call locally
// instead of at the ledger address. Owner identities are unproven (opaque
// Rva names). One ledger row per destructor, landed one commit at a time.

class Rva005AFE3F
{
public:
	virtual ~Rva005AFE3F();
};

class Rva005AFA03 : public Rva005AFE3F
{
public:
	virtual ~Rva005AFA03();
};

Rva005AFA03::~Rva005AFA03()
{
}

class Rva005D50D8 : public Rva005AFE3F
{
public:
	virtual ~Rva005D50D8();
};

Rva005D50D8::~Rva005D50D8()
{
}

class Rva005D583C : public Rva005AFE3F
{
public:
	virtual ~Rva005D583C();
};

Rva005D583C::~Rva005D583C()
{
}
