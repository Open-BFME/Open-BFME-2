// cl: /DNDEBUG /MD /EHsc
// ?Rva00486687Find@@YAPAXPAX@Z @0x00486687 108B: free finder scanning the
// +0x244 module list for the cached RebuildHoleExposeDie key; static guard
// plus nameToKey call match the rowed RebuildHoleExposeDie pool-key body,
// virtual slot +0x10 key compare plus null-terminated scan, caller pushes
// an Object and tests the result for null.

#include "../../../../Include/GameLogic/Module/DieModule.h"

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Owner244
{
public:
	char m_pad[0x244];
	DieModule **m_list;
};

void *Rva00486687Find(void *obj)
{
	static NameKeyType key = TheNameKeyGenerator->nameToKey("RebuildHoleExposeDie");
	DieModule **pp = static_cast<Owner244 *>(obj)->m_list;
	for (; *pp != 0; ++pp)
	{
		if ((*pp)->getModuleNameKey() == key)
			return *pp;
	}
	return 0;
}
