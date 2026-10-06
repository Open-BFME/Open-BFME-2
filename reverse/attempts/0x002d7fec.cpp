// ?registerObject@PartitionManager@@QAEXPAVObject@@@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?registerObject@PartitionManager@@QAEXPAVObject@@@Z, retail 0x002D7FEC (512 bytes):
// PartitionManager::registerObject(Object*). Evidence: pinned name, 9 callers
// including Object::friend_notifyOfNewMapBoundary and KeepObjectDie, donor hits
// in BFME1/ZH PartitionManager.cpp (same name, smaller body; BFME2 adds
// relationship/shroud/indicator/color and sorted insert). Callee pins/rows from
// packet; ThePlayerList extern; vtable via new (gate fills DIR32).

class Object;
class Team;
class Player;
class PlayerList;
class BfmeMemberRV;
class Rva00373EC6;

enum Relationship
{
	REL_ENEMY = 0,
	REL_NEUTRAL = 1,
	REL_ALLY = 2
};

class Rva0028E58E
{
public:
	int rva0028E58E();
};

bool __stdcall Rva002D7ACBCheck(int v);
int __cdecl rva002D7BFD(int v);

class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

class BfmeMemberRV
{
public:
	bool bfmeAskRV();
	unsigned char m_pad[0x2EC];
	Team *m_team; // +0x2EC
};

class PlayerList : public BfmeThingRV
{
public:
	Player *getNthPlayer(int i);
};

extern PlayerList *ThePlayerList;

class Player
{
public:
	Relationship getRelationship(const Team *t) const;
	unsigned char m_pad[0x280];
	int m_280; // +0x280
};

class Object
{
public:
	int rva0028E58E();
	bool isNeutralControlled() const;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	int getIndicatorColor() const;
	bool isLocallyControlled() const;
	unsigned char m_pad0[4];
	void *m_4; // +0x4
	unsigned char m_pad8[0x250 - 8];
	void *m_250; // +0x250
	unsigned char m_pad254[0x260 - 0x254];
	void *m_260; // +0x260
	unsigned char m_pad264[0x304 - 0x264];
	Team *m_304; // +0x304
};

class Rva00373EC6
{
public:
	unsigned char m_pad[0x38];
	int m_38; // +0x38
	int m_3C; // +0x3C
};

struct I250Vtbl
{
	virtual void _V00();
	virtual void _V01();
	virtual void _V02();
	virtual void _V03();
	virtual void _V04();
	virtual void _V05();
	virtual void _V06();
	virtual void _V07();
	virtual void _V08();
	virtual void _V09();
	virtual void _V10();
	virtual void _V11();
	virtual void _V12();
	virtual void _V13();
	virtual void _V14();
	virtual void _V15();
	virtual void _V16();
	virtual void _V17();
	virtual void _V18();
	virtual int getV(void *p);
};

class PartitionData
{
public:
	virtual void _V00();
	void *m_obj; // +0x4 (Object*)
	void *m_next; // +0x8
	int m_c; // +0xC
	PartitionData();
};

inline PartitionData::PartitionData()
{
	m_obj = 0;
	m_next = 0;
	m_c = -1;
}

class PartitionManager
{
public:
	void registerObject(Object *object);
private:
	PartitionData *m_list; // +0x0
	unsigned char m_pad4[0x14 - 4];
	PartitionData *m_head14; // +0x14
	PartitionData *m_head18; // +0x18
};

void PartitionManager::registerObject(Object *object)
{
	if (object == 0)
		return;
	int key = ((Rva0028E58E *)object)->rva0028E58E();
	if (!Rva002D7ACBCheck(key))
		return;
	void *t = object->m_4;
	int flags = *(int *)((char *)t + 0x108);
	if ((char)flags < 0)
	{
		if ((flags & 0x20000) != 0)
			goto alloc;
		if ((*((unsigned char *)t + 0x116) & 0x40) != 0)
			goto alloc;
		if ((*((unsigned char *)t + 0x10E) & 4) != 0)
			goto alloc;
		if (object->isNeutralControlled())
			return;
		BfmeMemberRV *rv = ThePlayerList->bfmePickRV();
		if (rv == 0)
			return;
		if ((int)((Player *)rv)->getRelationship(object->m_304) != 1)
			goto alloc;
		return;
	}
	else
	{
		if ((*((unsigned char *)t + 0x10F) & 0x30) != 0)
			return;
	}
alloc:
	PartitionData *mod = new PartitionData;
	object->m_260 = mod;
	mod->m_obj = object;
	Player *ctrl = object->getControllingPlayer();
	Rva00373EC6 *r = object->rva0028F4BC();
	bool useAlt = true;
	Player *alt = 0;
	if (r != 0 && r->m_3C != 0)
	{
		BfmeMemberRV *rv2 = ThePlayerList->bfmePickRV();
		if (rv2 != 0)
		{
			if ((int)((Player *)ctrl)->getRelationship(rv2->m_team) != 2)
			{
				if (((BfmeMemberRV *)ThePlayerList)->bfmeAskRV())
				{
					Player *nth = ThePlayerList->getNthPlayer(r->m_38);
					if (nth != 0)
					{
						alt = nth;
						useAlt = false;
					}
				}
			}
		}
	}
	void *iface = object->m_250;
	if (iface != 0)
	{
		BfmeMemberRV *rv3 = ThePlayerList->bfmePickRV();
		int v = ((I250Vtbl *)iface)->getV(rv3);
		if (v != 0)
		{
			alt = (Player *)(void *)v;
			useAlt = false;
		}
	}
	mod->m_c = rva002D7BFD((!useAlt && alt != 0) ? alt->m_280 : object->getIndicatorColor());
	mod->m_obj = object;
	object->m_260 = mod;
	bool local = object->isLocallyControlled();
	PartitionData **headp;
	if (local)
		headp = &m_head18;
	else
		headp = &m_head14;
	PartitionData *cur = *headp;
	if (cur == 0)
	{
		*headp = mod;
		return;
	}
	PartitionData *prev = 0;
	int curKey = 0;
	while (cur != 0)
	{
		int ck = ((Rva0028E58E *)cur->m_obj)->rva0028E58E();
		if (prev != 0 && curKey >= key)
			break;
		if (ck >= key)
			break;
		if (*(int *)&cur->m_next == 0)
		{
			cur->m_next = mod;
			break;
		}
		prev = cur;
		cur = (PartitionData *)cur->m_next;
		curKey = ck;
	}
	if (prev != 0)
	{
		mod->m_next = prev->m_next;
		prev->m_next = mod;
	}
	else
	{
		mod->m_next = cur;
		*headp = mod;
	}
}
