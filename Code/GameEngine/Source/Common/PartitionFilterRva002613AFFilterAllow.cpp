// ?allow@Rva002613AFFilter@@UAE_NPAVObject@@@Z @ 0x002613AF 50B: vtable 0x00C1FDE0 slot 1 and adjacent getPlayerMask rows identify this filter override.
// cl: /DNDEBUG /O1 /arch:SSE /G7 /MD

typedef int Int;
typedef bool Bool;

#include "../../Include/Common/Player.h"
#include "../GameLogic/Object/object.h"
#include "../../Include/GameLogic/PartitionFilter.h"
class Rva002613AFFilter : public Rva000421C8
{
public:
	virtual Bool allow(Object *obj);
	virtual Int getPlayerMask();
private:
	Int m_08;
	Bool m_0C;
};
Bool Rva002613AFFilter::allow(Object *obj)
{
	Player *player = obj->getControllingPlayer();
	Int playerMask = 0;
	if (player)
		playerMask = 1 << player->m_playerIndex;
	return ((m_08 & playerMask) != 0) == m_0C;
}
