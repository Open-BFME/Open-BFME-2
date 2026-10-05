// cl: /O1 /DNDEBUG /MD /EHsc
//
// Destructors of the 59-byte member-then-base shape: store the class vptr,
// destroy one member at a fixed offset (EH state 0), then call the base
// destructor; the same shape as the rowed ??1Rva0098477@@UAE@XZ
// (SubsystemDerivedDtors.cpp) and ??1Rva001E4DB0@@UAE@XZ.  Each class is
// named after its destructor address; the base and member destructors are
// declared, not defined, and resolve to their ledger rows or address-named
// pins at the addresses the retail calls prove.  Layout is modelled only as
// far as the member offset; identities are not recovered.
//
//   dtor        vptr        member      base
//   0x00413A24  0x00BE7660  +0xC   0x0022DC9B  0x001B4E74
//   0x00414166  0x00BE7698  +0xC   0x0022DCDA  0x001B4E74
//   0x005685EE  0x00C6CF74  +0xC   0x0056850D  0x005C3549
//   0x00575D45  0x00C6E664  +0x8   0x00577010  0x00575395
//   0x00576B5E  0x00C6E7D4  +0x8   0x00577010  0x00575395
//   0x005772BF  0x00C6E960  +0x8   0x00577010  0x00575395
//   0x00577FA7  0x00C6EA28  +0x44  0x00577EB2  0x005C6C7B
//   0x005CF7BF  0x00C75254  +0x8   0x005CF363  0x005E6810
//   0x005E1FBC  0x00C77A64  +0xC   0x005E1E81  0x004E84A4
//   0x005E362F  0x00C77BD0  +0xC   0x005E35DA  0x004E84A4
//   0x005F64F5  0x00C796D0  +0x8   0x005F64DB  0x005F38CA
//   0x005F86C3  0x00C79CBC  +0x20  0x005F85E1  0x00577936
//   0x005FB1AD  0x00C79EDC  +0x20  0x005FAFB2  0x006003FC

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class Rva0022DC9B
{
public:
	~Rva0022DC9B();

private:
	void *m_value;
};

class Rva0022DCDA
{
public:
	~Rva0022DCDA();

private:
	void *m_value;
};

class Rva005C3549
{
public:
	virtual ~Rva005C3549();
};

class Rva0056850D
{
public:
	~Rva0056850D();

private:
	void *m_value;
};

class Rva00575395
{
public:
	virtual ~Rva00575395();
};

class Rva00577010
{
public:
	~Rva00577010();

private:
	void *m_value;
};

class Rva005C6C7B
{
public:
	virtual ~Rva005C6C7B();
};

class Rva00577EB2
{
public:
	~Rva00577EB2();

private:
	void *m_value;
};

class Rva005E6810
{
public:
	virtual ~Rva005E6810();
};

class Rva005CF363
{
public:
	~Rva005CF363();

private:
	void *m_value;
};

class Rva00539926Base
{
public:
	virtual ~Rva00539926Base();
};

class Rva005E1E81
{
public:
	~Rva005E1E81();

private:
	void *m_value;
};

class Rva005E35DA
{
public:
	~Rva005E35DA();

private:
	void *m_value;
};

class Rva005F38CA
{
public:
	virtual ~Rva005F38CA();
};

class Rva005F64DB
{
public:
	~Rva005F64DB();

private:
	void *m_value;
};

class Rva00577936
{
public:
	virtual ~Rva00577936();
};

class Rva005F85E1
{
public:
	~Rva005F85E1();

private:
	void *m_value;
};

class Rva006003FC
{
public:
	virtual ~Rva006003FC();
};

class Rva005FAFB2
{
public:
	~Rva005FAFB2();

private:
	void *m_value;
};



class Rva00413A24 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00413A24();

private:
	char m_unmodelled_04[0x8];
	Rva0022DC9B m_member;	// +0xC
};

Rva00413A24::~Rva00413A24()
{
}

class Rva00414166 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00414166();

private:
	char m_unmodelled_04[0x8];
	Rva0022DCDA m_member;	// +0xC
};

Rva00414166::~Rva00414166()
{
}

class Rva005685EE : public Rva005C3549
{
public:
	virtual ~Rva005685EE();

private:
	char m_unmodelled_04[0x8];
	Rva0056850D m_member;	// +0xC
};

Rva005685EE::~Rva005685EE()
{
}

class Rva00575D45 : public Rva00575395
{
public:
	virtual ~Rva00575D45();

private:
	char m_unmodelled_04[0x4];
	Rva00577010 m_member;	// +0x8
};

Rva00575D45::~Rva00575D45()
{
}

class Rva00576B5E : public Rva00575395
{
public:
	virtual ~Rva00576B5E();

private:
	char m_unmodelled_04[0x4];
	Rva00577010 m_member;	// +0x8
};

Rva00576B5E::~Rva00576B5E()
{
}

class Rva005772BF : public Rva00575395
{
public:
	virtual ~Rva005772BF();

private:
	char m_unmodelled_04[0x4];
	Rva00577010 m_member;	// +0x8
};

Rva005772BF::~Rva005772BF()
{
}

class Rva00577FA7 : public Rva005C6C7B
{
public:
	virtual ~Rva00577FA7();

private:
	char m_unmodelled_04[0x40];
	Rva00577EB2 m_member;	// +0x44
};

Rva00577FA7::~Rva00577FA7()
{
}

class Rva005CF7BF : public Rva005E6810
{
public:
	virtual ~Rva005CF7BF();

private:
	char m_unmodelled_04[0x4];
	Rva005CF363 m_member;	// +0x8
};

Rva005CF7BF::~Rva005CF7BF()
{
}

class Rva005E1FBC : public Rva00539926Base
{
public:
	virtual ~Rva005E1FBC();

private:
	char m_unmodelled_04[0x8];
	Rva005E1E81 m_member;	// +0xC
};

Rva005E1FBC::~Rva005E1FBC()
{
}

class Rva005E362F : public Rva00539926Base
{
public:
	virtual ~Rva005E362F();

private:
	char m_unmodelled_04[0x8];
	Rva005E35DA m_member;	// +0xC
};

Rva005E362F::~Rva005E362F()
{
}

class Rva005F64F5 : public Rva005F38CA
{
public:
	virtual ~Rva005F64F5();

private:
	char m_unmodelled_04[0x4];
	Rva005F64DB m_member;	// +0x8
};

Rva005F64F5::~Rva005F64F5()
{
}

class Rva005F86C3 : public Rva00577936
{
public:
	virtual ~Rva005F86C3();

private:
	char m_unmodelled_04[0x1C];
	Rva005F85E1 m_member;	// +0x20
};

Rva005F86C3::~Rva005F86C3()
{
}

class Rva005FB1AD : public Rva006003FC
{
public:
	virtual ~Rva005FB1AD();

private:
	char m_unmodelled_04[0x1C];
	Rva005FAFB2 m_member;	// +0x20
};

Rva005FB1AD::~Rva005FB1AD()
{
}

