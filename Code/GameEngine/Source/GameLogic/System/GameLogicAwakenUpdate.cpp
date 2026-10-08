// ?friend_awakenUpdateModule@GameLogic@@QAEXPAVObject@@PAVUpdateModule@@I@Z
// ?friend_awakenUpdateModule@GameLogic@@QAEXPAVObject@@PAVUpdateModule@@I@Z
// cl: /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// ?friend_awakenUpdateModule@GameLogic@@QAEXPAVObject@@PAVUpdateModule@@I@Z, retail 0x0024297F (323 bytes).
// BFME scheduler wake path transferred from BFME1 donor
// GameLogicAwakenUpdate.cpp:228 with BFME2 layout (+4 shift: frame+0x40 objList+0xAC
// phase+0xC8 sleeping+0xF8 current+0x104; UpdateModule frame+0x14 index+0x18 phase+0x1C).
// Evidence: pinned name, sole blocker Object::isInList 0x0028B47C now rowed,
// caller UpdateModule::setWakeFrame 0x0044DF85, TheGameLogic 0x00DFE78C frame+0x40.

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

extern class Debug *theDebug;

#include <vector>
#include <list>

class Object;

// processDestroyList's retail module interface is embedded at +0x0C;
// slot +0x24 returns an interface 0x10 bytes into the UpdateModule.
class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void *getUpdate();
};

class BehaviorModule
{
public:
	char m_pad00[12];
	BehaviorModuleInterface m_behavior;
};

// Retain the established callee identities until these owners are named.
class Rva0023C420
{
public:
	void rva0023C420();
};

class Rva001EB130Holder
{
public:
	void rva001EB130();
};

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *obj);
};

class AI
{
public:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

typedef unsigned int UnsignedInt;
typedef int Int;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object
{
public:
	bool isInList(Object **pListHead) const;
	void removeFromList(Object **head, Object **tail);
	char m_pad00[0x244];
	BehaviorModule **m_modules;
};

class UpdateModule
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual Int getUpdatePhase() const;

private:
	unsigned char m_pad04[0x10]; // +0x04..0x14

public:
	UnsignedInt m_nextCallFrame; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_phaseInLogic; // +0x1C

	UnsignedInt friend_getNextCallFrame() const
	{
		return m_nextCallFrame;
	}

	__forceinline void friend_setNextCallFrame(UnsignedInt frame)
	{
		if (frame > UPDATE_SLEEP_FOREVER)
			frame = UPDATE_SLEEP_FOREVER;
		m_nextCallFrame = frame;
	}

	void friend_setIndexInLogic(Int index)
	{
		m_phaseInLogic = -1;
		m_indexInLogic = index;
	}

	void friend_setIndexInLogic(Int index, Int phase)
	{
		m_phaseInLogic = phase;
		m_indexInLogic = index;
	}
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int, int, int);
};

void _bfme_debugRecordCallsite(int);

#define TheBfmeAwakenDebug (*(BfmeAwakenDebug **)&theDebug)

class GameLogic
{
public:
	void friend_awakenUpdateModule(Object *obj, UpdateModule *u, UnsignedInt when);
	void processDestroyList();
	void removeObjectFromLookupTable(Object *obj);

private:
	unsigned char m_pad00[0x40]; // +0x00..0x40
	UnsignedInt m_frame; // +0x40
	unsigned char m_pad44[0x68]; // +0x44..0xAC
	Object *objList; // +0xAC
	Object *objTail; // +0xB0
	unsigned char m_padB4[0x14]; // +0xB4..0xC8
	_STL::vector<UpdateModule *> phaseUpdates[4]; // +0xC8
	_STL::vector<UpdateModule *> sleeping; // +0xF8
	UpdateModule *current; // +0x104
	_STL::list<Object *> destroy; // +0x108
};
extern GameLogic *TheGameLogic;

void GameLogic::friend_awakenUpdateModule(Object *obj, UpdateModule *u, UnsignedInt when)
{
	UnsignedInt now = TheGameLogic->m_frame;
	if (u == current)
		return;
	if (when == u->friend_getNextCallFrame())
		return;
	if (now > 0 && u->friend_getNextCallFrame() == now && when == now + 1)
		return;

	Int phase = u->m_phaseInLogic;
	Int idx = u->m_indexInLogic;
	if (obj->isInList(&objList))
	{
		if (phase < 0 && when < UPDATE_SLEEP_FOREVER)
		{
			Int newPhase = u->getUpdatePhase();
			if (idx < (Int)sleeping.size() - 1)
			{
				sleeping[idx] = sleeping.back();
				sleeping[idx]->friend_setIndexInLogic(idx);
			}
			sleeping.pop_back();
			Int newIndex = (Int)phaseUpdates[newPhase].size();
			phaseUpdates[newPhase].push_back(u);
			u->friend_setIndexInLogic(newIndex, newPhase);
		}
		u->friend_setNextCallFrame(when);
	}
	else
	{
		if (idx != -1)
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			TheBfmeAwakenDebug->slot6C(0, 0, 0)->slot38("fatal error! sleepy update module index mismatch.\n")->slot4C(1);
			return;
		}
		u->friend_setNextCallFrame(when);
	}
}

// ?processDestroyList@GameLogic@@QAEXXZ, retail 0x002413DF (330 bytes).
// Identity: WorldBuilder 0x00D02920 names this function and pairs its five
// callees; destroyAllObjectsImmediate's verified call at 0x00243B87 agrees.
// WorldBuilder supplies the statement order and two-container scheduler
// algorithm. BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f's GameLogic.cpp
// supplies the object-destruction semantic lead, but its heap scheduler is
// different. The layouts here come from retail accesses, also corroborating
// the existing wake path: module array +0x244, phase vectors +0xC8, sleeping
// vector +0xF8, destroy list +0x108, and update index/phase +0x18/+0x1C.
void GameLogic::processDestroyList()
{
	for (_STL::list<Object *>::iterator it = destroy.begin(); it != destroy.end(); ++it)
	{
		Object *obj = *it;
		for (BehaviorModule **m = obj->m_modules; *m; ++m)
		{
			void *iface = (*m)->m_behavior.getUpdate();
			UpdateModule *u = iface
				? reinterpret_cast<UpdateModule *>(static_cast<char *>(iface) - 0x10)
				: 0;
			if (!u)
				continue;
			Int index = u->m_indexInLogic;
			Int phase = u->m_phaseInLogic;
			if (index == -1)
				continue;
			u->friend_setIndexInLogic(-1);
			if (phase < 0)
			{
				if (index < (Int)sleeping.size() - 1)
				{
					sleeping[index] = sleeping.back();
					sleeping[index]->friend_setIndexInLogic(index);
				}
				sleeping.pop_back();
			}
			else
			{
				if (index < (Int)phaseUpdates[phase].size() - 1)
				{
					phaseUpdates[phase][index] = phaseUpdates[phase].back();
					phaseUpdates[phase][index]->friend_setIndexInLogic(index, phase);
				}
				phaseUpdates[phase].pop_back();
			}
		}
		TheAI->m_pathfinder->RemoveObjectFromPathfindMap(obj);
		obj->removeFromList(&objList, &objTail);
		removeObjectFromLookupTable(obj);
		reinterpret_cast<Rva0023C420 *>(obj)->rva0023C420();
	}
	reinterpret_cast<Rva001EB130Holder *>(&destroy)->rva001EB130();
}
