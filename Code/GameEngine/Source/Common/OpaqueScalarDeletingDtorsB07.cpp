// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B07: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x00362EAB  0x00362E1C  0x00C17088#0
//   0x00367E0A  0x00367E26  0x00C17600#0
//   0x0036C693  0x0036B8E6  0x00C17A80#0
//   0x00373800  0x0037343B  0x00C17DD0#0
//   0x00373B54  0x0037381C  0x00C17E14#0
//   0x0037BD0F  0x0037BB53  0x00C187C0#0
//   0x0037BD48  0x0037BBED  0x00C18828#0
//   0x0038745D  0x00386374  0x00C19500#0
//   0x0038ADC6  0x0038ADE2  0x00C1989C#0
//   0x003AE9BF  0x003ABA4C  0x00C1D588#0
//   0x003B01EC  0x003B00D6  0x00C1D8F0#0
//   0x003B055C  0x003B0344  0x00C1D9B0#0
//   0x003B93A0  0x003B923B  0x00C1FB04#0
//   0x003ED249  0x003ED1FC  0x00C36100#0
//   0x003EE3E2  0x003EE1BE  0x00C3613C#0
//   0x003EF44B  0x003EF36E  0x00C363D8#0
//   0x003F36EC  0x003F332E  0x00C36FA4#0
//   0x003F6CDD  0x003F6A91  0x00C3709C#0
//   0x003F8DC0  0x003F8728  0x00C37314#0
//   0x003F8DDC  0x003F87A9  0x00C37318#0
//   0x003F901B  0x003F8E20  0x00C3731C#0
//   0x003F9DBE  0x003F9D08  0x00C375F0#0
//   0x003FD173  0x003FCE38  0x00C37C30#0
//   0x003FE5F3  0x003FE58A  0x00C37E48#0

struct EmitVtableTag;

class Rva00362E1C
{
public:
	Rva00362E1C(EmitVtableTag *);
public:
	virtual ~Rva00362E1C();
};

// ?<Rva00362E1C::Rva00362E1C> absent-from-retail
Rva00362E1C::Rva00362E1C(EmitVtableTag *)
{
}

class Rva00367E26
{
public:
	Rva00367E26(EmitVtableTag *);
public:
	virtual ~Rva00367E26();
};

// ?<Rva00367E26::Rva00367E26> absent-from-retail
Rva00367E26::Rva00367E26(EmitVtableTag *)
{
}

class Rva0036B8E6
{
public:
	Rva0036B8E6(EmitVtableTag *);
public:
	virtual ~Rva0036B8E6();
};

// ?<Rva0036B8E6::Rva0036B8E6> absent-from-retail
Rva0036B8E6::Rva0036B8E6(EmitVtableTag *)
{
}

class Rva0037343B
{
public:
	Rva0037343B(EmitVtableTag *);
public:
	virtual ~Rva0037343B();
};

// ?<Rva0037343B::Rva0037343B> absent-from-retail
Rva0037343B::Rva0037343B(EmitVtableTag *)
{
}

class Rva0037381C
{
public:
	Rva0037381C(EmitVtableTag *);
public:
	virtual ~Rva0037381C();
};

// ?<Rva0037381C::Rva0037381C> absent-from-retail
Rva0037381C::Rva0037381C(EmitVtableTag *)
{
}

class Rva0037BB53
{
public:
	Rva0037BB53(EmitVtableTag *);
public:
	virtual ~Rva0037BB53();
};

// ?<Rva0037BB53::Rva0037BB53> absent-from-retail
Rva0037BB53::Rva0037BB53(EmitVtableTag *)
{
}

class Rva0037BBED
{
public:
	Rva0037BBED(EmitVtableTag *);
public:
	virtual ~Rva0037BBED();
};

// ?<Rva0037BBED::Rva0037BBED> absent-from-retail
Rva0037BBED::Rva0037BBED(EmitVtableTag *)
{
}

class Rva00386374
{
public:
	Rva00386374(EmitVtableTag *);
public:
	virtual ~Rva00386374();
};

// ?<Rva00386374::Rva00386374> absent-from-retail
Rva00386374::Rva00386374(EmitVtableTag *)
{
}

class Rva0038ADE2
{
public:
	Rva0038ADE2(EmitVtableTag *);
public:
	virtual ~Rva0038ADE2();
};

// ?<Rva0038ADE2::Rva0038ADE2> absent-from-retail
Rva0038ADE2::Rva0038ADE2(EmitVtableTag *)
{
}

class Rva003ABA4C
{
public:
	Rva003ABA4C(EmitVtableTag *);
public:
	virtual ~Rva003ABA4C();
};

// ?<Rva003ABA4C::Rva003ABA4C> absent-from-retail
Rva003ABA4C::Rva003ABA4C(EmitVtableTag *)
{
}

class Rva003B00D6
{
public:
	Rva003B00D6(EmitVtableTag *);
public:
	virtual ~Rva003B00D6();
};

// ?<Rva003B00D6::Rva003B00D6> absent-from-retail
Rva003B00D6::Rva003B00D6(EmitVtableTag *)
{
}

class Rva003B0344
{
public:
	Rva003B0344(EmitVtableTag *);
public:
	virtual ~Rva003B0344();
};

// ?<Rva003B0344::Rva003B0344> absent-from-retail
Rva003B0344::Rva003B0344(EmitVtableTag *)
{
}

class Rva003B923B
{
public:
	Rva003B923B(EmitVtableTag *);
public:
	virtual ~Rva003B923B();
};

// ?<Rva003B923B::Rva003B923B> absent-from-retail
Rva003B923B::Rva003B923B(EmitVtableTag *)
{
}

class Rva003ED1FC
{
public:
	Rva003ED1FC(EmitVtableTag *);
public:
	virtual ~Rva003ED1FC();
};

// ?<Rva003ED1FC::Rva003ED1FC> absent-from-retail
Rva003ED1FC::Rva003ED1FC(EmitVtableTag *)
{
}

class Rva003EE1BE
{
public:
	Rva003EE1BE(EmitVtableTag *);
public:
	virtual ~Rva003EE1BE();
};

// ?<Rva003EE1BE::Rva003EE1BE> absent-from-retail
Rva003EE1BE::Rva003EE1BE(EmitVtableTag *)
{
}

class Rva003EF36E
{
public:
	Rva003EF36E(EmitVtableTag *);
public:
	virtual ~Rva003EF36E();
};

// ?<Rva003EF36E::Rva003EF36E> absent-from-retail
Rva003EF36E::Rva003EF36E(EmitVtableTag *)
{
}

class Rva003F332E
{
public:
	Rva003F332E(EmitVtableTag *);
public:
	virtual ~Rva003F332E();
};

// ?<Rva003F332E::Rva003F332E> absent-from-retail
Rva003F332E::Rva003F332E(EmitVtableTag *)
{
}

class Rva003F6A91
{
public:
	Rva003F6A91(EmitVtableTag *);
public:
	virtual ~Rva003F6A91();
};

// ?<Rva003F6A91::Rva003F6A91> absent-from-retail
Rva003F6A91::Rva003F6A91(EmitVtableTag *)
{
}

class Rva003F8728
{
public:
	Rva003F8728(EmitVtableTag *);
public:
	virtual ~Rva003F8728();
};

// ?<Rva003F8728::Rva003F8728> absent-from-retail
Rva003F8728::Rva003F8728(EmitVtableTag *)
{
}

class Rva003F87A9
{
public:
	Rva003F87A9(EmitVtableTag *);
public:
	virtual ~Rva003F87A9();
};

// ?<Rva003F87A9::Rva003F87A9> absent-from-retail
Rva003F87A9::Rva003F87A9(EmitVtableTag *)
{
}

class Rva003F8E20
{
public:
	Rva003F8E20(EmitVtableTag *);
public:
	virtual ~Rva003F8E20();
};

// ?<Rva003F8E20::Rva003F8E20> absent-from-retail
Rva003F8E20::Rva003F8E20(EmitVtableTag *)
{
}

class Rva003F9D08
{
public:
	Rva003F9D08(EmitVtableTag *);
public:
	virtual ~Rva003F9D08();
};

// ?<Rva003F9D08::Rva003F9D08> absent-from-retail
Rva003F9D08::Rva003F9D08(EmitVtableTag *)
{
}

class Rva003FCE38
{
public:
	Rva003FCE38(EmitVtableTag *);
public:
	virtual ~Rva003FCE38();
};

// ?<Rva003FCE38::Rva003FCE38> absent-from-retail
Rva003FCE38::Rva003FCE38(EmitVtableTag *)
{
}

class Rva003FE58A
{
public:
	Rva003FE58A(EmitVtableTag *);
public:
	virtual ~Rva003FE58A();
};

// ?<Rva003FE58A::Rva003FE58A> absent-from-retail
Rva003FE58A::Rva003FE58A(EmitVtableTag *)
{
}
