// cl: /O1 /MD
// ??0Rva005D7706@@QAE@XZ @0x005D76F4 18B, ??0Rva005D7855@@QAE@XZ @0x005D7843 18B,
// ??0Rva005D7B3E@@QAE@XZ @0x005D7B2C 18B, ??0Rva005D7D88@@QAE@XZ @0x005D7D76 18B,
// ??0Rva005D817D@@QAE@XZ @0x005D816B 18B, ??0Rva005D8223@@QAE@XZ @0x005D8211 18B,
// ??0Rva005D86E6@@QAE@XZ @0x005D86D4 18B, ??0Rva005D8AE4@@QAE@XZ @0x005D8AD2 18B,
// ??0Rva005D8C25@@QAE@XZ @0x005D8C13 18B, ??0Rva005D8EE8@@QAE@XZ @0x005D8ED6 18B,
// ??0Rva005D91AB@@QAE@XZ @0x005D9199 18B, ??0Rva005D944A@@QAE@XZ @0x005D9438 18B,
// ??0Rva005D9CD5@@QAE@XZ @0x005D9CC3 18B.
// Thirteen opaque single-inheritance ctors deriving from Rva005EE30C (rowed ctor
// at 0x005EE2E6 in Rva005EE30CCtor.cpp). Each body is push esi / mov esi ecx /
// call base / mov [esi] vtable / mov eax esi / pop esi / ret (18B). Each ctor
// immediately precedes its rowed dtor in Rva005EE30CDerived.cpp
// (005D76F4->7706, 005D7843->7855, 005D7B2C->7B3E, 005D7D76->7D88,
// 005D816B->817D, 005D8211->8223, 005D86D4->86E6, 005D8AD2->8AE4,
// 005D8C13->8C25, 005D8ED6->8EE8, 005D9199->91AB, 005D9438->944A, 005D9CC3->9CD5), proving the class identity. Vtable
// immediates are DIR32 filled by the gate. Base declared only here.

class Rva005EE30C
{
public:
	Rva005EE30C();
	virtual ~Rva005EE30C();
};

class Rva005D7706 : public Rva005EE30C
{
public:
	Rva005D7706();
	virtual ~Rva005D7706();
};

Rva005D7706::Rva005D7706()
{
}

class Rva005D7855 : public Rva005EE30C
{
public:
	Rva005D7855();
	virtual ~Rva005D7855();
};

Rva005D7855::Rva005D7855()
{
}

class Rva005D7B3E : public Rva005EE30C
{
public:
	Rva005D7B3E();
	virtual ~Rva005D7B3E();
};

Rva005D7B3E::Rva005D7B3E()
{
}

class Rva005D7D88 : public Rva005EE30C
{
public:
	Rva005D7D88();
	virtual ~Rva005D7D88();
};

Rva005D7D88::Rva005D7D88()
{
}

class Rva005D817D : public Rva005EE30C
{
public:
	Rva005D817D();
	virtual ~Rva005D817D();
};

Rva005D817D::Rva005D817D()
{
}

class Rva005D8223 : public Rva005EE30C
{
public:
	Rva005D8223();
	virtual ~Rva005D8223();
};

Rva005D8223::Rva005D8223()
{
}

class Rva005D86E6 : public Rva005EE30C
{
public:
	Rva005D86E6();
	virtual ~Rva005D86E6();
};

Rva005D86E6::Rva005D86E6()
{
}

class Rva005D8AE4 : public Rva005EE30C
{
public:
	Rva005D8AE4();
	virtual ~Rva005D8AE4();
};

Rva005D8AE4::Rva005D8AE4()
{
}

class Rva005D8C25 : public Rva005EE30C
{
public:
	Rva005D8C25();
	virtual ~Rva005D8C25();
};

Rva005D8C25::Rva005D8C25()
{
}

class Rva005D8EE8 : public Rva005EE30C
{
public:
	Rva005D8EE8();
	virtual ~Rva005D8EE8();
};

Rva005D8EE8::Rva005D8EE8()
{
}

class Rva005D9CD5 : public Rva005EE30C
{
public:
	Rva005D9CD5();
	virtual ~Rva005D9CD5();
};

Rva005D9CD5::Rva005D9CD5()
{
}

class Rva005D91AB : public Rva005EE30C
{
public:
	Rva005D91AB();
	virtual ~Rva005D91AB();
};

Rva005D91AB::Rva005D91AB()
{
}

class Rva005D944A : public Rva005EE30C
{
public:
	Rva005D944A();
	virtual ~Rva005D944A();
};

Rva005D944A::Rva005D944A()
{
}

class Rva005D95A8 : public Rva005EE30C
{
public:
	Rva005D95A8();
	virtual ~Rva005D95A8();
};

Rva005D95A8::Rva005D95A8()
{
}

class Rva005D96FA : public Rva005EE30C
{
public:
	Rva005D96FA();
	virtual ~Rva005D96FA();
};

Rva005D96FA::Rva005D96FA()
{
}

class Rva005D9C6C : public Rva005EE30C
{
public:
	Rva005D9C6C();
	virtual ~Rva005D9C6C();
};

// ??0Rva005D9C6C@@QAE@XZ @0x005D9C5A 18B: base ctor 0x005EE2E6 then vtable
// 0x008763FC. Evidence: vtable store at [this]; caller 0x0058A7C3.
Rva005D9C6C::Rva005D9C6C()
{
}

class Rva005D7A1B : public Rva005EE30C
{
public:
	Rva005D7A1B();
	virtual ~Rva005D7A1B();
};

// ??0Rva005D7A1B@@QAE@XZ @0x005D7A09 18B: base ctor 0x005EE2E6 then vtable
// 0x00875E20. Evidence: vtable store at [this]; precedes rowed dtor 0x005D7A1B.
Rva005D7A1B::Rva005D7A1B()
{
}
