// cl: /MD
//
// Opaque single-inheritance destructor tail-calling AIUpgrade::~
// AIUpgrade at 0x0059734B (row in Rva0055B0CCDerived.cpp). The class below
// stores its own vtable (0xC76640, DIR32 auto-patch) and tail-calls the base
// destructor; the base itself is only declared here (defined once in
// Rva0055B0CCDerived.cpp), because a same-TU definition would capture the
// call locally instead of at the ledger address. Owner identity is unproven
// (opaque Rva name). One ledger row per destructor, landed one commit at a
// time.

class AIUpgrade
{
public:
	AIUpgrade();
	virtual ~AIUpgrade();
};

class Rva005DAFD7 : public AIUpgrade
{
public:
	Rva005DAFD7();
	virtual ~Rva005DAFD7();
};

// ??0Rva005DAFD7@@QAE@XZ @0x005DAFC5 18B ctor calls base ??0AIUpgrade then stores vtable 0x00876640
Rva005DAFD7::Rva005DAFD7()
{
}

Rva005DAFD7::~Rva005DAFD7()
{
}
