// cl: /DNDEBUG /MD /EHs-c-
// Disable both C++ EH modes, as in the matched deleting-destructor units.
// Otherwise VC7.1 emits deleting destructors that call these 11-byte bodies;
// retail inlines the derived vptr store and calls the base destructor directly.
//
// Opaque single-inheritance destructors tail-calling BfmeDirtyBase::~
// BfmeDirtyBase at 0x00658650 (matched 7B leaf base dtor in
// DirtySock/BfmeDirtyBaseDtor.cpp; only declared here so each tail-call
// resolves to the ledger address instead of a same-TU definition). Each
// class below stores its own vtable (DIR32 auto-patches) and tail-jumps to
// the base destructor. Owner identities are unproven (opaque Rva names). One
// ledger row per destructor, landed one commit at a time.

#include "../../../GameEngine/Include/Common/BfmeDirtyBase.h"

class Rva006560E0 : public BfmeDirtyBase
{
public:
	virtual ~Rva006560E0();
public:
	// Retail table 0x00CE0FC8: the deleting destructor, then 21 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
};

Rva006560E0::~Rva006560E0()
{
}

class Rva0065D1D0 : public BfmeDirtyBase
{
public:
	virtual ~Rva0065D1D0();
public:
	// Retail table 0x00CE1E30: the deleting destructor, then 12 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
};

Rva0065D1D0::~Rva0065D1D0()
{
}

class Rva0065E7D0 : public BfmeDirtyBase
{
public:
	virtual ~Rva0065E7D0();
public:
	// Retail table 0x00CE2368: the deleting destructor, then 4 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
};

Rva0065E7D0::~Rva0065E7D0()
{
}

class Rva0065ECF0 : public BfmeDirtyBase
{
public:
	virtual ~Rva0065ECF0();
public:
	// Retail table 0x00CE24A0: the deleting destructor, then 12 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
};

Rva0065ECF0::~Rva0065ECF0()
{
}

class Rva0065F970 : public BfmeDirtyBase
{
public:
	virtual ~Rva0065F970();
public:
	// Retail table 0x00CE2730: the deleting destructor, then 5 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
};

Rva0065F970::~Rva0065F970()
{
}

class Rva00660060 : public BfmeDirtyBase
{
public:
	virtual ~Rva00660060();
public:
	// Retail table 0x00CE2870: the deleting destructor, then 12 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
};

Rva00660060::~Rva00660060()
{
}

class Rva00660BE0 : public BfmeDirtyBase
{
public:
	virtual ~Rva00660BE0();
public:
	// Retail table 0x00CE2A6C: the deleting destructor, then 5 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
};

Rva00660BE0::~Rva00660BE0()
{
}

class Rva006672E0 : public BfmeDirtyBase
{
public:
	virtual ~Rva006672E0();
public:
	// Retail table 0x00CE34D0: the deleting destructor, then 25 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
};

Rva006672E0::~Rva006672E0()
{
}

class Rva00668120 : public BfmeDirtyBase
{
public:
	virtual ~Rva00668120();
public:
	// Retail table 0x00CE36D8: the deleting destructor, then 24 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
};

Rva00668120::~Rva00668120()
{
}
