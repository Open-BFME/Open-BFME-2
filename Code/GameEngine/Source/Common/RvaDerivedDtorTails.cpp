// cl: /MD
//
// Derived-class destructors with empty bodies: store the class's vtable, then
// tail-jump to the rowed base destructor (11 bytes: mov [ecx], vtable; jmp).
// The derived destructor is defined here, so its vtable is emitted with the
// class and resolves in this unit. The classes are not recovered, so each keeps
// its address; the bases are the rowed destructors' address-named classes.

class Rva005C7CBB
{
public:
	virtual ~Rva005C7CBB();
};

class Rva005F38CA
{
public:
	virtual ~Rva005F38CA();
};

class Rva006003FC
{
public:
	virtual ~Rva006003FC();
};

// ??1Rva005C33D2@@UAE@XZ @0x005C33D2 11B: vtable VA 0xc74434, then ~Rva005C7CBB
class Rva005C33D2 : public Rva005C7CBB
{
public:
	virtual ~Rva005C33D2();
};

Rva005C33D2::~Rva005C33D2()
{
}

// ??1Rva005E54AE@@UAE@XZ @0x005E54AE 11B: vtable VA 0xc77d10, then ~Rva005F38CA
class Rva005E54AE : public Rva005F38CA
{
public:
	virtual ~Rva005E54AE();
};

Rva005E54AE::~Rva005E54AE()
{
}

// ??1Rva005FB204@@UAE@XZ @0x005FB204 11B: vtable VA 0xc79ef0, then ~Rva006003FC
class Rva005FB204 : public Rva006003FC
{
public:
	virtual ~Rva005FB204();
};

Rva005FB204::~Rva005FB204()
{
}

// ??1Rva005FB3D9@@UAE@XZ @0x005FB3D9 11B: vtable VA 0xc79f10, then ~Rva006003FC
class Rva005FB3D9 : public Rva006003FC
{
public:
	virtual ~Rva005FB3D9();
};

Rva005FB3D9::~Rva005FB3D9()
{
}
