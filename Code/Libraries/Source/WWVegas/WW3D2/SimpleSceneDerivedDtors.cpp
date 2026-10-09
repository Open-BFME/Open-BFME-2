// cl: /MD
//
// Opaque single-inheritance destructor tail-calling the matched
// SimpleSceneClass::~SimpleSceneClass at 0x00141DF0 (defined in
// WW3D2/SimpleSceneClass_dtor.cpp; only declared here so the tail-call
// resolves to the ledger address instead of a same-TU definition). The
// class below stores its own vtable (0xBC6310, DIR32 auto-patch) and
// tail-jumps to the base destructor. Owner identity is unproven (opaque
// Rva name). One ledger row per destructor, landed one commit at a time.

class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();
};

class Rva0006EE6F : public SimpleSceneClass
{
public:
	Rva0006EE6F();
	virtual ~Rva0006EE6F();
};

Rva0006EE6F::~Rva0006EE6F()
{
}

// Target6EE5D..6EE6F calls the now-recovered SimpleScene constructor142960,
// then installs the same BC6310 table as this opaque derived destructor.
// Only the inherited constructor call and virtual prefix are modeled here;
// neither sizeof the derived allocation nor a semantic class name is asserted.
Rva0006EE6F::Rva0006EE6F() {}
