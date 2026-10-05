// cl: /O1 /MD
//
// Opaque derived destructors that tail-call GameEngineDeletingBase::~
// GameEngineDeletingBase at 0x001B4E74 (vtable store, tail jump, no member
// of their own). Each class below is a distinct retail vtable whose owner
// identity is unproven. One ledger row per destructor, landed one commit at
// a time; the base declaration is shared and defined once in
// GameEngineDeletingBaseDtor.cpp (its row resolves the tail calls).

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class Rva00221027 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00221027();
};

Rva00221027::~Rva00221027()
{
}

class Rva00225ACA : public GameEngineDeletingBase
{
public:
	virtual ~Rva00225ACA();
};

Rva00225ACA::~Rva00225ACA()
{
}

class Rva00232D7B : public GameEngineDeletingBase
{
public:
	virtual ~Rva00232D7B();
};

Rva00232D7B::~Rva00232D7B()
{
}

class Rva0025DB46 : public GameEngineDeletingBase
{
public:
	virtual ~Rva0025DB46();
};

Rva0025DB46::~Rva0025DB46()
{
}

class Rva0026201C : public GameEngineDeletingBase
{
public:
	virtual ~Rva0026201C();
};

Rva0026201C::~Rva0026201C()
{
}

class Rva002D22CA : public GameEngineDeletingBase
{
public:
	virtual ~Rva002D22CA();
};

Rva002D22CA::~Rva002D22CA()
{
}

class Rva002E55D8 : public GameEngineDeletingBase
{
public:
	virtual ~Rva002E55D8();
};

Rva002E55D8::~Rva002E55D8()
{
}

class Rva003BA6A9 : public GameEngineDeletingBase
{
public:
	virtual ~Rva003BA6A9();
};

Rva003BA6A9::~Rva003BA6A9()
{
}

class Rva003E3BD4 : public GameEngineDeletingBase
{
public:
	virtual ~Rva003E3BD4();
};

Rva003E3BD4::~Rva003E3BD4()
{
}

class Rva00419CD4 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00419CD4();
};

Rva00419CD4::~Rva00419CD4()
{
}

class Rva0041B8C7 : public GameEngineDeletingBase
{
public:
	virtual ~Rva0041B8C7();
};

Rva0041B8C7::~Rva0041B8C7()
{
}

class Rva0041FE0E : public GameEngineDeletingBase
{
public:
	virtual ~Rva0041FE0E();
};

inline Rva0041FE0E::~Rva0041FE0E()
{
}

class Rva0044954D : public GameEngineDeletingBase
{
public:
	virtual ~Rva0044954D();
};

Rva0044954D::~Rva0044954D()
{
}

// ??1Rva0041FE0E is a header inline elsewhere: other units emit select-any
// copies of it, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva0041FE0EDtor@@YAXPAVRva0041FE0E@@@Z present-unmatched
void bfmeEmitRva0041FE0EDtor(Rva0041FE0E *p)
{
	p->Rva0041FE0E::~Rva0041FE0E();
}
#pragma inline_depth()
