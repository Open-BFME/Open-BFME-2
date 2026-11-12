// cl: /DNDEBUG /MD
//
// ??1Rva00666BA0@@UAE@XZ, retail 0x00666BA0 (7 bytes). Dedicated TU: the
// shared base destructor only reinstalls its vtable (0x00CE2BD8). It lives
// apart from the derived TU on purpose -- derived destructors at 0x00661350
// (11B) and 0x006617C0 (39B) call it out of line, and a same-TU definition
// would capture those calls locally instead of at the ledger address
// (BfmeDirtyBaseDtor.cpp precedent).

struct Rva00666BA0
{
	Rva00666BA0();
	virtual ~Rva00666BA0();
	// Retail table 0x00CE2BD8: the deleting destructor, then 3 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
};

// Retail's scalar deleting destructor (0x00661330) calls this body out of
// line; noinline keeps this unit's emitted ??_G the same call shape.
__declspec(noinline) Rva00666BA0::~Rva00666BA0()
{
}
