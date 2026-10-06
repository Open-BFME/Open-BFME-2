// cl: /MD
//
// Opaque single-inheritance destructor tail-calling the matched
// MultiListObjectClass::~MultiListObjectClass at 0x006109C0 (defined in
// WWLib/multilist.cpp; only declared here so the tail-call resolves to the
// ledger address instead of a same-TU definition). The class below stores
// its own vtable (0xBC5C74, DIR32 auto-patch) and tail-jumps to the base
// destructor. Owner identity is unproven (opaque Rva name). One ledger row
// per destructor, landed one commit at a time.

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
};

class Rva000658BA : public MultiListObjectClass
{
public:
	virtual ~Rva000658BA();
};

Rva000658BA::~Rva000658BA()
{
}
