// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva006F1360::~
// Rva006F1360 at 0x006F1360 (matched opaque dtor with member clears in
// Rva006F1360Dtor.cpp; only declared here so the tail-call resolves to the
// ledger address instead of a same-TU definition). The class below stores
// its own vtable (0xCECD4C, DIR32 auto-patch) and tail-calls the base
// destructor. Owner identity is unproven (opaque Rva name). One ledger row
// per destructor, landed one commit at a time.

class Rva006F1360
{
public:
	virtual ~Rva006F1360();
};

class Rva006F1DB0 : public Rva006F1360
{
public:
	virtual ~Rva006F1DB0();
};

Rva006F1DB0::~Rva006F1DB0()
{
}
