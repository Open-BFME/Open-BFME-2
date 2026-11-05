// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?AddEmotionNuggetTemplate@EmotionSystem@@QAEXPAVMultiplayerColorDefinition@@@Z retail 0x00426580 89B
// Evidence: thiscall ret4 Splits via calls rowed getTooltipName 0x002E4336 pinned findNugget 0x004264F4 rowed releaseBuffer 0x00036410 rowed push_back 0x004DFCB0; vector at this+0xC; caller 0x004DCBCD unblocks 0x004DCAE4; neighbours 0x00426556/0x00426612 share O1 bfmealloc flags
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}

#include <vector>
#include "ascii_string.h"

#include "../../Include/GameNetwork/MultiplayerColorDefinition.h"

class BfmeEmotionName;
class EmotionNugget;
class ModuleData;

enum ObjectID;
#include "../../../Libraries/Include/Lib/BfmeE16.h"
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

// The constructor's view (EmotionSystem.cpp): nugget templates at +0x0C,
// +0x18 and the scary-object ids at +0x24 (RegisterScaryObject 0x004265D9
// appends ObjectIDs there; clear calls the ObjectID erase 0x00532803).
class EmotionSystem : public SubsystemInterface
{
public:
	EmotionSystem();
	EmotionNugget *findNugget(const BfmeEmotionName &name);
	void AddEmotionNuggetTemplate(MultiplayerColorDefinition *def);
	void rva00426572();
private:
	_STL::vector<const ModuleData *> m_vec0C;
	_STL::vector<BfmeE16> m_vec18;
	_STL::vector<ObjectID> m_vec24;
};

// ?rva00426572@EmotionSystem@@QAEXXZ @0x00426572 (14B)
void EmotionSystem::rva00426572()
{
	m_vec24.clear();
}

void EmotionSystem::AddEmotionNuggetTemplate(MultiplayerColorDefinition *def)
{
	if (!def)
		return;
	EmotionNugget *nug = findNugget((const BfmeEmotionName &)def->getTooltipName());
	if (nug)
		return;
	m_vec0C.push_back(*(const ModuleData * const *)&def);
}
