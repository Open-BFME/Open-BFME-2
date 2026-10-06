// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?createGroup@AI@@QAEPAVAIGroup@@XZ
// Target boundary 0x002FEC4B..0x002FEC97 (76B). Identity: BFME2's
// TEAM_SET_ATTITUDE at 0x003BEE5E loads TheAI and calls this body; the same
// sequence constructs a group before Team::getTeamAsAIGroup. The neighboring
// AI group-destroy body at 0x002FE712 reads the AI group list at +0x14.
// Donor: BFME1 AI::createGroup allocates an AIGroup, appends it, and returns
// it; BFME2's +0x14 list evidence supports the target-specific AI prefix.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class AIGroup
{
public:
	AIGroup();

private:
	char m_body[0x3C];
};

class AI
{
public:
	AIGroup *createGroup();

private:
	char m_pad[0x14];
	_STL::list<AIGroup *> m_groupList;
};

AIGroup *AI::createGroup()
{
	AIGroup *group = new AIGroup;
	m_groupList.push_back(group);
	return group;
}
