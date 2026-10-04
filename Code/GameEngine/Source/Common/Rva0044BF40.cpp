// cl: /O1 /EHsc /MD
// ?rva0044BF40@Rva0044BF40@@QAEPAU1@URva0044BA4E@@@Z @0x0044BF40 55B
// EH setter twin of rowed Rva0044BF77 (0x0044BF77 59B): forward the by-value
// 8-byte holder at [ebp+8] as const Pair ref to the rowed setter
// rva0044BEB9 (0x0044BEB9 45B), then destroy the holder via rowed dtor
// ??1Rva0044BA4E (0x0044BA4E 61B), return this. Holder and Pair are both
// two-pointer 8-byte views; the reinterpret cast keeps the rowed callee
// names byte-identical. Model and flags mirror Rva0044BF77.cpp.
// Caller 0x0044C060; landing unblocks 0x0044BFE9 plus four others.
struct Rva004C5DD0Ref
{
	int m_00;
	int m_refs;
};

struct Rva004C5DD0Pair
{
	Rva004C5DD0Ref *a;
	Rva004C5DD0Ref *b;
};

struct Rva0044BA4E
{
	~Rva0044BA4E();
	void *m_00;
	void *m_04;
};

struct Rva0044BD34;
struct Rva0044BEB9
{
	Rva0044BD34 *m_ptr;
	Rva0044BEB9 *rva0044BEB9(const Rva004C5DD0Pair &arg);
};

struct Rva0044BF40 : Rva0044BEB9
{
	Rva0044BF40 *rva0044BF40(Rva0044BA4E arg);
};

Rva0044BF40 *Rva0044BF40::rva0044BF40(Rva0044BA4E arg)
{
	rva0044BEB9((const Rva004C5DD0Pair &)arg);
	return this;
}

// ?rva0044BFB2@Rva0044BFB2@@QAEPAU1@URva0044BA4E@@@Z @0x0044BFB2 55B
// EH setter twin of rowed rva0044BF40 above over the rowed setter rva0044BF13
// (0x0044BF13 45B): same by-value BA4E holder, same Pair reinterpret,
// same rowed dtor 0x0044BA4E. Caller 0x0044C1BD; landing unblocks 0x0044C146.
struct Rva0044BDD8;
struct Rva0044BF13
{
	Rva0044BDD8 *m_ptr;
	Rva0044BF13 *rva0044BF13(const Rva004C5DD0Pair &arg);
};

struct Rva0044BFB2 : Rva0044BF13
{
	Rva0044BFB2 *rva0044BFB2(Rva0044BA4E arg);
};

Rva0044BFB2 *Rva0044BFB2::rva0044BFB2(Rva0044BA4E arg)
{
	rva0044BF13((const Rva004C5DD0Pair &)arg);
	return this;
}
