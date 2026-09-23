// cl: /O1 /DNDEBUG /MD
//
// ??0ModelConditionAudioLoopClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004CBECA, 67 bytes.
// ModelConditionAudioLoopClientBehavior behavior ctor over the rowed
// Rva00252B68 base (0x252B68, thing plus data): double-stores +0x0C/+0x10
// (both firsts volatile) around the primary vtable slot, an int 1 at +0x14
// and a trailing and-zero at +0x18 (address-of TU-local dummies,
// DIR32-masked). The rowed name getter at 0x4CBF13 proves the class; the rowed instance
// factory 0x252D62 is the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_first0C;
static int s_first10;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Rowed Rva00252B68 base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva00252B68
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
	const void *m_p10;
};

class ModelConditionAudioLoopClientBehavior : public Rva00252B68
{
public:
	ModelConditionAudioLoopClientBehavior(Thing *thing, const ModuleData *moduleData);

private:
	int m_14;
	int m_18;
};

// ??0ModelConditionAudioLoopClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x4CBECA
ModelConditionAudioLoopClientBehavior::ModelConditionAudioLoopClientBehavior(Thing *thing, const ModuleData *moduleData)
	: Rva00252B68(thing, moduleData)
{
	*(const void * volatile *)&m_p0C = &s_first0C;
	*(const void * volatile *)&m_p10 = &s_first10;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_14 = 1;
	_ReadWriteBarrier();
	m_18 = 0;
}
