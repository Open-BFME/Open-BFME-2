// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native53E754..53E783 RET4; the330B button callback328700 passes this=TheControlBar
// and a GameWindow stack argument. The previous free stdcall signature omitted
// that witnessed receiver. Retail ignores this and scans the32 global window/ID
// pairs before calling the canonical GameLogic provider. Name remains neutral.
class Object;
class GameWindow;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#include "../../../../Include/Common/ControlBarInventoryEntry.h"
extern ControlBarInventoryEntry ControlBarInventoryEntries[32];
#include "../../../../Include/GameClient/ControlBar.h"
Object *ControlBar::rva0053E754(GameWindow *window)
{
 int mapped=0;
 for(int i=0;i<32;++i) {
  if(ControlBarInventoryEntries[i].window==window) { mapped=ControlBarInventoryEntries[i].objectID;break; }
 }
 return TheGameLogic->findObjectByID((ObjectID)mapped);
}
