// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// Retail 0x00945FE0 appends the argument to the GenericMultiListClass at
// this+0x34, taking the node only once. The node is null-guarded: a null
// argument returns without touching the list. IDENTITY IS NOT RECOVERED:
// the name keeps its address token.

#include "../WWLib/MultiListObjectClass.h"

class GenericMultiListClass
{
	friend class Rva00945FE0Box;

protected:
	bool Internal_Add_Tail(MultiListObjectClass *obj, bool onlyonce = true);

private:
	unsigned char m_head[24];
};

class Rva00945FE0Box
{
public:
	void addTail(MultiListObjectClass *obj);
	char m_pad[0x34];
	GenericMultiListClass m_list;
};

void Rva00945FE0Box::addTail(MultiListObjectClass *obj)
{
	if (obj)
		m_list.Internal_Add_Tail(obj, true);
}
