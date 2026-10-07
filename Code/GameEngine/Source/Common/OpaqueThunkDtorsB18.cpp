// cl: /O1 /arch:SSE /G7 /Ob2 /EHsc /DNDEBUG /MD
// Thunk dtors for OpaqueScalarDeletingDtorsB18 (6x5B jmp to rowed base dtors).
// Each is a virtual dtor that only tail-jmps to its rowed base dtor (no vptr
// store: novtable derived with empty body). Precedent: Rva00072FE1 (5B
// novtable dtor tail-jumps to base Rva0072AED) in Rva00072AEDDtor.cpp.
//   ??1Rva005F8F5A@@UAE@XZ @0x005F8F5A 5B jmp ??1Rva005FE7FA@@UAE@XZ @0x005FE7FA (59B rowed Rva005FE7FA.cpp); caller ??_G 0x005F8F3E; vtable 0x00C79CF8#0
//   ??1Rva005F8F7B@@UAE@XZ @0x005F8F7B 5B jmp ??1Rva005FE750@@UAE@XZ @0x005FE750 (87B rowed Rva005FE750.cpp); caller ??_G 0x005F8F5F; vtable 0x00C79D0C#0
//   ??1Rva005FA141@@UAE@XZ @0x005FA141 5B jmp ??1Rva005F8FEE@@UAE@XZ @0x005F8FEE (101B rowed Rva005F8FEEDtor.cpp); caller ??_G 0x005FA125; vtable 0x00C79D78#0
//   ??1Rva005FCFE5@@UAE@XZ @0x005FCFE5 5B jmp ??1Rva005FCF0E@@UAE@XZ @0x005FCF0E (75B rowed same B18); caller ??_G 0x005FCFC9; vtable 0x00C7A1D0#0
//   ??1Rva005FED4D@@UAE@XZ @0x005FED4D 5B jmp ??1Rva005FF95C@@UAE@XZ @0x005FF95C (14B rowed Rva005FF95CDtor.cpp); caller ??_G 0x005FEDB1; vtable 0x00C7A448#0
//   ??1Rva00600379@@UAE@XZ @0x00600379 5B jmp ??1Rva00600084@@UAE@XZ @0x00600084 (14B rowed OpaqueScalarDeletingDtors.cpp); caller ??_G 0x006003D3; vtable 0x00C7A620#0

class Rva005FE7FA
{
public:
	virtual ~Rva005FE7FA();
};

class __declspec(novtable) Rva005F8F5A : public Rva005FE7FA
{
public:
	virtual ~Rva005F8F5A();
};

Rva005F8F5A::~Rva005F8F5A()
{
}

class Rva005FE750
{
public:
	virtual ~Rva005FE750();
};

class __declspec(novtable) Rva005F8F7B : public Rva005FE750
{
public:
	virtual ~Rva005F8F7B();
};

Rva005F8F7B::~Rva005F8F7B()
{
}

class Rva005F8FEE
{
public:
	virtual ~Rva005F8FEE();
};

class __declspec(novtable) Rva005FA141 : public Rva005F8FEE
{
public:
	virtual ~Rva005FA141();
};

Rva005FA141::~Rva005FA141()
{
}

class Rva005FCF0E
{
public:
	virtual ~Rva005FCF0E();
};

class __declspec(novtable) Rva005FCFE5 : public Rva005FCF0E
{
public:
	virtual ~Rva005FCFE5();
};

Rva005FCFE5::~Rva005FCFE5()
{
}

class Rva005FF95C
{
public:
	virtual ~Rva005FF95C();
};

class __declspec(novtable) Rva005FED4D : public Rva005FF95C
{
public:
	virtual ~Rva005FED4D();
};

Rva005FED4D::~Rva005FED4D()
{
}

class Rva00600084
{
public:
	virtual ~Rva00600084();
};

class __declspec(novtable) Rva00600379 : public Rva00600084
{
public:
	virtual ~Rva00600379();
};

Rva00600379::~Rva00600379()
{
}
