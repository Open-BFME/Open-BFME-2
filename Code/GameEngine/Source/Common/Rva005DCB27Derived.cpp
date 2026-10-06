// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva005DCB27::~
// Rva005DCB27 at 0x005DCB27 (row in Rva004EDCE9Derived.cpp). The class below
// stores its own vtable (0xC71FBC, DIR32 auto-patch) and tail-calls the base
// destructor; the base itself is only declared here (defined once in
// Rva004EDCE9Derived.cpp), because a same-TU definition would capture the
// call locally instead of at the ledger address. Owner identity is unproven
// (opaque Rva name). One ledger row per destructor, landed one commit at a
// time.

class Rva005DCB27
{
public:
	virtual ~Rva005DCB27();
};

class Rva005AA735 : public Rva005DCB27
{
public:
	virtual ~Rva005AA735();
};

Rva005AA735::~Rva005AA735()
{
}
