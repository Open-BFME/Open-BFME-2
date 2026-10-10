// cl: /O2 /DNDEBUG /MD
// Scalar deleting destructors of opaque polymorphic classes whose
// destructor is inline and empty: each 31B body stores a vtable, frees
// through operator delete 0x0002FD60 on flag bit 0 and returns this. Each
// is the destructor slot (index read from .rdata, listed beside it) of the
// vtable it stores. The dummy tag constructors (no retail counterpart) only
// make this TU emit each vtable and with it the deleting destructor. Owner
// identities and layouts are not recovered.

struct EmitVtableTag;

// ??_GRva00657670@@UAEPAXI@Z @0x00657670 31B: slot 0 of the vtable it stores, VA 0x00CE1354
class Rva00657670
{
public:
	Rva00657670();
	Rva00657670(EmitVtableTag *);
	virtual ~Rva00657670();
};

// ??1Rva00657670@@UAE@XZ @0x00657660 7B: the empty destructor, restoring the vtable
// (VA 0x00CE1354); the deleting destructor still expands it inline.
Rva00657670::~Rva00657670()
{
}

// ??0Rva00657670@@QAE@XZ @0x00656C80 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE1354) and returning this.
Rva00657670::Rva00657670()
{
}

// ?<Rva00657670::Rva00657670> absent-from-retail
Rva00657670::Rva00657670(EmitVtableTag *)
{
}

// ??_GRva00661380@@UAEPAXI@Z @0x00661380 31B: slot 0 of the vtable it stores, VA 0x00CE2C04
class Rva00661380
{
public:
	Rva00661380(EmitVtableTag *);
	virtual ~Rva00661380() {}
};

// ?<Rva00661380::Rva00661380> absent-from-retail
Rva00661380::Rva00661380(EmitVtableTag *)
{
}

// ??_GRva006613E0@@UAEPAXI@Z @0x006613E0 31B: slot 0 of the vtable it stores, VA 0x00CE2BCC
class Rva006613E0
{
public:
	Rva006613E0();
	Rva006613E0(EmitVtableTag *);
	virtual ~Rva006613E0();
};

// ??1Rva006613E0@@UAE@XZ @0x00661360 7B: the empty destructor, restoring the vtable
// (VA 0x00CE2BCC); the deleting destructor still expands it inline.
Rva006613E0::~Rva006613E0()
{
}

// ??0Rva006613E0@@QAE@XZ @0x00661310 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE2BCC) and returning this.
Rva006613E0::Rva006613E0()
{
}

// ?<Rva006613E0::Rva006613E0> absent-from-retail
Rva006613E0::Rva006613E0(EmitVtableTag *)
{
}

// ??_GRva00663530@@UAEPAXI@Z @0x00663530 31B: slot 0 of the vtable it stores, VA 0x00CE2DB4
class Rva00663530
{
public:
	Rva00663530();
	Rva00663530(EmitVtableTag *);
	virtual ~Rva00663530();
};

// ??1Rva00663530@@UAE@XZ @0x00661D70 7B: the empty destructor, restoring the vtable
// (VA 0x00CE2DB4); the deleting destructor still expands it inline.
Rva00663530::~Rva00663530()
{
}

// ??0Rva00663530@@QAE@XZ @0x00661D60 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE2DB4) and returning this.
Rva00663530::Rva00663530()
{
}

// ?<Rva00663530::Rva00663530> absent-from-retail
Rva00663530::Rva00663530(EmitVtableTag *)
{
}

// ??_GRva00663550@@UAEPAXI@Z @0x00663550 31B: slot 0 of the vtable it stores, VA 0x00CE2E10
class Rva00663550
{
public:
	Rva00663550();
	Rva00663550(EmitVtableTag *);
	virtual ~Rva00663550();
};

// ??1Rva00663550@@UAE@XZ @0x00661EA0 7B: the empty destructor, restoring the vtable
// (VA 0x00CE2E10); the deleting destructor still expands it inline.
Rva00663550::~Rva00663550()
{
}

// ??0Rva00663550@@QAE@XZ @0x00661E80 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE2E10) and returning this.
Rva00663550::Rva00663550()
{
}

// ?<Rva00663550::Rva00663550> absent-from-retail
Rva00663550::Rva00663550(EmitVtableTag *)
{
}

// ??_GRva00665030@@UAEPAXI@Z @0x00665030 31B: slot 0 of the vtable it stores, VA 0x00CE30A8
class Rva00665030
{
public:
	Rva00665030();
	Rva00665030(EmitVtableTag *);
	virtual ~Rva00665030();
};

// ??1Rva00665030@@UAE@XZ @0x00664DA0 7B: the empty destructor, restoring the vtable
// (VA 0x00CE30A8); the deleting destructor still expands it inline.
Rva00665030::~Rva00665030()
{
}

// ??0Rva00665030@@QAE@XZ @0x00664D80 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE30A8) and returning this.
Rva00665030::Rva00665030()
{
}

// ?<Rva00665030::Rva00665030> absent-from-retail
Rva00665030::Rva00665030(EmitVtableTag *)
{
}

// ??_GRva006655B0@@UAEPAXI@Z @0x006655B0 31B: slot 10 of the vtable it stores, VA 0x00CE3168
class Rva006655B0
{
public:
	Rva006655B0();
	Rva006655B0(EmitVtableTag *);
	virtual ~Rva006655B0();
};

// ??1Rva006655B0@@UAE@XZ @0x00665420 7B: the empty destructor, restoring the vtable
// (VA 0x00CE3168); the deleting destructor still expands it inline.
Rva006655B0::~Rva006655B0()
{
}

// ??0Rva006655B0@@QAE@XZ @0x006655F0 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE3168) and returning this.
Rva006655B0::Rva006655B0()
{
}

// ?<Rva006655B0::Rva006655B0> absent-from-retail
Rva006655B0::Rva006655B0(EmitVtableTag *)
{
}

// ??_GRva00665C10@@UAEPAXI@Z @0x00665C10 31B: slot 0 of the vtable it stores, VA 0x00CE31BC
class Rva00665C10
{
public:
	Rva00665C10();
	Rva00665C10(EmitVtableTag *);
	virtual ~Rva00665C10();
};

// ??1Rva00665C10@@UAE@XZ @0x00665B60 7B: the empty destructor, restoring the vtable
// (VA 0x00CE31BC); the deleting destructor still expands it inline.
Rva00665C10::~Rva00665C10()
{
}

// ??0Rva00665C10@@QAE@XZ @0x006656C0 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE31BC) and returning this.
Rva00665C10::Rva00665C10()
{
}

// ?<Rva00665C10::Rva00665C10> absent-from-retail
Rva00665C10::Rva00665C10(EmitVtableTag *)
{
}

// ??_GRva00667260@@UAEPAXI@Z @0x00667260 31B: slot 0 of the vtable it stores, VA 0x00CE3410
class Rva00667260
{
public:
	Rva00667260();
	Rva00667260(EmitVtableTag *);
	virtual ~Rva00667260();
};

// ??1Rva00667260@@UAE@XZ @0x00666EA0 7B: the empty destructor, restoring the vtable
// (VA 0x00CE3410); the deleting destructor still expands it inline.
Rva00667260::~Rva00667260()
{
}

// ??0Rva00667260@@QAE@XZ @0x00666E90 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE3410) and returning this.
Rva00667260::Rva00667260()
{
}

// ?<Rva00667260::Rva00667260> absent-from-retail
Rva00667260::Rva00667260(EmitVtableTag *)
{
}

// ??_GRva006680E0@@UAEPAXI@Z @0x006680E0 31B: slot 10 of the vtable it stores, VA 0x00CE36A0
class Rva006680E0
{
public:
	Rva006680E0();
	Rva006680E0(EmitVtableTag *);
	virtual ~Rva006680E0();
};

// ??1Rva006680E0@@UAE@XZ @0x00668060 7B: the empty destructor, restoring the vtable
// (VA 0x00CE36A0); the deleting destructor still expands it inline.
Rva006680E0::~Rva006680E0()
{
}

// ??0Rva006680E0@@QAE@XZ @0x00668110 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE36A0) and returning this.
Rva006680E0::Rva006680E0()
{
}

// ?<Rva006680E0::Rva006680E0> absent-from-retail
Rva006680E0::Rva006680E0(EmitVtableTag *)
{
}

// ??_GRva00669510@@UAEPAXI@Z @0x00669510 31B: slot 10 of the vtable it stores, VA 0x00CE3934
class Rva00669510
{
public:
	Rva00669510();
	Rva00669510(EmitVtableTag *);
	virtual ~Rva00669510();
};

// ??1Rva00669510@@UAE@XZ @0x006694B0 7B: the empty destructor, restoring the vtable
// (VA 0x00CE3934); the deleting destructor still expands it inline.
Rva00669510::~Rva00669510()
{
}

// ??0Rva00669510@@QAE@XZ @0x00669540 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE3934) and returning this.
Rva00669510::Rva00669510()
{
}

// ?<Rva00669510::Rva00669510> absent-from-retail
Rva00669510::Rva00669510(EmitVtableTag *)
{
}

// ??_GRva0066D950@@UAEPAXI@Z @0x0066D950 31B: slot 0 of the vtable it stores, VA 0x00CE3B38
class Rva0066D950
{
public:
	Rva0066D950();
	Rva0066D950(EmitVtableTag *);
	virtual ~Rva0066D950();
};

// ??0Rva0066D950@@QAE@XZ @0x0066D530 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE3B38) and returning this.
Rva0066D950::Rva0066D950()
{
}

// ?<Rva0066D950::Rva0066D950> absent-from-retail
Rva0066D950::Rva0066D950(EmitVtableTag *)
{
}

// ??1Rva0066D950@@UAE@XZ @0x0066D580 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva0066D950::~Rva0066D950()
{
}

// ??_GRva00672490@@UAEPAXI@Z @0x00672490 31B: slot 0 of the vtable it stores, VA 0x00CE3F2C
class Rva00672490
{
public:
	Rva00672490();
	Rva00672490(EmitVtableTag *);
	virtual ~Rva00672490();
};

// ??1Rva00672490@@UAE@XZ @0x00672330 7B: the empty destructor, restoring the vtable
// (VA 0x00CE3F2C); the deleting destructor still expands it inline.
Rva00672490::~Rva00672490()
{
}

// ??0Rva00672490@@QAE@XZ @0x00672320 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE3F2C) and returning this.
Rva00672490::Rva00672490()
{
}

// ?<Rva00672490::Rva00672490> absent-from-retail
Rva00672490::Rva00672490(EmitVtableTag *)
{
}
