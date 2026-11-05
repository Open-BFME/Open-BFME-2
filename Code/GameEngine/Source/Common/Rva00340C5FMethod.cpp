// cl: /MD
// ?onEnter@Rva00340C5F@@QAEHXZ, retail 0x00340C5F, 81 bytes.
// Unlock method: goal object via TurretStateMachine at +0x18, null returns
// -2, optional CritterDesync log via globals, then 12B copy from +0x38 to
// +0x20, flag +0x48=1, state +0x4C=3, return 0. Evidence: callees rowed,
// globals 0x00A03745 0x009FEFF0 string 0x008121B4, caller 0x0036808B.
class Object;
struct TurretStateMachine;
struct FprintfTarget;

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../GameLogic/Object/object.h"

#include "../../Include/GameLogic/Module/TurretStateMachine.h"

struct FprintfTarget
{
	char m_pad[4];
};

extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;

class Rva00340C5F
{
public:
	int onEnter();
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

int Rva00340C5F::onEnter()
{
	Object *obj = m_18->getGoalObject();
	if (obj == 0)
		return -2;
	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, "CritterDesync: setAdjustDestination(TRUE) 38");
	}
	Coord3D *src = (Coord3D *)((char *)obj + 0x38);
	m_48 = true;
	m_20 = *src;
	m_4C = 3;
	return 0;
}
