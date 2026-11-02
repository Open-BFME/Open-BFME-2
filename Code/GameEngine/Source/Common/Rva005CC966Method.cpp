// cl: /O1 /DNDEBUG /MD
// ?rva005CC966@Rva005CC966@@QAEXXZ @0x005CC966 30B evidence: Eva reportEvaEvent pin event pos 0; caller jmp 0x005CCB6B; global TheEva
#include "../../../Libraries/Include/Lib/Coord3D.h"
enum EvaEventID { EVA_EVENT_STUB = 0 };
#include "../../Include/GameClient/Eva.h"
extern Eva *TheEva;
class Rva005CC966
{
public:
	void rva005CC966();
	char m_pad[0x10];
	int m_event;
	Coord3D m_pos;
	unsigned char m_flag;
};
void Rva005CC966::rva005CC966()
{
	const Coord3D *pos = m_flag ? &m_pos : 0;
	TheEva->reportEvaEvent((EvaEventID)m_event, pos, 0);
}
