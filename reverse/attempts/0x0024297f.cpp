// ?friend_awakenUpdateModule@GameLogic@@QAEXPAVObject@@PAVUpdateModule@@I@Z
// partial score=0.99 date=2026-09-26
// ?friend_awakenUpdateModule@GameLogic@@QAEXPAVObject@@PAVUpdateModule@@I@Z
// partial score=0.99 date=2026-09-26
// cl: /O1 /G7 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// ?friend_awakenUpdateModule@GameLogic@@QAEXPAVObject@@PAVUpdateModule@@I@Z, retail 0x0024297F (323 bytes).
// BFME scheduler wake path transferred from BFME1 donor
// GameLogicAwakenUpdate.cpp:228 with BFME2 layout (+4 shift: frame+0x40 objList+0xAC
// phase+0xC8 sleeping+0xF8 current+0x104; UpdateModule frame+0x14 index+0x18 phase+0x1C).
// Evidence: pinned name, sole blocker Object::isInList 0x0028B47C now rowed,
// caller UpdateModule::setWakeFrame 0x0044DF85, TheGameLogic 0x00DFE78C frame+0x40.

#include <vector>

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

#define TheGameLogic (*(GameLogic **)0x00DFE78C)
#define TheBfmeAwakenDebug (*(BfmeAwakenDebug **)0x00DE0880)

class GameLogic
{
public:
	void friend_awakenUpdateModule(Object *obj, UpdateModule *u, UnsignedInt when);

private:
	unsigned char m_pad00[0x40]; // +0x00..0x40
	UnsignedInt m_frame; // +0x40
	unsigned char m_pad44[0x68]; // +0x44..0xAC
	Object *objList; // +0xAC
	unsigned char m_padB0[0x18]; // +0xB0..0xC8
	_STL::vector<UpdateModule *> phaseUpdates[4]; // +0xC8
	_STL::vector<UpdateModule *> sleeping; // +0xF8
	UpdateModule *current; // +0x104
};

// ?friend_awakenUpdateModule@GameLogic@@QAEXPAVObject@@PAVUpdateModule@@I@Z present-unmatched
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
