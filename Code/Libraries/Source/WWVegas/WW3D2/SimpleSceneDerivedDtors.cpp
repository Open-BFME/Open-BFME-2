// cl: /MD
//
// Opaque single-inheritance destructor tail-calling the matched
// SimpleSceneClass::~SimpleSceneClass at 0x00141DF0 (defined in
// WW3D2/SimpleSceneClass_dtor.cpp; only declared here so the tail-call
// resolves to the ledger address instead of a same-TU definition). The
// class below stores its own vtable (0xBC6310, DIR32 auto-patch) and
// tail-jumps to the base destructor. Owner identity is unproven (opaque
// Rva name). One ledger row per destructor, landed one commit at a time.

class RenderInfoClass;

class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();
protected:
	virtual void Customized_Render(RenderInfoClass &rinfo);
};

class Rva0006EE6F : public SimpleSceneClass
{
public:
	Rva0006EE6F();
	virtual ~Rva0006EE6F();
protected:
	virtual void Customized_Render(RenderInfoClass &rinfo);
};

Rva0006EE6F::~Rva0006EE6F()
{
}

// Target6EE5D..6EE6F calls the now-recovered SimpleScene constructor142960,
// then installs the same BC6310 table as this opaque derived destructor.
// Only the inherited constructor call and virtual prefix are modeled here;
// neither sizeof the derived allocation nor a semantic class name is asserted.
Rva0006EE6F::Rva0006EE6F() {}

// ?Customized_Render@Rva0006EE6F@@MAEXAAVRenderInfoClass@@@Z @0x0006EE22 5B:
// slot 23 of the class's vtable 0x00BC6310 (and of the derived table at
// 0x00BC62A0): extends nothing, a tail jump to the rowed
// SimpleSceneClass::Customized_Render 0x00141A30 with the same arguments.
void Rva0006EE6F::Customized_Render(RenderInfoClass &rinfo)
{
	SimpleSceneClass::Customized_Render(rinfo);
}
