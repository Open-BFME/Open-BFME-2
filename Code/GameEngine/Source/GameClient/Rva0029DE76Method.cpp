// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0029DE76@Rva0029DE76@@QAE_NPBUCoord3D@@@Z @0x0029DE76 164B
// evidence: unlock caller 0x0029EAFA; rowed PartitionManager::getShroudStatusForPlayer plus Object::isMobile plus AIUpdateInterface::isQuickPathAvailable 0x00264274 path test
enum CellShroudStatus
{
	SHROUD_CLEAR = 0
};

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/Common/Player.h"
#include "../../Include/Common/PlayerList.h"

#include "../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *TheShroudManager;

class ObjectAux2
{
public:
	char m_pad[0x11a];
	unsigned char m_11a;
};

#include "../../Include/GameLogic/Module/AIUpdate.h"

class Object
{
public:
	bool isMobile() const;
	void *m_vtable;
	ObjectAux2 *m_aux;
	char m_pad08[0xfc - 8];
	Object *m_fc;
	char m_pad100[0x258 - 0x100];
	AIUpdateInterface *m_ai;
};

struct ListNode
{
	ListNode *m_next;
	ListNode *m_prev;
	Object *m_obj;
};

struct ObjList
{
	ListNode *m_head;
};

#include "../../Include/Common/Rva0029DE76.h"

bool Rva0029DE76::rva0029DE76(const Coord3D *pos)
{
	int idx = ThePlayerList->m_local->m_playerIndex;
	if (TheShroudManager->getShroudStatusForPlayer(idx, pos) != SHROUD_CLEAR)
		return true;
	ObjList *list = getObjList();
	for (ListNode *node = list->m_head->m_next; node != list->m_head; node = node->m_next)
	{
		Object *object = node->m_obj;
		Object *inner = object ? object->m_fc : (Object *)0;
		AIUpdateInterface *ai = inner ? inner->m_ai : (AIUpdateInterface *)0;
		if (!inner)
			continue;
		if (!inner->isMobile())
			continue;
		if ((inner->m_aux->m_11a & 0x80) != 0)
			return true;
		if (!ai)
			continue;
		if (ai->isQuickPathAvailable(pos))
			return true;
	}
	return false;
}
