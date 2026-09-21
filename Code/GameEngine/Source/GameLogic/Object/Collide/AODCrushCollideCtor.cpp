// cl: /O1 /DNDEBUG /MD
//
// ??0AODCrushCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BC00D, 67 bytes. AODCrushCollide behavior ctor over the rowed
// UpdateModule base (0x253390, thing plus data): initializes the
// CrushCollide-interface slot at +0x20 and zeroes +0x24/+0x28/+0x2C, then
// re-stores the primary vtable slot (the behavior vtable 0x00C5A31C) and
// the +0x0C/+0x10/+0x20 secondary slots (address-of TU-local dummies,
// DIR32-masked).
//
// Donor: BFME1 AODCrushCollideConstructor.cpp (three inline-ctor levels;
// the CrushCollide level adds the +0x20 interface slot with +0x24/+0x28/+0x2C
// fields, and AODCrushCollide overwrites all four vtable slots). Retail
// calls UpdateModule directly, so the CrushCollide level is modeled flat
// with init-list members; the _ReadWriteBarrier keeps the init-list +0x20
// store from folding into the body +0x20 re-store (zero bytes emitted), and
// the zeros live in the body so the xor materializes after the +0x20 store.
// Class identity is the AODCrush retail cluster (pool key rowed at
// 0x004BBF44, name getter at 0x004BBEFD pushing AODCrushCollide, vtable
// 0x00C5A31C installed here and in the thunk at 0x004BBEDD, the instance
// factory at 0x0025101E is the sole raw caller).

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_crush20;
static int s_aod20;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x20 - 0x14];
};

class AODCrushCollide : public UpdateModule
{
public:
	AODCrushCollide(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_x20;
	int m_x24;
	int m_x28;
	bool m_x2C;
};

// ??0AODCrushCollide@@QAE@PAVThing@@PBVModuleData@@@Z
AODCrushCollide::AODCrushCollide(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_x20(&s_crush20)
{
	_ReadWriteBarrier();
	m_x24 = 0;
	m_x28 = 0;
	m_x2C = false;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_x20 = &s_aod20;
}
