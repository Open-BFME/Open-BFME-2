// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0ObjectDefectionHelper@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0028C955, 61 bytes.
// ObjectDefectionHelper behavior ctor over the rowed ObjectHelper base
// (0x28C8DF, thing plus data): detection-window zeros at +0x20/+0x24, FX flag
// false at +0x2C, the three most-derived vtable slots, flash phase 0.0f at
// +0x28 last (address-of TU-local dummies, DIR32-masked; xorps float zero).
// BFME1 donor is ObjectDefectionHelper.cpp; BFME2 keeps the member order
// with the float store scheduled last. The rowed factory 0x2996CC
// (news 0x30, matching this layout) is the sole raw caller, and the
// ObjectDefectionHelper pool key at 0x28C992 immediately follows. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque ObjectHelper base (0x20 bytes); 2-arg ctor resolves to its row.
class ObjectHelper
{
public:
	ObjectHelper(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_baseVtable;
	unsigned char m_midPad[0x0C - 0x04];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_tailPad[0x20 - 0x14];
};

class ObjectDefectionHelper : public ObjectHelper
{
public:
	ObjectDefectionHelper(Thing *thing, const ModuleData *moduleData);

private:
	unsigned int m_defectionDetectionStart;
	unsigned int m_defectionDetectionEnd;
	float m_defectionDetectionFlashPhase;
	bool m_doDefectorFX;
};

// ??0ObjectDefectionHelper@@QAE@PAVThing@@PBVModuleData@@@Z @0x28C955
ObjectDefectionHelper::ObjectDefectionHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	m_defectionDetectionEnd = 0;
	m_defectionDetectionStart = 0;
	m_doDefectorFX = false;
	m_baseVtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_defectionDetectionFlashPhase = 0.0f;
}
