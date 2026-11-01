// cl: /MD
// ?postInit@Rva00598F24@@QAEXXZ @0x00598F24 27B via global store lookup plus add
// Evidence: thiscall void; pushes Player at this+0x2C; rowed rva002A8F24 0x002A8F24 via global TheSkirmishAIManager; rowed addInfoReceiver 0x004DFEC8 with this as ModuleData; caller 0x004EBFBA
class Player;
class ModuleData;
#include "../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
class AIStatCollector
{
public:
	void addInfoReceiver(const ModuleData *data);
};
class Rva00598F24
{
public:
	void postInit();
private:
	char m_pad[0x2C];
	Player *m_player;
};
void Rva00598F24::postInit()
{
	void *store = TheSkirmishAIManager->rva002A8F24(m_player);
	((AIStatCollector *)store)->addInfoReceiver((const ModuleData *)(void *)this);
}
