// cl: /DNDEBUG /MD /EHsc
// ??1SkirmishGameInfo@@UAE@XZ retail 0x0022C516 69B
// Called by the scalar deleting dtor 0x0022C4FA (slot 0 of vtable 0x00BE7480).
// The eight 0x1AC-byte slot records at +0xDC run the vector dtor iterator with
// the rowed element dtor ??1GameSlot@@UAE@XZ (VA 0x006294FD),
// then the rowed base dtor ??1GameInfo@@UAE@XZ 0x00400A7F. No own vtable
// store (novtable), as the retail SEH body shows.
#include "../../Include/GameNetwork/GameInfo.h"


class __declspec(novtable) SkirmishGameInfo : public GameInfo
{
public:
	virtual ~SkirmishGameInfo();
private:
	GameSlot m_slots[8]; // +0xDC
};

SkirmishGameInfo::~SkirmishGameInfo()
{
}
