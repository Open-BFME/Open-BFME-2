// cl: /O1 /DNDEBUG /MD
//
// AODCrushCollide destructor pair, retail 0x004BBEDD (32 bytes) and
// 0x004BC050 (28 bytes). The dtor reinstalls the behavior vtable slot and
// the +0x0C/+0x10/+0x20 secondary slots, then tail-jumps to the UpdateModule
// base dtor (existing pin at 0x0024A797); the scalar-deleting-dtor runs the
// dtor and conditionally frees through the rowed operator delete.
//
// The four vtable slots need a four-vptr TU-local model (single inheritance
// emits one store): CollideDtorB1 carries the module-data/object members to
// +0x0C, B2 is a bare vptr at +0x0C, B3 pads to +0x20, B4 is the +0x20 vptr.
// The MI is a vptr-placement model only; the proven facts are the four
// store slots, the single base-dtor tail jump, and the AODCrushCollide
// name (vtable 0x00C5A31C slot2 getter pushes AODCrushCollide, pool key
// rowed at 0x004BBF44). Recipe: the opaque MI-dtor pattern
// (Rva004BC4FCDerived.cpp). The anchors are defined trivially so the TU
// links; only the dtor pair is rowed.

class Thing;
class ModuleData;

class CollideDtorB1
{
public:
	virtual void b1anchor() {}

protected:
	const ModuleData *m_moduleData;
	void *m_object;
};

class CollideDtorB2
{
public:
	virtual void b2anchor() {}
};

class CollideDtorB3
{
public:
	virtual void b3anchor() {}

protected:
	char m_pad[0x0C];
};

class CollideDtorB4
{
public:
	virtual void b4anchor() {}
};

class UpdateModule : public CollideDtorB1, public CollideDtorB2, public CollideDtorB3, public CollideDtorB4
{
public:
	virtual ~UpdateModule();
};

class AODCrushCollide : public UpdateModule
{
public:
	virtual ~AODCrushCollide();
};

// ??1AODCrushCollide@@UAE@XZ
AODCrushCollide::~AODCrushCollide()
{
}
