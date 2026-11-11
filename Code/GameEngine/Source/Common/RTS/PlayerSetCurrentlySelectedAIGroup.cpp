// cl: /MD /GX-
// ?setCurrentlySelectedAIGroup@Player@@QAEXPAVAIGroup@@@Z @0x002ACC53 80B: Player selection setter.
// Evidence: BFME1 donor PlayerSetCurrentlySelectedAIGroup.cpp plus ZH Player.cpp;
// BFME2 offset +0x730 with 0x1c Squad alloc via pin Squad ctor plus rowed
// rva004D6C29Clear plus rowed Rva0018B8B0 apply(true); prev/next PlayerRva
// same flags; callers include GameLogicDeselectObject; pin reuses Squad name.
// ?addAIGroupToCurrentSelection@Player@@QAEXPAVAIGroup@@@Z @0x002ACCA3 102B: chain via +0x730
// selection plus pin Squad alloc plus rowed AIGroup::getAllIDs plus rowed rva004D6C9C loop;
// prev is setCurrentlySelectedAIGroup same flags; caller 0x0023C991.
enum ScienceType
{
	SCIENCE_INVALID = 0
};

struct BfmePartCDF
{
	ScienceType *m_start;
	ScienceType *m_finish;
};

class Squad
{
public:
	Squad();
private:
	char m_pad[0x1c];
};

#include "../../../Include/Common/Rva004D6C29.h"

class Rva0018B8B0Arg;

enum ObjectID
{
	INVALID_ID = 0
};

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector;
}

#include "../../../Include/GameLogic/AIGroup.h"

class Rva0018B8B0Holder
{
public:
	void apply(Rva0018B8B0Arg *arg, bool clearFirst);
};

class Rva004D6C9C
{
public:
	void rva004D6C9C(ScienceType science);
};

#include "../../../Include/Common/Player.h"

void Player::setCurrentlySelectedAIGroup(AIGroup *group)
{
	if (m_currentSelection == 0)
		m_currentSelection = new Squad;
	((Rva004D6C29 *)m_currentSelection)->rva004D6C29();
	if (group != 0)
		((Rva0018B8B0Holder *)m_currentSelection)->apply((Rva0018B8B0Arg *)group, true);
}

void Player::addAIGroupToCurrentSelection(AIGroup *group)
{
	if (group == 0)
		return;
	if (m_currentSelection == 0)
		m_currentSelection = new Squad;
	const BfmePartCDF *part = (const BfmePartCDF *)&group->getAllIDs();
	int count = part->m_finish - part->m_start;
	for (int i = 0; i < count; ++i)
		((Rva004D6C9C *)m_currentSelection)->rva004D6C9C(part->m_start[i]);
}
