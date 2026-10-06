// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva006DE350::~
// Rva006DE350 at 0x006DE350 (pinned opaque dtor asserting IsDestroyedGC with
// vtable 0xCEAED0; exact method unproven). Each class below stores its own
// vtable and tail-calls the base destructor; the base itself is only declared
// here (defined nowhere -- it resolves via the pin), because a same-TU
// definition would capture the call locally instead of at the ledger address.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva006DE350
{
public:
	virtual ~Rva006DE350();
};

class Rva006D8510 : public Rva006DE350
{
public:
	virtual ~Rva006D8510();
};

Rva006D8510::~Rva006D8510()
{
}

class Rva006D86F0 : public Rva006DE350
{
public:
	virtual ~Rva006D86F0();
};

Rva006D86F0::~Rva006D86F0()
{
}

class Rva006D88B0 : public Rva006DE350
{
public:
	virtual ~Rva006D88B0();
};

Rva006D88B0::~Rva006D88B0()
{
}

class Rva006FB9B0 : public Rva006DE350
{
public:
	virtual ~Rva006FB9B0();
};

Rva006FB9B0::~Rva006FB9B0()
{
}

class Rva006FBA10 : public Rva006DE350
{
public:
	virtual ~Rva006FBA10();
};

Rva006FBA10::~Rva006FBA10()
{
}
