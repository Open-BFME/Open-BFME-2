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
	Rva00657670(EmitVtableTag *);
	virtual ~Rva00657670() {}
};

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
	Rva006613E0(EmitVtableTag *);
	virtual ~Rva006613E0() {}
};

// ?<Rva006613E0::Rva006613E0> absent-from-retail
Rva006613E0::Rva006613E0(EmitVtableTag *)
{
}

// ??_GRva00663530@@UAEPAXI@Z @0x00663530 31B: slot 0 of the vtable it stores, VA 0x00CE2DB4
class Rva00663530
{
public:
	Rva00663530(EmitVtableTag *);
	virtual ~Rva00663530() {}
};

// ?<Rva00663530::Rva00663530> absent-from-retail
Rva00663530::Rva00663530(EmitVtableTag *)
{
}

// ??_GRva00663550@@UAEPAXI@Z @0x00663550 31B: slot 0 of the vtable it stores, VA 0x00CE2E10
class Rva00663550
{
public:
	Rva00663550(EmitVtableTag *);
	virtual ~Rva00663550() {}
};

// ?<Rva00663550::Rva00663550> absent-from-retail
Rva00663550::Rva00663550(EmitVtableTag *)
{
}

// ??_GRva00665030@@UAEPAXI@Z @0x00665030 31B: slot 0 of the vtable it stores, VA 0x00CE30A8
class Rva00665030
{
public:
	Rva00665030(EmitVtableTag *);
	virtual ~Rva00665030() {}
};

// ?<Rva00665030::Rva00665030> absent-from-retail
Rva00665030::Rva00665030(EmitVtableTag *)
{
}

// ??_GRva006655B0@@UAEPAXI@Z @0x006655B0 31B: slot 10 of the vtable it stores, VA 0x00CE3168
class Rva006655B0
{
public:
	Rva006655B0(EmitVtableTag *);
	virtual ~Rva006655B0() {}
};

// ?<Rva006655B0::Rva006655B0> absent-from-retail
Rva006655B0::Rva006655B0(EmitVtableTag *)
{
}

// ??_GRva00665C10@@UAEPAXI@Z @0x00665C10 31B: slot 0 of the vtable it stores, VA 0x00CE31BC
class Rva00665C10
{
public:
	Rva00665C10(EmitVtableTag *);
	virtual ~Rva00665C10() {}
};

// ?<Rva00665C10::Rva00665C10> absent-from-retail
Rva00665C10::Rva00665C10(EmitVtableTag *)
{
}

// ??_GRva00667260@@UAEPAXI@Z @0x00667260 31B: slot 0 of the vtable it stores, VA 0x00CE3410
class Rva00667260
{
public:
	Rva00667260(EmitVtableTag *);
	virtual ~Rva00667260() {}
};

// ?<Rva00667260::Rva00667260> absent-from-retail
Rva00667260::Rva00667260(EmitVtableTag *)
{
}

// ??_GRva006680E0@@UAEPAXI@Z @0x006680E0 31B: slot 10 of the vtable it stores, VA 0x00CE36A0
class Rva006680E0
{
public:
	Rva006680E0(EmitVtableTag *);
	virtual ~Rva006680E0() {}
};

// ?<Rva006680E0::Rva006680E0> absent-from-retail
Rva006680E0::Rva006680E0(EmitVtableTag *)
{
}

// ??_GRva00669510@@UAEPAXI@Z @0x00669510 31B: slot 10 of the vtable it stores, VA 0x00CE3934
class Rva00669510
{
public:
	Rva00669510(EmitVtableTag *);
	virtual ~Rva00669510() {}
};

// ?<Rva00669510::Rva00669510> absent-from-retail
Rva00669510::Rva00669510(EmitVtableTag *)
{
}

// ??_GRva0066D950@@UAEPAXI@Z @0x0066D950 31B: slot 0 of the vtable it stores, VA 0x00CE3B38
class Rva0066D950
{
public:
	Rva0066D950(EmitVtableTag *);
	virtual ~Rva0066D950();
};

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
	Rva00672490(EmitVtableTag *);
	virtual ~Rva00672490() {}
};

// ?<Rva00672490::Rva00672490> absent-from-retail
Rva00672490::Rva00672490(EmitVtableTag *)
{
}
