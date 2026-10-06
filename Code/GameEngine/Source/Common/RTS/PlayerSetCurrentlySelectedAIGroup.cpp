// cl: /MD /GX-
// ?setCurrentlySelectedAIGroup@Player@@QAEXPAVAIGroup@@@Z @0x002ACC53 80B: Player selection setter.
// Evidence: BFME1 donor PlayerSetCurrentlySelectedAIGroup.cpp plus ZH Player.cpp;
// BFME2 offset +0x730 with 0x1c Squad alloc via pin Squad ctor plus rowed
// rva004D6C29Clear plus rowed Rva0018B8B0 apply(true); prev/next PlayerRva
// same flags; callers include GameLogicDeselectObject; pin reuses Squad name.
// ?rva002ACCA3@Player@@QAEXPAVAIGroup@@@Z @0x002ACCA3 102B: chain via +0x730
// selection plus pin Squad alloc plus pin getPart plus rowed rva004D6C9C loop;
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

class Rva004D6C29
{
public:
	void rva004D6C29();
};

class Rva0018B8B0Arg
{
public:
	BfmePartCDF *getPart();
};

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

class AIGroup;
class Player
{
public:
	void setCurrentlySelectedAIGroup(AIGroup *group);
	void rva002ACCA3(AIGroup *group);
private:
	char m_pad[0x730];
	Squad *m_currentSelection;
};

void Player::setCurrentlySelectedAIGroup(AIGroup *group)
{
	if (m_currentSelection == 0)
		m_currentSelection = new Squad;
	((Rva004D6C29 *)m_currentSelection)->rva004D6C29();
	if (group != 0)
		((Rva0018B8B0Holder *)m_currentSelection)->apply((Rva0018B8B0Arg *)group, true);
}

void Player::rva002ACCA3(AIGroup *group)
{
	if (group == 0)
		return;
	if (m_currentSelection == 0)
		m_currentSelection = new Squad;
	BfmePartCDF *part = ((Rva0018B8B0Arg *)group)->getPart();
	int count = part->m_finish - part->m_start;
	for (int i = 0; i < count; ++i)
		((Rva004D6C9C *)m_currentSelection)->rva004D6C9C(part->m_start[i]);
}
