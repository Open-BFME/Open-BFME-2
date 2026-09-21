// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0HordeGarrisonContainModuleData@@QAE@XZ, retail 0x0047A251, 88 bytes.
// Frameless derived ctor over the ExitDelay table 0xC46388 (ExitDelay@AC,
// EntryOffset@B0, EntryPosition@BC, ExitOffset@C8). Identity is the table
// plus the HordeGarrisonContain poolkey 0x47A110 in the same cluster plus
// factory 0x24BAD1 (news 0xD4, sole caller) plus rowed chained proc 0x47A025
// plus the GarrisonContain-family base chain (rowed chained proc 0x254F75).
// Shape follows Defector/Oathbreakers precedent: the pinned base ctor
// 0x47978F (GarrisonContainModuleData, sole-caller pin documents the derived
// base-call 0x47A251) builds the 0xAC base; the derived overwrites the
// shared vtable slot via pointer-cast (Defector law: a source-written store
// lands in position, here 3rd after the base call and the +0xAC zero, while
// a compiler-emitted virtual store would lead); the three Coord3D float
// triples zero through address-CSEd lea runs under /O1 plus /arch:SSE.
// Vtable 0x00BF4328 is DIR32-masked (pinned ??_7 for identity; slot0 is the
// scalar-deleting dtor 0x2579E9).

class GarrisonContainModuleData
{
public:
	GarrisonContainModuleData();

private:
	unsigned char m_pad[0xAC];
};

class HordeGarrisonContainModuleData : public GarrisonContainModuleData
{
public:
	HordeGarrisonContainModuleData();

private:
	int m_exitDelay; // +0xAC
	float m_entryOffset[3]; // +0xB0
	float m_entryPosition[3]; // +0xBC
	float m_exitOffset[3]; // +0xC8
};

// ??0HordeGarrisonContainModuleData@@QAE@XZ @0x47A251
HordeGarrisonContainModuleData::HordeGarrisonContainModuleData()
	: GarrisonContainModuleData()
	, m_exitDelay(0)
{
	float *entryOffset;
	float *entryPosition;
	float *exitOffset;

	*(unsigned int *)this = 0x00BF4328;
	entryOffset = m_entryOffset;
	entryOffset[0] = 0.0f;
	entryOffset[1] = 0.0f;
	entryOffset[2] = 0.0f;
	exitOffset = m_exitOffset;
	exitOffset[0] = 0.0f;
	exitOffset[1] = 0.0f;
	exitOffset[2] = 0.0f;
	entryPosition = m_entryPosition;
	entryPosition[0] = 0.0f;
	entryPosition[1] = 0.0f;
	entryPosition[2] = 0.0f;
}
