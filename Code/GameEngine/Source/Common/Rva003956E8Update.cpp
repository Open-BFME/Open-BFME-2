// cl: /DNDEBUG /MD /EHsc
// ?loadPostProcess@Rva003956E8@@UAEXXZ, retail 0x003956E8, 32 bytes.
// Module-style update: chain the rowed Rva00497805::loadPostProcess on our
// own this, then when the +0x34 flag is set forward our +0x08 object to the
// pathfinder shim reached through TheAI (0x00DFF0F8) at +0x10 via the rowed
// Pathfinder::RemoveObjectFromPathfindMap. Evidence: direct call 0x00497805 with
// ecx=this; cmpl $0,0x34; mov eax,[0xdff0f8]; push 0x8(esi);
// mov ecx,[eax+0x10]; call 0x002E718A.
class Object;

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *object);
};

#include "../../Include/GameLogic/Module/UpdateModule.h"
class Rva00497805 : public UpdateModule
{
protected:
	void loadPostProcess();
};

#include "../../Include/GameLogic/AI.h"
extern AI *TheAI;

class Rva003956E8 : public Rva00497805
{
public:
	void loadPostProcess();
private:
	char m_pad20[0x34 - 0x20];
	int m_34;
};

void Rva003956E8::loadPostProcess()
{
	// Qualified to the Rva00497805 spelling: retail calls 0x00497805
	// directly, not through the module vtable slot.
	Rva00497805::loadPostProcess();
	if (m_34)
	{
		TheAI->m_pathfinder->RemoveObjectFromPathfindMap(getObject());
	}
}
