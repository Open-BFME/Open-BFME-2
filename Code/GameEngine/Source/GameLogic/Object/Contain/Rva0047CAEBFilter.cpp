// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0047CAEB, 84 bytes, thiscall (ret 8). A null object argument takes
// the base SlaughterHordeContain path. Otherwise it asks the controlling player
// of the object at this-0x18, and when the filter at this-0x1C +0x18C accepts
// the argument it copy-constructs the record at +0x1A4 into the out object.
// The base path tail-calls the base body with (out, obj). Returns out.
class Player;
class Object;
class BfmeObject872Header;

#include "../object.h"

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

#include "../../../../Include/Common/BfmeObject872Header.h"


typedef void (__cdecl *ContainIterateFunc)(Object *, void *);
// SlaughterHordeContain as SiegeEngineContainIterateRiders.cpp also spells it
// (qualified-call virtuals only; slot order not asserted).
class SlaughterHordeContain {
public:
    virtual void rva004635EC(ContainIterateFunc, void *, int);
    virtual BfmeObject872Header *rva00462CE1(BfmeObject872Header *out, int flag);
};

class Rva0047CAEBOwner : public SlaughterHordeContain
{
public:
	BfmeObject872Header *rva0047CAEB(BfmeObject872Header *out, Object *obj);
};

BfmeObject872Header *Rva0047CAEBOwner::rva0047CAEB(BfmeObject872Header *out, Object *obj)
{
	Object *object = *(Object **)((char *)this - 0x18);
	if (obj)
	{
		char *b = *(char **)((char *)this - 0x1C);
		Player *player = object->getControllingPlayer();
		Rva2225E0Filter *filter = (Rva2225E0Filter *)(b + 0x18C);
		if (filter->accepts(obj, player))
		{
			__assume(out != 0);
			new (out) BfmeObject872Header(*(BfmeObject872Header *)(*(char **)((char *)this - 0x1C) + 0x1A4));
			return out;
		}
	}
	SlaughterHordeContain::rva00462CE1(out, (int)obj);
	return out;
}
