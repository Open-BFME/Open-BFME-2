// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Script clause removal on BFME 2's Script layout (clause heads +0x30 or,
// +0x34/+0x38 true/false actions, as ScriptGetUiText.cpp reads them):
//  - Script::deleteOrCondition @0x003B258F (62B): Zero Hour Scripts.cpp's
//    body; OrCondition links through +4.
//  - 0x003B25CD (66B, RET 8): the same unlink-and-delete over the action list
//    the int selects (+0x34 + 4*which), ScriptAction linking through +0x3C.
//    Zero Hour's deleteAction/deleteFalseAction pair takes no index; BFME 2's
//    name for the merged form is not established, so it is address-derived.
// Both end in a global-scope delete: the virtual destructor with flags 0,
// then ::operator delete on the pointer it returns (deleteCondition
// 0x003B26A1 in Scripts.cpp has the same tail).
//  - Script::updateFrom @0x003B3668 (197B): Zero Hour's copy-and-gut of an
//    edited script on the same layout. The three strings at +4/+8/+0xC copy
//    through StringBase<char>::set, the 16-byte record at +0x10 through its
//    rowed copy 0x003B2498, and the scalars in retail's order; field names
//    beyond the clause heads are not established.
#include "ascii_string.h"

typedef int Int;

class Rva003B2498
{
public:
	Rva003B2498 &rva003B2498(const Rva003B2498 &other);
	Rva003B2498 &operator=(const Rva003B2498 &other) { return rva003B2498(other); }
private:
	char m_bytes[0x10];
};

class OrCondition
{
public:
	virtual ~OrCondition();
	OrCondition *getNextOrCondition() const { return m_next; }
	void setNextOrCondition(OrCondition *next) { m_next = next; }
private:
	OrCondition *m_next;	// +0x04
};

#include "../../../Include/GameLogic/ScriptAction.h"

class Script
{
public:
	void deleteOrCondition(OrCondition *pCond);
	void rva003B25CD(Int which, ScriptAction *pAct);
	void updateFrom(Script *pSrc);
private:
	void *m_vtable;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	Rva003B2498 m_10;
	int m_20;
	int m_24;
	unsigned char m_28;
	unsigned char m_29;
	unsigned char m_2A;
	unsigned char m_2B;
	unsigned char m_2C;
	unsigned char m_2D;
	char m_pad2E[2];
	OrCondition *m_condition;	// +0x30
	ScriptAction *m_actions[2];	// +0x34 true, +0x38 false
	char m_pad3C[4];
	unsigned char m_40;
};

void Script::deleteOrCondition(OrCondition *pCond)
{
	OrCondition *pPrev = 0;
	OrCondition *pCur = m_condition;
	while (pCond != pCur) {
		pPrev = pCur;
		pCur = pCur->getNextOrCondition();
	}
	if (pCur == 0) return;
	if (pPrev) {
		pPrev->setNextOrCondition(pCur->getNextOrCondition());
	} else {
		m_condition = pCur->getNextOrCondition();
	}
	pCur->setNextOrCondition(0);
	::delete pCur;
}

void Script::rva003B25CD(Int which, ScriptAction *pAct)
{
	ScriptAction *&head = m_actions[which];
	ScriptAction *pPrev = 0;
	ScriptAction *pCur = head;
	while (pAct != pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
	}
	if (pCur == 0) return;
	if (pPrev) {
		pPrev->setNextAction(pCur->getNext());
	} else {
		head = pCur->getNext();
	}
	pCur->setNextAction(0);
	::delete pCur;
}

void Script::updateFrom(Script *pSrc)
{
	m_04 = pSrc->m_04;
	m_08 = pSrc->m_08;
	m_0C = pSrc->m_0C;
	m_40 = pSrc->m_40;
	m_28 = pSrc->m_28;
	m_2A = pSrc->m_2A;
	m_20 = pSrc->m_20;
	m_10 = pSrc->m_10;
	m_24 = pSrc->m_24;
	m_29 = pSrc->m_29;
	m_2B = pSrc->m_2B;
	m_2C = pSrc->m_2C;
	m_2D = pSrc->m_2D;
	::delete m_condition;
	m_condition = pSrc->m_condition;
	pSrc->m_condition = 0;
	for (Int i = 0; i < 2; ++i) {
		::delete m_actions[i];
		m_actions[i] = pSrc->m_actions[i];
		pSrc->m_actions[i] = 0;
	}
}
