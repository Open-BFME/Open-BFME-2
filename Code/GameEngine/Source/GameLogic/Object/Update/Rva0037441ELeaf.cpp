// cl: /DNDEBUG /MD
//
// ?hintDetectableWhileUnstealthed@StealthUpdate@@IAEXXZ @0x0037441E 80B: Zero
// Hour's and BFME1's StealthUpdate::hintDetectableWhileUnstealthed (BFME1
// 0x002AC5C0: same callee, same local-player test and drawable opacity store).
// BehaviorModule method: m_object at +8 null-checked, module data +0x10
// tested via rowed ?test@Rva00331682Holder 0x00331682 at Object+0x94,
// controlling player via rowed ?getControllingPlayer@Object 0x0028AFA9
// compared to ThePlayerList+0x10, drawable via rowed ?getDrawable@Thing
// 0x005508E2 null-checked, then float g_Va00BBB8D8 to Drawable+0x358.
// Evidence: packet callees all rowed, prev/next Rva003743CF/Rva00373EC6
// show BehaviorModule layout +4/+8, ThePlayerList and g_Va00BBB8D8 names
// from packet externs in use.
#include "../../../../Include/GameLogic/Module/Rva00331682Holder.h"

class Player;
#include "../../../../Include/GameClient/Drawable.h"

#include "../../../Common/Thing/thing.h"

#include "../../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;
extern float g_Va00BBB8D8;

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad[0x94];
	Rva00331682Holder m_holder;
};

class Rva0037441EModuleData
{
public:
	unsigned char m_pad[0x10];
	int m_vals[4];
};

#include "../../../../Include/GameLogic/Module/StealthUpdate.h"

void StealthUpdate::hintDetectableWhileUnstealthed()
{
	Object *object = m_object;
	if (object == 0)
		return;
	const void *other = (const void *)((const char *)m_moduleData + 0x10);
	if (!object->m_holder.test(other))
		return;
	Player *expected = ThePlayerList->m_local;
	Player *actual = object->getControllingPlayer();
	if (actual != expected)
		return;
	Drawable *drawable = ((Thing *)object)->getDrawable();
	if (drawable == 0)
		return;
	drawable->m_secondMaterialPassOpacity = g_Va00BBB8D8;
}
