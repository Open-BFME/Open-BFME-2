// cl: /DNDEBUG /MD /EHsc
// ?rva0029DE76@Rva0029DE76@@QAE_NPBUCoord3D@@@Z @0x0029DE76 164B
// evidence: unlock caller 0x0029EAFA; rowed PartitionManager::getShroudStatusForPlayer plus Object::rva002907A1 plus AIUpdateInterface::isQuickPathAvailable 0x00264274 path test
enum CellShroudStatus
{
	SHROUD_CLEAR = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PlayerMid
{
public:
	char m_pad[0x54];
	int m_index;
};

class PlayerList
{
public:
	char m_pad[0x10];
	PlayerMid *m_mid;
};
extern PlayerList *ThePlayerList;

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
};
extern PartitionManager *TheShroudManager;

class ObjectAux2
{
public:
	char m_pad[0x11a];
	unsigned char m_11a;
};

class AIUpdateInterface;

// Native call at 0x0029DEFB targets Rva00264274Path.cpp (0x00264274).
// ECX is the same AI update pointer read from Object+0x258; the sole stack
// argument is the destination and AL is the bool result. Retain the
// provider spelling without asserting a semantic name for its path test.
class Rva00264274
{
public:
	bool rva00264274(const Coord3D *destination);
};

class Object
{
public:
	bool rva002907A1();
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

class Rva0029DE76
{
public:
	virtual void dummy00();
	virtual void dummy01();
	virtual void dummy02();
	virtual void dummy03();
	virtual void dummy04();
	virtual void dummy05();
	virtual void dummy06();
	virtual void dummy07();
	virtual void dummy08();
	virtual void dummy09();
	virtual void dummy10();
	virtual void dummy11();
	virtual void dummy12();
	virtual void dummy13();
	virtual void dummy14();
	virtual void dummy15();
	virtual void dummy16();
	virtual void dummy17();
	virtual void dummy18();
	virtual void dummy19();
	virtual void dummy20();
	virtual void dummy21();
	virtual void dummy22();
	virtual void dummy23();
	virtual void dummy24();
	virtual void dummy25();
	virtual void dummy26();
	virtual void dummy27();
	virtual void dummy28();
	virtual void dummy29();
	virtual void dummy30();
	virtual void dummy31();
	virtual void dummy32();
	virtual void dummy33();
	virtual void dummy34();
	virtual void dummy35();
	virtual void dummy36();
	virtual void dummy37();
	virtual void dummy38();
	virtual void dummy39();
	virtual void dummy40();
	virtual void dummy41();
	virtual void dummy42();
	virtual void dummy43();
	virtual void dummy44();
	virtual void dummy45();
	virtual void dummy46();
	virtual void dummy47();
	virtual void dummy48();
	virtual void dummy49();
	virtual void dummy50();
	virtual void dummy51();
	virtual void dummy52();
	virtual void dummy53();
	virtual void dummy54();
	virtual void dummy55();
	virtual void dummy56();
	virtual void dummy57();
	virtual void dummy58();
	virtual void dummy59();
	virtual void dummy60();
	virtual void dummy61();
	virtual void dummy62();
	virtual void dummy63();
	virtual void dummy64();
	virtual void dummy65();
	virtual void dummy66();
	virtual void dummy67();
	virtual void dummy68();
	virtual void dummy69();
	virtual void dummy70();
	virtual void dummy71();
	virtual void dummy72();
	virtual ObjList *getObjList();
	bool rva0029DE76(const Coord3D *pos);
};

bool Rva0029DE76::rva0029DE76(const Coord3D *pos)
{
	int idx = ThePlayerList->m_mid->m_index;
	if (TheShroudManager->getShroudStatusForPlayer(idx, pos) != SHROUD_CLEAR)
		return true;
	ObjList *list = getObjList();
	for (ListNode *node = list->m_head->m_next; node != list->m_head; node = node->m_next)
	{
		Object *v = node->m_obj;
		Object *inner = v ? v->m_fc : (Object *)0;
		AIUpdateInterface *ai = inner ? inner->m_ai : (AIUpdateInterface *)0;
		if (!inner)
			continue;
		if (!inner->rva002907A1())
			continue;
		if ((inner->m_aux->m_11a & 0x80) != 0)
			return true;
		if (!ai)
			continue;
		if (reinterpret_cast<Rva00264274 *>(ai)->rva00264274(pos))
			return true;
	}
	return false;
}
