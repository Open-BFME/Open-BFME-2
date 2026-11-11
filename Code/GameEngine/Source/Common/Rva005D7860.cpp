// cl: /MD
// ?Rva005D7860Check@@YG_NPAVObject@@@Z @0x005D7860 101B via vtable slot 6 class Rva005D7855 gap between dtor and deleting dtor; callees rowed getControllingPlayer get rva002A7461; floats g_Va00BBB8D8 length_estimate_factor.
class Player;
#include "../GameLogic/Object/object.h"
#include "../../Include/GameLogic/Rva002A7389.h"
#include "../../Include/GameLogic/Rva002A7461.h"
extern float g_Va00BBB8D8;
// length_estimate_factor was the retail address alias (RVA 0x007BB8D4) of the pooled constant 0.25f; the literal is the source.
bool __stdcall Rva005D7860Check(Object *obj)
{
	Player *player = obj->getControllingPlayer();
	char *base = (char *)player;
	int limit = *(int *)(base + 0x94);
	void *holder = base + 0x60;
	float f = (float)((Rva002A7389 *)holder)->get(1);
	int total = ((Rva002A7461 *)holder)->rva002A7461();
	float totalF = (float)total;
	if (limit <= 1000)
		return false;
	float ratio = f / totalF;
	float diff = g_Va00BBB8D8 - ratio;
	if (diff > 0.25f)
		return true;
	return false;
}
