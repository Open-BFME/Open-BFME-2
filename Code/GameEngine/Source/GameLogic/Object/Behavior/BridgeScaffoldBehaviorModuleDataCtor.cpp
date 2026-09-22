// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// stlport
//
// ??0BridgeScaffoldBehaviorModuleData@@QAE@XZ, retail 0x00457FF1 (89 bytes).
// The module-data half of BridgeScaffoldBehavior: vtable 0x00C40A10,
// LateralScaffoldSpeed@8 plus VerticalScaffoldSpeed@C (both 1.0f, via the
// retail literal at 0xBBB8D8) plus BridgeDieFX@10 plus BridgeDieOCL@14 (both
// coordinate lists through the rowed _List_base<Coord3D> at 0x280A8D).
// Field identity is the rowed buildFieldParse proc (table 0xC40B20:
// LateralScaffoldSpeed/VerticalScaffoldSpeed/BridgeDieFX/BridgeDieOCL) plus
// the rowed poolkey 0x4583BD plus factory 0x24AC3B (news 0x18, sole caller).
// The empty UpdateModuleData base (inline-empty ctor plus declared-only dtor)
// is load-bearing for the EH state machine (SpawnUnit precedent). /arch:SSE
// for movss float stores; /EHsc for the __EH_prolog frame.

#include <list>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class UpdateModuleData
{
public:
	UpdateModuleData()
	{
	}
	~UpdateModuleData();
};

class BridgeScaffoldBehaviorModuleData : public UpdateModuleData
{
public:
	BridgeScaffoldBehaviorModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	float m_lateralScaffoldSpeed;
	float m_verticalScaffoldSpeed;
	std::list<Coord3D> m_bridgeDieFX;
	std::list<Coord3D> m_bridgeDieOCL;
};

// ??0BridgeScaffoldBehaviorModuleData@@QAE@XZ @0x457FF1
BridgeScaffoldBehaviorModuleData::BridgeScaffoldBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C40A10))
{
	m_lateralScaffoldSpeed = 1.0f;
	m_verticalScaffoldSpeed = 1.0f;
}
