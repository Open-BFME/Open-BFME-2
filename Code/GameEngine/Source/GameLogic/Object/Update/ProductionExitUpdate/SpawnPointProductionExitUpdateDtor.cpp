// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??1SpawnPointProductionExitUpdate@@MAE@XZ, retail 0x004A3B35, 90 bytes.
// Destructor for SpawnPointProductionExitUpdate (ctor rowed at 0x004A3C1B in
// SpawnPointProductionExitUpdateCtor.cpp, vtable 0x0085259C with slot 0 ??_G
// at 0x004A3CCE which calls this body).
//
// Shape follows the ctor TU's MI layout (UpdateModule 0x20 over three bases
// plus trailing SpawnB4 vptr at +0x20): the body reinstalls the four vptrs
// at +0/+0x0C/+0x10/+0x20, destroys the Coord3D array m_spawnPoints[10] at
// +0x2C through the rowed ehvec dtor iterator 0x00629110 (count 0xA, stride
// 0xC, element dtor rowed ??1Coord3D@@QAE@XZ at 0x000B3FD0), then calls the
// pinned UpdateModule base dtor ??1UpdateModule@@UAE@XZ at 0x0024A797.
// /GX for the EH prologue plus the two state stores (and-early, or-late).
// BFME1 donor SpawnPointProductionExitUpdateDestructor.cpp proves the array
// at +0x2C and the 4-vptr teardown; BFME2 revalidate occupier TU pins count
// at +0x28 and occupiers at +0xCC.

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
	virtual ~UpdateModule();
};

class SpawnB4
{
public:
	virtual void spawnAnchor4() {}
};

class Coord3D
{
public:
	~Coord3D();

	float m_x;
	float m_y;
	float m_z;
};

class SpawnPointProductionExitUpdate : public UpdateModule, public SpawnB4
{
protected:
	virtual ~SpawnPointProductionExitUpdate();

private:
	unsigned char m_doorReady24;
	unsigned char m_pad25[3];
	int m_exitDelay28;
	Coord3D m_spawnPoints[10];
	float m_pointFloats[10];
	int m_pointInts[10];
};

SpawnPointProductionExitUpdate::~SpawnPointProductionExitUpdate()
{
}
