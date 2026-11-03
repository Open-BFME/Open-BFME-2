// cl: /EHs-
// ?Rva0030EFD5@@YAI_N@Z, retail 0x0030EFD5, 117 bytes.
// Selection capability mask for caller 0x0030F099 (which forwards an
// argument this body never reads). Returns 0 unless
// InGameUI::areSelectedObjectsControllable; otherwise walks TheInGameUI's
// slot 0x124 selection list (STL node data at +8, object at +0xFC) and ORs
// 0x8 for Object 0x002917E8 and 0x200 for Object 0x00291837, stopping at the
// first selected object that contributes either bit.

struct ListNode
{
	ListNode *m_next;
	void *m_prev;
	void *m_data8;
};

struct Sel
{
	ListNode *m_head;
};

class Rva002917E8
{
public:
	bool rva002917E8();	// 0x002917E8
};

#include "../GameLogic/Object/object.h"

struct DataWithObject
{
	char m_pad[0xFC];
	Object *m_obj;
};

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual Sel *slot73();
	bool areSelectedObjectsControllable() const;	// 0x0029C752
};

extern InGameUI *TheInGameUI;

unsigned int Rva0030EFD5(bool alternate)
{
	unsigned int flags = 0;
	if (!TheInGameUI->areSelectedObjectsControllable())
		return 0;
	Sel *sel = TheInGameUI->slot73();
	for (ListNode *listNode = sel->m_head->m_next; listNode != sel->m_head; listNode = listNode->m_next)
	{
		DataWithObject *data = (DataWithObject *)listNode->m_data8;
		if (data == 0)
			continue;
		Object *obj = data->m_obj;
		if (obj == 0)
			continue;
		if (reinterpret_cast<Rva002917E8 *>(obj)->rva002917E8())
			flags |= 0x8;
		if (obj->rva00291837())
			flags |= 0x200;
		if (flags & 0x208)
			break;
	}
	return flags;
}