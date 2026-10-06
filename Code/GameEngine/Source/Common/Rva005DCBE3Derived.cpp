// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva005DCBE3::~
// Rva005DCBE3 at 0x005DCBE3 (row in Rva004EDCE9Derived.cpp). The class below
// stores its own vtable (0xC71FF4, DIR32 auto-patch) and tail-calls the base
// destructor; the base itself is only declared here (defined once in
// Rva004EDCE9Derived.cpp), because a same-TU definition would capture the
// call locally instead of at the ledger address. Owner identity is unproven
// (opaque Rva name). One ledger row per destructor, landed one commit at a
// time.

class Rva005DCBE3
{
public:
	virtual ~Rva005DCBE3();
};

class AISimpleExpansionTactic : public Rva005DCBE3
{
public:
	virtual ~AISimpleExpansionTactic();
};

AISimpleExpansionTactic::~AISimpleExpansionTactic()
{
}
