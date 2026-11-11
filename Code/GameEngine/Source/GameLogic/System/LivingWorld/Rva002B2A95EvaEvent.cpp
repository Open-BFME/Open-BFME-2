// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
#include "Coord2D.h"
#include "Coord3D.h"

#include "../../../../Include/GameLogic/Rva002E0687.h"

class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;

// The coordinate helper 0x002BF5B0, rowed as Rva002BF4F3::rva002BF5B0.
class Vector3;
#include "../../../../Include/Common/Rva002BF4F3.h"

enum EvaEventID { EVA_EVENT_STUB = 0 };
#include "../../../../Include/GameClient/Eva.h"
extern Eva *TheEva;

struct Rva002B2A95Record
{
	unsigned char m_head[0x40];
	int m_event;
	unsigned char m_unknown44[4];
	Coord2D m_position;
};

class Rva002B2A95Callback
{
public:
	void rva002B2A95(const Rva002E0687 *target,
		const Rva002B2A95Record *record, void *unused);
};

// Native 0x002B2A95..0x002B2AFD (RET 12) gates on the verified target
// predicate, reads the event at record+0x40 and XY at +0x48/+0x4C, and
// passes an initially zero-height position through 0x002BF5B0 before EVA.
// The native coordinate helper is 107 bytes ending RET 8: it reads the two
// input floats, writes the three output floats, and returns a bool after
// the already verified 0x002BF4F3 intersection helper. Its pointee names,
// callback receiver, record identity and third argument remain ABI views.
void Rva002B2A95Callback::rva002B2A95(const Rva002E0687 *target,
	const Rva002B2A95Record *record, void *unused)
{
	if (target->rva002E0687())
	{
		Coord2D xy;
		xy.x = record->m_position.x;
		xy.y = record->m_position.y;
		Coord3D position = { xy.x, xy.y, 0.0f };
		((Rva002BF4F3 *)((Rva002D3627Host *)TheLivingWorld))->rva002BF5B0((const Vector3 *)&xy, (Vector3 *)&position);
		TheEva->reportEvaEvent((EvaEventID)record->m_event, &position, 0);
	}
}
