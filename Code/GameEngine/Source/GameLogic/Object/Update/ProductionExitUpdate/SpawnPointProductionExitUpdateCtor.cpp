// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0SpawnPointProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004A3C1B, 177 bytes. Behavior-side ctor completing the
// SpawnPointProductionExitUpdate file-unit (behavior instance factory
// rowed at 0x24ECEC news 0xF4 with this pinned 2-arg ctor as its sole
// caller; poolkey rowed at 0x4A3BD6; bone methods rowed at 0x4A3CEA,
// 0x4A3F04 and 0x4A3F3B).
//
// Shape follows the MI-virtual installer pattern over the rowed
// UpdateModule base 0x253390 (whose three internal vptrs the opaque call
// installs, then this TU's derived virtuals reinstall): the compiler
// places its +0/+0x0C/+0x10/+0x20 installs ahead of the member array,
// which is built through the rowed ehvec iterator 0x629512 (opaque
// element ctor/dtor keep the frame while the element addresses stay
// DIR32 slots; the element spells the folded Coord3D rows at
// 0x47A6A9/0xB3FD0). An int zero at +0x28 plus a byte zero at +0x24 ride
// the init list around the installs, then a fused zero loop over the
// points plus the float/int tails, then the setWakeFrame tail (m_object
// at +0x08, 0x3FFFFFFF never-wake literal; the loop fences its pushes
// together). /GX for the EH prologue plus the two state stores
// (and-early for the base, byte-mid for the array); the declared-only
// base dtor arms them with no emitted code. Zero new pins (base ctor,
// ehvec iterator and element ctor/dtor resolve via their rows;
// setWakeFrame resolves via the existing IAEX Object-uint pin at
// 0x44DF71). Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

class SpawnB1
{
public:
	virtual void spawnAnchor1() {}
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SpawnB2
{
public:
	virtual void spawnAnchor2() {}
};

class SpawnB3
{
public:
	virtual void spawnAnchor3() {}
protected:
	char m_pad[0x0C];
};

class UpdateModule : public SpawnB1, public SpawnB2, public SpawnB3
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, unsigned int frame);
};

class SpawnB4
{
public:
	virtual void spawnAnchor4() {}
};

class Coord3D
{
public:
	Coord3D();
	~Coord3D();

	float m_x;
	float m_y;
	float m_z;
};

class SpawnPointProductionExitUpdate : public UpdateModule, public SpawnB4
{
public:
	SpawnPointProductionExitUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~SpawnPointProductionExitUpdate();

private:
	unsigned char m_doorReady24;
	unsigned char m_pad25[3];
	int m_exitDelay28;
	Coord3D m_spawnPoints[10];
	float m_pointFloats[10];
	int m_pointInts[10];
};

// ??0SpawnPointProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4A3C1B
SpawnPointProductionExitUpdate::~SpawnPointProductionExitUpdate()
{
}

SpawnPointProductionExitUpdate::SpawnPointProductionExitUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_exitDelay28(0)
	, m_doorReady24(0)
{
	float fzero = 0.0f;
	int *pointCount = &m_pointInts[0];
	float *pointZ = &m_spawnPoints[0].m_z;
	for (int n = 10; n != 0; ++pointCount, pointZ += 3, --n)
	{
		pointZ[-2] = fzero;
		pointZ[-1] = fzero;
		pointZ[0] = fzero;
		*pointCount = 0;
		((float *)pointCount)[-10] = fzero;
	}
	setWakeFrame(m_object, 0x3FFFFFFF);
}
