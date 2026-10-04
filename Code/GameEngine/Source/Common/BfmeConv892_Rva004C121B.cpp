// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoFCB@BfmeThingFCB@@QAEXPAX@Z
// retail 0x004C121B, 33 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/BfmeConv892.cpp. Recompiled /Os the donor
// body is byte-identical to retail once relocations are masked (unique hit
// on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// Retail 0x0028FCD9: the member-function thunk this body invokes, read off the
// REL32 in this body. Pinned as ?bfmeCallFCB@BfmeSubFCB@@QAEXPAXH@Z.
class BfmeSubFCB
{
public:
	typedef void (BfmeSubFCB::*BfmeCallFCBMember)(void *, int);
	union BfmeCallFCBTarget
	{
		void (*asFunction)();
		BfmeCallFCBMember asMember;
	};
};

extern void j_00043135();

class Player;

class Object
{
public:
	virtual void bfmeVirtual00();
	virtual void bfmeVirtual01();
	virtual void bfmeVirtual02();
	virtual void bfmeVirtual03();
	virtual void bfmeVirtual04();
	virtual void bfmeVirtual05();
	virtual void bfmeVirtual06();
	virtual void bfmeVirtual07();
	virtual void bfmeVirtual08();
	virtual void bfmeVirtual09();
	virtual void *bfmeVirtual10();
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class PlayerList
{
public:
	char m_pad[0xc];
	Player *m_localPlayer;
};

extern void j_0000f763();

extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;

#define TheBfmeGameLogic TheGameLogic
#define ThePlayers ThePlayerList

class BfmeOwnFCB
{
public:
	void bfmeAfterFCB();

	virtual void bfmeAnchorFCB();
	char m_pad0[4];
	Object *m_object;
	char m_pad1[0xd8];
	int m_objectID;
};

class BfmeAfterFCBTarget
{
public:
	void apply(int type, float x, float y, float z);
};

typedef void (BfmeAfterFCBTarget::*BfmeAfterFCBApply)(
	int, float, float, float);

void BfmeOwnFCB::bfmeAfterFCB()
{
	register BfmeOwnFCB &owner = *this;
	Object *found = TheBfmeGameLogic->findObjectByID(owner.m_objectID);
	if (found)
	{
		Object *object = owner.m_object;
		if (object)
		{
			Player *local = ThePlayers->m_localPlayer;
			Player *objectPlayer = object->getControllingPlayer();
			if (local && objectPlayer)
			{
				void *first;
				void *second;
				if (local == objectPlayer)
				{
					first = found->bfmeVirtual10();
					second = object->bfmeVirtual10();
				}
				else
				{
					first = object->bfmeVirtual10();
					second = found->bfmeVirtual10();
				}
				if (first)
				{
					union { void (*asFunction)(); BfmeAfterFCBApply asMember; } thunk;
					thunk.asFunction = j_0000f763;
					(reinterpret_cast<BfmeAfterFCBTarget *>(first)->*thunk.asMember)(
						5, 0.2f, 0.7f, 2.0f);
				}
				if (second)
				{
					union { void (*asFunction)(); BfmeAfterFCBApply asMember; } thunk;
					thunk.asFunction = j_0000f763;
					(reinterpret_cast<BfmeAfterFCBTarget *>(second)->*thunk.asMember)(
						0, 0.2f, 0.7f, 2.0f);
				}
			}
		}
	}
}

struct BfmeThingFCB
{
	void bfmeGoFCB(void *a);
};

void BfmeThingFCB::bfmeGoFCB(void *a)
{
	BfmeSubFCB *s = *(BfmeSubFCB **)((char *)this - 8);
	if (s)
	{
		BfmeSubFCB::BfmeCallFCBTarget callFCB;
		callFCB.asFunction = j_00043135;
		(s->*callFCB.asMember)(a, 0);
		((BfmeOwnFCB *)((char *)this - 0x10))->bfmeAfterFCB();
	}
}
