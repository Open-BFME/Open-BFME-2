// cl: /MD
//
// Opaque single-inheritance destructors tail-calling the matched
// Rva006D6470Owner::~ at 0x006D6470 (constructor row at 0x006D6410).
// Each class below stores its own vtable and tail-calls the base
// destructor; the base is only declared here so the call resolves through the
// matched row rather than a same-TU definition. Derived owner identities remain unproven
// (opaque Rva names). One ledger row per destructor, landed one commit at
// a time.

class Rva006D6470Owner
{
public:
	virtual ~Rva006D6470Owner();
};

class Rva006D65A0 : public Rva006D6470Owner
{
public:
	virtual ~Rva006D65A0();
};

Rva006D65A0::~Rva006D65A0()
{
}

class Rva006E8F30 : public Rva006D6470Owner
{
public:
	virtual ~Rva006E8F30();
};

Rva006E8F30::~Rva006E8F30()
{
}

class Rva006F25D0 : public Rva006D6470Owner
{
public:
	virtual ~Rva006F25D0();
};

Rva006F25D0::~Rva006F25D0()
{
}

class Rva006F3990 : public Rva006D6470Owner
{
public:
	virtual ~Rva006F3990();
};

Rva006F3990::~Rva006F3990()
{
}

class Rva006FC120 : public Rva006D6470Owner
{
public:
	virtual ~Rva006FC120();
};

Rva006FC120::~Rva006FC120()
{
}

class Rva006FC1C0 : public Rva006D6470Owner
{
public:
	virtual ~Rva006FC1C0();
};

Rva006FC1C0::~Rva006FC1C0()
{
}

class Rva00709B80 : public Rva006D6470Owner
{
public:
	virtual ~Rva00709B80();
};

Rva00709B80::~Rva00709B80()
{
}
