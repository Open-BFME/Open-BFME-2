// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva005D8964::~
// Rva005D8964 at 0x005D8964 (row in Rva005EE2A0Derived.cpp). The class below
// stores its own vtable (0xC76190, DIR32 auto-patch) and tail-calls the base
// destructor; the base itself is only declared here (defined once in
// Rva005EE2A0Derived.cpp), because a same-TU definition would capture the
// call locally instead of at the ledger address. Owner identity is unproven
// (opaque Rva name). One ledger row per destructor, landed one commit at a
// time.

class Rva005D8964
{
public:
	Rva005D8964();
	virtual ~Rva005D8964();
};

class Rva005D8883 : public Rva005D8964
{
public:
	Rva005D8883();
	virtual ~Rva005D8883();
};

// ??0Rva005D8883@@QAE@XZ @0x005D8871 18B: base ctor 0x005D8952 then vtable
// 0x00876190. Evidence: vtable store at [this]; caller 0x0058A9AA.
Rva005D8883::Rva005D8883()
{
}

Rva005D8883::~Rva005D8883()
{
}
