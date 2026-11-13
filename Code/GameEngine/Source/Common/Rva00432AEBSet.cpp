// cl: /MD
// ?rva00432AEB@Rva00432AEB@@QAEHH@Z, retail 0x00432AEB, 45 bytes.
// Setter at +0x1F0 returning old value; if the AptTranslator check 0x0043287E (+0x200) passes,
// notifies TheMouse via vtable slot 0x4C with the new value.
// Evidence: callees rowed 0x0043287E, global TheMouse ?TheMouse@@3PAVMouse@@A,
// callers at 0x00320A42 0x00320E5C 0x00320FAF 0x0054CA6B.
class AptTranslator
{
public:
	int rva0043287E();
};
#include "../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
#include "../../Include/GameClient/Rva00432AEB.h"
int Rva00432AEB::rva00432AEB(int v)
{
	int *slot = (int *)((char *)this + 0x1F0);
	int old = *slot;
	*slot = v;
	if ((unsigned char)((AptTranslator *)this)->rva0043287E())
		TheMouse->setCursor((Mouse::MouseCursor)*slot);
	return old;
}
