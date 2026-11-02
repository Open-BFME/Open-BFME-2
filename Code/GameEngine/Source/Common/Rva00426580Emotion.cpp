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

struct Rva005334A4Element;
namespace _STL {
template <> Rva005334A4Element *vector<Rva005334A4Element, allocator<Rva005334A4Element> >::erase(Rva005334A4Element *, Rva005334A4Element *);
}

class EmotionSystem
{
public:
	EmotionNugget *findNugget(const BfmeEmotionName &name);
	void AddEmotionNuggetTemplate(MultiplayerColorDefinition *def);
	void rva00426572();
private:
	char m_pad[0xC];
	_STL::vector<const ModuleData *> m_vec0C;
	char m_pad18[0xC];
	_STL::vector<Rva005334A4Element> m_vec24;
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
