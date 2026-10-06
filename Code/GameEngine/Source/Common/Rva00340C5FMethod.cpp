// cl: /MD
// ?rva00340C5F@Rva00340C5F@@QAEHXZ, retail 0x00340C5F, 81 bytes.
// Unlock method: goal object via TurretStateMachine at +0x18, null returns
// -2, optional CritterDesync log via globals, then 12B copy from +0x38 to
// +0x20, flag +0x48=1, state +0x4C=3, return 0. Evidence: callees rowed,
// globals 0x00A03745 0x009FEFF0 string 0x008121B4, caller 0x0036808B.
class Object;
struct TurretStateMachine;
struct FprintfTarget;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_pad[0x438];
	unsigned char m_deadFlags;
};

struct TurretStateMachine
{
	char m_pad[0x20 - 4];
	int m_goalObjectID;
	Coord3D m_goalPosition;
	Object *getGoalObject();
};

struct FprintfTarget
{
	char m_pad[4];
};

extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;

class Rva00340C5F
{
public:
	int rva00340C5F();
private:
	char m_00[0x18];
	TurretStateMachine *m_18;
	char m_1C[4];
	Coord3D m_20;
	char m_2C[0x48 - 0x2C];
	bool m_48;
	char m_pad49[3];
	int m_4C;
};

int Rva00340C5F::rva00340C5F()
{
	Object *obj = m_18->getGoalObject();
	if (obj == 0)
		return -2;
	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
		if (log != 0)
			fprintf(log, "CritterDesync: setAdjustDestination(TRUE) 38");
	}
	Coord3D *src = (Coord3D *)((char *)obj + 0x38);
	m_48 = true;
	m_20 = *src;
	m_4C = 3;
	return 0;
}
