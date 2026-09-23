// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0W3DBoatWakeModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000D0B34,
// 47 bytes. Draw-side ctor completing the W3DBoatWakeModelDraw file-unit
// (name getter rowed at 0xD0B63 returning the W3DBoatWakeModelDraw literal;
// pool key rowed at 0xD0C93; ModuleData factory rowed at 0x6505F; behavior
// instance factory rowed at 0x65027 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the DrawModule base 0xB19A1 with a
// flag zero, two int zeros and a float zero around the derived vtable stored
// explicitly via pointer cast (W3DTreeDraw precedent: no virtuals are
// declared anywhere so no vtable is emitted here; the vtable immediate is
// DIR32-masked in comparison). Zero new pins (base resolves via the existing
// DrawModule pin). Row supersedes the ctor pin.

class Thing;
class ModuleData;

class DrawModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
};

class W3DBoatWakeModelDraw : public DrawModule
{
public:
	W3DBoatWakeModelDraw(Thing *thing, const ModuleData *moduleData);

private:
	float m_0C;
	bool m_flag10;
	int m_14;
	int m_18;
};

// ??0W3DBoatWakeModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0xD0B34
W3DBoatWakeModelDraw::W3DBoatWakeModelDraw(Thing *thing, const ModuleData *moduleData) :
	DrawModule(thing, moduleData)
{
	m_flag10 = false;
	m_14 = 0;
	m_18 = 0;
	*(unsigned int *)this = 0x00BCDD70;
	m_0C = 0.0f;
}
