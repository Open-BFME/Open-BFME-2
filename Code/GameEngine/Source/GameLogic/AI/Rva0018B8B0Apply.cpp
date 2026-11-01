// cl: -DNDEBUG -DWIN32 -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport
// Open-BFME: BFME holder apply body, retail 0x0018B8B0.

#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct BfmePartCDF
{
	void bfmeCopyOneCDF(BfmePartCDF *other);
	int m_0, m_1, m_2;
};

// LINK: 0x0036F710 is rowed as AIGroup::getAllIDs; the argument is that group
// and the returned word is the part pointer, so the call keeps its shape
// through a member-pointer cast.
#include "../../../Include/GameLogic/AIGroup.h"

class Rva0018B8B0Arg;

class Rva0018B8B0Holder
{
public:
	void apply(Rva0018B8B0Arg *arg, bool shouldClearExistingIds);

private:
	int m_vptr;
	_STL::vector<ObjectID> m_ids;
};

// ?apply@Rva0018B8B0Holder@@QAEXPAVRva0018B8B0Arg@@_N@Z
void Rva0018B8B0Holder::apply(Rva0018B8B0Arg *arg, bool shouldClearExistingIds)
{
	if (arg)
	{
		if (shouldClearExistingIds)
			m_ids.clear();

		((BfmePartCDF *)&m_ids)->bfmeCopyOneCDF((((AIGroup *)arg)->*reinterpret_cast<BfmePartCDF *(AIGroup::*)()>(&AIGroup::getAllIDs))());
	}
}
