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
	virtual ~SimpleSceneClass();
};

class Rva0006EE6F : public SimpleSceneClass
{
public:
	virtual ~Rva0006EE6F();
};

Rva0006EE6F::~Rva0006EE6F()
{
}
